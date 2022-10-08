/*****************************************************************************
* | File      	:   MPU6050.h
* | Author      :   Fabrice Beya
* | Function    :   Driver library for MPU6050 IMU sensor
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2022-09-25
* | Info        :   
#
# Summary
******************************************************************************/

#ifndef _MPU6050_H_
#define _MPU6050_H_

#include "utils.h"
#include "hardware/i2c.h"

/**
 * @brief I2C configurations
 * 
 */
#define SCL_PIN                         27
#define SDA_PIN                         26
#define BUS_FREQ                        100000

/**
 * @brief PCA9685 Regsiters
 * 
 */
#define DEV_ADR                         0x68
#define ACC_ADR                         0x3B
#define GYRO_ADR                        0x43
#define TEMP_ADR                        0x41
#define RST_ADR                         0x6B

struct imu_type {
    int16_t accel[3];
    int16_t gyro[3];
    int16_t temp;
} typedef imu_type;

void MPU6050Init(void);
void ReadIMU(imu_type *imu_data) ;

#endif

