/*
 * dmaTasks.c
 *
 *  Created on: 15 ago. 2017
 *      Author: federicosilva
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "dmaTasks.h"



const DMA_ControlTable altTaskList[NUMBER_OF_TASKS] =
{
    DMA_TaskStructEntry(DMA_BLOCK_SIZE, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[0],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(DMA_BLOCK_SIZE, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*2],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*3],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*4],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*5],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*6],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*7],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*8],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*9],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*10],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*11],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*12],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*13],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*14],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*15],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*16],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*17],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*18],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*19],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*20],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*21],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*22],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*23],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*24],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*25],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*26],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*27],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*28],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*29],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*30],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*31],
            UDMA_ARB_32, (UDMA_MODE_MEM_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*32],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*33],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*34],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*35],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*36],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*37],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*38],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*39],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*40],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*41],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*42],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*43],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*44],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*45],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*46],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*47],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*48],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*49],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*50],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*51],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*52],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*53],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*54],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*55],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*56],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*57],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*58],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*59],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*60],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*61],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*62],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*63],
            UDMA_ARB_32, (UDMA_MODE_MEM_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*64],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*65],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*66],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*67],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*68],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*69],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*70],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*71],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*72],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*73],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*74],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*75],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*76],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*77],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*78],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*79],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*80],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*81],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*82],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*83],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*84],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            ),
    DMA_TaskStructEntry(32, UDMA_SIZE_32,
            UDMA_SRC_INC_32, &ADC14->MEM[0],
            UDMA_DST_INC_32, (void*) &data[DMA_BLOCK_SIZE*85],
            UDMA_ARB_32, (UDMA_MODE_PER_SCATTER_GATHER)
            )
};


