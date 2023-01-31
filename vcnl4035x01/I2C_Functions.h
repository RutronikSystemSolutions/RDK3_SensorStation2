/*
 * I2C_Functions.h
 *
 * Created  : 9 November 2020
 * Modified : 6 May 2021
 * Author   : HWanyusof
 * Version	: 1.0
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "typedefinition.h"

/* Include I2C Library for PSoC6 Infineon MCUs */
#ifdef Cypress
	#include "cy_pdl.h"
	#include "cyhal.h"
	#include "cybsp.h"
	#ifdef FREERTOS_APP
	/*FreeRTOS Header Files*/
	#include "FreeRTOS.h"
	#include "task.h"
	#include "semphr.h"
	#endif
#endif

//Include I2C Library for STM32F
#ifdef STM32F
	#include "stm32f4xx_hal.h"
#endif

//Include I2C Library for Arduino supported MCU
#ifdef Arduino
	//Arduino platforms use Wire.h library while Teensy platforms use i2c_t3.h library.
	#ifdef i2ct3
		#include <i2c_t3.h>
	#endif

	#ifdef wirelib
		#include <Arduino.h>
		#include <Wire.h>
	#endif
#endif

//Struct TransferData Member Definition
struct TransferData
{
	uint8_t RegisterAddress;
	uint8_t WData[2];
	uint8_t RData[2];
	uint8_t length;
	uint8_t Slave_Address;
	uint8_t Select_I2C_Bus;
}; //Struct variables will be declared separately in Sensor API and I2C_Functions.cpp/c

//Struct TransferData Member Definition
struct GestureTransferData
{
	uint8_t RegisterAddress;
	uint8_t WData[2];
	uint8_t RData[6];
	uint8_t length;
	uint8_t Slave_Address;
	uint8_t Select_I2C_Bus;
}; //Struct variables will be declared separately in Sensor API and I2C_Functions.cpp/c

//Function Prototypes For I2C_Functions.cpp/c
int ReadI2C_Bus(struct TransferData *Data);
int WriteI2C_Bus(struct TransferData *Data);
int ReadI2C_Bus_Gesture_Mode(struct GestureTransferData *Data);
