// MIT License

// Copyright (c) 2023 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __MPU9250_PUBLIC_H__
#define __MPU9250_PUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <err_code.h>

typedef uint8_t (*func_read_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);
typedef uint8_t (*func_write_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/**
 * @brief   Clock source select.
 */
typedef enum {
    MPU9250_CLKSEL_INTERNAL_20_MHZ = 0,     /*!< Internal 20 MHz clock source */
    MPU9250_CLKSEL_AUTO,                    /*!< Auto select available clock source */
    MPU9250_CLKSEL_MAX
} mpu9250_clksel_t;

/**
 * @brief   Bandwidth select.
 */
typedef enum {
    MPU9250_250ACEL_4000GYRO_BW_HZ = 0,     /*!< 250 Hz accelerometer bandwidth, 4000 Hz gyroscope bandwidth */
    MPU9250_184ACEL_188GYRO_BW_HZ,          /*!< 184 Hz accelerometer bandwidth, 188 Hz gyroscope bandwidth */
    MPU9250_92ACEL_98GYRO_BW_HZ,            /*!< 92 Hz accelerometer bandwidth, 98 Hz gyroscope bandwidth */
    MPU9250_41ACEL_42GYRO_BW_HZ,            /*!< 41 Hz accelerometer bandwidth, 42 Hz gyroscope bandwidth */
    MPU9250_20ACEL_20GYRO_BW_HZ,            /*!< 20 Hz accelerometer bandwidth, 20 Hz gyroscope bandwidth */
    MPU9250_10ACEL_10GYRO_BW_HZ,            /*!< 10 Hz accelerometer bandwidth, 10 Hz gyroscope bandwidth */
    MPU9250_5ACEL_5GYRO_BW_HZ,              /*!< 5 Hz accelerometer bandwidth, 5 Hz gyroscope bandwidth */
    MPU9250_DLPF_CFG_MAX
} mpu9250_dlpf_cfg_t;

/**
 * @brief   Sleep mode.
 */
typedef enum {
    MPU9250_DISABLE_SLEEP_MODE = 0,         /*!< Disable sleep mode */
    MPU9250_LOW_PWR_SLEEP_MODE,             /*!< Low power mode */
    MPU9250_SLEEP_MODE_MAX
} mpu9250_sleep_mode_t;

/**
 * @brief   FS scale.
 */
typedef enum {
    MPU9250_FS_SEL_250 = 0,                 /*!< 250 deg/s */
    MPU9250_FS_SEL_500,                     /*!< 500 deg/s */
    MPU9250_FS_SEL_1000,                    /*!< 1000 deg/s */
    MPU9250_FS_SEL_2000,                    /*!< 2000 deg/s */
    MPU9250_FS_SEL_MAX
} mpu9250_fs_sel_t;

/**
 * @brief   AFS scale.
 */
typedef enum {
    MPU9250_AFS_SEL_2G = 0,                 /*!< 2g */
    MPU9250_AFS_SEL_4G,                     /*!< 4g */
    MPU9250_AFS_SEL_8G,                     /*!< 8g */
    MPU9250_AFS_SEL_16G,                    /*!< 16g */
    MPU9250_AFS_SEL_MAX
} mpu9250_afs_sel_t;

/**
 * @brief   Communication mode.
 */
typedef enum {
    MPU9250_COMM_MODE_I2C = 0,              /*!< Interface over I2C */
    MPU9250_COMM_MODE_SPI,                  /*!< Interface over SPI */
    MPU9250_COMM_MODE_MAX
} mpu9250_comm_mode_t;

/**
 * @brief   Configuration structure.
 */
typedef struct {
    mpu9250_clksel_t        clksel;         /*!< MPU9250 clock source */
    mpu9250_dlpf_cfg_t      dlpf_cfg;       /*!< MPU9250 digital low pass filter (DLPF) */
    mpu9250_sleep_mode_t    sleep_mode;     /*!< MPU9250 sleep mode */
    mpu9250_fs_sel_t        fs_sel;         /*!< MPU9250 gyroscope full scale range */
    mpu9250_afs_sel_t       afs_sel;        /*!< MPU9250 accelerometer full scale range */
    mpu9250_comm_mode_t     comm_mode;      /*!< Interface protocol */
    func_read_bytes         read_bytes;     /*!< MPU9250 read function */
    func_write_bytes        write_bytes;    /*!< MPU9250 write function */
} mpu9250_cfg_t;


#ifdef __cplusplus
}
#endif

#endif /* __MPU9250_PUBLIC_H__ */
