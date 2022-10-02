/*****************************************************************************
* | File      	:   main.c
* | Author      :   Fabrice Beya
* | Function    :   Robot car application
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-09-18
* | Info        :   
#
# Summary
******************************************************************************/

#include "Car.h"
#include "MPU.h"
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include "pico/stdlib.h"

QueueHandle_t CarMessageQueue;

void Car_Task(void *pvParameters) {
    CarInit(CarMessageQueue);
    CarListen();
}

void MPU_Task(void *pvParameters) {
    MPUInit(CarMessageQueue);
    MPUListen();
}

void Init_Queues(void) {
    CarMessageQueue = xQueueCreate(5, sizeof(car_message_t));
    if (CarMessageQueue == 0) {
        printf("Failed to create car message queue.");
    }
}

int main(void) {
    
    Init_Queues();

    xTaskCreate(Car_Task, "Car_Task", 1024, NULL, 1, NULL);
    xTaskCreate(MPU_Task, "MPU_Task", 1024, NULL, 1, NULL);

    vTaskStartScheduler();
}