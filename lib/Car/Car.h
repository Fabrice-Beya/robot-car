/*****************************************************************************
* | File      	:   Car.h
* | Author      :   Fabrice Beya
* | Function    :   Library to control robot car movement
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-09-18
* | Info        :   
#
# Summary
******************************************************************************/

#ifndef _CAR_H_
#define _CAR_H_

#include "PCA9685.h"

#define FORWARD             1
#define BACKWARD            0

#define TURNING_COEFF       (1 / 4)

struct motor_wheel {
    uint8_t p_line;
    uint8_t n_line;
    uint8_t direction;
    uint16_t speed;
} typedef motor_wheel;

void CarInit(void);
void Forward(uint16_t speed, uint8_t runtime);
void Backward(uint16_t speed, uint8_t runtime);
void ForwardLeft(uint16_t speed, uint8_t runtime);
void ForwardRight(uint16_t speed, uint8_t runtime);
void BackwardLeft(uint16_t speed, uint8_t runtime);
void BackwardRight(uint16_t speed, uint8_t runtime);

#endif