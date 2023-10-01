#ifndef __MPU6500_PUBLIC_H__
#define __MPU6500_PUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

typedef err_code_t (*func_read_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);
typedef err_code_t (*func_write_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);

/**
 * @brief   Clock source select.
 */
typedef enum {
    MPU6500_CLKSEL_INTERNAL_20_MHZ = 0,     /*!< Internal 20 MHz clock source */
    MPU6500_CLKSEL_AUTO,                    /*!< Auto select available clock source */
    MPU6500_CLKSEL_MAX
} mpu6500_clksel_t;

/**
 * @brief   Bandwidth select.
 */
typedef enum {
    MPU6500_250ACEL_4000GYRO_BW_HZ = 0,     /*!< 250 Hz accelerometer bandwidth, 4000 Hz gyroscope bandwidth */
    MPU6500_184ACEL_188GYRO_BW_HZ,          /*!< 184 Hz accelerometer bandwidth, 188 Hz gyroscope bandwidth */
    MPU6500_92ACEL_98GYRO_BW_HZ,            /*!< 92 Hz accelerometer bandwidth, 98 Hz gyroscope bandwidth */
    MPU6500_41ACEL_42GYRO_BW_HZ,            /*!< 41 Hz accelerometer bandwidth, 42 Hz gyroscope bandwidth */
    MPU6500_20ACEL_20GYRO_BW_HZ,            /*!< 20 Hz accelerometer bandwidth, 20 Hz gyroscope bandwidth */
    MPU6500_10ACEL_10GYRO_BW_HZ,            /*!< 10 Hz accelerometer bandwidth, 10 Hz gyroscope bandwidth */
    MPU6500_5ACEL_5GYRO_BW_HZ,              /*!< 5 Hz accelerometer bandwidth, 5 Hz gyroscope bandwidth */
    MPU6500_DLPF_CFG_MAX
} mpu6500_dlpf_cfg_t;

/**
 * @brief   Sleep mode.
 */
typedef enum {
    MPU6500_DISABLE_SLEEP_MODE = 0,         /*!< Disable sleep mode */
    MPU6500_LOW_PWR_SLEEP_MODE,             /*!< Low power mode */
    MPU6500_SLEEP_MODE_MAX
} mpu6500_sleep_mode_t;

/**
 * @brief   FS scale.
 */
typedef enum {
    MPU6500_GFS_SEL_250 = 0,                /*!< 250 deg/s */
    MPU6500_GFS_SEL_500,                    /*!< 500 deg/s */
    MPU6500_GFS_SEL_1000,                   /*!< 1000 deg/s */
    MPU6500_GFS_SEL_2000,                   /*!< 2000 deg/s */
    MPU6500_GFS_SEL_MAX
} mpu6500_gfs_sel_t;

/**
 * @brief   AFS scale.
 */
typedef enum {
    MPU6500_AFS_SEL_2G = 0,                 /*!< 2g */
    MPU6500_AFS_SEL_4G,                     /*!< 4g */
    MPU6500_AFS_SEL_8G,                     /*!< 8g */
    MPU6500_AFS_SEL_16G,                    /*!< 16g */
    MPU6500_AFS_SEL_MAX
} mpu6500_afs_sel_t;

/**
 * @brief   Configuration structure.
 */
typedef struct {
    mpu6500_clksel_t        clksel;         /*!< MPU6500 clock source */
    mpu6500_dlpf_cfg_t      dlpf_cfg;       /*!< MPU6500 digital low pass filter (DLPF) */
    mpu6500_sleep_mode_t    sleep_mode;     /*!< MPU6500 sleep mode */
    mpu6500_gfs_sel_t       gfs_sel;        /*!< MPU6500 gyroscope full scale range */
    mpu6500_afs_sel_t       afs_sel;        /*!< MPU6500 accelerometer full scale range */
    func_read_bytes         read_bytes;     /*!< MPU6500 read function */
    func_write_bytes        write_bytes;    /*!< MPU6500 write function */
} mpu6500_cfg_t;


#ifdef __cplusplus
}
#endif

#endif /* __MPU6500_PUBLIC_H__ */
