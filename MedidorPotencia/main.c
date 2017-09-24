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
 *          --|RST          P4.6 | <-- GPIO req
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

#include "modulo_PwrProc.h"


#define TEST_FREQ 1

volatile int i;

static volatile uint32_t mclk,smclk;
int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Deshabilitar las interrupciones antes de configurar todo */
    MAP_Interrupt_disableMaster();

    // Habilito FPU
    MAP_FPU_enableModule();

    /*
     * El seteo de la frecuencia la realizo en el archivo system_msp432p401r.c
     */
    mclk = CS_getMCLK();
    smclk = CS_getSMCLK();


    MAP_Interrupt_enableMaster();
    read_freq();
    while(1)
    {
        
#if TEST_FREQ
    // Si hacemos el test de frecuencia

#else
        read_pwr();
#endif

    }
}
