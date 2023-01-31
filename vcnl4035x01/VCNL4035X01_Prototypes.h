/*
 *VCNL4035X01_Prototypes.h
 *
 * Created  : 9 November 2020
 * Modified : 6 May 2021
 * Author   : HWanyusof
 * Version	: 1.0
 */

#include "typedefinition.h"


/*Turn On/Off the ALS Sensor
 *VCNL4035X01_SET_ALS_SD(Byte SD_Bit)
 *Byte SD_Bit - Input Parameter:
 *
 * VCNL4035X01_ALS_SD_DIS
 * VCNL4035X01_ALS_SD_EN
 */
void VCNL4035X01_SET_ALS_SD(Byte SD_Bit);

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
void VCNL4035X01_SET_ALS_IT(Byte IntTime);

/*Set the Typical Dynamic Range
 *VCNL4035X01_SET_ALS_HD(Byte HD)
 *Byte HD - Input Parameter:
 *
 * VCNL4035X01_ALS_HD_X1
 * VCNL4035X01_ALS_HD_X2
 */
void VCNL4035X01_SET_ALS_HD(Byte HD);

/*Set the Persistence
 *VCNL4035X01_SET_ALS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4035X01_ALS_PERS_1
 * VCNL4035X01_ALS_PERS_2
 * VCNL4035X01_ALS_PERS_4
 * VCNL4035X01_ALS_PERS_8
 */
void VCNL4035X01_SET_ALS_PERS(Byte Pers);

/*Enable/Disable Interrupt
 *VCNL4035X01_SET_ALS_Interrupt(Byte Interrupt)
 *Byte Interrupt - Input Parameter:
 *
 * VCNL4035X01_ALS_INT_EN
 * VCNL4035X01_ALS_INT_DIS
 */
void VCNL4035X01_SET_ALS_Interrupt(Byte Interrupt);

/*Set the ALS Sensitivity
 *VCNL4035X01_SET_ALS_NS(Byte ALS_NS)
 *Byte ALS_NS - Input Parameter:
 *
 * VCNL4035X01_ALS_NS_X1
 * VCNL4035X01_ALS_NS_X2
 */
void VCNL4035X01_SET_ALS_NS(Byte ALS_NS);

/*Turn On/Off the White Channel
 *VCNL4035X01_SET_WHITE_SD(Byte WhiteSD)
 *Byte WhiteSD - Input Parameter:
 *
 * VCNL4035X01_ALS_WHITE_SD_EN
 * VCNL4035X01_ALS_WHITE_SD_DIS
 */
void VCNL4035X01_SET_WHITE_SD(Byte WhiteSD);

/*Read the ALS Data
 *VCNL4035X01_GET_ALS_Data() returns ALS Data between 0d0 and 0d65535
 */
Word VCNL4035X01_GET_ALS_Data();

/*Read the White Channel Data
 *VCNL4035X01_GET_White_Data() returns White Data between 0d0 and 0d65535
 */
Word VCNL4035X01_GET_White_Data();

/*Set the Low threshold
 *VCNL4035X01_SET_ALS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_ALS_LowThreshold(Word LowThreshold);

/*Set the High Threshold
 *VCNL4035X01_SET_ALS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_ALS_HighThreshold(Word HighThreshold);

/*Read the ALS Interrupt Flag
 *VCNL4035X01_GET_ALS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 11
 */
Word VCNL4035X01_GET_ALS_Interrupt();

/*Read the ALS_SD bit
 *returns 1 for Shutdown and 0 for ALS On
 */
bool VCNL4035X01_GET_ALS_SD_Bit();

/*Read the WHITE_SD bit
 *returns 1 for White Mode and 0 for White Mode Disable (Normal ALS)
 */
bool VCNL4035X01_GET_WHITE_SD_Bit();

/*Set the PS On/Off Duty Ratio
 *VCNL4035X01_SET_PS_DUTY(Byte DutyRatio)
 *Byte DutyRatio - Input Parameter:
 *
 * VCNL4035X01_PS_DR_1_40
 * VCNL4035X01_PS_DR_1_80
 * VCNL4035X01_PS_DR_1_160
 * VCNL4035X01_PS_DR_1_320
 */
void VCNL4035X01_SET_PS_DUTY(Byte DutyRatio);

/*Set the Persistence
 *VCNL4035X01_SET_PS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4035X01_PS_PERS_1
 * VCNL4035X01_PS_PERS_2
 * VCNL4035X01_PS_PERS_3
 * VCNL4035X01_PS_PERS_4
 */
void VCNL4035X01_SET_PS_PERS(Byte Pers);

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
void VCNL4035X01_SET_PS_IT(Byte IntegrationTime);

/*Turn the PS Sensor On/Off
 *VCNL4035X01_SET_PS_SD(Byte SDBit)
 *Byte SDBit - Input Parameter:
 *
 * VCNL4035X01_PS_SD_EN
 * VCNL4035X01_PS_SD_DIS
 */
void VCNL4035X01_SET_PS_SD(Byte SDBit);

/*Enable/Disable the Gesture Interrupt
 *VCNL4035X01_SET_GESTURE_INT(Byte gesture_int)
 *Byte gesture_int - Input Parameter:
 *
 * VCNL4035X01_PS_GESTURE_INT_EN
 * VCNL4035X01_PS_GESTURE_INT_DIS
 */
void VCNL4035X01_SET_GESTURE_INT(Byte gesture_int);

/*Enable/Disable the Gesture Mode
 *VCNL4035X01_SET_GESTURE_MODE(Byte gesture_mode)
 *Byte gesture_mode - Input Parameter:
 *
 * VCNL4035X01_PS_GESTURE_MODE_EN
 * VCNL4035X01_PS_GESTURE_MODE_DIS
 */
void VCNL4035X01_SET_GESTURE_MODE(Byte gesture_mode);

/*Set the Gain
 *VCNL4035X01_SET_PS_Gain(Byte Gain)
 *Byte Gain - Input Parameter:
 *
 * VCNL4035X01_PS_GAIN_2_STEP
 * VCNL4035X01_PS_GAIN_SINGLEx8
 * VCNL4035X01_PS_GAIN_SINGLEx1
 */
void VCNL4035X01_SET_PS_Gain(Byte Gain);

/*Set the PS Output size (12/16Bits)
 *VCNL4035X01_SET_PS_HD(Byte HDBit)
 *Byte HDBit - Input Parameter:
 *
 * VCNL4035X01_PS_HD_12Bits
 * VCNL4035X01_PS_HD_16Bits
 */
void VCNL4035X01_SET_PS_HD(Byte HDBit);

/*Set the Sensitivity
 *VCNL4035X01_SET_PS_NS(Byte NSBit)
 *Byte NSBit - Input Parameter:
 *
 * VCNL4035X01_PS_NS_2STEP_MODE_X4
 * VCNL4035X01_PS_NS_2STEP_MODE
 */
void VCNL4035X01_SET_PS_NS(Byte NSBit);

/*Set the Interrupt Mode
 *VCNL4035X01_SET_PS_INT(Byte InterruptMode)
 *Byte InterruptMode - Input Parameter:
 *
 * VCNL4035X01_PS_INT_DIS
 * VCNL4035X01_PS_INT_CLOSE
 * VCNL4035X01_PS_INT_AWAY
 * VCNL4035X01_PS_INT_CLOSE_AWAY
 */
void VCNL4035X01_SET_PS_INT(Byte InterruptMode);

/*Enable/Disable Low Power Mode
 *VCNL4035X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit)
 *Byte LOW_I_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_I_LOW_EN
 * VCNL4035X01_PS_I_LOW_DIS
 */
void VCNL4035X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit);

/*Set IRED input to be Driven by the Internal Driver
 *VCNL4035X01_SET_PS_IRED_select(Byte ired)
 *Byte ired - Input Parameter:
 *
 * VCNL4035X01_PS_IRED_1
 * VCNL4035X01_PS_IRED_2
 * VCNL4035X01_PS_IRED_3
 */
void VCNL4035X01_SET_PS_IRED_select(Byte ired);

/*Enable/Disable Smart Persistence
 *VCNL4035X01_SET_PS_SMART_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4035X01_PS_SMART_PERS_EN
 * VCNL4035X01_PS_SMART_PERS_DIS
 */
void VCNL4035X01_SET_PS_SMART_PERS(Byte Pers);

/*Enable/Disable Active Force or Auto Mode
 *VCNL4035X01_SET_PS_AF(Byte AF_Bit)
 *Byte AF_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_AUTO
 * VCNL4035X01_PS_AF_EN
 */
void VCNL4035X01_SET_PS_AF(Byte AF_Bit);

/*Enable/Disable Trigger for AF Mode
 *VCNL4035X01_SET_PS_TRIG(Byte TriggerBit)
 *Byte TriggerBit - Input Parameter:
 *
 * VCNL4035X01_PS_TRIG_EN
 * VCNL4035X01_PS_TRIG_DIS
 */
void VCNL4035X01_SET_PS_TRIG(Byte TriggerBit);

/*Set the Proximity Mode (Normal/Logic)
 *VCNL4035X01_SET_PS_MS(Byte MS_Bit)
 *Byte MS_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_MS_NORMAL
 * VCNL4035X01_PS_MS_LOGIC
 */
void VCNL4035X01_SET_PS_MS(Byte MS_Bit);

/*Enable/Disable Sunlight Cancellation
 *VCNL4035X01_SET_PS_SC_EN(Byte SunlightBit)
 *Byte SunlightBit - Input Parameter:
 *
 * VCNL4035X01_PS_SC_EN
 * VCNL4035X01_PS_SC_DIS
 */
void VCNL4035X01_SET_PS_SC_EN(Byte SunlightBit);

/*Set the Sunlight Cancellation Current
 *VCNL4035X01_SET_PS_SC_CUR(Byte SC_Current)
 *Byte SC_Current - Input Parameter:
 *
 * VCNL4035X01_PS_SC_CURx1
 * VCNL4035X01_PS_SC_CURx2
 * VCNL4035X01_PS_SC_CURx4
 * VCNL4035X01_PS_SC_CURx8
 */
void VCNL4035X01_SET_PS_SC_CUR(Byte SC_Current);

/*Set the Sunlight Capability
 *VCNL4035X01_SET_PS_SP(Byte SP_Bit)
 *Byte SP_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_SPx1
 * VCNL4035X01_PS_SPx1_5
 */
void VCNL4035X01_SET_PS_SP(Byte SP_Bit);

/*Set the Output of Sunlight Protect Mode
 *VCNL4035X01_SET_PS_SPO(Byte SPO_Bit)
 *Byte SPO_Bit - Input Parameter:
 *
 * VCNL4035X01_PS_SPO_00
 * VCNL4035X01_PS_SPO_FF
 */
void VCNL4035X01_SET_PS_SPO(Byte SPO_Bit);

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
void VCNL4035X01_SET_PS_LED_I(Byte IRED_Current);

/*Set the PS Cancellation
 *VCNL4035X01_SET_PS_CANC(Word CancelValue)
 *Word CancelValue - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_PS_CANC(Word CancelValue);

/*Set the Low Threshold
 *VCNL4035X01_SET_PS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_PS_LowThreshold(Word LowThreshold);

/*Set the High Threshold
 *VCNL4035X01_SET_PS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4035X01_SET_PS_HighThreshold(Word HighThreshold);

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
Word VCNL4035X01_GET_PS_Data(Byte Reg);

/*Read the PS Interruppt Flag
 *VCNL4035X01_GET_PS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 11
 */
Word VCNL4035X01_GET_PS_Interrupt();

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
Word VCNL4035X01_READ_Reg(Byte Reg);

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
void VCNL4035X01_GET_Gesture_Mode_Data(Word *Data1, Word *Data2, Word *Data3);

/*Read the Gesture Data Ready Flag
 *returns 1 when Gesture Data Ready and 0 otherwise
 */
bool VCNL4035X01_GET_Gesture_Data_Ready_Flag();

/*Read the PS_SD bit
*returns 1 for Shutdown and 0 for Sensor On
*/
bool VCNL4035X01_GET_PS_SD_Bit();

/*Read the PS_AF bit
 *returns 1 for AF Mode and 0 for Auto Mode
 */
bool VCNL4035X01_GET_PS_AF_Bit();

/*Read the LED_I_LOW bit
 *returns 1 for Low Power Mode and 0 for Normal Mode
 */
bool VCNL4035X01_GET_LED_I_LOW_Bit();

/*Read the GESTURE_MODE bit
 *returns 1 for Gesture Mode and 0 for Gesture Mode Disable
 */
bool VCNL4035X01_GET_GESTURE_MODE_Bit();

/*Read Device ID
 *Returns ID
 */
Word VCNL4035X01_GET_ID();
