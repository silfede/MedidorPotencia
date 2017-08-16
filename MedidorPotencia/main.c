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

#include "modulo_PwrConf.h"



uint32_t data[2752];
uint16_t N=0;




// Índice para indicar la secuencia del DMA
static uint16_t i=0;
static uint16_t j=0;


static volatile uint32_t mclk;
int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

    memset(data, 0x00, 2752);


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

    configToggle();
    /****************************************************************************/

    /****************************************************************************
     ************************CONFIGURACIÓN DE ADC14******************************
     ****************************************************************************/

    configADC();

    /*MAP_ADC14_enableInterrupt(ADC_INT0);
    MAP_ADC14_enableInterrupt(ADC_INT1);


    // Enabling Interrupts
    MAP_Interrupt_enableInterrupt(INT_ADC14);*/
    /****************************************************************************/

    /****************************************************************************
     **************************CONFIGURACIÓN DE DMA******************************
     ****************************************************************************/
   configDMA();


    MAP_Interrupt_enableMaster();

    while(1)
    {
        
    }
}




void ADC14_IRQHandler(void)
{
    if(ADC14->IFGR0 & ADC14_IFGR0_IFG1)
    {
        ++j;

        // Limpio interrupciones
        ADC14->CLRIFGR0 |= ADC14_IFGR0_IFG0 | ADC14_IFGR0_IFG0;

    }

}
