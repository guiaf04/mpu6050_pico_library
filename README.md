# MPU6050 Library for Raspberry Pi Pico (with FreeRTOS)

This library facilitates communication with the MPU6050 6-axis gyroscope and accelerometer sensor using the Raspberry Pi Pico and the FreeRTOS real-time operating system. It provides an easy-to-use interface for configuring the sensor, reading raw accelerometer and gyroscope data, and converting it into human-readable formats.

---

## Features
- **MPU6050 Configuration**: Set up the sensor for desired sensitivity and sample rates.
- **I2C Communication**: Handles I2C initialization and data transfer.
- **Data Acquisition**: Retrieve accelerometer and gyroscope values as raw data.
- **Real-Time Example**: Demonstrates the library with FreeRTOS, using tasks to read and display sensor data in real time.

---

## Hardware Requirements
- Raspberry Pi Pico
- MPU6050 Sensor Module
- I2C connections:
    - **SDA**: Connect to GPIO pin specified in the library instantiation.
    - **SCL**: Connect to GPIO pin specified in the library instantiation.

---

## Software Requirements
- [Pico SDK](https://github.com/raspberrypi/pico-sdk)
- C++17 or higher

---

## Installation

1. Clone this repository into your project directory:
   ```bash
   git clone <repository-url>
   ```

2. Include the library files in your `CMakeLists.txt`:
   ```cmake
   target_sources(${PROJECT_NAME} PRIVATE
       ${CMAKE_CURRENT_LIST_DIR}/mpu6050.cpp
   )
   ```

3. Ensure FreeRTOS is configured in your Pico SDK project.

---

## Example Usage

Here is an example demonstrating the integration of the library with FreeRTOS:

### main.cpp

```cpp
#include "mpu6050.hpp"
#include "FreeRTOS.h"
#include "task.h"

void read_sensor_task(void *params) {
    mpu6050 sensor(i2c0, 20, 21); // I2C0 with SDA on GPIO20, SCL on GPIO21

    accel accel_data;
    gyro gyro_data;

    while (true) {
        sensor.print_raw_data(accel_data, gyro_data);

        vTaskDelay(pdMS_TO_TICKS(500)); // Delay for 500 ms
    }
}

int main() {
    stdio_init_all(); // Initialize standard I/O


    xTaskCreate(read_sensor_task, "Read Sensor Task", 1024, NULL, 1, NULL);

    vTaskStartScheduler(); // Start FreeRTOS scheduler

    while (true) {
        // Should never reach here
    }

    return 0;
}
```

---

## API Reference

### Constructor
```cpp
mpu6050(i2c_inst *i2c_port, uint16_t sda, uint16_t scl);
```
**Parameters**:
- `i2c_port`: Pointer to the I2C instance (e.g., `i2c0` or `i2c1`).
- `sda`: GPIO pin for SDA.
- `scl`: GPIO pin for SCL.

### Destructor
```cpp
~mpu6050();
```

### Methods
- **`void getAccel(accel *accel);`**  
  Reads accelerometer data and stores it in the provided `accel` struct.

- **`void getGyro(gyro *gyro);`**  
  Reads gyroscope data and stores it in the provided `gyro` struct.

- **`void print_raw_data(accel accelData, gyro gyroData);`**  
  Prints formatted accelerometer and gyroscope values to the console.

- **`void toString(char *buffer, size_t buffer_size, accel accelData, gyro gyroData);`**  
  Returns by pointer a formatted string that cointains accelerometer and gyroscope values.
---

## MPU6050 Configuration

Adjust the following macros in `mpu6050.hpp` to modify the sensor's sensitivity and range:

- Accelerometer sensitivity:
  ```cpp
  #define ACCEL_SCALE_FACTOR ACCEL_SCALE_FACTOR_4G
  #define ACCEL_CONFIG_VALUE 0x08
  ```

- Gyroscope sensitivity:
  ```cpp
  #define GYRO_SCALE_FACTOR GYRO_SCALE_FACTOR_250DPS
  #define GYRO_CONFIG_VALUE 0x00
  ```

---

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

---

## Acknowledgments
This library is based on the Raspberry Pi Pico SDK and integrates FreeRTOS for real-time performance.