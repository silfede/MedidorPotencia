/*
 * Medidor de Potencia
 *
 * Testeo de interrupciones desde GPIO y velocidad del ADC
 *
 * Se generan interrupciones en cada flanco de GPIO. Dentro de la interrupción
 * se activa el ADC en modo continuo, dos canales. En la interrupción se lleva
 * la cuenta de muestras a las que llega.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST          P1.5 | <-- GPIO req
 *            |                  |
 *            |             P5.5 | <-- ADC / A0
 *            |             P5.4 | <-- ADC / A1
 *            |                  |
 *            |                  |
 * Author: EAEU
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

static uint32_t N=0;

volatile uint16_t N_ADC[128];
static uint8_t index=0;

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    /****************************************************************************
     ************************CONFIGURACIÓN DE RELOJES****************************
     ****************************************************************************/

    // Seteo el DCO a máxima frecuencia 48 MHz

    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);

    // Asigno el DCO como Master Clock
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    /****************************************************************************/


    /****************************************************************************
     ************************CONFIGURACIÓN DE GPIO*******************************
     ****************************************************************************/

    // Configuro 1.5 como entrada
    MAP_GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN5);

    // Limpio bandera de interrupciones y activo las del puerto 1.5
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN5);

    // Seteo que interrumpta por flanco de subida
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P1,GPIO_PIN5,GPIO_LOW_TO_HIGH_TRANSITION);

    // Activo las interrupciones generales del puerto 1
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    /****************************************************************************/

    /****************************************************************************
     ************************CONFIGURACIÓN DE ADC14******************************
     ****************************************************************************/

    // Inicializo el módulo ADC
    MAP_ADC14_enableModule();
    // Seteo el MCLK como reloj
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
            0);

    // Configuro entradas para usar con periférico
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN5 | GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

    // Configuro conversión secuencial de memoria 0 y 1, en bucle
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);

    // Asigno las memorias a los canales del ADC, referencia AVCC
    MAP_ADC14_configureConversionMemory(ADC_MEM0,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM1,
            ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A2, false);

    // Cambia entre canales automáticamente
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    // Habilito interrupciones del puerto (son con respecto a la memoria)
    MAP_ADC14_enableInterrupt(ADC_INT1);

    // Habilito interrupciones del ADC
    MAP_Interrupt_enableInterrupt(INT_ADC14);
    
    // Habilito interrupciones generales
    MAP_Interrupt_enableMaster();

    // Inicio conversión
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;

    while(1)
    {
        
    }
}

/*
 * ISR del puerto 1
 * (Notar que es del puerto 1 en su totalidad, de ahí que debe verificar
 * que efectivamente provenga del P1.5).
 * A la hora de probar otra cosa, aterrar esta pata
 */
void PORT1_IRQHandler(void)
{
    if (P1IFG & BIT5)
    {
        N_ADC[index] = N;
        index = (index + 1) & 0x7F;
        N=0;
    }
    P1IFG &= ~BIT5;
}


void ADC14_IRQHandler(void)
{
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        N = N+1;
        // Limpio interrupciones
        ADC14->CLRIFGR0 |= ADC14_IFGR0_IFG1 | ADC14_IFGR0_IFG0;
    }

}
