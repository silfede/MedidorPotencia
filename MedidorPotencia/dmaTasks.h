/*
 * dmaTasks.h
 *
 *  Created on: 15 ago. 2017
 *      Author: federicosilva
 */

#define NUMBER_OF_TASKS 86
#define DMA_BLOCK_SIZE 26

#ifndef DMATASKS_H_
#define DMATASKS_H_

extern const DMA_ControlTable altTaskList[NUMBER_OF_TASKS];

extern uint32_t data[NUMBER_OF_TASKS*DMA_BLOCK_SIZE];

extern uint16_t N;

#endif /* DMATASKS_H_ */
