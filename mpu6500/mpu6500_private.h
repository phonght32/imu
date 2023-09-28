#ifndef __MPU6500_PRIVATE_H__
#define __MPU6500_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mpu6500_public.h"

/*
 * @brief  	Initialize MPU6500 with default parameters.
 *
 * @note 	This function must be called first.
 * 			To change default configuration, see "mpu6500_set_config" function.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t mpu6500_init(void);

/*
 * @brief   Set MPU6500 's parameters such as clock source, digital low
 * 			pass filter (DLPF), sleep mode, gyroscope and accelerometer full
 * 			scale range, bias value, ...
 *
 * @param   config Configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t mpu6500_set_config(mpu6500_cfg_t config);

/*
 * @brief   Send control commands to target with configuration parameters.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t mpu6500_config(void);

/*
 * @brief   Get accelerometer raw value.
 *
 * @param   raw_x Raw data x axis.
 * @param   raw_y Raw data y axis.
 * @param   raw_z Raw data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t mpu6500_get_accel_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief   Get gyroscope raw value.
 *
 * @param   raw_x Raw data x axis.
 * @param   raw_y Raw data y axis.
 * @param   raw_z Raw data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t mpu6500_get_gyro_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief  	Destroy MPU6500.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t mpu6500_destroy();


#ifdef __cplusplus
}
#endif

#endif /* __MPU6500_PRIVATE_H__ */
