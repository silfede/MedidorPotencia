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

/* Lugares donde se retornan los valores una vez encontrados */
float potencia,frecuencia;


/*
 * Función para pedir valores de potencia y frecuencia.
 * Los valores de retorno se dan en potencia y frecuencia definidos
 * al inicio.
 */
void req_PyF();

/*
 * Procesa los datos relevados por el ADC y el Timer.
 * Guarda los resultados en las variables arriba definidas.
 */
void proc_PyF();

#endif /* MODULO_PWRPROC_H_ */
