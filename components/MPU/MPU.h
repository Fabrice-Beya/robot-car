/*****************************************************************************
* | File      	:   MPU6050.h
* | Author      :   Fabrice Beya
* | Function    :   Driver library to interface with a Master Processing Unit
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-09-27
* | Info        :   
#
# Summary
******************************************************************************/

#ifndef _MPU_H_
#define _MPU_H_

#include "utils.h"
#include "hardware/spi.h"

#define CLK_SPEED           1000*1000
#define CLK                 6       
#define MOSI                7
#define MISO                4
#define CS                  5

// Commands
#define MOVE                1
#define SLEEP               2
#define REBOOT              3
#define STATUS              4
#define IDLE                5

/**
 * @brief 
 * 4 byte message protocol
 * Command, Forward, Speed, Duration
 */

#define BUF_LEN             4

// Commands
#define COMMAND             0
#define DIRECTION           1
#define SPEED               2
#define DURATION            3

void MPU(QueueHandle_t _carMessageQueue);
void MPUListen(void);

#endif

