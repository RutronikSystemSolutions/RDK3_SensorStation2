/*
 * DIO59020.c
 *
 *  Created on: Jun 10, 2021
 *      Authors: GDR, IUS
 */

#include "dio59020.h"

#include "stdlib.h"

/*Global variables*/
extern cyhal_i2c_t I2C_scb3;
extern cyhal_i2c_cfg_t I2C_cfg;

/*Initializes the I2C connected with DIO59020*/
uint32_t dio_i2c_init(void)
{
cy_rslt_t result;

	    I2C_cfg.is_slave = false;
	    I2C_cfg.address = 0;
	    I2C_cfg.frequencyhal_hz = 100000UL;
	    result = cyhal_i2c_init(&I2C_scb3, ARDU_SDA, ARDU_SCL, NULL);
	    if (result != CY_RSLT_SUCCESS)
	    {
	    	return (uint32_t)result;
	    }
	    result = cyhal_i2c_configure(&I2C_scb3, &I2C_cfg);
	    CyDelay(100);

		return (uint32_t)result;
}

/*Write to DIO59020 over the I2C*/
uint32_t dio_write(uint16_t reg, uint8_t* data, uint16_t size)
{
	cy_rslt_t result;
	uint8_t* i2c_data = NULL;

	/*Allocate buffer for a register and the data*/
    i2c_data = malloc(size+1);
    if(i2c_data == NULL)
    {
    	return 1;
    }

    /*Copy register register and all the data*/
    i2c_data[0] = reg;
    memcpy(&i2c_data[1], data, size);

    /*Execute write command*/
    result = cyhal_i2c_master_write( &I2C_scb3, DIO_SLAVE_ADDR, i2c_data, size+1, 100, true );

    /*Free allocated buffer and exit*/
    free(i2c_data);
    return (uint32_t)result;
}

/*Read from DIO59020 over the I2C*/
uint32_t dio_read(uint8_t reg, uint8_t* data, uint16_t size)
{
	cy_rslt_t result;

    result = cyhal_i2c_master_write( &I2C_scb3, DIO_SLAVE_ADDR, &reg, 1, 100, false );
    if (result != CY_RSLT_SUCCESS)
    {
    	return (uint32_t)result;
    }

    result = cyhal_i2c_master_read( &I2C_scb3, DIO_SLAVE_ADDR, data, size, 100, true );
    return (uint32_t)result;
}

/*Check if DIO59020 device is responsive*/
_Bool dio_online(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(IC_INFO_REG, &data, 1);
	if(result == 0)
	{
		if(data == IC_INFO_D_VALUE)
		{
			return true;
		}
	}

	return false;
}


/*Read the MONITOR Register*/
uint32_t dio_monitor_read(dio_monitor_reg_status_t* status)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(MONITOR_REG, &data, 1);

	status->CV_status = 		(_Bool)(data & CV);
	status->VBUS_VALID_status = (_Bool)(data & VBUS_VALID) >> 1;
	status->IBUS_status = 		(_Bool)(data & IBUS) >> 2;
	status->CHG_status = 		(_Bool)(data & CHG) >> 3;
	status->T_100_status = 		(_Bool)(data & T_100) >> 4;
	status->LINCHG_status = 	(_Bool)(data & LINCHG) >> 5;
	status->VBAT_CMP_status = 	(_Bool)(data & VBAT_CMP) >> 6;
	status->ITERM_status = 		(_Bool)(data & ITERM) >> 7;

	return result;
}

/*Disables the charger, puts into the hi-impedance mode*/
uint32_t dio_charger_disable(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL1, &data, 1);
	if(result == 0)
	{
		data |= CTRL1_CE;
		data |= CTRL1_HZ_MODE;

		result = dio_write(CONTROL1, &data, 1);
	}

	return result;
}

/*Enables the charger, exits from the hi-impedance mode*/
uint32_t dio_charger_enable(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL1, &data, 1);
	if(result == 0)
	{
		data &= ~CTRL1_CE;
		data &= ~CTRL1_HZ_MODE;

		result = dio_write(CONTROL1, &data, 1);
	}

	return result;
}

/*Sets the input current limit*/
uint32_t dio_set_current_lim(input_curr_lim_t curr_limit)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL1, &data, 1);
	if(result == 0)
	{
		data &= ~CTRL1_INLIM;
		data |= (curr_limit << 6);

		result = dio_write(CONTROL1, &data, 1);
	}

	return result;
}

/*Enables the Boost Mode*/
uint32_t dio_booster_enable(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL1, &data, 1);
	if(result == 0)
	{
		data |= CTRL1_OPA_MODE;

		result = dio_write(CONTROL1, &data, 1);
	}

	return result;
}

/*Disables the Boost Mode*/
uint32_t dio_booster_disable(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL1, &data, 1);
	if(result == 0)
	{
		data &= ~CTRL1_OPA_MODE;

		result = dio_write(CONTROL1, &data, 1);
	}

	return result;
}

/*Disables STAT pin*/
uint32_t dio_stat_pin_disable(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL0, &data, 1);
	if(result == 0)
	{
		data &= ~CTRL0_EN_STAT;

		result = dio_write(CONTROL0, &data, 1);
	}

	return result;
}

/*Enables STAT pin*/
uint32_t dio_stat_pin_enable(void)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL0, &data, 1);
	if(result == 0)
	{
		data |= CTRL0_EN_STAT;

		result = dio_write(CONTROL0, &data, 1);
	}

	return result;
}

/*Reads the charger status*/
uint32_t dio_get_status(charge_stat_t* status)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL0, &data, 1);
	if(result == 0)
	{
		*status = (data & CTRL0_STAT) >> 4;
	}

	return result;
}

/*Reads the voltage boost status*/
uint32_t dio_get_boost(_Bool* boost_mode)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL0, &data, 1);
	if(result == 0)
	{
		*boost_mode = (_Bool)((data & CTRL0_BOOST) >> 3);
	}

	return result;
}

/*Reads the charger faults*/
uint32_t dio_get_fault(chrg_fault_t* charger_fault)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(CONTROL0, &data, 1);
	if(result == 0)
	{
		data &= CTRL0_CHG_FAULT;

		*charger_fault = data;
	}

	return result;
}

/*Configures OTG pin*/
uint32_t dio_otg_pin_config(_Bool otg_pl, _Bool otg_en)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(OREG, &data, 1);
	if(result == 0)
	{
		data &= ~OREG_OTG_EN;
		data &= ~OREG_OTG_PL;
		data |= otg_en;
		data |= (otg_pl << 1);

		result = dio_write(OREG, &data, 1);
	}

	return result;
}

/*Sets the maximum battery charge current*/
uint32_t dio_set_batt_current(batt_chrg_curr_t curr_vref)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(IBAT, &data, 1);
	if(result == 0)
	{
		data &= ~IBAT_ICHRG;
		data |= (curr_vref << 4);

		result = dio_write(IBAT, &data, 1);
	}

	return result;
}

/*Sets the battery charge termination current*/
uint32_t dio_set_batt_term_curr(batt_term_curr_t curr_vref)
{
	uint32_t result;
	uint8_t data = 0;

	result = dio_read(IBAT, &data, 1);
	if(result == 0)
	{
		data &= ~IBAT_ITERM;
		data |= curr_vref;

		result = dio_write(IBAT, &data, 1);
	}

	return result;
}
