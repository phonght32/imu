#include "stdlib.h"
#include "stddef.h"

#include "mpu9250_private.h"
#include "imu_public.h"

typedef struct imu {
	mpu_type_t 			mpu_type;
	imu_accel_bias_t	accel_bias;
	imu_gyro_bias_t		gyro_bias;
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

	return ERR_CODE_SUCCESS;
}
