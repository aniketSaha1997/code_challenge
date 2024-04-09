/**
 * @file       lis3mdl.h
 *
 * @brief      Header file for the LIS3MDL magnetometer sensor driver.
 *
 *             This file contains declarations of functions and data structures for
 *             interacting with the LIS3MDL magnetometer sensor. It provides an API
 *             for configuring the sensor, setting output data rates, toggling interrupts,
 *             and reading output data from specified axes.
 *
 * @author     Aniket SAHA
 * @date       Apr 9, 2024
 */

#ifndef LIS3MDL_H_
#define LIS3MDL_H_

/******************************************************************************
 * Include Header Files
 ******************************************************************************/
#include "stdint.h"

/******************************************************************************
 * Types Declarations
 ******************************************************************************/
typedef enum
{
    LIS3MDL_SCALE_4G,          /* ±4 Gauss scale */
    LIS3MDL_SCALE_8G,          /* ±8 Gauss scale */
    LIS3MDL_SCALE_12G,         /* ±12 Gauss scale */
    LIS3MDL_SCALE_16G,         /* ±16 Gauss scale */
    LIS3MDL_SCALE_UNKNOWN      /* Unknown scale */
} Lis3mdlScale_t;

typedef enum
{
    LIS3MDL_ODR_0_625_HZ,      /* Output data rate: 0.625 Hz */
    LIS3MDL_ODR_1_25_HZ,       /* Output data rate: 1.25 Hz */
    LIS3MDL_ODR_2_5_HZ,        /* Output data rate: 2.5 Hz */
    LIS3MDL_ODR_5_HZ,          /* Output data rate: 5 Hz */
    LIS3MDL_ODR_10_HZ,         /* Output data rate: 10 Hz */
    LIS3MDL_ODR_40_HZ,         /* Output data rate: 40 Hz */
    LIS3MDL_ODR_80_HZ          /* Output data rate: 80 Hz */
} Lis3mdlDataRate_t;

typedef enum
{
    LIS3MDL_INTR_EN,           /* Enable interrupt */
    LIS3MDL_INTR_DIS           /* Disable interrupt */
} Lis3mdlInterruptState_t;

typedef enum
{
    LIS3MDL_MODE_LP,           /* Low-power mode */
    LIS3MDL_MODE_MP,           /* Medium-performance mode */
    LIS3MDL_MODE_HP,           /* High-performance mode */
    LIS3MDL_MODE_UHP           /* Ultra-high-performance mode */
} Lis3mdlOperatingMode_t;

typedef enum
{
    LIS3MDL_OUT_AXIS_X,        /* Output data for X-axis */
    LIS3MDL_OUT_AXIS_Y,        /* Output data for Y-axis */
    LIS3MDL_OUT_AXIS_Z         /* Output data for Z-axis */
} Lis3mdlOutputAxisData_t;

typedef struct
{
    Lis3mdlDataRate_t dataRate_en;              /* Output data rate configuration */
    Lis3mdlOperatingMode_t operatingMode_en;    /* Operating mode configuration */
    uint8_t fastOdr_u8;                         /* Fast output data rate configuration */
} Lis3mdlSpeedConfig_st;

/******************************************************************************
 * Extern Functions Declarations
 ******************************************************************************/
/**
 * @brief Get the full-scale configuration of the LIS3MDL sensor.
 *
 * @param[out] configScale_pen Pointer to a variable to store the full-scale configuration.
 *                             The value will be one of the values from Lis3mdlScale_t enum.
 *
 * @return Status of the operation. Returns STATUS_OK on success, otherwise an error code.
 */
extern status_t Lis3mdlGetFullScaleConfig(Lis3mdlScale_t *configScale_pen);

/**
 * @brief Get the output data rate configuration of the LIS3MDL sensor.
 *
 * @param[out] config_st Pointer to a structure to store the output data rate configuration.
 *
 * @return Status of the operation. Returns STATUS_OK on success, otherwise an error code.
 */
extern status_t Lis3mdlGetOutputDataRate(Lis3mdlSpeedConfig_st *config_st);

/**
 * @brief Set the output data rate configuration of the LIS3MDL sensor.
 *
 * @param[in] config_st Configuration structure containing the desired data rate, operating mode, and fast ODR.
 *
 * @return Status of the operation. Returns STATUS_OK on success, otherwise an error code.
 */
extern status_t Lis3mdlSetOutputDataRate(Lis3mdlSpeedConfig_st config_st);

/**
 * @brief Enable or Disable interrupt of the LIS3MDL sensor.
 *
 * @param[in] state_en State of the interrupt to be set.
 *
 * @return Status of the operation. Returns STATUS_OK on success, otherwise an error code.
 */
extern status_t Lis3mdlToggleInterrupt(Lis3mdlInterruptState_t state_en);

/**
 * @brief Read the output data of a specified axis from the LIS3MDL sensor.
 *
 * @param[in]  axisSelect_en Enum identifying the axis from which to read the output data.
 * @param[out] axisData_pu8  Pointer to a variable to store the output data of the specified axis.
 *                           The variable will contain a 16-bit signed integer value representing the output data.
 *
 * @return Status of the operation. Returns STATUS_OK on success, otherwise an error code.
 */
extern status_t Lis3mdlReadOutputData(Lis3mdlOutputAxisData_t axisSelect_en, int16_t *axisData_pu8);

#endif /* LIS3MDL_H_ */
