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
 *          --|RST          P1.1 | <-- GPIO req
 *            |             P1.2 | --> Output
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

int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    // Seteo 1.2 como salida
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN2);

    // Configuro 1.1 como entrada con resistencia de pull-up
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    // Limpio bandera de interrupciones y activo las del puerto 1.1
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);

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
 * que efectivamente provenga del P1.1).
 */
void PORT1_IRQHandler(void)
{
    uint32_t status;

    // Obtengo todo el vector estado de las interrupciones del puerto 1
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    // Limipio la que me llama
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    // Verifico que provenga del pin 1 efectivamente (trivial en este caso)
    if(status & GPIO_PIN1)
    {
        // Niego el estado del pin de salida
        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN2);
    }

}
