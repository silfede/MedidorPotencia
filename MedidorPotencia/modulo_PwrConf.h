/*
 * modulo_PwrConf.h
 *
 * Configuración de los periféricos a utilizar para la
 * medición de potencia. Los mismos son: ADC, DMA, Timer3.
 *
 *  Created on: 15 ago. 2017
 *      Author: federicosilva
 */

#ifndef MODULO_PWRCONF_H_
#define MODULO_PWRCONF_H_

#include "modulo_PwrProc.h"



// Bloque de datos
extern uint32_t data[NUMBER_OF_BLOCKS*DMA_BLOCK_SIZE];
// Variables de tiempo definidas en modulo_PwrProc
extern uint16_t sampling_time;
// Número de interrupciones del DMA
extern uint16_t iter_PingPong;



/**
 * Configuración del módulo ADC medición de potencia.
 * En particular, lo configura a máxima velocidad, usa
 * dos canales y los guarda en todos los lugares de memoria
 * de manera alternada.
 * Puertos configurados:
 *      -A0 PIN5.5
 *      -A1 PIN 5.4
 * Se debe habilitar la conversión y encender el módulo.
 * Luego de usar, deshabilitar.
 */
void configADC();


/**
 * Configuración del módulo DMA.
 * Se configura en modo scatter-gather, por lo que requiere
 * asignación de tareas. La lista de tareas se ubica en dmaTasksc
 * para claridad del código. Se invoca como extern en dmaTasks.h.
 * Resta habilitar el canal (7);
 */
void configDMA();


/**
 * Configuración del Timer3 (el que no se usa en otras partes).
 * Configuración:
 *      -CLK 24MHz
 *      -Divide hasta 12MHz
 *      -Sin interrupciones activas
 */
void configTimer();


/**
 * Configuración puerto toggle para medición de períodos.
 * Habilita la interrupción del puerto PIN4.6
 * @param is_freq Bandera que indica si se está en modo leer frecuencia.
 * En caso contrario, se está en modo leer potencia.
 *
 */
void configToggle(bool is_freq);


#endif /* MODULO_PWRCONF_H_ */
