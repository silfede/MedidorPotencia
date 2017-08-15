/*
 * modulo_PwrConf.c
 *
 *  Created on: 15 ago. 2017
 *      Author: federicosilva
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "modulo_PwrConf.h"
#include "dmaTasks.h"


/* DMA Control Table */
#if defined(__TI_COMPILER_VERSION__)
#pragma DATA_ALIGN(MSP_EXP432P401RLP_DMAControlTable, 256)
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma data_alignment=256
#elif defined(__GNUC__)
__attribute__ ((aligned (256)))
#elif defined(__CC_ARM)
__align(256)
#endif
static DMA_ControlTable MSP_EXP432P401RLP_DMAControlTable[16];

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
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM31, true);

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
    MAP_ADC14_configureConversionMemory(ADC_MEM24,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM25,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM26,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM27,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM28,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM29,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM30,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A0, false);
    MAP_ADC14_configureConversionMemory(ADC_MEM31,ADC_VREFPOS_AVCC_VREFNEG_VSS,
            ADC_INPUT_A1, false);

    MAP_ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
    // Cambia entre canales automáticamente
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}



void configDMA()
{
    // Habilitación del módulo
    MAP_DMA_enableModule();

    MAP_DMA_setControlBase(MSP_EXP432P401RLP_DMAControlTable);

    // Seteo de DMA + ADC. Habilita modo ráfaga
    MAP_DMA_disableChannelAttribute(DMA_CH7_ADC14,
                                     UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                     UDMA_ATTR_HIGH_PRIORITY |
                                     UDMA_ATTR_REQMASK);
    MAP_DMA_enableChannelAttribute(DMA_CH7_ADC14, UDMA_ATTR_USEBURST);

    // Configuro modo ScatterGather, con destino en data
    MAP_DMA_setChannelScatterGather(DMA_CH7_ADC14, 86, (void*)&altTaskList[0], false);

    MAP_DMA_assignChannel(DMA_CH7_ADC14);
}


const Timer_A_ContinuousModeConfig continuousModeConfig =
{
        TIMER_A_CLOCKSOURCE_SMCLK,           // SMCLK Clock Source (24MHz)
        TIMER_A_CLOCKSOURCE_DIVIDER_2,      // ACLK/1 = 32.768khz
        TIMER_A_TAIE_INTERRUPT_DISABLE,      // Enable Overflow ISR
        TIMER_A_DO_CLEAR                    // Clear Counter
};

void configTimer()
{
    MAP_Timer_A_configureContinuousMode(TIMER_A3_BASE, &continuousModeConfig);
}


void configToggle()
{
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
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;
        MAP_DMA_enableChannel(7);
    }
    else if (N==5)
    {
        ADC14->CTL0 &= ~(ADC14_CTL0_ENC | ADC14_CTL0_CONSEQ_0);
        MAP_DMA_disableModule();
        MAP_Interrupt_disableInterrupt(INT_PORT4);
        P2->OUT &= ~BIT3;
        P2->OUT &= ~BIT3;
    }
    P4->IFG &= ~BIT6;
    ++N;
}
