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

#include "PCA9685.h"
#include "pico/stdlib.h"

void Init() {
    // Initialise PWM controller on ic20
    PCA9685Init();
    // Set PWM signal to 100hz
    SetPwnFrequency(100);
}

int main(void) {
    Init();

    uint8_t random_duty;

    while(true) {
        // Generate a random number between 0 - 90
        random_duty = rand()%90; 

        // Set the duty cycle to random duty cycle plus constant in range of 1 - 10
        SetDutyCycle(LED2, random_duty);     
        SetDutyCycle(LED4, random_duty + 5);     
        SetDutyCycle(LED8, random_duty - 5);     
        SetDutyCycle(LED10, random_duty - 10 );    
    }
}