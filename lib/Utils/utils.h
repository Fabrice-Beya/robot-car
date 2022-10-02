/*****************************************************************************
* | File      	:   utils.h
* | Author      :   Fabrice Beya
* | Function    :   General utility needed across the app.
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-10-02
* | Info        :   
#
# Summary
******************************************************************************/

#ifndef _UTILS_H_
#define _UTILS_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>

#define FORWARD             1
#define BACKWARD            0

// Car message struct
typedef struct {
    uint8_t direction;
    uint8_t speed;
    uint8_t duration;
} car_message_t;

#endif