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
#include "pico/stdlib.h"

void Init() {
    CarInit();

}

int main(void) {
    Init();

    while(true) {
        Forward(50, 2000);
        sleep_ms(2000);
        Backward(50, 2000);
        sleep_ms(2000);
    }
}