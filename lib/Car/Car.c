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

#include "Car.h"

motor_wheel front_left;
motor_wheel front_right;
motor_wheel back_left;
motor_wheel back_right;

void CarInit(void) {
    PCA9685Init();
    SetPwnFrequency(100);

    front_left  =   (motor_wheel){ .p_line = LED1, .n_line = LED2, .direction = FORWARD, .speed = 0 };
    front_right =   (motor_wheel){ .p_line = LED3, .n_line = LED4, .direction = FORWARD, .speed = 0 };
    back_left   =   (motor_wheel){ .p_line = LED7, .n_line = LED8, .direction = FORWARD, .speed = 0 };
    back_right  =   (motor_wheel){ .p_line = LED9, .n_line = LED10, .direction = FORWARD, .speed = 0 };
}

void update_all_speed(uint16_t speed) {
    front_left.speed = speed;
    front_right.speed = speed;
    back_left.speed = speed;
    back_right.speed = speed;
}

void stop_all(void) {
    update_all_speed(0);
    update_motors();
}

void update_motors(uint8_t runtime) {
    SetInvertedDutyCycles(front_left.direction, front_left.p_line, front_left.n_line, front_left.speed);
    SetInvertedDutyCycles(front_right.direction, front_right.p_line, front_right.n_line, front_right.speed);
    SetInvertedDutyCycles(back_left.direction, back_left.p_line, back_left.n_line, back_left.speed);
    SetInvertedDutyCycles(back_right.direction, back_right.p_line, back_right.n_line, back_right.speed);

    sleep_ms(runtime);

    stop_all();
}

void Forward(uint16_t speed, uint8_t runtime) {
    front_left.direction = FORWARD;
    front_right.direction = FORWARD;
    back_left.direction = FORWARD;
    back_right.direction = FORWARD;

    update_all_speed(speed);
    update_motors(runtime);
}

void Backward(uint16_t speed, uint8_t runtime) {
    front_left.direction = BACKWARD;
    front_right.direction = BACKWARD;
    back_left.direction = BACKWARD;
    back_right.direction = BACKWARD;

    update_all_speed(speed);
    update_motors(runtime);
}

void ForwardLeft(uint16_t speed, uint8_t runtime) {
    front_left.direction = FORWARD;
    front_left.speed = speed * TURNING_COEFF;
    front_right.direction = FORWARD;
    front_right.speed = speed;
    back_left.direction = FORWARD;
    back_left.speed = speed * TURNING_COEFF;
    back_right.direction = FORWARD;
    back_right.speed = speed;

    update_motors(runtime);
}

void ForwardRight(uint16_t speed, uint8_t runtime) {
    front_left.direction = FORWARD;
    front_left.speed = speed ;
    front_right.direction = FORWARD;
    front_right.speed = speed * TURNING_COEFF;
    back_left.direction = FORWARD;
    back_left.speed = speed;
    back_right.direction = FORWARD;
    back_right.speed = speed * TURNING_COEFF;

    update_motors(runtime);
}

void BackwardLeft(uint16_t speed, uint8_t runtime) {
    front_left.direction = BACKWARD;
    front_left.speed = speed * TURNING_COEFF;
    front_right.direction = BACKWARD;
    front_right.speed = speed;
    back_left.direction = BACKWARD;
    back_left.speed = speed * TURNING_COEFF;
    back_right.direction = BACKWARD;
    back_right.speed = speed;

    update_motors(runtime);
}

void BackwardRight(uint16_t speed, uint8_t runtime) {
    front_left.direction = BACKWARD;
    front_left.speed = speed ;
    front_right.direction = BACKWARD;
    front_right.speed = speed * TURNING_COEFF;
    back_left.direction = BACKWARD;
    back_left.speed = speed;
    back_right.direction = BACKWARD;
    back_right.speed = speed * TURNING_COEFF;

    update_motors(runtime);
}