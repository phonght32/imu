#include "stdlib.h"
#include "stddef.h"

#include "mpu6050/mpu6050.h"
#include "mpu6050/mpu6050_register.h"


#define MPU6050_INIT_TIMEOUT 		100
#define MPU6050_READ_TIMEOUT 		100
#define MPU6050_WRITE_TIMEOUT 		100


err_code_t mpu6050_init(imu_func_read_bytes read_bytes,
                        imu_func_write_bytes write_bytes,
                        imu_func_delay delay,
                        mpu6050_clksel_t clksel,
                        mpu6050_dlpf_cfg_t dlpf_cfg,
                        mpu6050_sleep_mode_t sleep_mode,
                        mpu6050_afs_sel_t afs_sel,
                        mpu6050_gfs_sel_t gfs_sel)
{
	err_code_t err_ret = ERR_CODE_FAIL;

	/* Reset mpu6050 */
	uint8_t buffer = 0;
	buffer = 0x80;
	err_ret = write_bytes(MPU6050_PWR_MGMT_1, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 100ms here if necessary */
	delay(100);

	/* Configure clock source and sleep mode */
	buffer = clksel & 0x07;
	buffer |= (sleep_mode << 6) & 0x40;
	err_ret = write_bytes(MPU6050_PWR_MGMT_1, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 100ms here if necessary */
	delay(100);

	/* Configure digital low pass filter */
	buffer = 0;
	buffer = dlpf_cfg & 0x07;
	err_ret = write_bytes(MPU6050_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure gyroscope range */
	buffer = 0;
	buffer = (gfs_sel << 3) & 0x18;
	err_ret = write_bytes(MPU6050_GYRO_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure accelerometer range */
	buffer = 0;
	buffer = (afs_sel << 3) & 0x18;
	err_ret = write_bytes(MPU6050_ACCEL_CONFIG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure sample rate divider */
	buffer = 0;
	buffer = 0x04;
	err_ret = write_bytes(MPU6050_SMPLRT_DIV, &buffer, 1, MPU6050_INIT_TIMEOUT);
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
	err_ret = write_bytes(MPU6050_INT_PIN_CFG, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	buffer = 0x01;
	err_ret = write_bytes(MPU6050_INT_ENABLE, &buffer, 1, MPU6050_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_accel_raw(imu_func_read_bytes read_bytes,
                                 int16_t *raw_x,
                                 int16_t *raw_y,
                                 int16_t *raw_z)
{
	if ((raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t accel_raw_data[6];

	err = read_bytes(MPU6050_ACCEL_XOUT_H, accel_raw_data, 6, MPU6050_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]);
	*raw_y = (int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]);
	*raw_z = (int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_gyro_raw(imu_func_read_bytes read_bytes,
                                int16_t *raw_x,
                                int16_t *raw_y,
                                int16_t *raw_z)
{
	if ((raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t gyro_raw_data[6];

	err = read_bytes(MPU6050_GYRO_XOUT_H, gyro_raw_data, 6, MPU6050_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]);
	*raw_y = (int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]);
	*raw_z = (int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

