/*
 * Medidor de Potencia
 *
 * Testeo de interrupciones desde GPIO y velocidad del ADC. Se suma ahora el uso del DMA.
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

#define SAMPLE_LENGTH 512

/* DMA Control Table */
#ifdef ewarm
#pragma data_alignment=256
#else
#pragma DATA_ALIGN(controlTable, 256)
#endif
uint8_t controlTable[256];

static uint32_t N=0;

volatile uint16_t N_ADC[128];
static uint8_t index=0;

uint16_t voltaje[SAMPLE_LENGTH];
uint16_t corriente[SAMPLE_LENGTH];
static volatile uint32_t mclk;
int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    memset(voltaje, 0x00, SAMPLE_LENGTH);
    memset(corriente, 0x00, SAMPLE_LENGTH);
    memset(controlTable, 0x00, 1024);

    /****************************************************************************
     ************************CONFIGURACIÓN DE RELOJES****************************
     ****************************************************************************/
    MAP_FPU_enableModule();
    // Seteo el DCO a máxima frecuencia 48 MHz

    //MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    //MAP_CS_setDCOFrequency(48000000);

    // Asigno el DCO como Master Clock
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    /****************************************************************************/
    mclk = CS_getMCLK();

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
    //MAP_Interrupt_enableInterrupt(INT_PORT1);
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
    MAP_ADC14_configureConversionMemory(ADC_MEM0,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM1,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);

    // Cambia entre canales automáticamente
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /****************************************************************************/

    /****************************************************************************
     **************************CONFIGURACIÓN DE DMA******************************
     ****************************************************************************/
    MAP_DMA_enableModule();
    MAP_DMA_setControlBase(controlTable);

    MAP_DMA_assignChannel(DMA_CH7_ADC14);

    MAP_DMA_disableChannelAttribute(DMA_CH7_ADC14,
                                  UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                  UDMA_ATTR_HIGH_PRIORITY |
                                  UDMA_ATTR_REQMASK);
    MAP_DMA_enableChannelAttribute(DMA_CH7_ADC14, UDMA_ATTR_USEBURST);


    MAP_DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
        UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
        voltaje, SAMPLE_LENGTH);

    MAP_DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
        UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[1],
        corriente, SAMPLE_LENGTH);

    

    MAP_DMA_assignInterrupt(DMA_INT1, 7);
    MAP_Interrupt_enableInterrupt(INT_DMA_INT1);

    MAP_DMA_enableChannel(7);


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


/*void ADC14_IRQHandler(void)
{
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        N = N+1;
        // Limpio interrupciones
        ADC14->CLRIFGR0 |= ADC14_IFGR0_IFG1 | ADC14_IFGR0_IFG0;
    }

}*/

void DMA_INT1_IRQHandler(void)
{
    N=N+1;
    MAP_DMA_clearInterruptFlag(7);
}
