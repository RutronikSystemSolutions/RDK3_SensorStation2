/*
 * thermal_imaging_task.h
 *
 *  Created on: Jan 2, 2023
 *      Author: Gintaras
 */

#ifndef THERMAL_IMAGING_TASK_H_
#define THERMAL_IMAGING_TASK_H_

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "MLX90640_I2C_Driver.h"
#include "MLX90640_API.h"

#define MLX90640_ADDR		0x33
#define MLX90641_ADDR		0x33
#define MLX_ID1_ADDR		0x2407
#define MLX_EEPROM_SIZE		1664
#define MLX_PIXELS			768
#define TA_SHIFT 			8
#define STARTUP_DELAY_MS	1000

/*MLX90640 Refresh Rate Selector*/
#define MLX_RATE_SELECT_4HZ
#ifdef MLX_RATE_SELECT_05HZ
#define MLX_REFRESH_RATE	0x00
#define MLX_DELAY_DIV		0.5
#endif
#ifdef MLX_RATE_SELECT_1HZ
#define MLX_REFRESH_RATE	0x01
#define MLX_DELAY_DIV		1
#endif
#ifdef MLX_RATE_SELECT_2HZ
#define MLX_REFRESH_RATE	0x02
#define MLX_DELAY_DIV		2
#endif
#ifdef MLX_RATE_SELECT_4HZ
#define MLX_REFRESH_RATE	0x03
#define MLX_DELAY_DIV		4
#endif
#ifdef MLX_RATE_SELECT_8HZ
#define MLX_REFRESH_RATE	0x04
#define MLX_DELAY_DIV		8
#endif
#ifdef MLX_RATE_SELECT_16HZ
#define MLX_REFRESH_RATE	0x05
#define MLX_DELAY_DIV		16
#endif
#ifdef MLX_RATE_SELECT_32HZ
#define MLX_REFRESH_RATE	0x06
#define MLX_DELAY_DIV		32
#endif
#ifdef MLX_RATE_SELECT_64HZ
#define MLX_REFRESH_RATE	0x07
#define MLX_DELAY_DIV		64
#endif

/* Set baud rate to special 1093750 */
#define ARDU_BAUD_RATE       		1093750

#define TH_IMG_POSLEFT				UINT16_C (207)
#define TH_IMG_POSTOP				UINT16_C (63)

#define RULER_POSLEFT				UINT16_C (159)
#define RULER_POSTOP				UINT16_C (80)

#define CHEVUP_POSLEFT				UINT16_C (54)
#define CHEVUP_POSTOP				UINT16_C (123)

#define CHEVDOWN_POSLEFT			UINT16_C (54)
#define CHEVDOWN_POSTOP				UINT16_C (224)

#define CHEVRIGHT_POSLEFT			UINT16_C (117)
#define CHEVRIGHT_POSTOP			UINT16_C (164)

#define CHEVLEFT_POSLEFT			UINT16_C (15)
#define CHEVLEFT_POSTOP				UINT16_C (164)

#define DUMMY_CMD					0
#define COLOUR_CMD					249
#define POSLEFT_CMD					251
#define POSTOP_CMD					252

#define BITS_UINT8					UINT8_C  (255)
#define THERMAL_SENSORS				UINT16_C (768)

#define BUFF_OVF_TOUT_MS			100

typedef struct thermal_image_data
{
	paramsMLX90640 mlx90640Config;
	float mlx90640To[768];
	uint16_t mlx90640Frame[834];
	float vdd;
	float Ta;
	float tr;
	float emissivity;
	uint8_t subpage;
	uint16_t device_id[3];

	float max_temp;
	float min_temp;

}thermal_image_t;

extern TaskHandle_t thermal_imaging_task_handle;

void thermal_imaging_task(void *param);

#endif /* THERMAL_IMAGING_TASK_H_ */
