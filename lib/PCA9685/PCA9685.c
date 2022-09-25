/*****************************************************************************
* | File      	:   PCA9685.c
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

#include "PCA9685.h"
#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

i2c_inst_t *i2c_handler;

static void reset(void);
static uint8_t readPrescalar(void);
static void reset_all_leds();

static void init_i2c() {
    i2c_handler = i2c0;
    i2c_init(i2c_handler, BUS_FREQ);
}

static void init_gpio() {
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}

void PCA9685Init(void) {
    stdio_init_all();
    init_i2c();
    init_gpio();
    reset();
}

static void readByte(const uint8_t reg, uint8_t *buffer) {
    i2c_write_blocking(i2c_handler, ADDRESS, &reg, 1, true);
    i2c_read_blocking(i2c_handler, ADDRESS, buffer, 1, false);
}

static void writeByte(const uint8_t reg, uint8_t buffer) {
    uint8_t msg[2];

    msg[0] = reg;
    msg[1] = buffer;

    i2c_write_blocking(i2c_handler, ADDRESS, msg, 2, false);
}

static uint8_t read_mode() {
    uint8_t mode;
    readByte(MODE1, &mode);
    return mode;
}

static void write_mode(uint8_t mode) {
    writeByte(MODE1, mode);
}

static void enter_sleep() {
    uint8_t new_mode;
    uint8_t current_mode;
    current_mode = read_mode();
    new_mode = (current_mode & 0x7F) | SLEEP_MODE;
    write_mode(new_mode);
}

void SetPwnFrequency(uint32_t freq) {
    float prescaler = 25000000;         
    prescaler /= 4096.0;                 
    prescaler /= freq;
    prescaler -= 1.0;
    uint8_t prescalar_value = (uint8_t)floor(prescaler + 0.5);
    uint8_t old_mode;
    old_mode = read_mode();
    enter_sleep();
    writeByte(PRESCALAR, prescalar_value); 

    write_mode(old_mode);
    sleep_ms(5);
    write_mode(old_mode | 0x80);
}

static void write_duty_cycle(uint8_t led, uint16_t on, uint16_t off) {
    uint8_t shift = 4*led;
    writeByte(LED0_ON_L + shift, on & 0xFF);
    writeByte(LED0_ON_H + shift, on >> 8);
    writeByte(LED0_OFF_L + shift, off & 0xFF);
    writeByte(LED0_OFF_H + shift, off >> 8);
}

static void write_duty_cycle_all(uint16_t on, uint16_t off) {
    writeByte(ALL_LED_ON_L, on & 0xFF);
    writeByte(ALL_LED_ON_H, on >> 8);
    writeByte(ALL_LED_OFF_L, off & 0xFF);
    writeByte(ALL_LED_OFF_H, off >> 8);
}

static uint16_t compute_percetage(uint16_t percentage) {
    if (percentage == 100) { 
        return 4095;
    } else if (percentage == 0) {
        return 0;
    } else {
        float constant = (4095.0f / 100.0f);
        percentage *= constant;
        return percentage;
    }
}

void SetDutyCycle(uint8_t led, uint16_t percentage) {
    uint16_t perc_value = compute_percetage(percentage);
    write_duty_cycle(led, 0, perc_value);
}

void SetDutyCycleAll(uint16_t percentage) {
    uint16_t perc_value = compute_percetage(percentage);
    write_duty_cycle_all(0, perc_value);
}

void SetLevel(uint8_t led, uint8_t level) {
    if (level == 1) {
        write_duty_cycle(led, 0, 4095);
    } else {
        write_duty_cycle(led, 0, 0);
    }
}

void SetInvertedDutyCycles(uint8_t direction, uint8_t led, uint8_t inverted_led, uint16_t percentage) {
    uint16_t perc_value = compute_percetage(percentage);

    if (direction == 1) {
        write_duty_cycle(led, 0, perc_value);
        // write_duty_cycle(inverted_led, 0, 0);
    } else {
        write_duty_cycle(inverted_led, perc_value, 0);
        write_duty_cycle(led, 0, 0);
    }
}

static void reset(void) {
    writeByte(MODE1, 0x00);
    sleep_ms(100);
    SetDutyCycleAll(0);
}

static uint8_t readPrescalar(void) {
    uint8_t value;
    readByte(PRESCALAR, &value);
    return value;
}

static void reset_all_leds() {
    for(uint8_t i = 0; i < 16; i++) {
        SetLevel(i, 0);
    }
}

