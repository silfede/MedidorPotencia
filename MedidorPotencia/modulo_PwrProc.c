/*
 * modulo_PwrProc.c
 *
 *  Created on: 29 ago. 2017
 *      Author: federicosilva
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "modulo_PwrProc.h"

#define FREQ 1
#define POWER 0

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


/* Devuelve el número de pares de muestras */
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
    configToggle(POWER);
    configADC();
    configDMA();
    MAP_Interrupt_enableMaster();
}

void read_freq()
{
    MAP_Interrupt_disableMaster();
    configTimer();

    // Interrupción de señal cuadrada. ISR configurada para freq.
    configToggle(FREQ);
    MAP_Interrupt_enableMaster();

}


void proc_freq(uint16_t timer)
{
    frecuencia = 100 * 24e6f / timer;
    /* Transformo en chars para poder enviar mediante UART.
     * Luego agrego a buffer de envío y mando.
     */
    unsigned char *chptr;
    chptr = (unsigned char *) &frecuencia;
    //Tx(*chptr++);Tx(*chptr++);Tx(*chptr++);Tx(*chptr);
    // RESPUESTA UART
}


void proc_pwr()
{
    uint32_t s1=0,s2=0,sum=0;
    float potencia;
    int i,n;
    float h;
    // Número de muestras recabadas por ADC
    n = SampleNumber(iter_PingPong);

    /* Integración por el método de Simpson:
     *
     * int(y_i) entre a y b = h/3 * (y0 + 4(y1+y3+...) + 2(y2+y4+...) + yn)
     * siendo h=(b-a)/n el paso de integración
     */

    // Tiempo entre muestras sucesivas
    h = sampling_time / (n * 12e6f);

    if(n%2==1)
        n -=1;

    for(i=1;i<=n-1;i++)
    {
        if(i%2==0)
        {
            s1=s1+data[2*i]*data[2*i+1];
        }
        else
        {
            s2=s2+data[2*i]*data[2*i+1];
        }
    }
    // Suma parcial de la integral
    sum=(data[0]*data[1]+data[2*n]*data[2*n+1]+4*s2+2*s1);
    /* Resta multiplicar por los factores de escala: ganancia de voltaje y
     * corriente, y factor de escala del ADC
     */
    potencia = sum * h/3 * GAINVOLT * GAINCURRENT * GAINADC * GAINADC / 10;

    /* Transformo en chars para poder enviar mediante UART.
     * Luego agrego a buffer de envío y mando.
     */
    unsigned char *chptr;
    chptr = (unsigned char *) &potencia;
    //Tx(*chptr++);Tx(*chptr++);Tx(*chptr++);Tx(*chptr);
    // RESPUESTA UART
}


















