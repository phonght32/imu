#include "stdlib.h"
#include "stddef.h"

#include "hw_define.h"
#include "imu.h"

#define AK8963_OPR_MODE  			AK8963_MODE_CONT_MEASUREMENT_2
#define AK8963_MFS_SEL  			AK8963_MFS_16BIT

#define MPU6050_CLKSEL  			MPU6050_CLKSEL_X_GYRO_REF
#define MPU6050_DLPF_CFG  			MPU6050_44ACCEL_42GYRO_BW_HZ
#define MPU6050_SLEEP_MODE  		MPU6050_DISABLE_SLEEP_MODE
#define MPU6050_GFS_SEL  			MPU6050_GFS_SEL_2000
#define MPU6050_AFS_SEL   			MPU6050_AFS_SEL_8G

#define MPU6500_CLKSEL  			MPU6500_CLKSEL_AUTO
#define MPU6500_DLPF_CFG  			MPU6500_41ACEL_42GYRO_BW_HZ
#define MPU6500_SLEEP_MODE  		MPU6500_DISABLE_SLEEP_MODE
#define MPU6500_GFS_SEL  			MPU6500_GFS_SEL_2000
#define MPU6500_AFS_SEL   			MPU6500_AFS_SEL_8G

#define BUFFER_CALIB_DEFAULT 		1000


#ifdef USE_MPU6050
#include "mpu6050/mpu6050.h"
#endif

#ifdef USE_MPU6500
#include "mpu6500/mpu6500.h"
#endif

#ifdef USE_AK8963
#include "ak8963/ak8963.h"
#endif


typedef struct imu {
	int16_t    				accel_bias_x;
	int16_t    				accel_bias_y;
	int16_t    				accel_bias_z;
	int16_t   				gyro_bias_x;
	int16_t   				gyro_bias_y;
	int16_t   				gyro_bias_z;
	float 					mag_hard_iron_bias_x;
	float 					mag_hard_iron_bias_y;
	float 					mag_hard_iron_bias_z;
	float 					mag_soft_iron_bias_x;
	float 					mag_soft_iron_bias_y;
	float 					mag_soft_iron_bias_z;
	float 					accel_scaling_factor;
	float 					gyro_scaling_factor;
	float 					mag_scaling_factor;
	float  					mag_sens_adj_x;
	float  					mag_sens_adj_y;
	float  					mag_sens_adj_z;
	imu_func_delay 			func_delay;
	imu_func_read_bytes 	ak8963_read_bytes;
	imu_func_write_bytes 	ak8963_write_bytes;
	imu_func_read_bytes 	mpu6050_read_bytes;
	imu_func_write_bytes 	mpu6050_write_bytes;
	imu_func_read_bytes 	mpu6500_read_bytes;
	imu_func_write_bytes 	mpu6500_write_bytes;
} imu_t;

#ifdef USE_AK8963
static err_code_t imu_config_ak8963(imu_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = ak8963_init(handle->ak8963_read_bytes,
	                  handle->ak8963_write_bytes,
	                  handle->func_delay,
	                  AK8963_OPR_MODE,
	                  AK8963_MFS_SEL);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	ak8963_get_sens_adj(handle->ak8963_read_bytes,
	                    &handle->mag_sens_adj_x,
	                    &handle->mag_sens_adj_y,
	                    &handle->mag_sens_adj_z);

	/* Update magnetometer scaling factor */
	switch (AK8963_MFS_SEL)
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

	return ERR_CODE_SUCCESS;
}
#endif

#ifdef USE_MPU6050
static err_code_t imu_config_mpu6050(imu_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = mpu6050_init(handle->mpu6050_read_bytes,
	                   handle->mpu6050_write_bytes,
	                   handle->func_delay,
	                   MPU6050_CLKSEL,
	                   MPU6050_DLPF_CFG,
	                   MPU6050_SLEEP_MODE,
	                   MPU6050_AFS_SEL,
	                   MPU6050_GFS_SEL);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	/* Update accelerometer scaling factor */
	switch (MPU6050_AFS_SEL)
	{
	case MPU6050_AFS_SEL_2G:
		handle->accel_scaling_factor = (2.0f / 32768.0f);
		break;

	case MPU6050_AFS_SEL_4G:
		handle->accel_scaling_factor = (4.0f / 32768.0f);
		break;

	case MPU6050_AFS_SEL_8G:
		handle->accel_scaling_factor = (8.0f / 32768.0f);
		break;

	case MPU6050_AFS_SEL_16G:
		handle->accel_scaling_factor = (16.0f / 32768.0f);
		break;

	default:
		break;
	}

	/* Update gyroscope scaling factor */
	switch (MPU6050_GFS_SEL)
	{
	case MPU6050_GFS_SEL_250:
		handle->gyro_scaling_factor = 250.0f / 32768.0f;
		break;

	case MPU6050_GFS_SEL_500:
		handle->gyro_scaling_factor = 500.0f / 32768.0f;
		break;

	case MPU6050_GFS_SEL_1000:
		handle->gyro_scaling_factor = 1000.0f / 32768.0f;
		break;

	case MPU6050_GFS_SEL_2000:
		handle->gyro_scaling_factor = 2000.0f / 32768.0f;
		break;

	default:
		break;
	}

	return ERR_CODE_SUCCESS;
}
#endif

#ifdef USE_MPU6500
static err_code_t imu_config_mpu6500(imu_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

	err = mpu6500_init(handle->mpu6500_read_bytes,
	                   handle->mpu6500_write_bytes,
	                   handle->func_delay,
	                   MPU6500_CLKSEL,
	                   MPU6500_DLPF_CFG,
	                   MPU6500_SLEEP_MODE,
	                   MPU6500_AFS_SEL,
	                   MPU6500_GFS_SEL);
	if (err != ERR_CODE_SUCCESS)
	{
		return ERR_CODE_FAIL;
	}

	/* Update accelerometer scaling factor */
	switch (MPU6500_AFS_SEL)
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
	switch (MPU6500_GFS_SEL)
	{
	case MPU6500_GFS_SEL_250:
		handle->gyro_scaling_factor = 250.0f / 32768.0f;
		break;

	case MPU6500_GFS_SEL_500:
		handle->gyro_scaling_factor = 500.0f / 32768.0f;
		break;

	case MPU6500_GFS_SEL_1000:
		handle->gyro_scaling_factor = 1000.0f / 32768.0f;
		break;

	case MPU6500_GFS_SEL_2000:
		handle->gyro_scaling_factor = 2000.0f / 32768.0f;
		break;

	default:
		break;
	}

	return ERR_CODE_SUCCESS;
}
#endif

imu_handle_t imu_init(void)
{
	imu_handle_t imu_handle = calloc(1, sizeof(imu_t));

	/* Check if handle structure is NULL */
	if (imu_handle == NULL)
	{
		return NULL;
	}

	return imu_handle;
}

err_code_t imu_set_config(imu_handle_t handle, imu_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	handle->accel_bias_x = config.accel_bias_x;
	handle->accel_bias_y = config.accel_bias_y;
	handle->accel_bias_z = config.accel_bias_z;
	handle->gyro_bias_x = config.gyro_bias_x;
	handle->gyro_bias_y = config.gyro_bias_y;
	handle->gyro_bias_z = config.gyro_bias_z;
	handle->mag_hard_iron_bias_x = config.mag_hard_iron_bias_x;
	handle->mag_hard_iron_bias_y = config.mag_hard_iron_bias_y;
	handle->mag_hard_iron_bias_z = config.mag_hard_iron_bias_z;
	handle->mag_soft_iron_bias_x = config.mag_soft_iron_bias_x;
	handle->mag_soft_iron_bias_y = config.mag_soft_iron_bias_y;
	handle->mag_soft_iron_bias_z = config.mag_soft_iron_bias_z;
	handle->func_delay = config.func_delay;
	handle->ak8963_read_bytes = config.ak8963_read_bytes;
	handle->ak8963_write_bytes = config.ak8963_write_bytes;
	handle->mpu6050_read_bytes = config.mpu6050_read_bytes;
	handle->mpu6050_write_bytes = config.mpu6050_write_bytes;
	handle->mpu6500_read_bytes = config.mpu6500_read_bytes;
	handle->mpu6500_write_bytes = config.mpu6500_write_bytes;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_config(imu_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

#ifdef USE_MPU6050
	imu_config_mpu6050(handle);
#endif

#ifdef USE_MPU6500
	imu_config_mpu6500(handle);
#endif

#ifdef USE_AK8963
	imu_config_ak8963(handle);
#endif

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_raw(imu_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

#ifdef USE_MPU6050
	err = mpu6050_get_accel_raw(handle->mpu6050_read_bytes, raw_x, raw_y, raw_z);
#endif

#ifdef USE_MPU6500
	err = mpu6500_get_accel_raw(handle->mpu6500_read_bytes, raw_x, raw_y, raw_z);
#endif

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_calib(imu_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_x == NULL) || (calib_y == NULL) || (calib_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	int16_t raw_x, raw_y, raw_z;

#ifdef USE_MPU6050
	err = mpu6050_get_accel_raw(handle->mpu6050_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

#ifdef USE_MPU6500
	err = mpu6500_get_accel_raw(handle->mpu6500_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	*calib_x = raw_x - handle->accel_bias_x;
	*calib_y = raw_y - handle->accel_bias_y;
	*calib_z = raw_z - handle->accel_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_scale(imu_handle_t handle, float *scale_x, float *scale_y, float *scale_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_x == NULL) || (scale_y == NULL) || (scale_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	int16_t raw_x, raw_y, raw_z;

#ifdef USE_MPU6050
	err = mpu6050_get_accel_raw(handle->mpu6050_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

#ifdef USE_MPU6500
	err = mpu6500_get_accel_raw(handle->mpu6500_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	*scale_x = (raw_x - handle->accel_bias_x) * handle->accel_scaling_factor;
	*scale_y = (raw_y - handle->accel_bias_y) * handle->accel_scaling_factor;
	*scale_z = (raw_z - handle->accel_bias_z) * handle->accel_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_raw(imu_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;

#ifdef USE_MPU6050
	err = mpu6050_get_gyro_raw(handle->mpu6050_read_bytes, raw_x, raw_y, raw_z);
#endif

#ifdef USE_MPU6500
	err = mpu6500_get_gyro_raw(handle->mpu6500_read_bytes, raw_x, raw_y, raw_z);
#endif

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_calib(imu_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_x == NULL) || (calib_y == NULL) || (calib_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	int16_t raw_x, raw_y, raw_z;

#ifdef USE_MPU6050
	err = mpu6050_get_gyro_raw(handle->mpu6050_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

#ifdef USE_MPU6500
	err = mpu6500_get_gyro_raw(handle->mpu6500_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	*calib_x = raw_x - handle->gyro_bias_x;
	*calib_y = raw_y - handle->gyro_bias_y;
	*calib_z = raw_z - handle->gyro_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_scale(imu_handle_t handle, float *scale_x, float *scale_y, float *scale_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_x == NULL) || (scale_y == NULL) || (scale_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	int16_t raw_x, raw_y, raw_z;

#ifdef USE_MPU6050
	err = mpu6050_get_gyro_raw(handle->mpu6050_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

#ifdef USE_MPU6500
	err = mpu6500_get_gyro_raw(handle->mpu6500_read_bytes, &raw_x, &raw_y, &raw_z);
#endif

	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}

	*scale_x = (raw_x - handle->gyro_bias_x) * handle->gyro_scaling_factor;
	*scale_y = (raw_y - handle->gyro_bias_y) * handle->gyro_scaling_factor;
	*scale_z = (raw_z - handle->gyro_bias_z) * handle->gyro_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_raw(imu_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

#ifdef USE_AK8963
	err_code_t err;
	err = ak8963_get_mag_raw(handle->ak8963_read_bytes, raw_x, raw_y, raw_z);
	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}
#endif

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_calib(imu_handle_t handle, float *calib_x, float *calib_y, float *calib_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_x == NULL) || (calib_y == NULL) || (calib_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	int16_t raw_x = 0, raw_y = 0, raw_z = 0;

#ifdef USE_AK8963
	err_code_t err;
	err = ak8963_get_mag_raw(handle->ak8963_read_bytes, &raw_x, &raw_y, &raw_z);
	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}
#endif

	*calib_x = ((float)raw_x * handle->mag_sens_adj_x - handle->mag_hard_iron_bias_x / handle->mag_scaling_factor) * handle->mag_soft_iron_bias_x;
	*calib_y = ((float)raw_y * handle->mag_sens_adj_y - handle->mag_hard_iron_bias_y / handle->mag_scaling_factor) * handle->mag_soft_iron_bias_y;
	*calib_z = ((float)raw_z * handle->mag_sens_adj_z - handle->mag_hard_iron_bias_z / handle->mag_scaling_factor) * handle->mag_soft_iron_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_scale(imu_handle_t handle, float *scale_x, float *scale_y, float *scale_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_x == NULL) || (scale_y == NULL) || (scale_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	int16_t raw_x = 0, raw_y = 0, raw_z = 0;

#ifdef USE_AK8963
	err_code_t err;
	err = ak8963_get_mag_raw(handle->ak8963_read_bytes, &raw_x, &raw_y, &raw_z);
	if (err != ERR_CODE_SUCCESS) {
		return ERR_CODE_FAIL;
	}
#endif

	*scale_x = ((float)raw_x * handle->mag_sens_adj_x * handle->mag_scaling_factor - handle->mag_hard_iron_bias_x) * handle->mag_soft_iron_bias_x;
	*scale_y = ((float)raw_y * handle->mag_sens_adj_y * handle->mag_scaling_factor - handle->mag_hard_iron_bias_y) * handle->mag_soft_iron_bias_y;
	*scale_z = ((float)raw_z * handle->mag_sens_adj_z * handle->mag_scaling_factor - handle->mag_hard_iron_bias_z) * handle->mag_soft_iron_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_accel_bias(imu_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->accel_bias_x = bias_x;
	handle->accel_bias_y = bias_y;
	handle->accel_bias_z = bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_gyro_bias(imu_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->gyro_bias_x = bias_x;
	handle->gyro_bias_y = bias_y;
	handle->gyro_bias_z = bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_mag_hard_iron_bias(imu_handle_t handle, float bias_x, float bias_y, float bias_z)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->mag_hard_iron_bias_x = bias_x;
	handle->mag_hard_iron_bias_y = bias_y;
	handle->mag_hard_iron_bias_z = bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_set_mag_soft_iron_bias(imu_handle_t handle, float bias_x, float bias_y, float bias_z)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->mag_soft_iron_bias_x = bias_x;
	handle->mag_soft_iron_bias_y = bias_y;
	handle->mag_soft_iron_bias_z = bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_accel_bias(imu_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (bias_x == NULL) || (bias_y == NULL) || (bias_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_x = handle->accel_bias_x;
	*bias_y = handle->accel_bias_y;
	*bias_z = handle->accel_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_gyro_bias(imu_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (bias_x == NULL) || (bias_y == NULL) || (bias_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_x = handle->gyro_bias_x;
	*bias_y = handle->gyro_bias_y;
	*bias_z = handle->gyro_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_hard_iron_bias(imu_handle_t handle, float *bias_x, float *bias_y, float *bias_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (bias_x == NULL) || (bias_y == NULL) || (bias_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_x = handle->mag_hard_iron_bias_x;
	*bias_y = handle->mag_hard_iron_bias_y;
	*bias_z = handle->mag_hard_iron_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_get_mag_soft_iron_bias(imu_handle_t handle, float *bias_x, float *bias_y, float *bias_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (bias_x == NULL) || (bias_y == NULL) || (bias_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_x = handle->mag_soft_iron_bias_x;
	*bias_y = handle->mag_soft_iron_bias_y;
	*bias_z = handle->mag_soft_iron_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t imu_auto_calib(imu_handle_t handle)
{
	int buffersize = BUFFER_CALIB_DEFAULT;
    int mean_ax, mean_ay, mean_az, mean_gx, mean_gy, mean_gz;
    long i = 0, buff_ax = 0, buff_ay = 0, buff_az = 0, buff_gx = 0, buff_gy = 0, buff_gz = 0;

    while (i < (buffersize + 101))                  /*!< Dismiss 100 first value */
    {
    	int16_t accel_raw_x, accel_raw_y, accel_raw_z;
    	int16_t gyro_raw_x, gyro_raw_y, gyro_raw_z;

#ifdef USE_MPU6050
    	mpu6050_get_accel_raw(handle->mpu6050_read_bytes, &accel_raw_x, &accel_raw_y, &accel_raw_z);
    	mpu6050_get_gyro_raw(handle->mpu6050_read_bytes, &gyro_raw_x, &gyro_raw_y, &gyro_raw_z);
#endif

#ifdef USE_MPU6500
    	mpu6500_get_accel_raw(handle->mpu6500_read_bytes, &accel_raw_x, &accel_raw_y, &accel_raw_z);
    	mpu6500_get_gyro_raw(handle->mpu6500_read_bytes, &gyro_raw_x, &gyro_raw_y, &gyro_raw_z);
#endif

        if (i > 100 && i <= (buffersize + 100))
        {
            buff_ax += accel_raw_x;
            buff_ay += accel_raw_y;
            buff_az += accel_raw_z;
            buff_gx += gyro_raw_x;
            buff_gy += gyro_raw_y;
            buff_gz += gyro_raw_z;
        }
        if (i == (buffersize + 100))
        {
            mean_ax = buff_ax / buffersize;
            mean_ay = buff_ay / buffersize;
            mean_az = buff_az / buffersize;
            mean_gx = buff_gx / buffersize;
            mean_gy = buff_gy / buffersize;
            mean_gz = buff_gz / buffersize;
        }
        i++;
    }

    handle->accel_bias_x = mean_ax;
    handle->accel_bias_y = mean_ay;
    handle->accel_bias_z = mean_az - 1.0f / handle->accel_scaling_factor;
    handle->gyro_bias_x = mean_gx;
    handle->gyro_bias_y = mean_gy;
    handle->gyro_bias_z = mean_gz;

    return ERR_CODE_SUCCESS;
}
