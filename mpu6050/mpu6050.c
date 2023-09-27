#include "stdlib.h"
#include "stddef.h"

#include "mpu6050_public.h"
#include "mpu6050_private.h"


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

#define MPU6050_ADDR                (0x68<<1)   /*!< MPU6050 Address */

#define MPU6050_INIT_TIMEOUT 		100
#define MPU6050_READ_TIMEOUT 		100
#define MPU6050_WRITE_TIMEOUT 		100


/**
 * @brief 	Handle structure.
 */
typedef struct mpu6050 {
	mpu6050_clksel_t        clksel;                 /*!< MPU6050 clock source */
	mpu6050_dlpf_cfg_t      dlpf_cfg;               /*!< MPU6050 digital low pass filter (DLPF) */
	mpu6050_sleep_mode_t    sleep_mode;             /*!< MPU6050 sleep mode */
	mpu6050_afs_sel_t       afs_sel;                /*!< MPU6050 accelerometer full scale range */
	mpu6050_gfs_sel_t       gfs_sel;                /*!< MPU6050 gyroscope full scale range */
	func_read_bytes         read_bytes;             /*!< MPU6050 read function */
	func_write_bytes        write_bytes;            /*!< MPU6050 write function */
} mpu6050_t;

/**
 * @brief 	MPU6050 handle structure.
 */
typedef struct mpu6050 *mpu6050_handle_t;

static mpu6050_handle_t mpu6050_handle = (void*)NULL;


err_code_t mpu6050_init(void)
{
	mpu6050_handle = calloc(1, sizeof(mpu6050_handle_t));

	if (mpu6050_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_set_config(mpu6050_cfg_t config)
{
	if (mpu6050_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	mpu6050_handle->afs_sel = config.afs_sel;
	mpu6050_handle->gfs_sel = config.gfs_sel;
	mpu6050_handle->clksel = config.clksel;
	mpu6050_handle->dlpf_cfg = config.dlpf_cfg;
	mpu6050_handle->sleep_mode = config.sleep_mode;
	mpu6050_handle->read_bytes = config.read_bytes;
	mpu6050_handle->write_bytes = config.write_bytes;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_config(void)
{
	if (mpu6050_handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err_ret = ERR_CODE_FAIL;

	/* Reset mpu6050 */
	uint8_t buffer = 0;
	buffer = 0x80;
	err_ret = mpu6050_handle->write_bytes(MPU6050_PWR_MGMT_1, &buffer, 1, MPU6050_INIT_TIMEOUT);
	/* Delay 100ms here if necessary */
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure clock source and sleep mode */
	buffer = mpu6050_handle->clksel & 0x07;
	buffer |= (mpu6050_handle->sleep_mode << 6) & 0x40;
	err_ret = mpu6050_handle->write_bytes(MPU6050_PWR_MGMT_1, &buffer, 1, MPU6050_INIT_TIMEOUT);
	/* Delay 100ms here if necessary */
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure digital low pass filter */
	buffer = 0;
	buffer = mpu6050_handle->dlpf_cfg & 0x07;
	err_ret = mpu6050_handle->write_bytes(MPU6050_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure gyroscope range */
	buffer = 0;
	buffer = (mpu6050_handle->gfs_sel << 3) & 0x18;
	err_ret = mpu6050_handle->write_bytes(MPU6050_GYRO_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure accelerometer range */
	buffer = 0;
	buffer = (mpu6050_handle->afs_sel << 3) & 0x18;
	err_ret = mpu6050_handle->write_bytes(MPU6050_ACCEL_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure sample rate divider */
	buffer = 0;
	buffer = 0x04;
	err_ret = mpu6050_handle->write_bytes(MPU6050_SMPLRT_DIV, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure interrupt and enable bypass.
	 * Set Interrupt pin active high, push-pull, Clear and read of INT_STATUS,
	 * enable I2C_BYPASS_EN in INT_PIN_CFG register so additional chips can
	 * join the I2C bus and can be controlled by master.
	 */
	buffer = 0x22;
	err_ret = mpu6050_handle->write_bytes(MPU6050_INT_PIN_CFG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	buffer = 0x01;
	err_ret = mpu6050_handle->write_bytes(MPU6050_INT_ENABLE, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_accel_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((mpu6050_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t accel_raw_data[6];

	err = mpu6050_handle->read_bytes(MPU6050_ACCEL_XOUT_H, accel_raw_data, 6, MPU6050_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]);
	*raw_y = (int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]);
	*raw_z = (int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_gyro_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((mpu6050_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t gyro_raw_data[6];

	err = mpu6050_handle->read_bytes(MPU6050_GYRO_XOUT_H, gyro_raw_data, 6, MPU6050_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]);
	*raw_y = (int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]);
	*raw_z = (int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_destroy()
{
	if (mpu6050_handle == NULL)
	{
		free(mpu6050_handle);
	}

	return ERR_CODE_SUCCESS;
}
