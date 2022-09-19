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

    // Set two led lines with inverter PWM signals
    SetInvertedDutyCycles(0, LED1, LED2, 60);

}

int main(void) {
    Init();

    while(true) {
        
    }
}