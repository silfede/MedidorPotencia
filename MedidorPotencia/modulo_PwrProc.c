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

uint8_t adc_data[2*NUMBER_OF_BLOCKS*DMA_BLOCK_SIZE];

// Tiempo durante el cual se samplea
uint16_t sampling_time = 0;
// Número de interrupciones del DMA
uint16_t iter_PingPong = 0;

/* Varaibles locales */
float frecuencia;


/* Devuelve el número de muestras */
uint16_t SampleNumber(uint16_t iter_PingPong)
{
    int i;
    // Recorro solo el final del arreglo
    for(i=26 * iter_PingPong;i<26 * (iter_PingPong + 1);i += 2)
    {
        if(data[i]==0 && data[i+1]==0)
        {
            if(data[i+2]==0 && data[i+3]==0)
            {
                return (i-1);
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
    frecuencia = 100 * FCLK / timer;
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
    float time;
    unsigned int i,u;
    uint16_t n;
    u = *(unsigned int*)&time;
    // Número de muestras recabadas por ADC
    n = SampleNumber(iter_PingPong);

    // Tiempo durante el cual muestreo
    time = sampling_time / FCLK;
    /*
     * Cabecera de los datos:
     * n = número de muestras
     * sampling_time = ticks de muestreo
     */
    adc_data[0] = n & 0xFF;
    adc_data[1] = n >> 8;
    adc_data[2] = u & 0xFF;
    adc_data[3] = u >> 8;
    adc_data[4] = u >> 16;
    adc_data[5] = u >> 24;

    for(i=3;i<=(n+3);i++)
    {
        adc_data[2*i] = data[i-3] & 0xFF;
        adc_data[2*i+1] = data[i-3]>>8;
    }
    adc_data[i]='\r';

    //transmitir_cadena(adc_data);


}


















