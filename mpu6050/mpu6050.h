#ifndef __MPU6050_PRIVATE_H__
#define __MPU6050_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"
#include "imu.h"


/**
 * @brief   Clock selection.
 */
typedef enum {
    MPU6050_CLKSEL_INTERNAL_8_MHZ = 0,      /*!< Internal 8 MHz oscillator */
    MPU6050_CLKSEL_X_GYRO_REF,              /*!< PLL with X axis gyroscope reference */
    MPU6050_CLKSEL_Y_GYRO_REF,              /*!< PLL with Y axis gyroscope reference */
    MPU6050_CLKSEL_Z_GYRO_REF,              /*!< PLL with Z axis gyroscope reference */
    MPU6050_CLKSEL_EXTERNAL_32_768_KHZ,     /*!< PLL with eternal 32.768 KHz reference */
    MPU6050_CLKSEL_EXTERNAL_19_2_MHZ,       /*!< PLL with external 19.2 MHz reference */
    MPU6050_TIM_GEN_RESET = 7,              /*!< Stops the clock and keeps the timing generator in reset */
    MPU6050_CLKSEL_MAX
} mpu6050_clksel_t;

/**
 * @brief   Low pass filter.
 */
typedef enum {
    MPU6050_260ACCEL_256GYRO_BW_HZ = 0,     /*!< 260 Hz accelerometer bandwidth, 256 Hz gyroscope bandwidth */
    MPU6050_184ACCEL_188GYRO_BW_HZ,         /*!< 184 Hz accelerometer bandwidth, 188 Hz gyroscope bandwidth */
    MPU6050_94ACCEL_98GYRO_BW_HZ,           /*!< 94 Hz accelerometer bandwidth, 98 Hz gyroscope bandwidth */
    MPU6050_44ACCEL_42GYRO_BW_HZ,           /*!< 44 Hz accelerometer bandwidth, 42 Hz gyroscope bandwidth */
    MPU6050_21ACCEL_20GYRO_BW_HZ,           /*!< 21 Hz accelerometer bandwidth, 20 Hz gyroscope bandwidth */
    MPU6050_10ACCEL_10GYRO_BW_HZ,           /*!< 10 Hz accelerometer bandwidth, 10 Hz gyroscope bandwidth */
    MPU6050_5ACCEL_5GYRO_BW_HZ,             /*!< 5 Hz accelerometer bandwidth, 5 Hz gyroscope bandwidth */
    MPU6050_DLPF_CFG_MAX
} mpu6050_dlpf_cfg_t;

/**
 * @brief   Sleep mode.
 */
typedef enum {
    MPU6050_DISABLE_SLEEP_MODE = 0,         /*!< Disable sleep mode */
    MPU6050_LOW_PWR_SLEEP_MODE,             /*!< Low power mode */
    MPU6050_SLEEP_MODE_MAX
} mpu6050_sleep_mode_t;

/**
 * @brief   Gyroscope full scale.
 */
typedef enum {
    MPU6050_GFS_SEL_250 = 0,                /*!< 250 deg/s */
    MPU6050_GFS_SEL_500,                    /*!< 500 deg/s */
    MPU6050_GFS_SEL_1000,                   /*!< 1000 deg/s */
    MPU6050_GFS_SEL_2000,                   /*!< 2000 deg/s */
    MPU6050_GFS_SEL_MAX
} mpu6050_gfs_sel_t;

/**
 * @brief   Accelerometer full scale.
 */
typedef enum {
    MPU6050_AFS_SEL_2G = 0,                 /*!< 2g */
    MPU6050_AFS_SEL_4G,                     /*!< 4g */
    MPU6050_AFS_SEL_8G,                     /*!< 8g */
    MPU6050_AFS_SEL_16G,                    /*!< 16g */
    MPU6050_AFS_SEL_MAX
} mpu6050_afs_sel_t;

/*
 * @brief   Send control commands to target with configuration parameters.
 *
 * @param   read_bytes Function read bytes.
 * @param   write_bytes Function write bytes.
 * @param   delay Function delay.
 * @param   clksel Clock source.
 * @param   dlpf_cfg Low-pass filter.
 * @param   sleep_mode Sleep mode.
 * @param   afs_sel Accelerometer full scale.
 * @param   gfs_sel Gyroscope full scale.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_init(imu_func_read_bytes read_bytes,
                        imu_func_write_bytes write_bytes,
                        imu_func_delay delay,
                        mpu6050_clksel_t clksel,
                        mpu6050_dlpf_cfg_t dlpf_cfg,
                        mpu6050_sleep_mode_t sleep_mode,
                        mpu6050_afs_sel_t afs_sel,
                        mpu6050_gfs_sel_t gfs_sel);

/*
 * @brief   Get accelerometer raw value.
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
err_code_t mpu6050_get_accel_raw(imu_func_read_bytes read_bytes,
                                 int16_t *raw_x,
                                 int16_t *raw_y,
                                 int16_t *raw_z);

/*
 * @brief   Get gyroscope raw value.
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
err_code_t mpu6050_get_gyro_raw(imu_func_read_bytes read_bytes,
                                int16_t *raw_x,
                                int16_t *raw_y,
                                int16_t *raw_z);


#ifdef __cplusplus
}
#endif

#endif /* __MPU6050_PRIVATE_H__ */
