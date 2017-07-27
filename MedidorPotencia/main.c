/*
 * Medidor de Potencia
 *
 * Testeo de interrupciones desde GPIO
 *
 * Se generan interrupciones en cada flanco de GPIO. Dentro de la interrupción
 * se niega la salida Output, produciendo entonces una señal de la mitad de
 * frecuencia.
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST          P1.5 | <-- GPIO req
 *            |             P1.6 | --> Output
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: EAEU
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

static volatile uint32_t mclk;

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    // Seteo el DCO a máxima frecuencia 64 MHz
    /*
     * Este comando no anda para la versión de la placa de Fede (pre-release).
    MAP_CS_setDCOFrequency(64000000);
     */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);





    // Asigno el DCO como Master Clock
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

    mclk = MAP_CS_getMCLK();

    // Seteo 1.2 como salida
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN6);

    // Configuro 1.1 como entrada con resistencia de pull-up
    MAP_GPIO_setAsInputPin(GPIO_PORT_P1, GPIO_PIN5);

    // Limpio bandera de interrupciones y activo las del puerto 1.5
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN5);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN5);

    // Seteo que interrumpta por flanco de subida
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P1,GPIO_PIN5,GPIO_LOW_TO_HIGH_TRANSITION);

    // Activo las interrupciones generales del puerto 1
    MAP_Interrupt_enableInterrupt(INT_PORT1);



    // Habilito interrupciones
    MAP_Interrupt_enableMaster();


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
    /*
     * Este código es muy lento. Con f_in=40k no le da para detectar varios flancos.
     * Workaround: escribir regustros directamente, no funciones de librería.

    uint32_t status;

    // Obtengo todo el vector estado de las interrupciones del puerto 1
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    // Limipio la que me llama
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    // Verifico que provenga del pin 5 efectivamente (trivial en este caso)
    if(status & GPIO_PIN5)
    {
        // Niego el estado del pin de salida
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN6);
    }
    */
    // Esto es lo más rápido que se puede.
    if (P1IFG & BIT5)
    {
        P1OUT^=BIT6;
    }
    P1IFG &= ~BIT5;


}
