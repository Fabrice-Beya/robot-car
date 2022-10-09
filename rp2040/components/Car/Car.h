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

#include "utils.h"
#include "PCA9685.h"

// #define TURNING_COEFF       (3 / 4)

struct motor_wheel {
    volatile uint8_t led;
    volatile uint8_t direction;
    volatile uint8_t speed;
} typedef motor_wheel;

void Car(QueueHandle_t _carMessageQueue);
void Forward(uint8_t speed, uint8_t runtime);
void Backward(uint8_t speed, uint8_t runtime);
void ForwardLeft(uint8_t speed, uint8_t runtime);
void ForwardRight(uint8_t speed, uint8_t runtime);
void BackwardLeft(uint8_t speed, uint8_t runtime);
void BackwardRight(uint8_t speed, uint8_t runtime);
void Stop(void);
void CarListen(void);

#endif