/**
 * @file       lis3mdl_register.h
 *
 * @brief      Header file for the LIS3MDL magnetometer register config.
 *
 *             This file contains the registers that have been used for the required
 *             operations. This file is subject to change as per requirements to add
 *             or remove the registers required.
 *
 * @note	   Only the registers currently being used for the driver are declared here.
 *
 * @author     Aniket SAHA
 * @date       Apr 9, 2024
 */
#ifndef LIS3MDL_REGISTER_H_
#define LIS3MDL_REGISTER_H_

/* Register mapping for required operations. */
#define LIS3MDL_WHO_AM_I    0x0F

#define LIS3MDL_CTRL_REG1   0x20
#define LIS3MDL_CTRL_REG2   0x21

#define LIS3MDL_OUT_X_L     0x28
#define LIS3MDL_OUT_X_H     0x29
#define LIS3MDL_OUT_Y_L     0x2A
#define LIS3MDL_OUT_Y_H     0x2B
#define LIS3MDL_OUT_Z_L     0x2C
#define LIS3MDL_OUT_Z_H     0x2D

#define LIS3MDL_INT_CFG     0x30


#endif /* LIS3MDL_REGISTER_H_ */
