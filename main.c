/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the RDK3_SensorStation2
*              Application for ModusToolbox.
*
* Related Document: See README.md
*
*
*  Created on: 2023-01-31
*  Company: Rutronik Elektronische Bauelemente GmbH
*  Address: Jonavos g. 30, Kaunas 44262, Lithuania
*  Author: GDR
*
********************************************************************************
* Copyright 2021-2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*
* Rutronik Elektronische Bauelemente GmbH Disclaimer: The evaluation board
* including the software is for testing purposes only and,
* because it has limited functions and limited resilience, is not suitable
* for permanent use under real conditions. If the evaluation board is
* nevertheless used under real conditions, this is done at one’s responsibility;
* any liability of Rutronik is insofar excluded
*******************************************************************************/
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "thermal_imaging_task.h"
#include "gesture_control_task.h"
#include "capsense_task.h"
#include "dio59020.h"

/*Priority for button interrupts*/
#define BTN_IRQ_PRIORITY		5

/*Function prototypes*/
void handle_error(void);

void btn_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);

/*User Button 1 Interrupt Data*/
cyhal_gpio_callback_data_t btn_data =
{
		.callback = btn_interrupt_handler,
		.callback_arg = NULL,

};

/*I2C Device Global Variables*/
cyhal_i2c_t I2C_scb3;
cyhal_i2c_cfg_t i2c_scb3_cfg =
{
		.is_slave = false,
	    .address = 0,
	    .frequencyhal_hz = 400000UL,
};

SemaphoreHandle_t i2c_mutex = NULL;

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
    	handle_error();
    }

    __enable_irq();

    /*Initialize LEDs*/
    result = cyhal_gpio_init( LED1, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    if (result != CY_RSLT_SUCCESS)
    {handle_error();}
    result = cyhal_gpio_init( LED2, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    if (result != CY_RSLT_SUCCESS)
    {handle_error();}
    result = cyhal_gpio_init( LED3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);
    if (result != CY_RSLT_SUCCESS)
    {handle_error();}

    /*Initialize Display RESET pin*/
    result = cyhal_gpio_init(ARDU_IO8, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);
    if (result != CY_RSLT_SUCCESS)
    {handle_error();}

    /*Initialize Buttons*/
    result = cyhal_gpio_init(USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, false);
    if (result != CY_RSLT_SUCCESS)
    {handle_error();}
    /*Register callback functions */
    cyhal_gpio_register_callback(USER_BTN, &btn_data);
    /* Enable falling edge interrupt events */
    cyhal_gpio_enable_event(USER_BTN, CYHAL_GPIO_IRQ_FALL, BTN_IRQ_PRIORITY, true);

    /*Enable debug output via KitProg UART*/
    result = cy_retarget_io_init( KITPROG_TX, KITPROG_RX, CY_RETARGET_IO_BAUDRATE);
    if (result != CY_RSLT_SUCCESS)
    {handle_error();}
    printf("\x1b[2J\x1b[;H");
    printf("RDK3 Sensor Station 2 Application.\r\n");

    /*Initialize I2C Master*/
    result = cyhal_i2c_init(&I2C_scb3, ARDU_SDA, ARDU_SCL, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }
    result = cyhal_i2c_configure(&I2C_scb3, &i2c_scb3_cfg);
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /* DIO59020 Charger Setup*/
    if(dio_online())
    {
    	/*Disable the charger*/
		dio_charger_disable();
    }

    /* Create a mutex for the I2C. */
    i2c_mutex = xSemaphoreCreateMutex();
    if( i2c_mutex == NULL )
    {CY_ASSERT(0);}

    /* Create a thermal imaging task. */
    xTaskCreate(thermal_imaging_task, "thermal task", configMINIMAL_STACK_SIZE*8, NULL, configMAX_PRIORITIES - 3, &thermal_imaging_task_handle);
    if(thermal_imaging_task_handle == NULL)
    {
    	printf("Error: could not create a thermal imaging task.\r\n");
    	handle_error();
    }

    /* Create a CapSense task. */
    xTaskCreate(capsense_task, "capsense task", configMINIMAL_STACK_SIZE*4, NULL, configMAX_PRIORITIES - 2, &capsense_task_handle);
    if(capsense_task_handle == NULL)
    {
    	printf("Error: could not create a capsense task.\r\n");
    	handle_error();
    }

    /* Create a gesture control task. */
    xTaskCreate(gesture_control_task, "gesture task", configMINIMAL_STACK_SIZE*8, NULL, configMAX_PRIORITIES - 1, &gesture_control_task_handle);
    if(gesture_control_task_handle == NULL)
    {
    	printf("Error: could not create a gesture control task.\r\n");
    	handle_error();
    }

    vTaskStartScheduler();
    /* RTOS scheduler exited */
    /* Halt the CPU if scheduler exits */
    CY_ASSERT(0);

}

/* Interrupt handler callback function */
void btn_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event)
{
	CY_UNUSED_PARAMETER(handler_arg);
    CY_UNUSED_PARAMETER(event);
}

void handle_error(void)
{
     /* Disable all interrupts. */
    __disable_irq();

    CY_ASSERT(0);
}

/* [] END OF FILE */
