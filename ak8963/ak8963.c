#include "stdlib.h"
#include "stddef.h"

#include "ak8963_private.h"
#include "ak8963_public.h"
#include "ak8963_register.h"


#define AK8963_INIT_TIMEOUT 		100
#define AK8963_READ_TIMEOUT 		100
#define AK8963_WRITE_TIMEOUT 		100

/**
 * @brief 	Handle structure.
 */
typedef struct ak8963 {
	ak8963_mode_t               opr_mode;               /*!< AK8963 operatkion mode */
	ak8963_mfs_sel_t            mfs_sel;                /*!< AK8963 magnetometer full scale range */
	func_read_bytes         	read_bytes;     		/*!< Read function */
	func_write_bytes        	write_bytes;    		/*!< Write function */
	func_delay                  delay;          		/*!< Delay function */
} ak8963_t;

/**
 * @brief 	AK8963 handle structure.
 */
typedef struct ak8963 *ak8963_handle_t;

static ak8963_handle_t ak8963_handle = (void*)NULL;

err_code_t ak8963_init(void)
{
	ak8963_handle = calloc(1, sizeof(ak8963_t));

	if (ak8963_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t ak8963_set_config(ak8963_cfg_t config)
{
	if (ak8963_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	ak8963_handle->opr_mode = config.opr_mode;
	ak8963_handle->mfs_sel = config.mfs_sel;
	ak8963_handle->read_bytes = config.read_bytes;
	ak8963_handle->write_bytes = config.write_bytes;
	ak8963_handle->delay = config.delay;

	return ERR_CODE_SUCCESS;
}

err_code_t ak8963_config(void)
{
	if (ak8963_handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err_ret = ERR_CODE_FAIL;

	/* Power down AK8963 magnetic sensor */
	uint8_t buffer = 0;
	buffer = 0x00;
	err_ret = ak8963_handle->write_bytes(AK8963_CNTL, &buffer, 1, AK8963_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 10ms here if necessary */
	ak8963_handle->delay(10);

	/* Set fuse ROM access mode */
	buffer = 0x0F;
	err_ret = ak8963_handle->write_bytes(AK8963_CNTL, &buffer, 1, AK8963_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 10ms here if necessary */
	ak8963_handle->delay(10);

	/* Power down AK8963 magnetic sensor */
	buffer = 0x00;
	err_ret = ak8963_handle->write_bytes(AK8963_CNTL, &buffer, 1, AK8963_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Delay 10ms here if necessary */
	ak8963_handle->delay(10);

	/* Configure magnetic operation mode and range */
	buffer = 0;
	buffer = (ak8963_handle->opr_mode) & 0x0F;
	buffer |= (ak8963_handle->mfs_sel << 4) & 0x10;
	err_ret = ak8963_handle->write_bytes(AK8963_CNTL, &buffer, 1, AK8963_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t ak8963_get_mag_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((ak8963_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err_ret;
	uint8_t mag_raw_data[7];

	err_ret = ak8963_handle->read_bytes(AK8963_XOUT_L, mag_raw_data, 7, AK8963_READ_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS) {
		return err_ret;
	}

	if ((mag_raw_data[6] & 0x08)) {
		return ERR_CODE_FAIL;
	}

	*raw_x = (int16_t)((int16_t)(mag_raw_data[1] << 8) | mag_raw_data[0]);
	*raw_y = (int16_t)((int16_t)(mag_raw_data[3] << 8) | mag_raw_data[2]);
	*raw_z = (int16_t)((int16_t)(mag_raw_data[5] << 8) | mag_raw_data[4]);

	return ERR_CODE_SUCCESS;
}

err_code_t ak8963_get_sens_adj(float *sens_adj_x, float *sens_adj_y, float *sens_adj_z)
{
	if ((ak8963_handle == NULL) || (sens_adj_x == NULL) || (sens_adj_y == NULL) || (sens_adj_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err_ret;
	uint8_t mag_raw_data[3];

	/* Read magnetic sensitivity adjustment */
	err_ret = ak8963_handle->write_bytes(AK8963_ASAX, mag_raw_data, 3, AK8963_INIT_TIMEOUT);
	if (err_ret != ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	*sens_adj_x = (float)(mag_raw_data[0] - 128) / 256.0f + 1.0f;
	*sens_adj_y = (float)(mag_raw_data[1] - 128) / 256.0f + 1.0f;
	*sens_adj_z = (float)(mag_raw_data[2] - 128) / 256.0f + 1.0f;

	return ERR_CODE_SUCCESS;
}

err_code_t ak8963_destroy()
{
	if (ak8963_handle == NULL)
	{
		free(ak8963_handle);
	}

	return ERR_CODE_SUCCESS;
}
