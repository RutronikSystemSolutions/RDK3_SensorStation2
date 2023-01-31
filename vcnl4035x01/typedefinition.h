/* typedefinition.h - VCNL4035X01 optical sensors library
 *
 * Copyright (C) 2021 Vishay Semiconductor GmbH
 * Author: Hakimi Wanyusof <hakimi.wanyusof@vishay.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */



/**********************************************************************************************************************
*	Typedefinition:																								  *
*	This headerfile is used to define the specific types for the given MCU platform. Please change them if			  *
*	neccessary.																										  *
***********************************************************************************************************************/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//Switch for the declared API function for the specific MCU plattform. With this it is easy to change the whole library
//to any other MCU platform with just changing the name. This is only possible if the 
//area with the chosen platform name is defined and declared. 
#define Cypress
#define FREERTOS_APP


//MCU specific types. Depending on the plattform which is used. 
typedef uint8_t Byte; 
typedef uint16_t Word; 
typedef uint32_t uint_32;
typedef int int_32;




