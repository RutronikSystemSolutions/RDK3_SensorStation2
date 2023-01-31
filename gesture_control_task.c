/*
 * gesture_control_task.c
 *
 *  Created on: Jan 9, 2023
 *      Author: Gintaras
 */

#include "VCNL4035X01.h"
#include "VCNL4035X01_Prototypes.h"
#include "pca9554_app.h"
#include "typedefinition.h"
#include "gesture_control_task.h"
#include "I2C_Functions.h"
#include "arm_math.h"


/*Gesture Control Task Handles*/
TaskHandle_t gesture_control_task_handle = NULL;

/*I2C SCB3 Device */
int I2C_Bus = 3;

Byte PS_IT;
int IRED_Channel = VCNL4035X01_PS_IRED_1;;
int SEL_Offset;

/* Variables for Offset Value */
int CalibValue = 0;
int OffsetValue = 0;
int AverageCount = 10; //Change the average count to the needed number of offset measurement
int Max_Offset = 0;

/*Gesture Sensor Reset Function Prototype*/
void Reset_Sensor();

/*Gesture Mode Initializing Function Prototype*/
void Gesture_Mode();

/*Moving Average Function Prototype*/
float MovingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum);

/*Moving average global variables*/
int sens_buff_1[MOV_AVERAGE] = {0};
int buff_pos_1 = 0;
long sum_1 = 0;
int sens_buff_2[MOV_AVERAGE] = {0};
int buff_pos_2 = 0;
long sum_2 = 0;
int sens_buff_3[MOV_AVERAGE] = {0};
int buff_pos_3 = 0;
long sum_3 = 0;

/*Gesture Frames Global Storage*/
gesture_data_t gesture_data =
{
		.sensor1 = {0},
		.sensor2 = {0},
		.sensor3 = {0},
		.buff_pos = 0,
		.std_left = 0,
		.std_up = 0,
		.std_right = 0,
		.crosscorr = {0},
		.gesture = GESTURE_NONE //currently recognized gesture
};

void gesture_control_task(void *param)
{
	(void) param;
	cy_rslt_t result;
	Word vcnl4035x01_ID = 0;
	Word Data1,Data2,Data3 = 0;
	_Bool Gesture_Data_Ready = false;
	float sens_av_1 = 0;
	float sens_av_2 = 0;
	float sens_av_3 = 0;

	float max_value = 0;
	uint32_t value_index = 0;
	int left_right_delay = 0;
	int left_up_delay = 0;
	int right_up_delay = 0;

	uint32_t frames_to_skip = 0;

	printf("gesture control task has started.\r\n");

	/*Configure the PCA9554 GPIO Expander*/
	result = pca9554_configure();
    if (result != CY_RSLT_SUCCESS)
    {
    	printf("PCA9554 GPIO expander failure.\r\n");
    	CY_ASSERT(0);
    }
    /*Initial LED Direction*/
    pca9554_dir_set(PCA9554_DIR_LOWER);

    /* Reset Sensor to default value */
	Reset_Sensor();

	/* Read the VCNL4035X01 ID */
	vcnl4035x01_ID = VCNL4035X01_GET_ID();
	if(vcnl4035x01_ID != 0x80)
	{
		printf("VCNL4035X01 sensor failure.\r\n");
		for(;;)
		{
			vTaskDelay(pdMS_TO_TICKS(1000));
		}
	}

	/* Choose the integration time for PS */
	PS_IT = VCNL4035X01_PS_IT_2T;

	/* Choose to turn on/off offset cancellation measurement */
	SEL_Offset = 1;

	/*Gesture Mode Initialize*/
	Gesture_Mode();

	/*Indicate the progress*/
	pca9554_dir_set(PCA9554_DIR_UPPER);

	for(;;)
	{
    	/* Set trigger to start a measurement */
    	VCNL4035X01_SET_PS_TRIG(VCNL4035X01_PS_TRIG_EN);

    	/* Delay of PS Measurement + other Circuit Delay */
    	vTaskDelay(pdMS_TO_TICKS(10));

    	/* Print the Gesture Data Ready Interrupt Flag */
    	Gesture_Data_Ready = VCNL4035X01_GET_Gesture_Data_Ready_Flag();

    	/* Read Gesture Data */
    	if(Gesture_Data_Ready)
    	{
    		/*Read the gesture data from the VCNL4035X01*/
    		VCNL4035X01_GET_Gesture_Mode_Data(&Data1, &Data2, &Data3);

    	    /*Do the moving average math for the sensor 1*/
    	    sens_av_1 = MovingAvg(sens_buff_1, &sum_1, buff_pos_1, MOV_AVERAGE, (int)Data1);
    	    buff_pos_1++;
    	    if(buff_pos_1 >= MOV_AVERAGE){buff_pos_1 = 0;}

    	    /*Do the moving average math for the sensor 2*/
    	    sens_av_2 = MovingAvg(sens_buff_2, &sum_2, buff_pos_2, MOV_AVERAGE, (int)Data2);
    	    buff_pos_2++;
    	    if(buff_pos_2 >= MOV_AVERAGE){buff_pos_2 = 0;}

    	    /*Do the moving average math for the sensor 3*/
    	    sens_av_3 = MovingAvg(sens_buff_3, &sum_3, buff_pos_3, MOV_AVERAGE, (int)Data3);
    	    buff_pos_3++;
    	    if(buff_pos_3 >= MOV_AVERAGE){buff_pos_3 = 0;}

    	    /*Put the data into the gesture frame storage*/
    	    if(gesture_data.buff_pos < GESTURE_FRAME_SIZE)
    	    {
        	    gesture_data.sensor1[gesture_data.buff_pos] = sens_av_1;
        	    gesture_data.sensor2[gesture_data.buff_pos] = sens_av_2;
        	    gesture_data.sensor3[gesture_data.buff_pos] = sens_av_3;
        	    gesture_data.buff_pos++;

        	    /*Frame counter decrease*/
        	    if(frames_to_skip > 0)
        	    {frames_to_skip--;}
    	    }
    	}

    	/* Frame buffer is full, do the data processing. */
    	if(gesture_data.buff_pos == GESTURE_FRAME_SIZE)
    	{
    		gesture_data.buff_pos = 0;
    		gesture_data.gesture = GESTURE_NONE;
    		pca9554_dir_set(PCA9554_DIR_NONE);

    		/*If no frames requested to skip*/
    		if(!frames_to_skip)
    		{
        		/*Calculate the standard deviation of all sensor frames*/
        		arm_std_f32(gesture_data.sensor1, GESTURE_FRAME_SIZE, &gesture_data.std_left);
        		arm_std_f32(gesture_data.sensor2, GESTURE_FRAME_SIZE, &gesture_data.std_right);
        		arm_std_f32(gesture_data.sensor3, GESTURE_FRAME_SIZE, &gesture_data.std_up);

    			#if STD_DEBUG_EN
        		/*Print standard deviation data*/
        		printf("Left: %.2f\r\n ", gesture_data.std_left);
        		printf("Up: %.2f\r\n ", gesture_data.std_up);
        		printf("Right: %.2f\r\n\r\n", gesture_data.std_right);
    			#endif

        		/*If motion detected, analyze the frame*/
        		if((gesture_data.std_left >= STD_THRESHOLD) || (gesture_data.std_right >= STD_THRESHOLD) || (gesture_data.std_up >= STD_THRESHOLD))
        		{

        			/*Left Right Cross-Correlation*/
            		arm_correlate_f32(gesture_data.sensor1, GESTURE_FRAME_SIZE, gesture_data.sensor2, GESTURE_FRAME_SIZE, gesture_data.crosscorr);
            		arm_max_f32(gesture_data.crosscorr, GESTURE_FRAME_SIZE*2-1, &max_value, &value_index);
            		left_right_delay = value_index - (GESTURE_FRAME_SIZE - 1);
            		if(left_right_delay < LFT_RHT_DELAY_TH)
            		{
            			frames_to_skip = GESTURE_FRAME_SKIP;
            			gesture_data.gesture = GESTURE_RIGHT;
            			pca9554_dir_set(PCA9554_DIR_RIGHT);

    					#if LFT_RHT_DEBUG_EN
            			printf("Right %d \r\n", left_right_delay);
    					#endif
            		}
            		else if (left_right_delay > LFT_RHT_DELAY_TH)
            		{
            			frames_to_skip = GESTURE_FRAME_SKIP;
            			gesture_data.gesture = GESTURE_LEFT;
            			pca9554_dir_set(PCA9554_DIR_LEFT);

    					#if LFT_RHT_DEBUG_EN
            			printf("Left %d \r\n", left_right_delay);
    					#endif
            		}
            		/*Left Up Cross-Correlation*/
            		else
            		{
                		arm_correlate_f32(gesture_data.sensor1, GESTURE_FRAME_SIZE, gesture_data.sensor3, GESTURE_FRAME_SIZE, gesture_data.crosscorr);
                		arm_max_f32(gesture_data.crosscorr, GESTURE_FRAME_SIZE*2-1, &max_value, &value_index);
                		left_up_delay = value_index - (GESTURE_FRAME_SIZE - 1);
                		if(left_up_delay > LFT_UP_DELAY_TH)
                		{
                			frames_to_skip = GESTURE_FRAME_SKIP;
                			gesture_data.gesture = GESTURE_DOWN;
                			pca9554_dir_set(PCA9554_DIR_DOWN);

        					#if LFT_UP_DEBUG_EN
                			printf("Down %d \r\n", left_up_delay);
        					#endif
                		}
                		else if (left_up_delay < LFT_UP_DELAY_TH)
                		{
                			frames_to_skip = GESTURE_FRAME_SKIP;
                			gesture_data.gesture = GESTURE_UP;
                			pca9554_dir_set(PCA9554_DIR_UP);

        					#if LFT_UP_DEBUG_EN
                			printf("Up %d \r\n", left_up_delay);
        					#endif
                		}
                		/*Right Up Cross-Correlation*/
                		else
                		{
                    		arm_correlate_f32(gesture_data.sensor2, GESTURE_FRAME_SIZE, gesture_data.sensor3, GESTURE_FRAME_SIZE, gesture_data.crosscorr);
                    		arm_max_f32(gesture_data.crosscorr, GESTURE_FRAME_SIZE*2-1, &max_value, &value_index);
                    		right_up_delay = value_index - (GESTURE_FRAME_SIZE - 1);
                    		if(right_up_delay > RHT_UP_DELAY_TH)
                    		{
                    			frames_to_skip = GESTURE_FRAME_SKIP;
                    			gesture_data.gesture = GESTURE_DOWN;
                    			pca9554_dir_set(PCA9554_DIR_DOWN);

            					#if RHT_UP_DEBUG_EN
                    			printf("Down %d \r\n", right_up_delay);
            					#endif
                    		}
                    		else if (right_up_delay < RHT_UP_DELAY_TH)
                    		{
                    			frames_to_skip = GESTURE_FRAME_SKIP;
                    			gesture_data.gesture = GESTURE_UP;
                    			pca9554_dir_set(PCA9554_DIR_UP);

            					#if RHT_UP_DEBUG_EN
                    			printf("Up %d \r\n", right_up_delay);
            					#endif
                    		}
                    		else
                    		{
                    			gesture_data.gesture = GESTURE_NONE;
                    			pca9554_dir_set(PCA9554_DIR_NONE);
                    		}
                		}
            		}

        		}

        		cyhal_gpio_toggle(LED2);
    		}
    	}
	}
}

/* Gesture Mode Initialization Function */
void Gesture_Mode()
{
    //1.)Initialization
    //Disable the PS
    VCNL4035X01_SET_PS_SD(VCNL4035X01_PS_SD_DIS);
    //Setting up AF Mode (Needed for Gesture Mode)
    VCNL4035X01_SET_PS_AF(VCNL4035X01_PS_AF_EN);

    //2.) Setting up PS
    //PS_CONF1
    //PS_DUTY doesn't have to be set for Gesture Mode
    //Set the Persistence
    VCNL4035X01_SET_PS_PERS(VCNL4035X01_PS_PERS_1);
    //Set the Integration Time
    VCNL4035X01_SET_PS_IT(PS_IT);

    //PS_CONF2
    //Enable/Disable the Gesture Interrupt
    VCNL4035X01_SET_GESTURE_INT(VCNL4035X01_PS_GESTURE_INT_EN);
    //Disable the Gesture Mode (Enable only after offset measurement)
    //If the mode be enabled now then only one channel will be measured
    VCNL4035X01_SET_GESTURE_MODE(VCNL4035X01_PS_GESTURE_MODE_DIS);
    //Set the Gain
    VCNL4035X01_SET_PS_Gain(VCNL4035X01_PS_GAIN_2_STEP);
    //Set the Output Bit Size
    VCNL4035X01_SET_PS_HD(VCNL4035X01_PS_HD_16Bits);
    //Set the Sensitivity Mode
    VCNL4035X01_SET_PS_NS(VCNL4035X01_PS_NS_2STEP_MODE_X4);
    //Set the Interrupt
    VCNL4035X01_SET_PS_INT(VCNL4035X01_PS_INT_CLOSE_AWAY);

    //PS_CONF3
    //Enable/Disable Low Current
    VCNL4035X01_SET_PS_LED_I_LOW(VCNL4035X01_PS_I_LOW_DIS);
    //Select IRED input to be Driven by the Internal Driver (For Gesture Mode not so important since all 3 channels will be read)
    VCNL4035X01_SET_PS_IRED_select(IRED_Channel);
    //Enable/Disable Smart Persistence
    VCNL4035X01_SET_PS_SMART_PERS(VCNL4035X01_PS_SMART_PERS_DIS);
    //Set Interrupt to Normal/Logic Mode
    VCNL4035X01_SET_PS_MS(VCNL4035X01_PS_MS_NORMAL);
    //Enable/Disable Sunlight Cancellation
    VCNL4035X01_SET_PS_SC_EN(VCNL4035X01_PS_SC_EN);
    //PS_AF has been set during initialization
    //PS_TRIG must be set before reading the proximity data

    //PS_MS
    //Set the Sunlight Cancellation Current
    VCNL4035X01_SET_PS_SC_CUR(VCNL4035X01_PS_SC_CURx1);
    //Set the Sunlight Capability
    VCNL4035X01_SET_PS_SP(VCNL4035X01_PS_SPx1);
    //Set the Output of Sunlight Protect Mode
    VCNL4035X01_SET_PS_SPO(VCNL4035X01_PS_SPO_00);
    //Set the LED Current
    VCNL4035X01_SET_PS_LED_I(VCNL4035X01_PS_LED_I_100mA);

    //3.) Switch On the sensor
    VCNL4035X01_SET_PS_SD(VCNL4035X01_PS_SD_EN);
    //Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
    vTaskDelay(pdMS_TO_TICKS(10));

    //Clear Initial Interrupt
    VCNL4035X01_GET_PS_Interrupt();
    vTaskDelay(pdMS_TO_TICKS(10));

	//4.) Threshold Setting and Offset Measurement
	//Calculate Offset for all of the 3 channels
	for(int i=0; i<AverageCount;i++)
	{
		//Channel 1
		//Select IRED input to be driven by the internal driver to calibrate
		VCNL4035X01_SET_PS_IRED_select(VCNL4035X01_PS_IRED_1);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));
		//Enable trigger to start offset measurement
		VCNL4035X01_SET_PS_TRIG(VCNL4035X01_PS_TRIG_EN);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));
		//Read offset data channel 1 and add as calibration value for offset
		CalibValue += VCNL4035X01_READ_Reg(VCNL4035X01_PS_DATA_1);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));

		//Channel 2
		//Select IRED input to be driven by the internal driver to calibrate
		VCNL4035X01_SET_PS_IRED_select(VCNL4035X01_PS_IRED_2);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));
		//Enable trigger to start offset measurement
		VCNL4035X01_SET_PS_TRIG(VCNL4035X01_PS_TRIG_EN);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));;
		//Read offset data channel 2 and add as calibration value for offset
		CalibValue += VCNL4035X01_READ_Reg(VCNL4035X01_PS_DATA_2);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));

		//Channel 3
		//Select IRED input to be driven by the internal driver to calibrate
		VCNL4035X01_SET_PS_IRED_select(VCNL4035X01_PS_IRED_3);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));
		//Enable trigger to start offset measurement
		VCNL4035X01_SET_PS_TRIG(VCNL4035X01_PS_TRIG_EN);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));
		//Read offset data channel 3 and add as calibration value for offset
		CalibValue += VCNL4035X01_READ_Reg(VCNL4035X01_PS_DATA_3);
		//Delay of 10 ms needs to be changed depending on the API of the µ-controller of use
		vTaskDelay(pdMS_TO_TICKS(10));
	}

	//Calculate the average of the offset measurement from the 3 channels
	CalibValue /= 3*AverageCount;

	//Check whether the offset value is too high to be set in the cancellation register
	// 1T max offset value for the cancellation register is 2048
	if((PS_IT==VCNL4035X01_PS_IT_1T)||(PS_IT==VCNL4035X01_PS_IT_1_5T))Max_Offset = 2048;
	// 2T max offset value for the cancellation register is 4096
	if((PS_IT==VCNL4035X01_PS_IT_2T)||(PS_IT==VCNL4035X01_PS_IT_2_5T)||(PS_IT==VCNL4035X01_PS_IT_3T)||(PS_IT==VCNL4035X01_PS_IT_3_5T))Max_Offset = 4096;
	// 4T max offset value for the cancellation register is 8192
	if(PS_IT==VCNL4035X01_PS_IT_4T)Max_Offset = 8192;
	// 8T max offset value for the cancellation register is 16384
	if(PS_IT==VCNL4035X01_PS_IT_8T)Max_Offset = 16384;

	if(CalibValue>Max_Offset)
	{
		//Perform Offset Measurement
		if(SEL_Offset == 0) OffsetValue = 0;
		if(SEL_Offset == 1) OffsetValue = CalibValue;
		//Set Cancellation register to eliminate offset
		VCNL4035X01_SET_PS_CANC(OffsetValue);
		//Set Low Threshold
		VCNL4035X01_SET_PS_LowThreshold(3000 + OffsetValue);
		//set High Threshold
		VCNL4035X01_SET_PS_HighThreshold(5000 + OffsetValue);
	}
	else
	{
		//Perform Offset Measurement
		if(SEL_Offset == 0) OffsetValue = 0;
		if(SEL_Offset == 1) OffsetValue = CalibValue;
		//Set Cancellation register to eliminate offset
		VCNL4035X01_SET_PS_CANC(OffsetValue);
		//Set Low Threshold
		VCNL4035X01_SET_PS_LowThreshold(3000);
		//set High Threshold
		VCNL4035X01_SET_PS_HighThreshold(5000);
	}

    //5.) Enable the Gesture Mode
    //Enable/Disable the Gesture Mode
    VCNL4035X01_SET_GESTURE_MODE(VCNL4035X01_PS_GESTURE_MODE_EN);
    vTaskDelay(pdMS_TO_TICKS(1000));
}

/* Reset the Sensor to the default value */
void Reset_Sensor(void)
{
	struct TransferData VCNL4035X01_Data;
	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x01;
	VCNL4035X01_Data.WData[1] = 0x01;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_THDL;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_ALS_THDH;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_1;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x01;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CONF_3;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

    VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_CANC;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_THDL;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_PS_THDH;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);

	VCNL4035X01_Data.Slave_Address = VCNL4035X01_SlaveAddress;
	VCNL4035X01_Data.RegisterAddress = VCNL4035X01_INT_FLAG;
	VCNL4035X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL4035X01_Data.WData[0] = 0x00;
	VCNL4035X01_Data.WData[1] = 0x00;
	WriteI2C_Bus(&VCNL4035X01_Data);
}

float MovingAvg(int *ptrArrNumbers, long *ptrSum, int pos, int len, int nextNum)
{
  /*Subtract the oldest number from the previous sum, add the new number*/
  *ptrSum = *ptrSum - ptrArrNumbers[pos] + nextNum;

  /*Assign the nextNum to the position in the array*/
  ptrArrNumbers[pos] = nextNum;

  /*Return the average*/
  return *ptrSum / len;
}
