/*****************************************************************************
* | File      	:   MPU.c
* | Author      :   Fabrice Beya
* | Function    :   Driver library to interface with a Master Processing Unit
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-09-27
* | Info        :   
#
# Summary
******************************************************************************/

#include "MPU.h"

uint8_t response[BUF_LEN], message[BUF_LEN];
QueueHandle_t carMessageQueue;

static void init_spi(void) {
    
    spi_init(spi0, CLK_SPEED);
    spi_set_slave(spi0, true);
    gpio_set_function(CLK, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);
    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(CS, GPIO_FUNC_SPI);
    spi_set_format(spi0, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
}

static void init_response_message(void) {
    response[COMMAND]   = IDLE;
    response[DIRECTION] = 0;
    response[SPEED]     = 0;
    response[DURATION]  = 0;    
}

void MPUInit(QueueHandle_t _carMessageQueue) {
    carMessageQueue = _carMessageQueue;
    init_spi();
    init_response_message();
}

static void send_car_message(uint8_t *message) {
    int ret = -1;
    car_message_t car_message = (car_message_t){ .direction = message[DIRECTION], .speed = message[SPEED], .duration = message[DURATION]};
    
    ret = xQueueSend(carMessageQueue, &car_message, portMAX_DELAY);

    if (ret != pdPASS) {
        printf("Failed to send car message");
    }
}

static void process_message(uint8_t *_message) {
    response[COMMAND]   = _message[COMMAND];
    response[DIRECTION] = _message[DIRECTION];
    response[SPEED]     = _message[SPEED];
    response[DURATION]  = _message[DURATION];

    switch (message[COMMAND])
    {
        case MOVE:
            send_car_message(_message);
            break;
        case STATUS:
            // TODO:
            break;
        case IDLE:
            // Do nothing
            break;
        case SLEEP:
            // TODO:
            break;
        case REBOOT:
            // TODO:
            break;
        default:
            break;
    }
}

void MPUListen(void) {
    while(true) {
        int ret = spi_write_read_blocking(spi0, response, message, BUF_LEN);
        
        if (ret) {
            process_message(message);
        }
    }
}
