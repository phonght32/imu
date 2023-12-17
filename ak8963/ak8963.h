#ifndef __AK8963_PRIVATE_H__
#define __AK8963_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"
#include "imu.h"

/**
 * @brief   Mode selection.
 */
typedef enum {
    AK8963_MODE_PWR_DOWN = 0x00,                /*!< AK8963 mode power down */
    AK8963_MODE_SINGLE_MEASUREMENT = 0x01,      /*!< AK8963 mode single measurement */
    AK8963_MODE_CONT_MEASUREMENT_1 = 0x02,      /*!< AK8963 mode continous measurement 1 */
    AK8963_MODE_EXT_TRIG_MEASUREMENT = 0x04,    /*!< AK8963 mode external trigger measurement */
    AK8963_MODE_CONT_MEASUREMENT_2 = 0x06,      /*!< AK8963 mode continous measurement 2 */
    AK8963_MODE_SELF_TEST = 0x08,               /*!< AK8963 mode self test */
    AK8963_MODE_FUSE_ROM_ACCESS = 0x0F,         /*!< AK8963 mode fuse ROM access */
    AK8963_MODE_MAX
} ak8963_mode_t;

/**
 * @brief   Magnetometer full scale.
 */
typedef enum {
    AK8963_MFS_14BIT = 0,                       /*!< Magnetometer 14 bit resolution  */
    AK8963_MFS_16BIT,                           /*!< Magnetometer 16 bit resolution  */
    AK8963_MFS_MAX
} ak8963_mfs_sel_t;

/*
 * @brief   Send control commands to target with configuration parameters.
 *
 * @param   read_bytes Function read bytes.
 * @param   write_bytes Function write bytes.
 * @param   delay Function delay.
 * @param   opr_mode Operation mode.
 * @param   mfs_sel Magnetometer full scale select.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ak8963_init(imu_func_read_bytes read_bytes,
					   imu_func_write_bytes write_bytes,
					   imu_func_delay delay,
                       ak8963_mode_t opr_mode,
                       ak8963_mfs_sel_t mfs_sel);

/*
 * @brief   Get magnetometer sensitive adjust data.
 *
 * @param   read_bytes Function read bytes.
 * @param   sens_adj_x Sensitive adjust data x axis.
 * @param   sens_adj_y Sensitive adjust data y axis.
 * @param   sens_adj_z Sensitive adjust data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ak8963_get_sens_adj(imu_func_read_bytes read_bytes, float *sens_adj_x, float *sens_adj_y, float *sens_adj_z);

/*
 * @brief   Get magnetometer raw value.
 *
 * @param   read_bytes Function read bytes.
 * @param   raw_x Raw data x axis.
 * @param   raw_y Raw data y axis.
 * @param   raw_z Raw data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t ak8963_get_mag_raw(imu_func_read_bytes read_bytes, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

#ifdef __cplusplus
}
#endif

#endif /* __AK8963_PRIVATE_H__ */
