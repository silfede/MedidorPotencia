/*
 * modulo_PwrProc.h
 *
 *  Módulo con funciones destinadas al usuario final.
 *  Created on: 29 ago. 2017
 *      Author: federicosilva
 */

#ifndef MODULO_PWRPROC_H_
#define MODULO_PWRPROC_H_


#define DMA_BLOCK_SIZE 24
#define NUMBER_OF_BLOCKS 220

#define GAINVOLT 44
#define GAINCURRENT 66e-3f
// Gain ADC = Vcc/2^14
#define GAINADC 3.3f/16384


#include "modulo_PwrConf.h"

/*
 * Función para pedir frecuencia. Automáticamente llama al procesamiento
 * el cual se encarga de enviar el resultado.
 */
void read_freq();

/*
 * Función para pedir potencia. Automáticamente llama al procesamiento
 * el cual se encarga de enviar el resultado.
 */
void read_pwr();

/*
 * Transforma el número del Timer al valor real de la frecuencia.
 * Posteriormente lo encola para mandar por UART.
 * @param timer Valor del timer
 */
void proc_freq(uint16_t timer);


/*
 * Procesa los valores obtenidos por el ADC y el timer, hallando la
 * potencia media en 10 perídos. Se definen las ganancias arriba descritas
 * para transformar las medidas del ADC a los valores reales.
 */
void proc_pwr();

#endif /* MODULO_PWRPROC_H_ */
