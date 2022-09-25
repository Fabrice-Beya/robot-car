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

void update_motors(uint32_t runtime);
void update_pwm(void);

void CarInit(void) {
    PCA9685Init();
    SetPwnFrequency(100);

    front_left  =   (motor_wheel){ .led = LED0, .direction = FORWARD, .speed = 0 };
    front_right =   (motor_wheel){ .led = LED3, .direction = FORWARD, .speed = 0  };
    back_left   =   (motor_wheel){ .led = LED6, .direction = FORWARD, .speed = 0  };
    back_right  =   (motor_wheel){ .led = LED9, .direction = FORWARD, .speed = 0 };
}

void set_all_motors_speed(uint16_t speed) {
    front_left.speed = speed;
    front_right.speed = speed;
    back_left.speed = speed;
    back_right.speed = speed;
}

void update_all_motors_speed(void) {
    SetDutyCycle(front_left.led, front_left.speed);
    SetDutyCycle(front_right.led, front_right.speed);
    SetDutyCycle(back_left.led, back_left.speed);
    SetDutyCycle(back_right.led, back_right.speed);
}

void update_motor(motor_wheel *motor) {
    SetDutyCycle(motor->led, motor->speed);
    if (motor->direction == FORWARD) {
        SetLevel(motor->led + 1, 1);
        SetLevel(motor->led + 2, 0);
    } else {
        SetLevel(motor->led + 1, 0);
        SetLevel(motor->led + 2, 1);
    }
}

void update_all(void) {
    update_motor(&front_left);
    update_motor(&front_right);
    update_motor(&back_left);
    update_motor(&back_right);
}

void update_all_motors(uint32_t runtime) {
    
    update_all();
    sleep_ms(runtime);
    Stop();
}

void Stop(void) {
    set_all_motors_speed(0);
    update_all_motors_speed();
}

void Backward(uint16_t speed, uint32_t runtime) {
    front_left.direction = FORWARD;
    front_right.direction = FORWARD;
    back_left.direction = FORWARD;
    back_right.direction = FORWARD;

    set_all_motors_speed(speed);
    update_all_motors(runtime);
}

void Forward(uint16_t speed, uint32_t runtime) {
    front_left.direction = BACKWARD;
    front_right.direction = BACKWARD;
    back_left.direction = BACKWARD;
    back_right.direction = BACKWARD;

    set_all_motors_speed(speed);
    update_all_motors(runtime);
}

void BackwardLeft(uint16_t speed, uint32_t runtime) {
    front_left.direction = FORWARD;
    front_left.speed = speed * TURNING_COEFF;
    front_right.direction = FORWARD;
    front_right.speed = speed;
    back_left.direction = FORWARD;
    back_left.speed = speed * TURNING_COEFF;
    back_right.direction = FORWARD;
    back_right.speed = speed;

    update_all_motors(runtime);
}

void BackwarRight(uint16_t speed, uint32_t runtime) {
    front_left.direction = FORWARD;
    front_left.speed = speed ;
    front_right.direction = FORWARD;
    front_right.speed = speed * TURNING_COEFF;
    back_left.direction = FORWARD;
    back_left.speed = speed;
    back_right.direction = FORWARD;
    back_right.speed = speed * TURNING_COEFF;

    update_all_motors(runtime);
}

void ForwardLeft(uint16_t speed, uint32_t runtime) {
    front_left.direction = BACKWARD;
    front_left.speed = speed * TURNING_COEFF;
    front_right.direction = BACKWARD;
    front_right.speed = speed;
    back_left.direction = BACKWARD;
    back_left.speed = speed * TURNING_COEFF;
    back_right.direction = BACKWARD;
    back_right.speed = speed;

    update_all_motors(runtime);
}

void ForwardRight(uint16_t speed, uint32_t runtime) {
    front_left.direction = BACKWARD;
    front_left.speed = speed ;
    front_right.direction = BACKWARD;
    front_right.speed = speed * TURNING_COEFF;
    back_left.direction = BACKWARD;
    back_left.speed = speed;
    back_right.direction = BACKWARD;
    back_right.speed = speed * TURNING_COEFF;

    update_all_motors(runtime);
}