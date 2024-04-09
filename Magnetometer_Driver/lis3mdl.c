/**
 * @file       lis3mdl.c
 *
 * @brief      Implementation file for the LIS3MDL magnetometer sensor driver.
 *
 *             This file contains the implementation of functions to interact with the
 *             LIS3MDL magnetometer sensor. It provides functionalities to configure the
 *             sensor, set output data rates, toggle interrupts, and read output data from
 *             specified axes.
 *
 * @author     Aniket SAHA
 * @date       Apr 9, 2024
 */

/******************************************************************************
 * Include Header Files
 ******************************************************************************/
#include "i2c.h"
#include "lis3mdl_register.h"
#include "lis3mdl.h"
#include "stdint.h"

/******************************************************************************
 * Macro Declarations
 ******************************************************************************/
#define LIS3MDL_I2C_BUS_ADDRESS		0x10
#define LIS3MDL_SPEED_MASK			0x1C	/* Bit DO0, DO1, DO2 */
#define LIS3MDL_FAST_ODR_MASK		0x01

/******************************************************************************
 * Extern Function Definitions
 ******************************************************************************/
extern status_t Lis3mdlGetFullScaleConfig(Lis3mdlScale_t *configScale_pen)
{
    uint8_t readBuffer_u8;
    status_t status = STATUS_DEFAULT;

    status = i2c_read(LIS3MDL_I2C_BUS_ADDRESS, LIS3MDL_CTRL_REG2, 1u, &readBuffer_u8);

    if (status == STATUS_OK) 
    {
        uint8_t scaleBits_u8 = (readBuffer_u8 >> 6) & 0x03;

        switch (scaleBits_u8)
        {
		case 0x00:
			*configScale_pen = LIS3MDL_SCALE_4G;
			break;
		case 0x01:
			*configScale_pen = LIS3MDL_SCALE_8G;
			break;
		case 0x02:
			*configScale_pen = LIS3MDL_SCALE_12G;
			break;
		case 0x03:
			*configScale_pen = LIS3MDL_SCALE_16G;
			break;
		default:
			*configScale_pen = LIS3MDL_SCALE_UNKNOWN;
			break;
        }

        return STATUS_OK;
    }
    else
    {
        return status;
    }
}


extern status_t Lis3mdlSetOutputDataRate(Lis3mdlSpeedConfig_st  config_st)
{
	uint8_t regVal_u8 = ((config_st.dataRate_en << 2) & LIS3MDL_SPEED_MASK) | (config_st.operatingMode_en & 0x03) | (config_st.fastOdr_u8 & LIS3MDL_FAST_ODR_MASK);
	
	
	status_t status = i2c_write(LIS3MDL_I2C_BUS_ADDRESS, LIS3MDL_CTRL_REG1,
								 1u, &regVal_u8);
	
	return status;
}


extern status_t Lis3mdlGetOutputDataRate(Lis3mdlSpeedConfig_st * config_st)
{
	uint8_t regVal_u8;
	status_t status = STATUS_DEFAULT;

	status = i2c_read(LIS3MDL_I2C_BUS_ADDRESS, LIS3MDL_CTRL_REG1,
								1u, &regVal_u8);

	if(status == STATUS_OK)
	{
		config_st->dataRate_en 		= (regVal_u8 & LIS3MDL_SPEED_MASK) >> 2;
		config_st->operatingMode_en = (regVal_u8 & 0x03);
		config_st->fastOdr_u8 		= (regVal_u8 & LIS3MDL_FAST_ODR_MASK);
	}

	return status;
}


extern status_t Lis3mdlToggleInterrupt(Lis3mdlInterruptState_t state_en)
{
	uint8_t regVal_u8;
	status_t status = STATUS_DEFAULT;

	status = i2c_read(LIS3MDL_I2C_BUS_ADDRESS, LIS3MDL_INT_CFG, 1u, &regVal_u8);

	if(status == STATUS_OK)
	{
		if(state_en == LIS3MDL_INTR_EN)
		{
			if((regVal_u8 & 0x01) == 0u)
			{
				regVal_u8 |= 0x01;
				(void)i2c_write(LIS3MDL_I2C_BUS_ADDRESS, LIS3MDL_INT_CFG, 1u, &regVal_u8);
			}
		}
		else if(state_en == LIS3MDL_INTR_DIS)
		{
			if((regVal_u8 & 0x01) != 0u)
			{
				regVal_u8 &= ~0x01;
				(void)i2c_write(LIS3MDL_I2C_BUS_ADDRESS, LIS3MDL_INT_CFG, 1u, &regVal_u8);
			}
		}
		else
		{
			status = STATUS_ERROR;
		}
	}

	return status;
}


extern status_t Lis3mdlReadOutputData(Lis3mdlOutputAxisData_t axisSelect_en, int16_t * axisData_pu8)
{
	uint8_t lowReg_u8;
	uint8_t highReg_u8;
	uint8_t regAddessLow_u8;
	uint8_t regAddessHi_u8;
	status_t status = STATUS_DEFAULT;

	switch(axisSelect_en)
	{
	case LIS3MDL_OUT_AXIS_X:
		regAddessLow_u8 = LIS3MDL_OUT_X_L;
		regAddessHi_u8 = LIS3MDL_OUT_X_H;
		break;

	case LIS3MDL_OUT_AXIS_Y:
		regAddessLow_u8 = LIS3MDL_OUT_Y_L;
		regAddessHi_u8 = LIS3MDL_OUT_Y_H;
		break;

	case LIS3MDL_OUT_AXIS_Z:
		regAddessLow_u8 = LIS3MDL_OUT_Z_L;
		regAddessHi_u8 = LIS3MDL_OUT_Z_H;
		break;

	default:
		break;

	}

	status |= i2c_read(LIS3MDL_I2C_BUS_ADDRESS, regAddessLow_u8, 1u, &lowReg_u8);
	status |= i2c_read(LIS3MDL_I2C_BUS_ADDRESS, regAddessHi_u8, 1u, &highReg_u8);

	if(status == STATUS_OK)
	{
		*axisData_pu8 = (int16_t)((highReg_u8 << 8) | (lowReg_u8));
	}

	return status;
}
