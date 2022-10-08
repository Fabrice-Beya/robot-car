/*****************************************************************************
* | File      	:   MPU6050.c
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

#include "MPU6050.h"

static void init_i2c();
static void init_gpio();
static void reset();

i2c_inst_t *i2c_handler;

void MPU6050Init(void) {
    stdio_init_all();
    init_i2c();
    init_gpio();
    reset();
}

static void init_i2c() {
    i2c_handler = i2c1;
    i2c_init(i2c_handler, BUS_FREQ);
}

static void init_gpio() {
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
}


static void reset() {
    uint8_t buf[] = {RST_ADR, 0x00};
    i2c_write_blocking(i2c_handler, DEV_ADR, buf, 2, false);
}

static void read_acc(imu_type *imu_data) {
    uint8_t buffer[6];
    uint8_t reg = ACC_ADR;

    i2c_write_blocking(i2c_handler, DEV_ADR, &reg, 1, true); 
    i2c_read_blocking(i2c_handler, DEV_ADR, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        imu_data->accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }
}

static void read_gyro(imu_type *imu_data) {
    uint8_t buffer[6];
    uint8_t reg = GYRO_ADR;

    i2c_write_blocking(i2c_handler, DEV_ADR, &reg, 1, true); 
    i2c_read_blocking(i2c_handler, DEV_ADR, buffer, 6, false);

    for (int i = 0; i < 3; i++) {
        imu_data->gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }
}

static void read_temp(imu_type *imu_data) {
    uint8_t buffer[2];
    uint8_t reg = TEMP_ADR;

    i2c_write_blocking(i2c_handler, DEV_ADR, &reg, 1, true); 
    i2c_read_blocking(i2c_handler, DEV_ADR, buffer, 6, false);

    imu_data->temp = buffer[0] << 8 | buffer[1];
}

void ReadIMU(imu_type *imu_data) {
    read_acc(imu_data);
    read_gyro(imu_data);
    read_temp(imu_data);
}