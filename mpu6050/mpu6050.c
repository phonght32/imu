#include "stdlib.h"
#include "stddef.h"

#include "mpu6050_public.h"
#include "mpu6050_private.h"
#include "mpu6050_register.h"

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
	func_delay  			delay; 					/*!< MPU6050 delay function */
} mpu6050_t;

/**
 * @brief 	MPU6050 handle structure.
 */
typedef struct mpu6050 *mpu6050_handle_t;

static mpu6050_handle_t mpu6050_handle = (void*)NULL;


err_code_t mpu6050_init(void)
{
	mpu6050_handle = calloc(1, sizeof(mpu6050_t));

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
	mpu6050_handle->delay = config.delay;

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
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 100ms here if necessary */
	mpu6050_handle->delay(100);

	/* Configure clock source and sleep mode */
	buffer = mpu6050_handle->clksel & 0x07;
	buffer |= (mpu6050_handle->sleep_mode << 6) & 0x40;
	err_ret = mpu6050_handle->write_bytes(MPU6050_PWR_MGMT_1, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 100ms here if necessary */
	mpu6050_handle->delay(100);

	/* Configure digital low pass filter */
	buffer = 0;
	buffer = mpu6050_handle->dlpf_cfg & 0x07;
	err_ret = mpu6050_handle->write_bytes(MPU6050_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure gyroscope range */
	buffer = 0;
	buffer = (mpu6050_handle->gfs_sel << 3) & 0x18;
	err_ret = mpu6050_handle->write_bytes(MPU6050_GYRO_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure accelerometer range */
	buffer = 0;
	buffer = (mpu6050_handle->afs_sel << 3) & 0x18;
	err_ret = mpu6050_handle->write_bytes(MPU6050_ACCEL_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure sample rate divider */
	buffer = 0;
	buffer = 0x04;
	err_ret = mpu6050_handle->write_bytes(MPU6050_SMPLRT_DIV, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
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
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	buffer = 0x01;
	err_ret = mpu6050_handle->write_bytes(MPU6050_INT_ENABLE, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
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
