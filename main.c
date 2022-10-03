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
#include "utils.h"
#include "pico/multicore.h" 
#include "main.h"

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

QueueHandle_t CarMessageQueue;

void Car_Task(void *pvParameters) {
    CarInit(CarMessageQueue);
    // CarListen();
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
    stdio_init_all();
    
    Init_Queues();

    TaskHandle_t MPU_Task_Handle; 
    TaskHandle_t Car_Task_Handle; 

    xTaskCreate(Car_Task, "Car_Task", 1024, NULL, tskIDLE_PRIORITY, &Car_Task_Handle);
    xTaskCreate(MPU_Task, "MPU_Task", 1024, NULL, tskIDLE_PRIORITY, &MPU_Task_Handle);

    vTaskCoreAffinitySet( MPU_Task_Handle, ( 1 << 0 ) );
    vTaskCoreAffinitySet( Car_Task_Handle, ( 1 << 0 ) );

    vTaskStartScheduler();

    while(1){};
}

void vApplicationMallocFailedHook( void )
{
    /* Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected. */

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    volatile size_t xFreeHeapSpace;

    /* This is just a trivial example of an idle hook.  It is called on each
    cycle of the idle task.  It must *NOT* attempt to block.  In this case the
    idle task just queries the amount of FreeRTOS heap that remains.  See the
    memory management section on the http://www.FreeRTOS.org web site for memory
    management options.  If there is a lot of heap memory free then the
    configTOTAL_HEAP_SIZE value in FreeRTOSConfig.h can be reduced to free up
    RAM. */
    xFreeHeapSpace = xPortGetFreeHeapSize();

    /* Remove compiler warning about xFreeHeapSpace being set but never used. */
    ( void ) xFreeHeapSpace;
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{

}