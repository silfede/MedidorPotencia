/*
 * modulo_PwrConf.c
 *
 *  Created on: 15 ago. 2017
 *      Author: federicosilva
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "modulo_PwrConf.h"



/* DMA Control Table */
#ifdef ewarm
#pragma data_alignment=256
#else
#pragma DATA_ALIGN(controlTable, 256)
#endif
uint8_t controlTable[256];

/* Local variables */
// i indica cuantas iteraciones necesitó del ping-pong
static uint16_t i;
// Número de períodos
static uint16_t N;

/*------------------------------------------------------------------------------*/


void configADC()
{
    // Inicializo el módulo ADC
    MAP_ADC14_enableModule();
    // Seteo el MCLK como reloj
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_1,0);

    // Configuro entradas para usar con periférico
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
            GPIO_PIN5 | GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

    // Configuro conversión secuencial de memoria 0 y 1, en bucle
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM23, true);

    // Asigno las memorias a los canales del ADC, referencia AVCC
    MAP_ADC14_configureConversionMemory(ADC_MEM0,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM1,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM2,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM3,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM4,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM5,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM6,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM7,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM8,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM9,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM10,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM11,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM12,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM13,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM14,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM15,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM16,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM17,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM18,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM19,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM20,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM21,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM22,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM23,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);

    MAP_ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
    // Cambia entre canales automáticamente
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

/*------------------------------------------------------------------------------*/

void configDMA()
{
    i = 0;
    // Habilitación del módulo
   DMA_enableModule();
   DMA_setControlBase(controlTable);


   DMA_disableChannelAttribute(DMA_CH7_ADC14,
                                 UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                 UDMA_ATTR_HIGH_PRIORITY |
                                 UDMA_ATTR_REQMASK);
   //MAP_DMA_enableChannelAttribute(DMA_CH7_ADC14, UDMA_ATTR_USEBURST);


   MAP_DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14,
       UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_32);
   MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
       UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
       data, DMA_BLOCK_SIZE);

   MAP_DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC14,
       UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_32);
   MAP_DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
       UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
       (void*) &data[DMA_BLOCK_SIZE], DMA_BLOCK_SIZE);

   MAP_DMA_assignInterrupt(DMA_INT1, 7);
   MAP_DMA_assignChannel(DMA_CH7_ADC14);
   MAP_Interrupt_enableInterrupt(INT_DMA_INT1);
   MAP_DMA_clearInterruptFlag(7);
}

void DMA_INT1_IRQHandler(void)
{
    ++i;
    /* Switch between primary and alternate bufferes with DMA's PingPong mode */
    if (DMA_getChannelAttribute(7) & UDMA_ATTR_ALTSELECT)
    {
        DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14,
            UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_32);
        DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
            UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
            (void*) &data[(i+1)*DMA_BLOCK_SIZE], DMA_BLOCK_SIZE);
    }
    else
    {
        DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC14,
            UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_32);
        DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
            UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
            (void*) &data[(i+1)*DMA_BLOCK_SIZE], DMA_BLOCK_SIZE);
    }
}

/*------------------------------------------------------------------------------*/

const Timer_A_ContinuousModeConfig continuousModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,           // SMCLK Clock Source (24MHz)
        TIMER_A_CLOCKSOURCE_DIVIDER_2,       // SMCLK/2 = 12MHz
        TIMER_A_TAIE_INTERRUPT_DISABLE,      // Disable Overflow ISR
        TIMER_A_DO_CLEAR                     // Clear Counter
};

void configTimer()
{
    MAP_Timer_A_configureContinuousMode(TIMER_A3_BASE, &continuousModeConfig);
}

/*------------------------------------------------------------------------------*/

void configToggle()
{
    N = 0;
    // Configuro 4.6 como entrada
    MAP_GPIO_setAsInputPin(GPIO_PORT_P4, GPIO_PIN6);

    // Limpio bandera de interrupciones y activo las del puerto
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P4, GPIO_PIN6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P4, GPIO_PIN6);

    // Seteo que interrumpta por flanco de subida
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P4,GPIO_PIN6,GPIO_LOW_TO_HIGH_TRANSITION);

    // Activo las interrupciones generales del puerto
    MAP_Interrupt_enableInterrupt(INT_PORT4);
}

/*
 * ISR del puerto donde se recibe la señal cuadrada.
 */
void PORT4_IRQHandler(void)
{
    if(N==0)
    {
        // Enciendo el ADC
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
        // Habilito el DMA
        MAP_DMA_enableChannel(7);
        // Inicio cuenta de períodos
        MAP_Timer_A_startCounter(TIMER_A3_BASE, TIMER_A_CONTINUOUS_MODE);
    }
    else if (N==10)
    {
        // Fuerzo a deshabilitar al DMA
        MAP_DMA_disableModule();
        // Fuerzo a deshabilitar al ADC
        ADC14->CTL0 &= ~(ADC14_CTL0_ENC | ADC14_CTL0_CONSEQ_0);
        // Guardo el tiempo que toma el sampleo
        sampling_time = MAP_Timer_A_getCounterValue(TIMER_A3_BASE);
    }
    else if (N==100)
    {
        frequency_period = MAP_Timer_A_getCounterValue(TIMER_A3_BASE);
        MAP_Timer_A_stopTimer(TIMER_A3_BASE);
        // Deshabilito interrupciones del puerto toggle
        MAP_Interrupt_disableInterrupt(INT_PORT4);
    }
    P4->IFG &= ~BIT6;
    ++N;
}
/*------------------------------------------------------------------------------*/
