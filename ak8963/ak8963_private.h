// MIT License

// Copyright (c) 2023 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
