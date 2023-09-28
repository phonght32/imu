#ifndef __AK8963_PRIVATE_H__
#define __AK8963_PRIVATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"
#include "ak8963_public.h"

/*
 * @brief  	Initialize AK8963 with default parameters.
 *
 * @note 	This function must be called first.
 * 			To change default configuration, see "ak8963_set_config" function.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t ak8963_init(void);

/*
 * @brief   Set AK8963 's parameters such as operation mode, magnetometer full
 * 			scale, communication mode, etc,..
 * *
 * @param   config Configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t ak8963_set_config(ak8963_cfg_t config);

/*
 * @brief   Send control commands to target with configuration parameters.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t ak8963_config(void);

/*
 * @brief   Get magnetometer sensitive adjust data.
 *
 * @param   sens_adj_x Sensitive adjust data x axis.
 * @param   sens_adj_y Sensitive adjust data y axis.
 * @param   sens_adj_z Sensitive adjust data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t ak8963_get_sens_adj(float *sens_adj_x, float *sens_adj_y, float *sens_adj_z);

/*
 * @brief   Get magnetometer raw value.
 *
 * @param   raw_x Raw data x axis.
 * @param   raw_y Raw data y axis.
 * @param   raw_z Raw data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t ak8963_get_mag_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief  	Destroy AK8963.
 *
 * @param   None.
 *
 * @return
 *      - ERR_CODE_SUCCESS:	Success.
 *      - Others:   		Fail.
 */
err_code_t ak8963_destroy();

#ifdef __cplusplus
}
#endif

#endif /* __AK8963_PRIVATE_H__ */
