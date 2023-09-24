#include "stdlib.h"
#include "stddef.h"

#include "mpu9250_private.h"
#include "imu_public.h"

typedef err_code_t (*func_get_accel)(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);
typedef err_code_t (*func_get_gyro)(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

typedef struct imu {
	mpu_type_t 			mpu_type;
	imu_accel_bias_t	accel_bias;
	imu_gyro_bias_t		gyro_bias;
	float 				accel_scaling_factor;
	float 				gyro_scaling_factor;
	func_get_accel 		get_accel;
	func_get_gyro 		get_gyro;
} imu_t;

err_code_t imu_init(void)
{
	imu_handle_t imu_handle = calloc(1, sizeof(imu_handle_t));

	/* Check if handle structure is NULL */
	if (imu_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_config(imu_handle_t handle, imu_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	handle->mpu_type = config.mpu_type;
	handle->accel_bias = config.accel_bias;
	handle->gyro_bias = config.gyro_bias;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_config(imu_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	if ((handle->mpu_type & MPU_TYPE_MPU9250) != 0)
	{
		mpu9250_config();
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_config_mpu9250(imu_handle_t handle, mpu9250_cfg_t mpu9250_cfg)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = mpu9250_init();
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	err = mpu9250_set_config(mpu9250_cfg);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	/* Update accelerometer scaling factor */
	switch (mpu9250_cfg.afs_sel)
	{
	case MPU9250_AFS_SEL_2G:
		handle->accel_scaling_factor = (2.0f / 32768.0f);
		break;

	case MPU9250_AFS_SEL_4G:
		handle->accel_scaling_factor = (4.0f / 32768.0f);
		break;

	case MPU9250_AFS_SEL_8G:
		handle->accel_scaling_factor = (8.0f / 32768.0f);
		break;

	case MPU9250_AFS_SEL_16G:
		handle->accel_scaling_factor = (16.0f / 32768.0f);
		break;

	default:
		break;
	}

	/* Update gyroscope scaling factor */
	switch (mpu9250_cfg.fs_sel)
	{
	case MPU9250_FS_SEL_250:
		handle->gyro_scaling_factor = 250.0f / 32768.0f;
		break;

	case MPU9250_FS_SEL_500:
		handle->gyro_scaling_factor = 500.0f / 32768.0f;
		break;

	case MPU9250_FS_SEL_1000:
		handle->gyro_scaling_factor = 1000.0f / 32768.0f;
		break;

	case MPU9250_FS_SEL_2000:
		handle->gyro_scaling_factor = 2000.0f / 32768.0f;
		break;

	default:
		break;
	}

	handle->get_accel = mpu9250_get_accel_raw;
	handle->get_gyro = mpu9250_get_gyro_raw;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_raw(imu_handle_t handle, imu_raw_data_t *raw_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = handle->get_accel(&raw_data->raw_x, &raw_data->raw_y, &raw_data->raw_z);

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_raw(imu_handle_t handle, imu_raw_data_t *raw_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = handle->get_gyro(&raw_data->raw_x, &raw_data->raw_y, &raw_data->raw_z);

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_calib(imu_handle_t handle, imu_calib_data_t *calib_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	imu_raw_data_t raw_data;

	err = handle->get_accel(&raw_data.raw_x, &raw_data.raw_y, &raw_data.raw_z);

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	calib_data->calib_x = raw_data.raw_x - handle->accel_bias.accel_bias_x;
	calib_data->calib_y = raw_data.raw_y - handle->accel_bias.accel_bias_y;
	calib_data->calib_z = raw_data.raw_z - handle->accel_bias.accel_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_calib(imu_handle_t handle, imu_calib_data_t *calib_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	imu_raw_data_t raw_data;

	err = handle->get_gyro(&raw_data.raw_x, &raw_data.raw_y, &raw_data.raw_z);

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	calib_data->calib_x = raw_data.raw_x - handle->gyro_bias.gyro_bias_x;
	calib_data->calib_y = raw_data.raw_y - handle->gyro_bias.gyro_bias_y;
	calib_data->calib_z = raw_data.raw_z - handle->gyro_bias.gyro_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_scale(imu_handle_t handle, imu_scale_data_t *scale_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	imu_raw_data_t raw_data;

	err = handle->get_accel(&raw_data.raw_x, &raw_data.raw_y, &raw_data.raw_z);

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	scale_data->scale_x = (raw_data.raw_x - handle->accel_bias.accel_bias_x) * handle->accel_scaling_factor;
	scale_data->scale_y = (raw_data.raw_y - handle->accel_bias.accel_bias_y) * handle->accel_scaling_factor;
	scale_data->scale_z = (raw_data.raw_z - handle->accel_bias.accel_bias_z) * handle->accel_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_scale(imu_handle_t handle, imu_scale_data_t *scale_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	imu_raw_data_t raw_data;

	err = handle->get_gyro(&raw_data.raw_x, &raw_data.raw_y, &raw_data.raw_z);

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	scale_data->scale_x = (raw_data.raw_x - handle->gyro_bias.gyro_bias_x) * handle->gyro_scaling_factor;
	scale_data->scale_y = (raw_data.raw_y - handle->gyro_bias.gyro_bias_y) * handle->gyro_scaling_factor;
	scale_data->scale_z = (raw_data.raw_z - handle->gyro_bias.gyro_bias_z) * handle->gyro_scaling_factor;

	return ERR_CODE_SUCCESS;
}
