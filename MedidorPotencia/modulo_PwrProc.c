/*
 * modulo_PwrProc.c
 *
 *  Created on: 29 ago. 2017
 *      Author: federicosilva
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "modulo_PwrProc.h"
#include "modulo_PwrConf.h"

/*
 * Las siguientes variables se definen aquí pero se modifican
 * en la configuración de este módulo
 */

// Variable donde guardo los resultados del ADC para procesar
uint32_t data[NUMBER_OF_BLOCKS*DMA_BLOCK_SIZE];
// Tiempo durante el cual se samplea
uint16_t sampling_time = 0;
// Número de interrupciones del DMA
uint16_t iter_PingPong = 0;

/* Varaibles locales */
float frecuencia;

int SampleNumber(uint16_t iter_PingPong)
{
    int i;
    // Recorro solo el final del arreglo
    for(i=26 * iter_PingPong;i<26 * (iter_PingPong + 1);i += 2)
    {
        if(data[i]==0 && data[i+1]==0)
        {
            if(data[i+2]==0 && data[i+3]==0)
            {
                return (i-2)/2;
            }
        }
    }
}

void read_pwr()
{
    MAP_Interrupt_disableMaster();

    // Reseteo el array de data
    memset(data, 0x00000000, NUMBER_OF_BLOCKS*DMA_BLOCK_SIZE);

    configTimer();
    // Interrupción de señal cuadrada. ISR configurada para pwr.
    configToggle(false);
    configADC();
    configDMA();
    MAP_Interrupt_enableMaster();
}

void read_freq()
{
    MAP_Interrupt_disableMaster();
    configTimer();

    // Interrupción de señal cuadrada. ISR configurada para freq.
    configToggle(true);
    MAP_Interrupt_enableMaster();

}


void proc_freq(uint16_t timer)
{
    frecuencia = 100 * timer / 12e6f;
    /* Transformo en chars para poder enviar mediante UART.
     * Luego agrego a buffer de envío y mando.
     */
    unsigned char *chptr;
    chptr = (unsigned char *) &frecuencia;
    //Tx(*chptr++);Tx(*chptr++);Tx(*chptr++);Tx(*chptr);
    // ENCOLAR RESPEUSTA UART
}


void proc_pwr()
{
    int n;

    // Número de muestras recabadas por ADC
    n = SampleNumber(iter_PingPong);

}

void proc_PyF()
{
    int i,n;
    float b,s1=0,s2=0,h;
    // Número de pares de muestras (corriente y volt)
    n = SampleNumber(iter_PingPong);


    // Integración por método de Simpson
/*
    // Paso de integración (tiempo de sampleo)
    h=sampling_time/ (n * 12e6f);

    if(n%2==1)
        n -=1;

    for(i=1;i<=n-1;i++)
    {
        if(i%2==0)
        {
            s1=s1+f(a+i*h);
        }
        else
        {
            s2=s2+f(a+i*h);
        }
    }
      sum=h/3*(f(a)+f(b)+4*s2+2*s1);*/

}















