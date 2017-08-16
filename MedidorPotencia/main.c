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

#define SAMPLE_LENGTH 10

/* DMA Control Table */
#ifdef ewarm
#pragma data_alignment=256
#else
#pragma DATA_ALIGN(controlTable, 256)
#endif
uint8_t controlTable[256];

static uint32_t N=0;
uint16_t i=0;

volatile uint16_t N_ADC[128];
static uint8_t index=0;


uint32_t data[1000];

static volatile uint32_t mclk;
int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();


    memset(controlTable, 0x00, 1024);

    /****************************************************************************
     ************************CONFIGURACIÓN DE RELOJES****************************
     ****************************************************************************/
    // Habilito FPU
    MAP_FPU_enableModule();

    /*
     * El seteo de la frecuencia la realizo en el archivo system_msp432p401r.c
     */
    mclk = CS_getMCLK();

    /****************************************************************************
     ************************CONFIGURACIÓN DE GPIO*******************************
     ****************************************************************************/

    // Configuro 1.5 como entrada
    MAP_GPIO_setAsInputPin(GPIO_PORT_P3, GPIO_PIN6);
    //MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);


    // Limpio bandera de interrupciones y activo las del puerto 1.5
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P3, GPIO_PIN6);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P3, GPIO_PIN6);

    // Seteo que interrumpta por flanco de subida
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P3,GPIO_PIN6,GPIO_LOW_TO_HIGH_TRANSITION);

    // Activo las interrupciones generales del puerto 1
    MAP_Interrupt_enableInterrupt(INT_PORT3);
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
    MAP_ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM25, true);


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

    ADC14_setPowerMode(ADC_UNRESTRICTED_POWER_MODE);
    // Cambia entre canales automáticamente
    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    /*MAP_ADC14_enableInterrupt(ADC_INT0);
    MAP_ADC14_enableInterrupt(ADC_INT1);


    // Enabling Interrupts
    MAP_Interrupt_enableInterrupt(INT_ADC14);*/
    /****************************************************************************/

    /****************************************************************************
     **************************CONFIGURACIÓN DE DMA******************************
     ****************************************************************************/
    DMA_enableModule();
    DMA_setControlBase(controlTable);


    DMA_disableChannelAttribute(DMA_CH7_ADC14,
                                  UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                  UDMA_ATTR_HIGH_PRIORITY |
                                  UDMA_ATTR_REQMASK);
    MAP_DMA_enableChannelAttribute(DMA_CH7_ADC14, UDMA_ATTR_USEBURST);


    MAP_DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
        UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
        data, 26);

    MAP_DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC14,
        UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_1);
    MAP_DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
        UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
        (void*) &data[26], 26);




    MAP_DMA_assignInterrupt(DMA_INT1, 7);
    MAP_DMA_assignChannel(DMA_CH7_ADC14);
    MAP_Interrupt_enableInterrupt(INT_DMA_INT1);
    MAP_DMA_clearInterruptFlag(7);



    // Habilito interrupciones generales
    MAP_Interrupt_enableMaster();

//    MAP_DMA_enableChannel(7);
//    // Inicio conversión
//    MAP_ADC14_enableConversion();
//    MAP_ADC14_toggleConversionTrigger();


    while(1)
    {
        
    }
}

/*
 * ISR del puerto 1
 * (Notar que es del puerto 1 en su totalidad, de ahí que debe verificar
 * que efectivamente provenga del P1.4).
 * A la hora de probar otra cosa, aterrar esta pata
 */
void PORT3_IRQHandler(void)
{
    if (N==0)
    {
        MAP_DMA_enableChannel(7);
        // Inicio conversión
        MAP_ADC14_enableConversion();
        MAP_ADC14_toggleConversionTrigger();
    }
    else if (N==2)
    {
        MAP_ADC14_disableModule();
        MAP_DMA_disableModule();
        ++N;
    }
    P1IFG &= ~BIT4;
    ++N;
}


/*void ADC14_IRQHandler(void)
{
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    MAP_ADC14_toggleConversionTrigger();
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        N = N+1;
        // Limpio interrupciones
    }

}*/

void DMA_INT1_IRQHandler(void)
{
    ++i;
    /* Switch between primary and alternate bufferes with DMA's PingPong mode */
    if (DMA_getChannelAttribute(7) & UDMA_ATTR_ALTSELECT)
    {
        DMA_setChannelControl(UDMA_PRI_SELECT | DMA_CH7_ADC14,
            UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_1);
        DMA_setChannelTransfer(UDMA_PRI_SELECT | DMA_CH7_ADC14,
            UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
            (void*) &data[(i+1)*26], 26);
    }
    else
    {
        DMA_setChannelControl(UDMA_ALT_SELECT | DMA_CH7_ADC14,
            UDMA_SIZE_32 | UDMA_SRC_INC_32 | UDMA_DST_INC_32 | UDMA_ARB_1);
        DMA_setChannelTransfer(UDMA_ALT_SELECT | DMA_CH7_ADC14,
            UDMA_MODE_PINGPONG, (void*) &ADC14->MEM[0],
            (void*) &data[(i+1)*26], 26);
    }
    //DMA_enableChannel(7);
}
