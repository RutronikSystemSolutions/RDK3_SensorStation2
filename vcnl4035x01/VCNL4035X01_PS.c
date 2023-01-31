/*
 * VCNL4035X01_PS.c
 *
 * Created  : 9 November 2020
 * Modified : 6 May 2021
 * Author   : HWanyusof
 * Version	: 1.0
 */

#include "VCNL4035X01_Prototypes.h"
#include "VCNL4035X01.h"
#include "I2C_Functions.h"

extern int I2C_Bus;

//****************************************************************************************************
//*****************************************Sensor API*************************************************

/*Set the PS On/Off Duty Ratio
 *VCNL4035X01_SET_PS_DUTY(Byte DutyRatio)
 *Byte DutyRatio - Input Parameter:
 *
 * VCNL4035X01_PS_DR_1_40
 * VCNL4035X01_PS_DR_1_80
 * VCNL4035X01_PS_DR_1_160
 * VCNL4035X01_PS_DR_1_320
 */
void VCNL4035X01_SET_PS_DUTY(Byte DutyRatio)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_1;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_DR_1_40|VCNL4035X01_PS_DR_1_80|VCNL4035X01_PS_DR_1_160|VCNL4035X01_PS_DR_1_320))|DutyRatio;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Persistence
 *VCNL4035X01_SET_PS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4035X01_PS_PERS_1
 * VCNL4035X01_PS_PERS_2
 * VCNL4035X01_PS_PERS_3
 * VCNL4035X01_PS_PERS_4
 */
void VCNL4035X01_SET_PS_PERS(Byte Pers)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_1;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_PERS_1|VCNL4035X01_PS_PERS_2|VCNL4035X01_PS_PERS_3|VCNL4035X01_PS_PERS_4))|Pers;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}
/*Set the Integration Time
 *VCNL4035X01_SET_PS_IT(Byte IntegrationTime)
 *Byte IntegrationTime - Input Parameter:
 *
 * VCNL4035X01_PS_IT_1T
 * VCNL4035X01_PS_IT_1_5T
 * VCNL4035X01_PS_IT_2T
 * VCNL4035X01_PS_IT_2_5T
 * VCNL4035X01_PS_IT_3T
 * VCNL4035X01_PS_IT_3_5T
 * VCNL4035X01_PS_IT_4T
 * VCNL4035X01_PS_IT_8T
 */
void VCNL4035X01_SET_PS_IT(Byte IntegrationTime)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_1;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_IT_1T|VCNL4035X01_PS_IT_1_5T|VCNL4035X01_PS_IT_2T|VCNL4035X01_PS_IT_2_5T|VCNL4035X01_PS_IT_3T|VCNL4035X01_PS_IT_3_5T|VCNL4035X01_PS_IT_4T|VCNL4035X01_PS_IT_8T))|IntegrationTime;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Turn the PS Sensor On/Off
 *VCNL4035X01_SET_PS_SD(Byte SDBit)
 *Byte SDBit - Input Parameter:
 *
 * VCNL4035X01_PS_SD_EN
 * VCNL4035X01_PS_SD_DIS
 */
void VCNL4035X01_SET_PS_SD(Byte SDBit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_1;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_SD_DIS|VCNL4035X01_PS_SD_EN))|SDBit;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable the Gesture Interrupt
 *VCNL4035X01_SET_GESTURE_INT(Byte gesture_int)
 *Byte gesture_int - Input Parameter:
 *
 * VCNL4035X01_PS_GESTURE_INT_EN
 * VCNL4035X01_PS_GESTURE_INT_DIS
 */
void VCNL4035X01_SET_GESTURE_INT(Byte gesture_int)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_GESTURE_INT_EN|VCNL4035X01_PS_GESTURE_INT_DIS))|gesture_int;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable the Gesture Mode
 *VCNL4035X01_SET_GESTURE_MODE(Byte gesture_mode)
 *Byte gesture_mode - Input Parameter:
 *
 * VCNL4035X01_PS_GESTURE_MODE_EN
 * VCNL4035X01_PS_GESTURE_MODE_DIS
 */
void VCNL4035X01_SET_GESTURE_MODE(Byte gesture_mode)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_GESTURE_MODE_EN|VCNL4035X01_PS_GESTURE_MODE_DIS))|gesture_mode;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Gain
 *VCNL4035X01_SET_PS_Gain(Byte Gain)
 *Byte Gain - Input Parameter:
 *
 * VCNL4035X01_PS_GAIN_2_STEP
 * VCNL4035X01_PS_GAIN_SINGLEx8
 * VCNL4035X01_PS_GAIN_SINGLEx1
 */
void VCNL4035X01_SET_PS_Gain(Byte Gain)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_GAIN_2_STEP|VCNL4035X01_PS_GAIN_SINGLEx8|VCNL4035X01_PS_GAIN_SINGLEx1))|Gain;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the PS Output size (12/16Bits)
 *VCNL4035X01_SET_PS_HD(Byte HDBit)
 *Byte HDBit - Input Parameter:
 *
 * VCNL4035X01_PS_HD_12Bits
 * VCNL4035X01_PS_HD_16Bits
 */
void VCNL4035X01_SET_PS_HD(Byte HDBit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_HD_12Bits|VCNL4035X01_PS_HD_16Bits))|HDBit;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Sensitivity
 *VCNL4035X01_SET_PS_NS(Byte NSBit)
 *Byte NSBit - Input Parameter:
 *
 * VCNL4035X01_PS_NS_2STEP_MODE_X4
 * VCNL4035X01_PS_NS_2STEP_MODE
 */
void VCNL4035X01_SET_PS_NS(Byte NSBit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_NS_2STEP_MODE_X4|VCNL4035X01_PS_NS_2STEP_MODE))|NSBit;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Interrupt Mode
 *VCNL4035X01_SET_PS_INT(Byte InterruptMode)
 *Byte InterruptMode - Input Parameter:
 *
 * VCNL4035X01_PS_INT_DIS
 * VCNL4035X01_PS_INT_CLOSE
 * VCNL4035X01_PS_INT_AWAY
 * VCNL4035X01_PS_INT_CLOSE_AWAY
 */
void VCNL4035X01_SET_PS_INT(Byte InterruptMode)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_INT_DIS|VCNL4035X01_PS_INT_CLOSE|VCNL4035X01_PS_INT_AWAY|VCNL4035X01_PS_INT_CLOSE_AWAY))|InterruptMode;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable Low Power Mode
 *VCNL4035X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit)
 *Byte LOW_I_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_I_LOW_EN
 * VCNL4035X01_PS_I_LOW_DIS
 */
void VCNL4035X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_I_LOW_DIS|VCNL4035X01_PS_I_LOW_EN))|LOW_I_Bit;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set IRED input to be Driven by the Internal Driver
 *VCNL4035X01_SET_PS_IRED_select(Byte ired)
 *Byte ired - Input Parameter:
 *
 * VCNL4035X01_PS_IRED_1
 * VCNL4035X01_PS_IRED_2
 * VCNL4035X01_PS_IRED_3
 */
void VCNL4035X01_SET_PS_IRED_select(Byte ired)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_IRED_1|VCNL4035X01_PS_IRED_2|VCNL4035X01_PS_IRED_3))|ired;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable Smart Persistence
 *VCNL4035X01_SET_PS_SMART_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4035X01_PS_SMART_PERS_EN
 * VCNL4035X01_PS_SMART_PERS_DIS
 */
void VCNL4035X01_SET_PS_SMART_PERS(Byte Pers)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_SMART_PERS_DIS|VCNL4035X01_PS_SMART_PERS_EN))|Pers;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable Active Force or Auto Mode
 *VCNL4035X01_SET_PS_AF(Byte AF_Bit)
 *Byte AF_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_AUTO
 * VCNL4035X01_PS_AF_EN
 */
void VCNL4035X01_SET_PS_AF(Byte AF_Bit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_AUTO|VCNL4035X01_PS_AF_EN))|AF_Bit;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable Trigger for AF Mode
 *VCNL4035X01_SET_PS_TRIG(Byte TriggerBit)
 *Byte TriggerBit - Input Parameter:
 *
 * VCNL4035X01_PS_TRIG_EN
 * VCNL4035X01_PS_TRIG_DIS
 */
void VCNL4035X01_SET_PS_TRIG(Byte TriggerBit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_TRIG_DIS|VCNL4035X01_PS_TRIG_EN))|TriggerBit;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Proximity Mode (Normal/Logic)
 *VCNL4035X01_SET_PS_MS(Byte MS_Bit)
 *Byte MS_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_MS_NORMAL
 * VCNL4035X01_PS_MS_LOGIC
 */
void VCNL4035X01_SET_PS_MS(Byte MS_Bit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_MS_NORMAL|VCNL4035X01_PS_MS_LOGIC))|MS_Bit;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable Sunlight Cancellation
 *VCNL4035X01_SET_PS_SC_EN(Byte SunlightBit)
 *Byte SunlightBit - Input Parameter:
 *
 * VCNL4035X01_PS_SC_EN
 * VCNL4035X01_PS_SC_DIS
 */
void VCNL4035X01_SET_PS_SC_EN(Byte SunlightBit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_PS_SC_DIS|VCNL4035X01_PS_SC_EN))|SunlightBit;
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Sunlight Cancellation Current
 *VCNL4035X01_SET_PS_SC_CUR(Byte SC_Current)
 *Byte SC_Current - Input Parameter:
 *
 * VCNL4035X01_PS_SC_CURx1
 * VCNL4035X01_PS_SC_CURx2
 * VCNL4035X01_PS_SC_CURx4
 * VCNL4035X01_PS_SC_CURx8
 */
void VCNL4035X01_SET_PS_SC_CUR(Byte SC_Current)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_MS;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]);
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_SC_CURx1|VCNL4035X01_PS_SC_CURx2|VCNL4035X01_PS_SC_CURx4|VCNL4035X01_PS_SC_CURx8))|SC_Current;
	WriteI2C_Bus(&VCNL4035X01_Data);

}

/*Set the Sunlight Capability
 *VCNL4035X01_SET_PS_SP(Byte SP_Bit)
 *Byte SP_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_SPx1
 * VCNL4035X01_PS_SPx1_5
 */
void VCNL4035X01_SET_PS_SP(Byte SP_Bit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_MS;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]);
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_SPx1|VCNL4035X01_PS_SPx1_5))|SP_Bit;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Output of Sunlight Protect Mode
 *VCNL4035X01_SET_PS_SPO(Byte SPO_Bit)
 *Byte SPO_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_SPO_00
 * VCNL4035X01_PS_SPO_FF
 */
void VCNL4035X01_SET_PS_SPO(Byte SPO_Bit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_MS;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]);
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_SPO_00|VCNL4035X01_PS_SPO_FF))|SPO_Bit;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the LED current
 *VCNL4035X01_SET_PS_LED_I(Byte IRED_Current))
 *Byte IRED_Current - Input Parameter:
 *
 * VCNL4035X01_PS_LED_I_50mA
 * VCNL4035X01_PS_LED_I_75mA
 * VCNL4035X01_PS_LED_I_100mA
 * VCNL4035X01_PS_LED_I_120mA
 * VCNL4035X01_PS_LED_I_140mA
 * VCNL4035X01_PS_LED_I_160mA
 * VCNL4035X01_PS_LED_I_180mA
 * VCNL4035X01_PS_LED_I_200mA
 */
void VCNL4035X01_SET_PS_LED_I(Byte IRED_Current)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_MS;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]);
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_PS_LED_I_50mA|VCNL4035X01_PS_LED_I_75mA|VCNL4035X01_PS_LED_I_100mA|VCNL4035X01_PS_LED_I_120mA|VCNL4035X01_PS_LED_I_140mA|VCNL4035X01_PS_LED_I_160mA|VCNL4035X01_PS_LED_I_180mA|VCNL4035X01_PS_LED_I_200mA))|IRED_Current;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the PS Cancellation
 *VCNL4035X01_SET_PS_CANC(Word CancelValue)
 *Word CancelValue - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_PS_CANC(Word CancelValue)
{
	Byte LowByte = CancelValue;
	Byte HighByte = CancelValue>>8;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CANC;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = LowByte;
	VCNL4035X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Low Threshold
 *VCNL4035X01_SET_PS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_PS_LowThreshold(Word LowThreshold)
{
	Byte LowByte = LowThreshold;
	Byte HighByte = LowThreshold>>8;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_THDL;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = LowByte;
	VCNL4035X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the High Threshold
 *VCNL4035X01_SET_PS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_PS_HighThreshold(Word HighThreshold)
{
	Byte LowByte = HighThreshold;
	Byte HighByte = HighThreshold>>8;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_THDH;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = LowByte;
	VCNL4035X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Read the PS Data
 *VCNL4035X01_GET_PS_Data(Byte Reg)
 *Byte Reg - Input Parameter:
 *
 * VCNL4035X01_PS_DATA_1
 * VCNL4035X01_PS_DATA_2
 * VCNL4035X01_PS_DATA_3
 *
 *returns PS Data between 0d0 and 0d65535
 */
Word VCNL4035X01_GET_PS_Data(Byte Reg)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = Reg;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	return (VCNL4035X01_Data.RData[1]<<8|VCNL4035X01_Data.RData[0]);
}

/*Read the PS Interruppt Flag
 *VCNL4035X01_GET_PS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 11
 */
Word VCNL4035X01_GET_PS_Interrupt()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_INT_FLAG;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	return (VCNL4035X01_Data.RData[1]);
}

/*Read Register value
 *VCNL4035X01_READ_Reg(Byte Reg)
 *Byte Reg - Input Parameter:
 *
 * VCNL4035X01_ALS_CONF_1
 * VCNL4035X01_ALS_CONF_2
 * VCNL4035X01_ALS_THDH
 * VCNL4035X01_ALS_THDL
 * VCNL4035X01_PS_CONF_1
 * VCNL4035X01_PS_CONF_2
 * VCNL4035X01_PS_CONF_3
 * VCNL4035X01_PS_CONF_MS
 * VCNL4035X01_PS_CANC
 * VCNL4035X01_PS_THDL
 * VCNL4035X01_PS_THDH
 * VCNL4035X01_PS_DATA_1
 * VCNL4035X01_PS_DATA_2
 * VCNL4035X01_PS_DATA_3
 * VCNL4035X01_ALS_DATA
 * VCNL4035X01_WHITE_DATA
 * VCNL4035X01_INT_FLAG
 * VCNL4035X01_ID
 *
 *returns Register Value between 0d0/0x00 and 0d65535/0xFFFF
 */
Word VCNL4035X01_READ_Reg(Byte Reg)
{
	Word RegValue;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = Reg;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	RegValue = VCNL4035X01_Data.RData[1]<<8|VCNL4035X01_Data.RData[0];
	return RegValue;
}

/*Read Gesture Mode Data
 *VCNL4035X01_GET_Gesture_Mode_Data(Word *Data1, Word *Data2, Word *Data3)
 *Word *Data1, Word *Data2, Word *Data3 - Input Parameter:
 *
 * Data1 - Pointers to gesture gata from VCNL4035X01_PS_DATA_1
 * Data2 - Pointers to gesture gata from VCNL4035X01_PS_DATA_2
 * Data3 - Pointers to gesture gata from VCNL4035X01_PS_DATA_3
 *
 *returns Register Value between 0d0/0x00 and 0d65535/0xFFFF via pointers
 */
void VCNL4035X01_GET_Gesture_Mode_Data(Word *Data1, Word *Data2, Word *Data3)
{
	struct GestureTransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus_Gesture_Mode(&VCNL4035X01_Data);
	*Data1 = VCNL4035X01_Data.RData[1]<<8|VCNL4035X01_Data.RData[0];
	*Data2 = VCNL4035X01_Data.RData[3]<<8|VCNL4035X01_Data.RData[2];
	*Data3 = VCNL4035X01_Data.RData[5]<<8|VCNL4035X01_Data.RData[4];
}

/*Read the Gesture Data Ready Flag
 *returns 1 when Gesture Data Ready and 0 otherwise
 */
bool VCNL4035X01_GET_Gesture_Data_Ready_Flag()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_INT_FLAG;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[1] & 0x80) == 0x80) {return 1;}
    else
    return 0;
}

/*Read the PS_SD bit
*returns 1 for Shutdown and 0 for Sensor On
*/
bool VCNL4035X01_GET_PS_SD_Bit()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_1;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[0] & 0x01) == 0x01) {return 1;}
    else
    return 0;
}

/*Read the PS_AF bit
 *returns 1 for AF Mode and 0 for Auto Mode
 */
bool VCNL4035X01_GET_PS_AF_Bit()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[0] & 0x08) == 0x08) {return 1;}
    else
    return 0;
}

/*Read the LED_I_LOW bit
 *returns 1 for Low Power Mode and 0 for Normal Mode
 */
bool VCNL4035X01_GET_LED_I_LOW_Bit()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[0] & 0x80) == 0x80) {return 1;}
    else
    return 0;
}

/*Read the GESTURE_MODE bit
 *returns 1 for Gesture Mode and 0 for Gesture Mode Disable
 */
bool VCNL4035X01_GET_GESTURE_MODE_Bit()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[1] & 0x40) == 0x40) {return 1;}
    else
    return 0;
}

/*Read Device ID
 *Returns ID
 */
Word VCNL4035X01_GET_ID()
{
	Word RegValue;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ID;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	RegValue = VCNL4035X01_Data.RData[1]<<8|VCNL4035X01_Data.RData[0];
	return RegValue;
}
