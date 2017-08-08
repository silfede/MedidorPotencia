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

static uint16_t N;

volatile uint16_t N_ADC[128];
static uint8_t index=0;

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    /****************************************************************************
     ************************CONFIGURACIÓN DE RELOJES****************************
     ****************************************************************************/

    // Seteo el DCO a máxima frecuencia 64 MHz
    /*
     * Este comando no anda para la versión de la placa de Fede (pre-release).
    MAP_CS_setDCOFrequency(64000000);
     */
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
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);

    // Seteo la referencia de voltaje en 2,5 V
    MAP_REF_A_setReferenceVoltage(REF_A_VREF2_5V);
    MAP_REF_A_enableReferenceVoltage();

   /* // Habilito el módulo ADC y seteo el clock del mismo a MCLK
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,0);*/

    // Configuración módulo ADC
    ADC14->CTL0 = ADC14_CTL0_ON |       // Enciendo el módulo
            ADC14_CTL0_SSEL__MCLK |     // Selecciono MCLK como source
            ADC14_CTL0_MSC |            // Conversión automática
            ADC14_CTL0_SHT0__4 |        // 4 períodos de S&H (mínimo)
            ADC14_CTL0_SHP |
            ADC14_CTL0_CONSEQ_3;        // Repetir secuencia de canales
    ADC14->CTL1 = ADC14_CTL1_RES__12BIT;

    ADC14->MCTL[0] = ADC14_MCTLN_INCH_0 | ADC14_MCTLN_VRSEL_14;  // ref+=Vref, channel = A0
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_1 | ADC14_MCTLN_VRSEL_14 |// ref+=Vref, channel = A1
            ADC14_MCTLN_EOS;                                    // End of sequence


    ADC14->IER0 = ADC14_IER0_IE1;           // Habilita interrupción A1



    // Habilito interrupciones generales
    MAP_Interrupt_enableMaster();

    // habilito conversión del ADC
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;

    while(1)
    {
        
    }
}

/*
 * ISR del puerto 1
 * (Notar que es del puerto 1 en su totalidad, de ahí que debe verificar
 * que efectivamente provenga del P1.5).
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
