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

#ifndef _IMU_PUBLIC_H_
#define _IMU_PUBLIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"
#include "mpu9250_public.h"

typedef struct imu* imu_handle_t;

/**
 * @brief   IMU raw data.
 */
typedef struct {
    int16_t raw_x;
    int16_t raw_y;
    int16_t raw_z;
} imu_raw_data_t;

/**
 * @brief   IMU scaled data.
 */
typedef struct {
    float scale_x;
    float scale_y;
    float scale_z;
} imu_scale_data_t;

/**
 * @brief   IMU calibrated data.
 */
typedef struct {
    int16_t calib_x;
    int16_t calib_y;
    int16_t calib_z;
} imu_calib_data_t;

/**
 * @brief   IMU accelerometer bias
 */
typedef struct {
    int16_t accel_bias_x;
    int16_t accel_bias_y;
    int16_t accel_bias_z;
} imu_accel_bias_t;

/**
 * @brief   IMU gyroscope bias
 */
typedef struct {
    int16_t gyro_bias_x;
    int16_t gyro_bias_y;
    int16_t gyro_bias_z;
} imu_gyro_bias_t;

typedef enum {
    MPU_TYPE_MPU6050 = 1,
    MPU_TYPE_MPU9250 = 2,
    MPU_TYPE_MAX
} mpu_type_t;

typedef struct {
    mpu_type_t          mpu_type;
    imu_accel_bias_t    accel_bias;
    imu_gyro_bias_t     gyro_bias;
} imu_cfg_t;

/*
 * @brief   Initialize IMU with default parameters.
 *
 * @note    This function must be called first.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_init(void);

/*
 * @brief   Set IMU's parameters.
 *
 * @param   handle Handle structure.
 * @param   config Configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_config(imu_handle_t handle, imu_cfg_t config);

/*
 * @brief   Configure IMU.
 *
 * @param   handle IMU handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_config(imu_handle_t handle);

/*
 * @brief   Configure MPU9250 parameters.
 *
 * @param   handle IMU handle structure.
 * @param   mpu9250_cfg MPU9250 configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_config_mpu9250(imu_handle_t handle, mpu9250_cfg_t mpu9250_cfg);


#ifdef __cplusplus
}
#endif

#endif /* _IMU_PUBLIC_H_ */
