/*
 * pca9554_app.c
 *
 *  Created on: Jan 12, 2023
 *      Author: Gintaras
 */

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "pca9554_app.h"

extern SemaphoreHandle_t i2c_mutex;

cy_rslt_t pca9554_configure(void)
{
	PCA9554_RET_TYPE result;

	xSemaphoreTake(i2c_mutex, portMAX_DELAY);

	result = pca9554_write_config_pol(PCA9554_DEV_ADDRESS, PCA9554_POL_CONFIG);
	if(result == PCA9554_COM_ERR)
	{
		xSemaphoreGive(i2c_mutex);
		return 1;
	}

	result = pca9554_write_config_dir(PCA9554_DEV_ADDRESS, PCA9554_DIR_CONFIG);
	if(result == PCA9554_COM_ERR)
	{
		xSemaphoreGive(i2c_mutex);
		return 1;
	}

	result = pca9554_pins_write(PCA9554_DEV_ADDRESS, PCA9554_OUT_CONFIG);
	if(result == PCA9554_COM_ERR)
	{
		xSemaphoreGive(i2c_mutex);
		return 1;
	}

	xSemaphoreGive(i2c_mutex);
	return CY_RSLT_SUCCESS;
}

cy_rslt_t pca9554_dir_set(uint8_t dir)
{
	PCA9554_RET_TYPE result;

	xSemaphoreTake(i2c_mutex, portMAX_DELAY);

	result = pca9554_pins_write(PCA9554_DEV_ADDRESS, dir);
	if(result == PCA9554_COM_ERR)
	{
		xSemaphoreGive(i2c_mutex);
		return 1;
	}

	xSemaphoreGive(i2c_mutex);
	return CY_RSLT_SUCCESS;
}
