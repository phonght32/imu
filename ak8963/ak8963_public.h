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

#ifndef __AK8963_PUBLIC_H__
#define __AK8963_PUBLIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"


typedef uint8_t (*func_read_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);
typedef uint8_t (*func_write_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);


/**
 * @brief   Mode selection.
 */
typedef enum {
    AK8963_MODE_PWR_DOWN = 0x00,                /*!< AK8963 mode power down */
    AK8963_MODE_SINGLE_MEASUREMENT = 0x01,      /*!< AK8963 mode single measurement */
    AK8963_MODE_CONT_MEASUREMENT_1 = 0x02,      /*!< AK8963 mode continous measurement 1 */
    AK8963_MODE_EXT_TRIG_MEASUREMENT = 0x04,    /*!< AK8963 mode external trigger measurement */
    AK8963_MODE_CONT_MEASUREMENT_2 = 0x06,      /*!< AK8963 mode continous measurement 2 */
    AK8963_MODE_SELF_TEST = 0x08,               /*!< AK8963 mode self test */
    AK8963_MODE_FUSE_ROM_ACCESS = 0x0F,         /*!< AK8963 mode fuse ROM access */
    AK8963_MODE_MAX
} ak8963_mode_t;

/**
 * @brief   Magnetometer full scale.
 */
typedef enum {
    AK8963_MFS_14BIT = 0,                       /*!< Magnetometer 14 bit resolution  */
    AK8963_MFS_16BIT,                           /*!< Magnetometer 16 bit resolution  */
    AK8963_MFS_MAX
} ak8963_mfs_sel_t;

/**
 * @brief   Communication mode.
 */
typedef enum {
    AK8963_COMM_MODE_I2C = 0,                   /*!< Interface over I2C */
    AK8963_COMM_MODE_SPI,                       /*!< Interface over SPI */
    AK8963_COMM_MODE_MAX
} ak8963_comm_mode_t;

/**
 * @brief   Configuration structure.
 */
typedef struct {
    ak8963_mode_t               opr_mode;       /*!< AK8963 operatkion mode */
    ak8963_mfs_sel_t            mfs_sel;        /*!< AK8963 magnetometer full scale range */
    ak8963_comm_mode_t          comm_mode;      /*!< AK8963 interface protocol */
    func_read_bytes             read_bytes;     /*!< Read function */
    func_write_bytes            write_bytes;    /*!< Write function */
} ak8963_cfg_t;


#ifdef __cplusplus
}
#endif

#endif /* __AK8963_PUBLIC_H__ */
