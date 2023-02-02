/*
 * capsense_task.h
 *
 *  Created on: Feb 2, 2023
 *      Author: Gintaras
 */

#ifndef CAPSENSE_TASK_H_
#define CAPSENSE_TASK_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

extern TaskHandle_t capsense_task_handle;
void capsense_task(void *param);

typedef struct capsense_data
{
    _Bool csb1_status;
    _Bool csb2_status;
    _Bool csb3_status;
}capsense_data_t;

extern capsense_data_t cbuttons;

#endif /* CAPSENSE_TASK_H_ */
