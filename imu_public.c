#include "stdlib.h"
#include "stddef.h"

#include "imu_public.h"
#include "mpu6500_private.h"
#include "ak8963_private.h"

typedef err_code_t (*func_get_accel)(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);
typedef err_code_t (*func_get_gyro)(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);
typedef err_code_t (*func_get_mag)(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

typedef struct imu {
	mpu_type_t 				mpu_type;
	imu_bias_data_t			accel_bias;
	imu_bias_data_t			gyro_bias;
	imu_mag_bias_data_t		mag_hard_iron_bias;
	imu_mag_bias_data_t		mag_soft_iron_bias;
	float 					accel_scaling_factor;
	float 					gyro_scaling_factor;
	float 					mag_scaling_factor;
	imu_mag_sens_adj_t 		mag_sens_adj;
	func_get_accel 			get_accel;
	func_get_gyro 			get_gyro;
	func_get_mag 			get_mag;
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
	handle->mag_hard_iron_bias = config.mag_hard_iron_bias;
	handle->mag_soft_iron_bias = config.mag_soft_iron_bias;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_config(imu_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	if ((handle->mpu_type & MPU_TYPE_MPU6500) != 0)
	{
		mpu6500_config();
	}

	if ((handle->mpu_type & MPU_TYPE_AK8963) != 0)
	{
		ak8963_config();
		ak8963_get_sens_adj(&handle->mag_sens_adj.sens_adj_x,
				&handle->mag_sens_adj.sens_adj_y,
				&handle->mag_sens_adj.sens_adj_z);
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_config_mpu6500(imu_handle_t handle, mpu6500_cfg_t mpu6500_cfg)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = mpu6500_init();
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	err = mpu6500_set_config(mpu6500_cfg);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	/* Update accelerometer scaling factor */
	switch (mpu6500_cfg.afs_sel)
	{
	case MPU6500_AFS_SEL_2G:
		handle->accel_scaling_factor = (2.0f / 32768.0f);
		break;

	case MPU6500_AFS_SEL_4G:
		handle->accel_scaling_factor = (4.0f / 32768.0f);
		break;

	case MPU6500_AFS_SEL_8G:
		handle->accel_scaling_factor = (8.0f / 32768.0f);
		break;

	case MPU6500_AFS_SEL_16G:
		handle->accel_scaling_factor = (16.0f / 32768.0f);
		break;

	default:
		break;
	}

	/* Update gyroscope scaling factor */
	switch (mpu6500_cfg.gfs_sel)
	{
	case MPU6500_FS_SEL_250:
		handle->gyro_scaling_factor = 250.0f / 32768.0f;
		break;

	case MPU6500_FS_SEL_500:
		handle->gyro_scaling_factor = 500.0f / 32768.0f;
		break;

	case MPU6500_FS_SEL_1000:
		handle->gyro_scaling_factor = 1000.0f / 32768.0f;
		break;

	case MPU6500_FS_SEL_2000:
		handle->gyro_scaling_factor = 2000.0f / 32768.0f;
		break;

	default:
		break;
	}

	handle->get_accel = mpu6500_get_accel_raw;
	handle->get_gyro = mpu6500_get_gyro_raw;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_config_ak8963(imu_handle_t handle, ak8963_cfg_t ak8963_cfg)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = ak8963_init();
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	err = ak8963_set_config(ak8963_cfg);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	/* Update magnetometer scaling factor */
	switch (ak8963_cfg.mfs_sel)
	{
	case AK8963_MFS_14BIT:
		handle->mag_scaling_factor = 10.0f * 4912.0f / 8190.0f;
		break;

	case AK8963_MFS_16BIT:
		handle->mag_scaling_factor = 10.0f * 4912.0f / 32760.0f;
		break;

	default:
		break;
	}

	handle->get_mag = ak8963_get_mag_raw;

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

err_code_t imu_get_mag_raw(imu_handle_t handle, imu_raw_data_t *raw_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = handle->get_mag(&raw_data->raw_x, &raw_data->raw_y, &raw_data->raw_z);
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

	calib_data->calib_x = raw_data.raw_x - handle->accel_bias.bias_x;
	calib_data->calib_y = raw_data.raw_y - handle->accel_bias.bias_y;
	calib_data->calib_z = raw_data.raw_z - handle->accel_bias.bias_z;

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

	calib_data->calib_x = raw_data.raw_x - handle->gyro_bias.bias_x;
	calib_data->calib_y = raw_data.raw_y - handle->gyro_bias.bias_y;
	calib_data->calib_z = raw_data.raw_z - handle->gyro_bias.bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_calib(imu_handle_t handle, imu_mag_calib_data_t *calib_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	imu_raw_data_t raw_data;

	err = handle->get_mag(&raw_data.raw_x, &raw_data.raw_y, &raw_data.raw_z);
	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	calib_data->calib_x = ((float)raw_data.raw_x * handle->mag_sens_adj.sens_adj_x - handle->mag_hard_iron_bias.bias_x / handle->mag_scaling_factor) * handle->mag_soft_iron_bias.bias_x;
	calib_data->calib_y = ((float)raw_data.raw_y * handle->mag_sens_adj.sens_adj_y - handle->mag_hard_iron_bias.bias_y / handle->mag_scaling_factor) * handle->mag_soft_iron_bias.bias_y;
	calib_data->calib_z = ((float)raw_data.raw_z * handle->mag_sens_adj.sens_adj_z - handle->mag_hard_iron_bias.bias_z / handle->mag_scaling_factor) * handle->mag_soft_iron_bias.bias_z;

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

	scale_data->scale_x = (raw_data.raw_x - handle->accel_bias.bias_x) * handle->accel_scaling_factor;
	scale_data->scale_y = (raw_data.raw_y - handle->accel_bias.bias_y) * handle->accel_scaling_factor;
	scale_data->scale_z = (raw_data.raw_z - handle->accel_bias.bias_z) * handle->accel_scaling_factor;

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

	scale_data->scale_x = (raw_data.raw_x - handle->gyro_bias.bias_x) * handle->gyro_scaling_factor;
	scale_data->scale_y = (raw_data.raw_y - handle->gyro_bias.bias_y) * handle->gyro_scaling_factor;
	scale_data->scale_z = (raw_data.raw_z - handle->gyro_bias.bias_z) * handle->gyro_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_scale(imu_handle_t handle, imu_scale_data_t *scale_data)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_data == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	imu_raw_data_t raw_data;

	err = handle->get_mag(&raw_data.raw_x, &raw_data.raw_y, &raw_data.raw_z);
	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	scale_data->scale_x = ((float)raw_data.raw_x * handle->mag_sens_adj.sens_adj_x * handle->mag_scaling_factor - handle->mag_hard_iron_bias.bias_x) * handle->mag_soft_iron_bias.bias_x;
	scale_data->scale_y = ((float)raw_data.raw_y * handle->mag_sens_adj.sens_adj_y * handle->mag_scaling_factor - handle->mag_hard_iron_bias.bias_y) * handle->mag_soft_iron_bias.bias_y;
	scale_data->scale_z = ((float)raw_data.raw_z * handle->mag_sens_adj.sens_adj_z * handle->mag_scaling_factor - handle->mag_hard_iron_bias.bias_z) * handle->mag_soft_iron_bias.bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_accel_bias(imu_handle_t handle, imu_bias_data_t bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->accel_bias = bias_data;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_gyro_bias(imu_handle_t handle, imu_bias_data_t bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->gyro_bias = bias_data;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_mag_hard_iron_bias(imu_handle_t handle, imu_mag_bias_data_t bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->mag_hard_iron_bias = bias_data;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_mag_soft_iron_bias(imu_handle_t handle, imu_mag_bias_data_t bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->mag_soft_iron_bias = bias_data;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_hard_iron_bias(imu_handle_t handle, imu_mag_bias_data_t *bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_data = handle->mag_hard_iron_bias;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_soft_iron_bias(imu_handle_t handle, imu_mag_bias_data_t *bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_data = handle->mag_soft_iron_bias;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_sensitive_adjust(imu_handle_t handle, imu_mag_sens_adj_t *sens_adj)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	*sens_adj = handle->mag_sens_adj;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_bias(imu_handle_t handle, imu_bias_data_t *bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_data = handle->accel_bias;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_bias(imu_handle_t handle, imu_bias_data_t *bias_data)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_data = handle->gyro_bias;

	return ERR_CODE_SUCCESS;
}
