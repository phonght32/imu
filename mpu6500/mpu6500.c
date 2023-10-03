#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"

#include "err_code.h"
#include "mpu6500_private.h"
#include "mpu6500_public.h"
#include "mpu6500_register.h"


#define MPU6500_INIT_TIMEOUT 			100
#define MPU6500_READ_TIMEOUT 			100
#define MPU6500_WRITE_TIMEOUT 			100


/**
 * @brief 	Handle structure.
 */
typedef struct mpu6500 {
	mpu6500_clksel_t        clksel;                 /*!< MPU6500 clock source */
	mpu6500_dlpf_cfg_t      dlpf_cfg;               /*!< MPU6500 digital low pass filter (DLPF) */
	mpu6500_sleep_mode_t    sleep_mode;             /*!< MPU6500 sleep mode */
	mpu6500_afs_sel_t       afs_sel;                /*!< MPU6500 accelerometer full scale range */
	mpu6500_gfs_sel_t       gfs_sel;                /*!< MPU6500 gyroscope full scale range */
	func_read_bytes         read_bytes;             /*!< MPU6500 read function */
	func_write_bytes        write_bytes;            /*!< MPU6500 write function */
	func_delay              delay;          		/*!< MPU6500 delay function */
} mpu6500_t;

/**
 * @brief 	MPU6500 handle structure.
 */
typedef struct mpu6500 *mpu6500_handle_t;

static mpu6500_handle_t mpu6500_handle = (void*)NULL;


err_code_t mpu6500_init(void)
{
	mpu6500_handle = calloc(1, sizeof(mpu6500_t));

	if (mpu6500_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6500_set_config(mpu6500_cfg_t config)
{
	if (mpu6500_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	mpu6500_handle->afs_sel = config.afs_sel;
	mpu6500_handle->gfs_sel = config.gfs_sel;
	mpu6500_handle->clksel = config.clksel;
	mpu6500_handle->dlpf_cfg = config.dlpf_cfg;
	mpu6500_handle->sleep_mode = config.sleep_mode;
	mpu6500_handle->read_bytes = config.read_bytes;
	mpu6500_handle->write_bytes = config.write_bytes;
	mpu6500_handle->delay = config.delay;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6500_config(void)
{
	if (mpu6500_handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err_ret = ERR_CODE_FAIL;

	/* Reset mpu6500 */
	uint8_t buffer = 0;
	buffer = 0x80;
	err_ret = mpu6500_handle->write_bytes(MPU6500_PWR_MGMT_1, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 100ms here if necessary */
	mpu6500_handle->delay(100);

	/* Configure clock source and sleep mode */
	buffer = mpu6500_handle->clksel & 0x07;
	buffer |= (mpu6500_handle->sleep_mode << 6) & 0x40;
	err_ret = mpu6500_handle->write_bytes(MPU6500_PWR_MGMT_1, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 100ms here if necessary */
	mpu6500_handle->delay(100);

	/* Configure digital low pass filter */
	buffer = 0;
	buffer = mpu6500_handle->dlpf_cfg & 0x07;
	err_ret = mpu6500_handle->write_bytes(MPU6500_CONFIG, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure gyroscope range */
	buffer = 0;
	buffer = (mpu6500_handle->gfs_sel << 3) & 0x18;
	err_ret = mpu6500_handle->write_bytes(MPU6500_GYRO_CONFIG, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure accelerometer range */
	buffer = 0;
	buffer = (mpu6500_handle->afs_sel << 3) & 0x18;
	err_ret = mpu6500_handle->write_bytes(MPU6500_ACCEL_CONFIG, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure sample rate divider */
	buffer = 0;
	buffer = 0x04;
	err_ret = mpu6500_handle->write_bytes(MPU6500_SMPLRT_DIV, &buffer, 1, MPU6500_INIT_TIMEOUT);
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
	err_ret = mpu6500_handle->write_bytes(MPU6500_INT_PIN_CFG, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	buffer = 0x01;
	err_ret = mpu6500_handle->write_bytes(MPU6500_INT_ENABLE, &buffer, 1, MPU6500_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6500_get_accel_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((mpu6500_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t accel_raw_data[6];

	err = mpu6500_handle->read_bytes(MPU6500_ACCEL_XOUT_H, accel_raw_data, 6, MPU6500_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]);
	*raw_y = (int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]);
	*raw_z = (int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6500_get_gyro_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((mpu6500_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t gyro_raw_data[6];

	err = mpu6500_handle->read_bytes(MPU6500_GYRO_XOUT_H, gyro_raw_data, 6, MPU6500_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]);
	*raw_y = (int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]);
	*raw_z = (int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6500_destroy()
{
	if (mpu6500_handle == NULL)
	{
		free(mpu6500_handle);
	}

	return ERR_CODE_SUCCESS;
}
