#ifndef __AK8963_REGISTER_H__
#define __AK8963_REGISTER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define AK8963_ADDR                 0x0C


#define AK8963_WHO_AM_I             0x00
#define AK8963_INFO                 0x01
#define AK8963_ST1                  0x02
#define AK8963_XOUT_L               0x03
#define AK8963_XOUT_H               0x04
#define AK8963_YOUT_L               0x05
#define AK8963_YOUT_H               0x06
#define AK8963_ZOUT_L               0x07
#define AK8963_ZOUT_H               0x08
#define AK8963_ST2                  0x09
#define AK8963_CNTL                 0x0A
#define AK8963_RSV                  0x0B
#define AK8963_ASTC                 0x0C
#define AK8963_TS1                  0x0D
#define AK8963_TS2                  0x0E
#define AK8963_I2CDIS               0x0F
#define AK8963_ASAX                 0x10
#define AK8963_ASAY                 0x11
#define AK8963_ASAZ                 0x12

#ifdef __cplusplus
}
#endif

#endif /* __AK8963_REGISTER_H__ */