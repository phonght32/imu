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
#include "mpu6500_public.h"
#include "ak8963_public.h"

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
 * @brief   IMU calibrated data.
 */
typedef struct {
    int16_t calib_x;
    int16_t calib_y;
    int16_t calib_z;
} imu_calib_data_t;

/**
 * @brief   IMU magnetometer calibrated data.
 */
typedef struct {
    float calib_x;
    float calib_y;
    float calib_z;
} imu_mag_calib_data_t;

/**
 * @brief   IMU scaled data.
 */
typedef struct {
    float scale_x;
    float scale_y;
    float scale_z;
} imu_scale_data_t;

/**
 * @brief   IMU bias data structure.
 */
typedef struct {
    int16_t bias_x;
    int16_t bias_y;
    int16_t bias_z;
} imu_bias_data_t;

/**
 * @brief   IMU magnetometer bias data structure.
 */
typedef struct {
    float bias_x;
    float bias_y;
    float bias_z;
} imu_mag_bias_data_t;

/**
 * @brief   IMU magnetometer sensitive adjust data structure.
 */
typedef struct {
    float sens_adj_x;
    float sens_adj_y;
    float sens_adj_z;
} imu_mag_sens_adj_t;


/**
 * @brief	Sensor type.
 */
typedef enum {
    MPU_TYPE_MPU6050 = 1,
    MPU_TYPE_MPU6500 = 2,
	MPU_TYPE_AK8963 = 3,
    MPU_TYPE_MAX
} mpu_type_t;

/**
 * @brief   IMU configuration structure.
 */
typedef struct {
    mpu_type_t          mpu_type;
    imu_bias_data_t    	accel_bias;
    imu_bias_data_t   	gyro_bias;
    imu_mag_bias_data_t mag_hard_iron_bias;
    imu_mag_bias_data_t mag_soft_iron_bias;
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
 * @brief   Configure MPU6500 parameters.
 *
 * @param   handle IMU handle structure.
 * @param   mpu6500_cfg MPU6500 configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_config_mpu6500(imu_handle_t handle, mpu6500_cfg_t mpu6500_cfg);

/*
 * @brief   Configure AK8963 parameters.
 *
 * @param   handle IMU handle structure.
 * @param   ak8963_cfg AK8963 configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_config_ak8963(imu_handle_t handle, ak8963_cfg_t ak8963_cfg);

/*
 * @brief   Get accelerometer raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_data Raw data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_raw(imu_handle_t handle, imu_raw_data_t *raw_data);

/*
 * @brief   Get gyroscope raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_data Raw data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_raw(imu_handle_t handle, imu_raw_data_t *raw_data);

/*
 * @brief   Get magnetometer raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_data Raw data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_raw(imu_handle_t handle, imu_raw_data_t *raw_data);

/*
 * @brief   Get accelerometer calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_data Calibrated data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_calib(imu_handle_t handle, imu_calib_data_t *calib_data);

/*
 * @brief   Get gyroscope calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_data Calibrated data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_calib(imu_handle_t handle, imu_calib_data_t *calib_data);

/*
 * @brief   Get magnetometer calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_data Calibrated data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_calib(imu_handle_t handle, imu_mag_calib_data_t *calib_data);

/*
 * @brief   Get accelerometer scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_data Scaled data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_scale(imu_handle_t handle, imu_scale_data_t *scale_data);

/*
 * @brief   Get gyroscope scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_data Scaled data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_scale(imu_handle_t handle, imu_scale_data_t *scale_data);

/*
 * @brief   Get magnetometer scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_data Scaled data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_scale(imu_handle_t handle, imu_scale_data_t *scale_data);

/*
 * @brief   Set accelerometer bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Accelerometer bias value.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_accel_bias(imu_handle_t handle, imu_bias_data_t bias_data);

/*
 * @brief   Set gyroscope bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Gyroscope bias value.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_gyro_bias(imu_handle_t handle, imu_bias_data_t bias_data);

/*
 * @brief   Set magnetometer hard iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Mgnetometer hard iron bias value.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_mag_hard_iron_bias(imu_handle_t handle, imu_mag_bias_data_t bias_data);

/*
 * @brief   Set magnetometer soft iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Mgnetometer soft iron bias value.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_mag_soft_iron_bias(imu_handle_t handle, imu_mag_bias_data_t bias_data);

/*
 * @brief   Get magnetometer hard iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Mgnetometer hard iron bias value.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_hard_iron_bias(imu_handle_t handle, imu_mag_bias_data_t *bias_data);

/*
 * @brief   Get magnetometer soft iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Mgnetometer soft iron bias value.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_soft_iron_bias(imu_handle_t handle, imu_mag_bias_data_t *bias_data);

/*
 * @brief   Get magnetometer sensitive adjust data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Mgnetometer sensitive adjust data.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_sensitive_adjust(imu_handle_t handle, imu_mag_sens_adj_t *sens_adj);

/*
 * @brief   Get accelerometer bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Data pointer.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_bias(imu_handle_t handle, imu_bias_data_t *bias_data);

/*
 * @brief   Get gyroscope bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_data Data pointer.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_bias(imu_handle_t handle, imu_bias_data_t *bias_data);


#ifdef __cplusplus
}
#endif

#endif /* _IMU_PUBLIC_H_ */
