/*
 * DIO59020.h
 *
 *  Created on: Jun 10, 2021
 *      Authors: GDR, IUS
 */

#ifndef DIO59020_H_
#define DIO59020_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

/* DIO59020 I2C 7-bit address */
#define DIO_SLAVE_ADDR 	0x6A

/* DIO59020 registers */
#define CONTROL0 		0x00	//Default Value=X1XX0XXX
#define CONTROL1 		0x01 	//Default Value=0111 0000 (70h)
#define OREG 			0x02    //Default Value=0000 1010 (0Ah)
#define IC_INFO_REG 	0x03    //Default Value=1001 0100 (94h)
#define IBAT 			0x04	//Default Value=1000 1001 (89h)
#define SP_CHARGER 		0x05	//Default Value=011X X100
#define RECHARGE_VOLT 	0x07 	//Default Value=0000 0001 (01h)
#define MONITOR_REG		0x10

/*CONTROL0 Register Bits */
#define CTRL0_EN_STAT	0x40
#define CTRL0_STAT		0x30
#define CTRL0_BOOST		0x08
#define CTRL0_CHG_FAULT	0x07

/*CONTROL1 Register Bits */
#define CTRL1_INLIM		0xC0
#define CTRL1_TE		0x08
#define CTRL1_CE		0x04
#define CTRL1_HZ_MODE	0x02
#define CTRL1_OPA_MODE	0x01

/*OREG Register Bits */
#define OREG_OREG		0xFC
#define OREG_OTG_PL		0x02
#define OREG_OTG_EN		0x01

/*IBAT Register Bits */
#define IBAT_ICHRG		0x70
#define IBAT_ITERM		0x07

/*MONITOR Register Bits */
#define ITERM 			0x80
#define VBAT_CMP		0x40
#define LINCHG			0x20
#define T_100			0x10
#define CHG				0x08
#define IBUS			0x04
#define VBUS_VALID 		0x02
#define CV 				0x01

/*IC_INFO Register Default Value*/
#define IC_INFO_D_VALUE 0x94

typedef enum
{
	LIMIT_100 = 0x00,
	LIMIT_500,
	LIMIT_800,
	LIMIT_INF

}input_curr_lim_t;

typedef enum
{
	CHRG_READY = 0x00,
	CHRG_IN_PROGRESS,
	CHRG_DONE,
	CHRG_FAULT
}charge_stat_t;

typedef enum
{
	CHRG_NORMAL = 0x00,
	CHRG_VBUS_OVP,
	CHRG_SLEEP_MODE,
	CHRG_POOR_INPUT,
	CHRG_BATT_OVP,
	CHRG_THERMAL,
	CHRG_RESERVED,
	CHRG_NO_BATT

}chrg_fault_t;

typedef enum
{
	CURR_VREF_37_5 = 0x00,
	CURR_VREF_44_4,
	CURR_VREF_51_2,
	CURR_VREF_57_5,
	CURR_VREF_71_3,
	CURR_VREF_78_1,
	CURR_VREF_91_9,
	CURR_VREF_101_8

}batt_chrg_curr_t;

typedef enum
{
	CURR_VREF_3_1 = 0x00,
	CURR_VREF_6_3,
	CURR_VREF_9_4,
	CURR_VREF_12_5,
	CURR_VREF_15_6,
	CURR_VREF_18_8,
	CURR_VREF_21_9,
	CURR_VREF_25


}batt_term_curr_t;

typedef struct
{
	_Bool ITERM_status;
	_Bool VBAT_CMP_status;
	_Bool LINCHG_status;
	_Bool T_100_status;
	_Bool CHG_status;
	_Bool IBUS_status;
	_Bool VBUS_VALID_status;
	_Bool CV_status;

}dio_monitor_reg_status_t;

typedef struct
{
	_Bool EN_status;
	_Bool STAT_status;
	_Bool BOOST_status;
	_Bool FAULT_status;

}dio_CONTROL0_reg_status_t;

/*Exported global variables*/
extern cyhal_i2c_t I2C_scb3;
extern cyhal_i2c_cfg_t I2C_cfg;

/*Exported functions*/
uint32_t dio_i2c_init(void);
uint32_t dio_write(uint16_t reg, uint8_t* data, uint16_t size);
uint32_t dio_read(uint8_t reg, uint8_t* data, uint16_t size);
uint32_t dio_monitor_read(dio_monitor_reg_status_t* status);
_Bool dio_online(void);
uint32_t dio_charger_disable(void);
uint32_t dio_charger_enable(void);
uint32_t dio_set_current_lim(input_curr_lim_t curr_limit);
uint32_t dio_booster_enable(void);
uint32_t dio_booster_disable(void);
uint32_t dio_stat_pin_disable(void);
uint32_t dio_stat_pin_enable(void);
uint32_t dio_get_status(charge_stat_t* status);
uint32_t dio_get_boost(_Bool* boost_mode);
uint32_t dio_get_fault(chrg_fault_t* charger_fault);
uint32_t dio_otg_pin_config(_Bool otg_pl, _Bool otg_en);
uint32_t dio_set_batt_current(batt_chrg_curr_t curr_vref);
uint32_t dio_set_batt_term_curr(batt_term_curr_t curr_vref);

#endif /* DIO59020_H_ */
