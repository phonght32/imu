#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"

#include "err_code.h"
#include "mpu9250_private.h"
#include "mpu9250_public.h"


#define MPU9250_SELF_TEST_X_GYRO        0x00        /*!< Gyroscope self-test registers */
#define MPU9250_SELF_TEST_Y_GYRO        0x01
#define MPU9250_SELF_TEST_Z_GYRO        0x02
#define MPU9250_SELF_TEST_X_ACCEL       0x0D        /*!< Accelerometer self-test registers */
#define MPU9250_SELF_TEST_Y_ACCEL       0x0E
#define MPU9250_SELF_TEST_Z_ACCEL       0x0F
#define MPU9250_XG_OFFSET_H             0x13        /*!< Gyroscope offset registers */
#define MPU9250_XG_OFFSET_L             0x14
#define MPU9250_YG_OFFSET_H             0x14
#define MPU9250_YG_OFFSET_L             0x16
#define MPU9250_ZG_OFFSET_H             0x17
#define MPU9250_ZG_OFFSET_L             0x18
#define MPU9250_SMPLRT_DIV              0x19        /*!< Sample rate divider */
#define MPU9250_CONFIG                  0x1A        /*!< Configuration */
#define MPU9250_GYRO_CONFIG             0x1B        /*!< Gyroscope configuration */
#define MPU9250_ACCEL_CONFIG            0x1C        /*!< Accelerometer configuration */
#define MPU9250_ACCEL_CONFIG2           0x1D        /*!< Accelerometer configuration 2 */
#define MPU9250_LP_ACCEL_ODR            0x1E        /*!< Low power accelerometer ODR control */
#define MPU9250_WOM_THR                 0x1F        /*!< Wake-on motion threshold */
#define MPU9250_FIFO_EN                 0x23        /*!< FIFO enable */
#define MPU9250_I2C_MST_CTRL            0x24        /*!< I2C master control */
#define MPU9250_I2C_SLV0_ADDR           0x25        /*!< I2C slave 0 control */
#define MPU9250_I2C_SLV0_REG            0x26
#define MPU9250_I2C_SLV0_CTRL           0x27
#define MPU9250_I2C_SLV1_ADDR           0x28        /*!< I2C slave 1 control */
#define MPU9250_I2C_SLV1_REG            0x29
#define MPU9250_I2C_SLV1_CTRL           0x2A
#define MPU9250_I2C_SLV2_ADDR           0x2B        /*!< I2C slave 2 control */
#define MPU9250_I2C_SLV2_REG            0x2C
#define MPU9250_I2C_SLV2_CTRL           0x2D
#define MPU9250_I2C_SLV3_ADDR           0x2E        /*!< I2C slave 3 control */
#define MPU9250_I2C_SLV3_REG            0x2F
#define MPU9250_I2C_SLV3_CTRL           0x30
#define MPU9250_I2C_SLV4_ADDR           0x31        /*!< I2C slave 4 control */
#define MPU9250_I2C_SLV4_REG            0x32
#define MPU9250_I2C_SLV4_DO             0x33
#define MPU9250_I2C_SLV4_CTRL           0x34
#define MPU9250_I2C_SLV4_DI             0x35
#define MPU9250_I2C_MST_STATUS          0x36        /*!< I2C master status */
#define MPU9250_INT_PIN_CFG             0x37        /*!< Interrupt pin/bypass enable configuration */
#define MPU9250_INT_ENABLE              0x38        /*!< Interrupt enable */
#define MPU9250_INT_STATUS              0x3A        /*!< Interrupt status */
#define MPU9250_ACCEL_XOUT_H            0x3B        /*!< Accelerometer measurements */
#define MPU9250_ACCEL_XOUT_L            0x3C
#define MPU9250_ACCEL_YOUT_H            0x3D
#define MPU9250_ACCEL_YOUT_L            0x3E
#define MPU9250_ACCEL_ZOUT_H            0x3F
#define MPU9250_ACCEL_ZOUT_L            0x40
#define MPU9250_TEMP_OUT_H              0x41        /*!< Temperature measurements */
#define MPU9250_TEMP_OUT_L              0x42
#define MPU9250_GYRO_XOUT_H             0x43        /*!< Gyroscope measurements */
#define MPU9250_GYRO_XOUT_L             0x44
#define MPU9250_GYRO_YOUT_H             0x45
#define MPU9250_GYRO_YOUT_L             0x46
#define MPU9250_GYRO_ZOUT_H             0x47
#define MPU9250_GYRO_ZOUT_L             0x48
#define MPU9250_EXT_SENS_DATA_00        0x49        /*!< External sensor data */
#define MPU9250_EXT_SENS_DATA_01        0x4A
#define MPU9250_EXT_SENS_DATA_02        0x4B
#define MPU9250_EXT_SENS_DATA_03        0x4C
#define MPU9250_EXT_SENS_DATA_04        0x4D
#define MPU9250_EXT_SENS_DATA_05        0x4E
#define MPU9250_EXT_SENS_DATA_06        0x4F
#define MPU9250_EXT_SENS_DATA_07        0x50
#define MPU9250_EXT_SENS_DATA_08        0x51
#define MPU9250_EXT_SENS_DATA_09        0x52
#define MPU9250_EXT_SENS_DATA_10        0x53
#define MPU9250_EXT_SENS_DATA_11        0x54
#define MPU9250_EXT_SENS_DATA_12        0x55
#define MPU9250_EXT_SENS_DATA_13        0x56
#define MPU9250_EXT_SENS_DATA_14        0x57
#define MPU9250_EXT_SENS_DATA_15        0x58
#define MPU9250_EXT_SENS_DATA_16        0x59
#define MPU9250_EXT_SENS_DATA_17        0x5A
#define MPU9250_EXT_SENS_DATA_18        0x5B
#define MPU9250_EXT_SENS_DATA_19        0x5C
#define MPU9250_EXT_SENS_DATA_20        0x5D
#define MPU9250_EXT_SENS_DATA_21        0x5E
#define MPU9250_EXT_SENS_DATA_22        0x5F
#define MPU9250_EXT_SENS_DATA_23        0x60
#define MPU9250_I2C_SLV0_DO             0x63        /*!< I2C slave 0 data out */
#define MPU9250_I2C_SLV1_DO             0x64        /*!< I2C slave 1 data out */
#define MPU9250_I2C_SLV2_DO             0x65        /*!< I2C slave 2 data out */
#define MPU9250_I2C_SLV3_DO             0x66        /*!< I2C slave 3 data out */
#define MPU9250_I2C_MST_DELAY_CTRL      0x67        /*!< I2C master delay control */
#define MPU9250_SIGNAL_PATH_RESET       0x68        /*!< Signal path reset */
#define MPU9250_MOT_DETECT_CTRL         0x69        /*!< Acelerometer interrupt control */
#define MPU9250_USER_CTRL               0x6A        /*!< User control */
#define MPU9250_PWR_MGMT_1              0x6B        /*!< Power management 1 */
#define MPU9250_PWR_MGMT_2              0x6C        /*!< Power management 2 */
#define MPU9250_FIFO_COUNTH             0x72        /*!< FIFO counter registers */
#define MPU9250_FIFO_COUNTL             0x73
#define MPU9250_FIFP_R_W                0x74        /*!< FIFO read write */
#define MPU9250_WHO_AM_I                0x75        /*!< Who am I */
#define MPU9250_XA_OFFSET_H             0x77        /*!< Accelerometer offset registers */
#define MPU9250_XA_OFFSET_L             0x78
#define MPU9250_YA_OFFSET_H             0x7A
#define MPU9250_YA_OFFSET_L             0x7B
#define MPU9250_ZA_OFFSET_H             0x7D
#define MPU9250_ZA_OFFSET_L             0x7E


#define MPU9250_ADDR                    (0x68<<1)   /*!< MPU9250 Address */

#define MPU9250_INIT_TIMEOUT 			100
#define MPU9250_READ_TIMEOUT 			100
#define MPU9250_WRITE_TIMEOUT 			100


/**
 * @brief 	Communication mode.
 */
typedef struct mpu9250 {
	mpu9250_clksel_t        clksel;                 /*!< MPU9250 clock source */
	mpu9250_dlpf_cfg_t      dlpf_cfg;               /*!< MPU9250 digital low pass filter (DLPF) */
	mpu9250_sleep_mode_t    sleep_mode;             /*!< MPU9250 sleep mode */
	mpu9250_afs_sel_t       afs_sel;                /*!< MPU9250 accelerometer full scale range */
	mpu9250_fs_sel_t        fs_sel;                 /*!< MPU9250 gyroscope full scale range */
	mpu9250_comm_mode_t     comm_mode;              /*!< MPU9250 interface protocol */
	func_read_bytes         read_bytes;             /*!< MPU9250 read function */
	func_write_bytes        write_bytes;            /*!< MPU9250 write function */
} mpu9250_t;

/**
 * @brief 	MPU9250 handle structure.
 */
typedef struct mpu9250 *mpu9250_handle_t;

static mpu9250_handle_t mpu9250_handle = (void*)NULL;


err_code_t mpu9250_init(void)
{
	mpu9250_handle = calloc(1, sizeof(mpu9250_handle_t));

	if (mpu9250_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu9250_set_config(mpu9250_cfg_t config)
{
	if (mpu9250_handle == NULL)
	{
		return ERR_CODE_FAIL;
	}

	mpu9250_handle->afs_sel = config.afs_sel;
	mpu9250_handle->fs_sel = config.fs_sel;
	mpu9250_handle->clksel = config.clksel;
	mpu9250_handle->dlpf_cfg = config.dlpf_cfg;
	mpu9250_handle->sleep_mode = config.sleep_mode;
	mpu9250_handle->comm_mode = config.comm_mode;
	mpu9250_handle->read_bytes = config.read_bytes;
	mpu9250_handle->write_bytes = config.write_bytes;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu9250_config(void)
{
	/* Check if configuration structure is NULL */
	if (mpu9250_handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err_ret = ERR_CODE_FAIL;

	/* Reset mpu9250 */
	uint8_t buffer = 0;
	buffer = 0x80;
	err_ret = mpu9250_handle->write_bytes(MPU9250_PWR_MGMT_1, &buffer, 1, MPU9250_INIT_TIMEOUT);
	// HAL_Delay(100);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure clock source and sleep mode */
	buffer = mpu9250_handle->clksel & 0x07;
	buffer |= (mpu9250_handle->sleep_mode << 6) & 0x40;
	err_ret = mpu9250_handle->write_bytes(MPU9250_PWR_MGMT_1, &buffer, 1, MPU9250_INIT_TIMEOUT);
	// HAL_Delay(100);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure digital low pass filter */
	buffer = 0;
	buffer = mpu9250_handle->dlpf_cfg & 0x07;
	err_ret = mpu9250_handle->write_bytes(MPU9250_CONFIG, &buffer, 1, MPU9250_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure gyroscope range */
	buffer = 0;
	buffer = (mpu9250_handle->fs_sel << 3) & 0x18;
	err_ret = mpu9250_handle->write_bytes(MPU9250_GYRO_CONFIG, &buffer, 1, MPU9250_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure accelerometer range */
	buffer = 0;
	buffer = (mpu9250_handle->afs_sel << 3) & 0x18;
	err_ret = mpu9250_handle->write_bytes(MPU9250_ACCEL_CONFIG, &buffer, 1, MPU9250_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure sample rate divider */
	buffer = 0;
	buffer = 0x04;
	err_ret = mpu9250_handle->write_bytes(MPU9250_SMPLRT_DIV, &buffer, 1, MPU9250_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	/* Configure interrupt and enable bypass.
	 * Set Interrupt pin active high, push-pull, Clear and read of INT_STATUS,
	 * enable I2C_BYPASS_EN in INT_PIN_CFG register so additional chips can
	 * join the I2C bus and can be controlled by master.
	 */
	buffer = 0x22;
	err_ret = mpu9250_handle->write_bytes(MPU9250_INT_PIN_CFG, &buffer, 1, MPU9250_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	buffer = 0x01;
	err_ret = mpu9250_handle->write_bytes(MPU9250_INT_ENABLE, &buffer, 1, MPU9250_INIT_TIMEOUT);
	if (err_ret !=  ERR_CODE_SUCCESS)
	{
		return err_ret;
	}

	return ERR_CODE_SUCCESS;
}

err_code_t mpu9250_get_accel_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((mpu9250_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t accel_raw_data[6];

	err = mpu9250_handle->read_bytes(MPU9250_ACCEL_XOUT_H, accel_raw_data, 6, MPU9250_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]);
	*raw_y = (int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]);
	*raw_z = (int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu9250_get_gyro_raw(int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	if ((mpu9250_handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	err_code_t err;
	uint8_t gyro_raw_data[6];

	err = mpu9250_handle->read_bytes(MPU9250_GYRO_XOUT_H, gyro_raw_data, 6, MPU9250_READ_TIMEOUT);
	if (err != ERR_CODE_SUCCESS) {
		return err;
	}

	*raw_x = (int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]);
	*raw_y = (int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]);
	*raw_z = (int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu9250_destroy()
{
	if (mpu9250_handle == NULL)
	{
		free(mpu9250_handle);
	}

	return ERR_CODE_SUCCESS;
}
