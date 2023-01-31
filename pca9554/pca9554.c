/*
 * pca9554.c
 *
 *  Created on: Jan 12, 2023
 *      Author: Gintaras
 */

#include "pca9554.h"

extern cyhal_i2c_t I2C_scb3;

PCA9554_RET_TYPE pca9554_pins_write(uint8_t address, uint8_t pins)
{
	cy_rslt_t result;
	uint8_t i2c_data[3];
	i2c_data[0] = PCA9554_OUTPUT_CMD;
    i2c_data[1] = pins;

    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, i2c_data, 2, 10, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

    return PCA9554_OK;
}

PCA9554_RET_TYPE pca9554_pins_read(uint8_t address, uint8_t* pins)
{
	cy_rslt_t result;
	uint8_t i2c_data = PCA9554_INPUT_CMD;
	uint8_t tx_data[2];

    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, &i2c_data, 1, 10, false);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

    result = cyhal_i2c_master_read(&I2C_scb3,(uint16_t)address, (uint8_t*)pins, 1, 10, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

	tx_data[0] = PCA9554_OUTPUT_CMD;
	tx_data[1] = *pins;
    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, tx_data, 2, 10, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

	return PCA9554_OK;
}

PCA9554_RET_TYPE pca9554_read_config_dir(uint8_t address, uint8_t* pins)
{
	cy_rslt_t result;
	uint8_t i2c_data = PCA9554_CONFIG_CMD;

    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, &i2c_data, 1, 10, false);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

    result = cyhal_i2c_master_read(&I2C_scb3,(uint16_t)address, pins, 1, 10, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

	return PCA9554_OK;
}

PCA9554_RET_TYPE pca9554_read_config_pol(uint8_t address, uint8_t* pins)
{
	cy_rslt_t result;
	uint8_t i2c_data = PCA9554_POLARITY_CMD;

    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, &i2c_data, 1, 100, false);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

    result = cyhal_i2c_master_read(&I2C_scb3,(uint16_t)address, pins, 1, 100, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

	return PCA9554_OK;
}

PCA9554_RET_TYPE pca9554_write_config_dir(uint8_t address, uint8_t pins)
{
	cy_rslt_t result;
	uint8_t i2c_data[3];
	i2c_data[0] = PCA9554_CONFIG_CMD;
    i2c_data[1] = pins;

    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, i2c_data, 2, 100, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

    return PCA9554_OK;
}

PCA9554_RET_TYPE pca9554_write_config_pol(uint8_t address, uint8_t pins)
{
	cy_rslt_t result;
	uint8_t i2c_data[3];
	i2c_data[0] = PCA9554_POLARITY_CMD;
    i2c_data[1] = pins;

    result = cyhal_i2c_master_write(&I2C_scb3,(uint16_t)address, i2c_data, 2, 100, true);
    if (result != CY_RSLT_SUCCESS)
    {
    	return PCA9554_COM_ERR;
    }

    return PCA9554_OK;
}
