/*
 * VCNL4035X01_ALS.c
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

/*Turn On/Off the ALS Sensor
 *VCNL4035X01_SET_ALS_SD(Byte SD_Bit)
 *Byte SD_Bit - Input Parameter:
 *
 * VCNL4035X01_ALS_SD_DIS
 * VCNL4035X01_ALS_SD_EN
 */
void VCNL4035X01_SET_ALS_SD(Byte SD_Bit)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_ALS_SD_EN|VCNL4035X01_ALS_SD_DIS))|SD_Bit;
	VCNL4035X01_Data.WData[1] = VCNL4035X01_Data.RData[1];
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Integration Time
 *VCNL4035X01_SET_ALS_IT(Byte IntTime)
 *Byte IntTime - Input Parameter:
 *
 * VCNL4035X01_ALS_IT_50MS
 * VCNL4035X01_ALS_IT_100MS
 * VCNL4035X01_ALS_IT_200MS
 * VCNL4035X01_ALS_IT_400MS
 * VCNL4035X01_ALS_IT_800MS
 */
void VCNL4035X01_SET_ALS_IT(Byte IntTime)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_ALS_IT_50MS|VCNL4035X01_ALS_IT_100MS|VCNL4035X01_ALS_IT_200MS|VCNL4035X01_ALS_IT_400MS|VCNL4035X01_ALS_IT_800MS))|IntTime;
	VCNL4035X01_Data.WData[1] = VCNL4035X01_Data.RData[1];
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Typical Dynamic Range
 *VCNL4035X01_SET_ALS_HD(Byte HD)
 *Byte HD - Input Parameter:
 *
 * VCNL4035X01_ALS_HD_X1
 * VCNL4035X01_ALS_HD_X2
 */
void VCNL4035X01_SET_ALS_HD(Byte HD)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0] = (VCNL4035X01_Data.RData[0]&~(VCNL4035X01_ALS_HD_X1|VCNL4035X01_ALS_HD_X2))|HD;
	VCNL4035X01_Data.WData[1] = VCNL4035X01_Data.RData[1];
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the Persistence
 *VCNL4035X01_SET_ALS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4035X01_ALS_PERS_1
 * VCNL4035X01_ALS_PERS_2
 * VCNL4035X01_ALS_PERS_4
 * VCNL4035X01_ALS_PERS_8
 */
void VCNL4035X01_SET_ALS_PERS(Byte Pers)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0]=(VCNL4035X01_Data.RData[0]&~(VCNL4035X01_ALS_PERS_1|VCNL4035X01_ALS_PERS_2|VCNL4035X01_ALS_PERS_4|VCNL4035X01_ALS_PERS_8))|Pers;
	VCNL4035X01_Data.WData[1] = VCNL4035X01_Data.RData[1];
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Enable/Disable Interrupt
 *VCNL4035X01_SET_ALS_Interrupt(Byte Interrupt)
 *Byte Interrupt - Input Parameter:
 *
 * VCNL4035X01_ALS_INT_EN
 * VCNL4035X01_ALS_INT_DIS
 */
void VCNL4035X01_SET_ALS_Interrupt(Byte Interrupt)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0]=(VCNL4035X01_Data.RData[0]&~(VCNL4035X01_ALS_INT_EN|VCNL4035X01_ALS_INT_DIS))|Interrupt;
	VCNL4035X01_Data.WData[1] = VCNL4035X01_Data.RData[1];
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the ALS Sensitivity
 *VCNL4035X01_SET_ALS_NS(Byte ALS_NS)
 *Byte ALS_NS - Input Parameter:
 *
 * VCNL4035X01_ALS_NS_X1
 * VCNL4035X01_ALS_NS_X2
 */
void VCNL4035X01_SET_ALS_NS(Byte ALS_NS)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_2;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0]=VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_ALS_NS_X1|VCNL4035X01_ALS_NS_X2))|ALS_NS;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Turn On/Off the White Channel
 *VCNL4035X01_SET_WHITE_SD(Byte WhiteSD)
 *Byte WhiteSD - Input Parameter:
 *
 * VCNL4035X01_ALS_WHITE_SD_EN
 * VCNL4035X01_ALS_WHITE_SD_DIS
 */
void VCNL4035X01_SET_WHITE_SD(Byte WhiteSD)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_2;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	VCNL4035X01_Data.WData[0]=VCNL4035X01_Data.RData[0];
	VCNL4035X01_Data.WData[1] = (VCNL4035X01_Data.RData[1]&~(VCNL4035X01_ALS_WHITE_SD_EN|VCNL4035X01_ALS_WHITE_SD_DIS))|WhiteSD;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Read the ALS Data
 *VCNL4035X01_GET_ALS_Data() returns ALS Data between 0d0 and 0d65535
 */
Word VCNL4035X01_GET_ALS_Data()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_DATA;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	return ((VCNL4035X01_Data.RData[1]<<8)|VCNL4035X01_Data.RData[0]);
}

/*Read the White Channel Data
 *VCNL4035X01_GET_White_Data() returns White Data between 0d0 and 0d65535
 */
Word VCNL4035X01_GET_White_Data()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_WHITE_DATA;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	return ((VCNL4035X01_Data.RData[1]<<8)|VCNL4035X01_Data.RData[0]);
}

/*Set the Low threshold
 *VCNL4035X01_SET_ALS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_ALS_LowThreshold(Word LowThreshold)
{
	Byte LowByte = LowThreshold;
	Byte HighByte = LowThreshold>>8;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_THDL;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = LowByte;
	VCNL4035X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Set the High Threshold
 *VCNL4035X01_SET_ALS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_ALS_HighThreshold(Word HighThreshold)
{
	Byte LowByte = HighThreshold;
	Byte HighByte = HighThreshold>>8;
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_THDH;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = LowByte;
	VCNL4035X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

/*Read the ALS Interrupt Flag
 *VCNL4035X01_GET_ALS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 11
 */
Word VCNL4035X01_GET_ALS_Interrupt()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_INT_FLAG;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	return (VCNL4035X01_Data.RData[1]);
}

/*Read the ALS_SD bit
 *returns 1 for Shutdown and 0 for ALS On
 */
bool VCNL4035X01_GET_ALS_SD_Bit()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[0] & 0x01) == 0x01) {return 1;}
	else
	return 0;
}

/*Read the WHITE_SD bit
 *returns 1 for White Mode and 0 for White Mode Disable (Normal ALS)
 */
bool VCNL4035X01_GET_WHITE_SD_Bit()
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_2;
    VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL4035X01_Data);
	if ((VCNL4035X01_Data.RData[1] & 0x01) == 0x01) {return 1;}
	else
	return 0;
}
