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

#ifndef __IMU_INTF_H__
#define __IMU_INTF_H__

#include "err_code.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef err_code_t (*func_read_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);
typedef err_code_t (*func_write_bytes)(uint8_t reg_addr, uint8_t *buf, uint16_t len, uint32_t timeout_ms);
typedef void (*func_delay)(uint32_t ms);


#ifdef __cplusplus
}
#endif

#endif /* __IMU_INTF_H__ */