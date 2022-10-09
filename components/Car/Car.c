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

QueueHandle_t messageQueue;

static const float TURNING_COEFF = 0.75;

void update_motors(uint32_t runtime);
void update_pwm(void);

void Car(QueueHandle_t _carMessageQueue) {
    messageQueue = _carMessageQueue;
    PCA9685();
    SetPwnFrequency(100);

    front_left  =   (motor_wheel){ .led = LED0, .direction = FORWARD, .speed = 0 };
    front_right =   (motor_wheel){ .led = LED3, .direction = FORWARD, .speed = 0  };
    back_left   =   (motor_wheel){ .led = LED6, .direction = FORWARD, .speed = 0  };
    back_right  =   (motor_wheel){ .led = LED9, .direction = FORWARD, .speed = 0 };
}

static void process_message( car_message_t *car_message) {
    switch (car_message->direction)
    {
        case FORWARD:
            Forward(car_message->speed, car_message->duration);
            break;
        case BACKWARD:
            Backward(car_message->speed, car_message->duration);
            break;
        case FORWARD_LEFT:
            ForwardLeft(car_message->speed, car_message->duration);
            break;
        case FORWARD_RIGHT:
            ForwardRight(car_message->speed, car_message->duration);
            break;
        case BACKWARD_LEFT:
            BackwardLeft(car_message->speed, car_message->duration);
            break;
        case BACKWARD_RIGHT:
            BackwardRight(car_message->speed, car_message->duration);
            break;
        default:
            break;
    }
}

void CarListen(void) {
    car_message_t car_message;
    while(true) {
        if (xQueueReceive(messageQueue, &car_message, portMAX_DELAY) == pdTRUE)
		{
			process_message(&car_message);
		}
		else
		{
			printf("No message received");
		}
    }
}

void set_all_motors_speed(uint8_t speed) {
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

void update_all_motors(uint8_t runtime) {
    
    update_all();
    sleep_ms(runtime*1000);
    Stop();
}

void Stop(void) {
    set_all_motors_speed(0);
    update_all_motors_speed();
}

void Forward(uint8_t speed, uint8_t runtime) {
    front_left.direction = FORWARD;
    front_right.direction = FORWARD;
    back_left.direction = FORWARD;
    back_right.direction = FORWARD;

    set_all_motors_speed(speed);
    update_all_motors(runtime);
}

void Backward(uint8_t speed, uint8_t runtime) {
    front_left.direction = BACKWARD;
    front_right.direction = BACKWARD;
    back_left.direction = BACKWARD;
    back_right.direction = BACKWARD;

    set_all_motors_speed(speed);
    update_all_motors(runtime);
}

void ForwardLeft(uint8_t speed, uint8_t runtime) {
    uint8_t differential_speed = (uint8_t)floor(speed * TURNING_COEFF);
    front_left.direction = FORWARD;
    front_left.speed = differential_speed;
    front_right.direction = FORWARD;
    front_right.speed = speed;
    back_left.direction = FORWARD;
    back_left.speed = differential_speed;
    back_right.direction = FORWARD;
    back_right.speed = speed;

    update_all_motors(runtime);
}

void ForwardRight(uint8_t speed, uint8_t runtime) {
    uint8_t differential_speed = (uint8_t)floor(speed * TURNING_COEFF);
    front_left.direction = FORWARD;
    front_left.speed = speed ;
    front_right.direction = FORWARD;
    front_right.speed = differential_speed;
    back_left.direction = FORWARD;
    back_left.speed = speed;
    back_right.direction = FORWARD;
    back_right.speed = differential_speed;

    update_all_motors(runtime);
}

void BackwardLeft(uint8_t speed, uint8_t runtime) {
    uint8_t differential_speed = (uint8_t)floor(speed * TURNING_COEFF);
    front_left.direction = BACKWARD;
    front_left.speed = differential_speed;
    front_right.direction = BACKWARD;
    front_right.speed = speed;
    back_left.direction = BACKWARD;
    back_left.speed = differential_speed;
    back_right.direction = BACKWARD;
    back_right.speed = speed;

    update_all_motors(runtime);
}

void BackwardRight(uint8_t speed, uint8_t runtime) {
    uint8_t differential_speed = (uint8_t)floor(speed * TURNING_COEFF);
    front_left.direction = BACKWARD;
    front_left.speed = speed ;
    front_right.direction = BACKWARD;
    front_right.speed = differential_speed;
    back_left.direction = BACKWARD;
    back_left.speed = speed;
    back_right.direction = BACKWARD;
    back_right.speed = differential_speed;

    update_all_motors(runtime);
}
