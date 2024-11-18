#include <cstdlib>

#include "mpu6050.hpp"
#include "FreeRTOS.h"
#include "task.h"

mpu6050 mpu6050(i2c0, 4, 5);
gyro gyroData;
accel accelData;

void mpu_task(void *pvParameters)
{
    while(1)
    {
        mpu6050.print_raw_data(accelData, gyroData);
        printf("\n");
        // mpu6050.mpu6050_print_raw_data(mpu6050_data);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

int main() {
    stdio_init_all();

    xTaskCreate(mpu_task, "MPUTask", 1024, NULL, 1, NULL);

    vTaskStartScheduler();

    while(true);
}
