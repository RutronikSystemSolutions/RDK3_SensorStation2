/*
 * capsense_task.c
 *
 *  Created on: Feb 2, 2023
 *      Author: Gintaras
 */

#include "capsense_task.h"
#include "cycfg_capsense.h"

#define CAPSENSE_INTR_PRIORITY      (7u)
#define EZI2C_INTR_PRIORITY         (6u)
#define BUTTON_DELAY_TIMES          (2u)

static uint32_t initialize_capsense(void);
static void capsense_isr(void);
static void capsense_callback();
static void process_touch(void);

/*CapSense Task Handles*/
TaskHandle_t capsense_task_handle = NULL;
volatile bool capsense_scan_complete = false;

capsense_data_t cbuttons =
		{
				.csb1_status = false,
				.csb2_status = false,
				.csb3_status = false
		};

void capsense_task(void *param)
{
	(void) param;
	cy_rslt_t result;

    /*CapSense Initializations*/
    result = initialize_capsense();
    if (result != CY_RSLT_SUCCESS)
    {
    	CY_ASSERT(0);
    }

    /* Initiate first scan */
    Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(20));

    	/*Check if the CSD slider scan is complete*/
        if (capsense_scan_complete)
        {
            /* Process all widgets */
            Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

            /* Process touch input */
            process_touch();

            /* Initiate next scan */
            Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

            capsense_scan_complete = false;
        }
	}
}

/*******************************************************************************
* Function Name: initialize_capsense
********************************************************************************
* Summary:
*  This function initializes the CapSense and configure the CapSense
*  interrupt.
*
*******************************************************************************/
static uint32_t initialize_capsense(void)
{
    uint32_t status = CYRET_SUCCESS;

    /* CapSense interrupt configuration */
    const cy_stc_sysint_t CapSense_interrupt_config =
        {
            .intrSrc = CAPSENSE_IRQ,
            .intrPriority = CAPSENSE_INTR_PRIORITY,
        };

    /* Capture the CSD HW block and initialize it to the default state. */
    status = Cy_CapSense_Init(&cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    /* Initialize CapSense interrupt */
    Cy_SysInt_Init(&CapSense_interrupt_config, capsense_isr);
    NVIC_ClearPendingIRQ(CapSense_interrupt_config.intrSrc);
    NVIC_EnableIRQ(CapSense_interrupt_config.intrSrc);

    /* Initialize the CapSense firmware modules. */
    status = Cy_CapSense_Enable(&cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    /* Assign a callback function to indicate end of CapSense scan. */
    status = Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E, capsense_callback, &cy_capsense_context);
    if (CYRET_SUCCESS != status)
    {
        return status;
    }

    return status;
}

/*******************************************************************************
* Function Name: capsense_isr
********************************************************************************
* Summary:
*  Wrapper function for handling interrupts from CapSense block.
*
*******************************************************************************/
static void capsense_isr(void)
{
    Cy_CapSense_InterruptHandler(CAPSENSE_HW, &cy_capsense_context);
}

/*******************************************************************************
* Function Name: capsense_callback()
********************************************************************************
* Summary:
*  This function sets a flag to indicate end of a CapSense scan.
*
* Parameters:
*  cy_stc_active_scan_sns_t* : pointer to active sensor details.
*
*******************************************************************************/
void capsense_callback(cy_stc_active_scan_sns_t * ptrActiveScan)
{
    capsense_scan_complete = true;
}

/*******************************************************************************
* Function Name: process_touch
********************************************************************************
* Summary:
*  Gets the details of touch position detected, processes the touch input
*  and updates the LED status.
*
*******************************************************************************/
static void process_touch(void)
{
    uint32_t button1_status;
    uint32_t button2_status;
    uint32_t button3_status;

    static uint32_t cnt_1 = 0;
    static _Bool rel_1 = true;
    static uint32_t cnt_2 = 0;
    static _Bool rel_2 = true;
    static uint32_t cnt_3 = 0;
    static _Bool rel_3 = true;

    /* Get button 0 status */
    button1_status = Cy_CapSense_IsSensorActive(CY_CAPSENSE_BUTTON0_WDGT_ID,CY_CAPSENSE_BUTTON0_SNS0_ID,&cy_capsense_context);

    /* Get button 1 status */
    button2_status = Cy_CapSense_IsSensorActive(CY_CAPSENSE_BUTTON1_WDGT_ID,CY_CAPSENSE_BUTTON1_SNS0_ID,&cy_capsense_context);

    /* Get button 2 status */
    button3_status = Cy_CapSense_IsSensorActive(CY_CAPSENSE_BUTTON2_WDGT_ID,CY_CAPSENSE_BUTTON2_SNS0_ID,&cy_capsense_context);

    /* Detect new touch on Button1 */
    if(button1_status)
    {
    	if(cnt_1 == BUTTON_DELAY_TIMES)
    	{
    		cnt_1 = 0;
    		if(rel_1 == true)
    		{
    			cbuttons.csb1_status = !cbuttons.csb1_status;
    			rel_1 = false;

    			if(cbuttons.csb1_status)
    			{
    				cyhal_gpio_write((cyhal_gpio_t)LED1, CYBSP_LED_STATE_ON);
    			}
    			else
    			{
    				cyhal_gpio_write((cyhal_gpio_t)LED1, CYBSP_LED_STATE_OFF);
    			}
    		}
    	}
    	cnt_1++;
    }
    else
    {
    	rel_1 = true;
    	cnt_1 = 0;
    }

    /* Detect new touch on Button2 */
    if(button2_status)
    {
    	if(cnt_2 == BUTTON_DELAY_TIMES)
    	{
    		cnt_2 = 0;
    		if(rel_2 == true)
    		{
    			cbuttons.csb2_status = !cbuttons.csb2_status;
    			rel_2 = false;

    			if(cbuttons.csb2_status)
    			{
    				cyhal_gpio_write((cyhal_gpio_t)LED2, CYBSP_LED_STATE_ON);
    			}
    			else
    			{
    				cyhal_gpio_write((cyhal_gpio_t)LED2, CYBSP_LED_STATE_OFF);
    			}
    		}
    	}
    	cnt_2++;
    }
    else
    {
    	rel_2 = true;
    	cnt_2 = 0;
    }

    /* Detect new touch on Button3 */
    if(button3_status)
    {
    	if(cnt_3 == BUTTON_DELAY_TIMES)
    	{
    		cnt_3 = 0;
    		if(rel_3 == true)
    		{
    			cbuttons.csb3_status = !cbuttons.csb3_status;
    			rel_3 = false;

    			if(cbuttons.csb3_status)
    			{
    				cyhal_gpio_write((cyhal_gpio_t)LED3, CYBSP_LED_STATE_ON);
    			}
    			else
    			{
    				cyhal_gpio_write((cyhal_gpio_t)LED3, CYBSP_LED_STATE_OFF);
    			}
    		}
    	}
    	cnt_3++;
    }
    else
    {
    	rel_3 = true;
    	cnt_3 = 0;
    }
}
