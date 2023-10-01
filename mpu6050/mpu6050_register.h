#ifndef __MPU6050_REGISTER_H__
#define __MPU6050_REGISTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MPU6050_ADDR                0x68   		/*!< MPU6050 Address */


#define MPU6050_SELF_TEST_X         0x0D        /*!< SELF TEST REGISTERS */
#define MPU6050_SELF_TEST_Y         0x0E
#define MPU6050_SELF_TEST_Z         0x0F
#define MPU6050_SELF_TEST_A         0x10
#define MPU6050_SMPLRT_DIV          0x19        /*!< Sample rate diveider */
#define MPU6050_CONFIG              0x1A        /*!< Configuration */
#define MPU6050_GYRO_CONFIG         0x1B        /*!< Gyroscope configuration */
#define MPU6050_ACCEL_CONFIG        0x1C        /*!< Accelerometer configuration */
#define MPU6050_FIFO_EN             0x23        /*!< FIFO enable */
#define MPU6050_I2C_MST_CTRL        0x24        /*!< I2C master control */
#define MPU6050_I2C_SLV0_ADDR       0x25        /*!< I2C slave 0 control */
#define MPU6050_I2C_SLV0_REG        0x26
#define MPU6050_I2C_SLV0_CTRL       0x27
#define MPU6050_I2C_SLV1_ADDR       0x28        /*!< I2C slave 1 control  */
#define MPU6050_I2C_SLV1_REG        0x29
#define MPU6050_I2C_SLV1_CTRL       0x2A
#define MPU6050_I2C_SLV2_ADDR       0x2B        /*!< I2C slave 2 control */
#define MPU6050_I2C_SLV2_REG        0x2C
#define MPU6050_I2C_SLV2_CTRL       0x2D
#define MPU6050_I2C_SLV3_ADDR       0x2E        /*!< I2C slave 3 control */
#define MPU6050_I2C_SLV3_REG        0x2F
#define MPU6050_I2C_SLV3_CTRL       0x30
#define MPU6050_I2C_SLV4_ADDR       0x31        /*!< I2C slave 4 control */
#define MPU6050_I2C_SLV4_REG        0x32
#define MPU6050_I2C_SLV4_DO         0x33
#define MPU6050_I2C_SLV4_CTRL       0x34
#define MPU6050_I2C_SLV4_DI         0x35
#define MPU6050_I2C_MST_STATUS      0x36        /*!< I2C master status */
#define MPU6050_INT_PIN_CFG         0x37        /*!< I2C interrupt pin/bypass enable configuration */
#define MPU6050_INT_ENABLE          0x38        /*!< Interrupt enable */
#define MPU6050_INT_STATUS          0x3A        /*!< Interrupt status */
#define MPU6050_ACCEL_XOUT_H        0x3B        /*!< Accelerometer measurements */
#define MPU6050_ACCEL_XOUT_L        0x3C
#define MPU6050_ACCEL_YOUT_H        0x3D
#define MPU6050_ACCEL_YOUT_L        0x3E
#define MPU6050_ACCEL_ZOUT_H        0x3F
#define MPU6050_ACCEL_ZOUT_L        0x40
#define MPU6050_TEMP_OUT_H          0x41        /*!< Temperature measurements */
#define MPU6050_TEMP_OUT_L          0x42
#define MPU6050_GYRO_XOUT_H         0x43        /*!< Gyroscope measurements */
#define MPU6050_GYRO_XOUT_L         0x44
#define MPU6050_GYRO_YOUT_H         0x45
#define MPU6050_GYRO_YOUT_L         0x46
#define MPU6050_GYRO_ZOUT_H         0x47
#define MPU6050_GYRO_ZOUT_L         0x48
#define MPU6050_EXT_SENS_DATA_00    0x49        /*!< External sensor data */
#define MPU6050_EXT_SENS_DATA_01    0x4A
#define MPU6050_EXT_SENS_DATA_02    0x4B
#define MPU6050_EXT_SENS_DATA_03    0x4C
#define MPU6050_EXT_SENS_DATA_04    0x4D
#define MPU6050_EXT_SENS_DATA_05    0x4E
#define MPU6050_EXT_SENS_DATA_06    0x4F
#define MPU6050_EXT_SENS_DATA_07    0x50
#define MPU6050_EXT_SENS_DATA_08    0x51
#define MPU6050_EXT_SENS_DATA_09    0x52
#define MPU6050_EXT_SENS_DATA_10    0x53
#define MPU6050_EXT_SENS_DATA_11    0x54
#define MPU6050_EXT_SENS_DATA_12    0x55
#define MPU6050_EXT_SENS_DATA_13    0x56
#define MPU6050_EXT_SENS_DATA_14    0x57
#define MPU6050_EXT_SENS_DATA_15    0x58
#define MPU6050_EXT_SENS_DATA_16    0x59
#define MPU6050_EXT_SENS_DATA_17    0x5A
#define MPU6050_EXT_SENS_DATA_18    0x5B
#define MPU6050_EXT_SENS_DATA_19    0x5C
#define MPU6050_EXT_SENS_DATA_20    0x5D
#define MPU6050_EXT_SENS_DATA_21    0x5E
#define MPU6050_EXT_SENS_DATA_22    0x5F
#define MPU6050_EXT_SENS_DATA_23    0x60
#define MPU6050_I2C_SLV0_D0         0x63        /*!< I2C slave 0 data out */
#define MPU6050_I2C_SLV1_D0         0x64        /*!< I2C slave 1 data out */
#define MPU6050_I2C_SLV2_D0         0x65        /*!< I2C slave 2 data out */
#define MPU6050_I2C_SLV3_D0         0x66        /*!< I2C slave 3 data out */
#define MPU6050_I2C_MST_DELAY_CTRL  0x67        /*!< I2C master delay control */
#define MPU6050_SIGNAL_PATH_RESET   0x68        /*!< Signal path reset */
#define MPU6050_USER_CTRL           0x6A        /*!< User control */
#define MPU6050_PWR_MGMT_1          0x6B        /*!< Power management 1 */
#define MPU6050_PWR_MGMT_2          0x6C        /*!< Power management 2 */
#define MPU6050_FIFO_COUNTH         0x72        /*!< FIFO counter registers */
#define MPU6050_FIRO_COUNTL         0x73
#define MPU6050_FIRO_R_W            0x74        /*!< FIFO read write */
#define MPU6050_WHO_AM_I            0x75        /*!< Who am I */


#ifdef __cplusplus
}
#endif

#endif /* __MPU6050_REGISTER_H__ */