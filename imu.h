#ifndef _IMU_PUBLIC_H_
#define _IMU_PUBLIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"
#include "imu_intf.h"

typedef struct imu* imu_handle_t;

/**
 * @brief   IMU configuration structure.
 */
typedef struct {
    int16_t             accel_bias_x;
    int16_t             accel_bias_y;
    int16_t             accel_bias_z;
    int16_t             gyro_bias_x;
    int16_t             gyro_bias_y;
    int16_t             gyro_bias_z;
    float               mag_hard_iron_bias_x;
    float               mag_hard_iron_bias_y;
    float               mag_hard_iron_bias_z;
    float               mag_soft_iron_bias_x;
    float               mag_soft_iron_bias_y;
    float               mag_soft_iron_bias_z;
    func_delay          func_delay;
    func_read_bytes     ak8963_read_bytes;
    func_write_bytes    ak8963_write_bytes;
    func_read_bytes     mpu6050_read_bytes;
    func_write_bytes    mpu6050_write_bytes;
    func_read_bytes     mpu6500_read_bytes;
    func_write_bytes    mpu6500_write_bytes;
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
imu_handle_t imu_init(void);

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
 * @brief   Get accelerometer raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_x Raw value x axis.
 * @param   raw_y Raw value y axis.
 * @param   raw_z Raw value z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_raw(imu_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief   Get accelerometer calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_x Calibrated data x axis.
 * @param   calib_y Calibrated data y axis.
 * @param   calib_z Calibrated data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_calib(imu_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z);

/*
 * @brief   Get accelerometer scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_x Scaled data x axis.
 * @param   scale_y Scaled data y axis.
 * @param   scale_z Scaled data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_scale(imu_handle_t handle, float *scale_x, float *scale_y, float *scale_z);

/*
 * @brief   Get gyroscope raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_x Raw value x axis.
 * @param   raw_y Raw value y axis.
 * @param   raw_z Raw value z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_raw(imu_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief   Get gyroscope calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_x Calibrated data x axis.
 * @param   calib_y Calibrated data y axis.
 * @param   calib_z Calibrated data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_calib(imu_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z);

/*
 * @brief   Get gyroscope scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_x Scaled data x axis.
 * @param   scale_y Scaled data y axis.
 * @param   scale_z Scaled data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_scale(imu_handle_t handle, float *scale_x, float *scale_y, float *scale_z);

/*
 * @brief   Get magnetometer raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_x Raw value x axis.
 * @param   raw_y Raw value y axis.
 * @param   raw_z Raw value z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_raw(imu_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief   Get magnetometer calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_x Calibrated data x axis.
 * @param   calib_y Calibrated data y axis.
 * @param   calib_z Calibrated data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_calib(imu_handle_t handle, float *calib_x, float *calib_y, float *calib_z);

/*
 * @brief   Get magnetometer scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_x Scaled data x axis.
 * @param   scale_y Scaled data y axis.
 * @param   scale_z Scaled data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_scale(imu_handle_t handle, float *scale_x, float *scale_y, float *scale_z);

/*
 * @brief   Set accelerometer bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_accel_bias(imu_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z);

/*
 * @brief   Set gyroscope bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_gyro_bias(imu_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z);

/*
 * @brief   Set magnetometer hard iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_mag_hard_iron_bias(imu_handle_t handle, float bias_x, float bias_y, float bias_z);

/*
 * @brief   Set magnetometer soft iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_set_mag_soft_iron_bias(imu_handle_t handle, float bias_x, float bias_y, float bias_z);

/*
 * @brief   Get accelerometer bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_accel_bias(imu_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z);

/*
 * @brief   Get gyroscope bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_gyro_bias(imu_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z);

/*
 * @brief   Get magnetometer hard iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_hard_iron_bias(imu_handle_t handle, float *bias_x, float *bias_y, float *bias_z);

/*
 * @brief   Get magnetometer soft iron bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_get_mag_soft_iron_bias(imu_handle_t handle, float *bias_x, float *bias_y, float *bias_z);

/*
 * @brief   Auto calibrate all acceleromter and gyroscope bias value.
 *
 * @param   handle Handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t imu_auto_calib(imu_handle_t handle);

#ifdef __cplusplus
}
#endif

#endif /* _IMU_PUBLIC_H_ */
