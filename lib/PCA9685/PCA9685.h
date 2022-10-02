/*****************************************************************************
* | File      	:   PCA9685.h
* | Author      :   Fabrice Beya
* | Function    :   Driver library for PCA9685 PWM Controller
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-09-18
* | Info        :   
#
# Summary
******************************************************************************/

#ifndef _PCA9685_H_
#define _PCA9685_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

/**
 * @brief I2C configurations
 * 
 */
#define SCL_PIN                         21
#define SDA_PIN                         20
#define BUS_FREQ                        100000

/**
 * @brief PCA9685 Regsiters
 * 
 */
#define ADDRESS                         0x40
#define SUBADR1                         0x02
#define SUBADR2                         0x03
#define SUBADR3                         0x04

#define MODE1                           0x00
#define SLEEP_MODE                      0x10

#define PRESCALAR                       0xFE

#define LED0_ON_L                       0x06
#define LED0_ON_H                       0x07
#define LED0_OFF_L                      0x08
#define LED0_OFF_H                      0x09
#define ALL_LED_ON_L                    0xFA
#define ALL_LED_ON_H                    0xFB
#define ALL_LED_OFF_L                   0xFC
#define ALL_LED_OFF_H                   0xFD

#define LED0                            0
#define LED1                            1
#define LED2                            2
#define LED3                            3
#define LED4                            4
#define LED5                            5
#define LED6                            6
#define LED7                            7
#define LED8                            8
#define LED9                            9
#define LED10                           10
#define LED11                           11
#define LED12                           12
#define LED13                           13
#define LED14                           14
#define LED15                           15

void PCA9685Init(void);
void SetPwnFrequency(uint32_t freq);
void SetDutyCycle(uint8_t led, uint16_t percentage);
void SetLevel(uint8_t led, uint8_t level);
void SetDutyCycleAll(uint16_t percentage);

#endif