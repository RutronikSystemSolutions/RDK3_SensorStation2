/*
 * I2C_Functions.c
 *
 * Created  : 9 November 2020
 * Modified : 6 May 2021
 * Author   : HWanyusof
 * Version	: 1.0
 */

#include "I2C_Functions.h"
#include <stdio.h>
#include <stdlib.h>

//STM32F specific I2C API call
#ifdef STM32F
	//All of the I2C API functions (For Example: HAL_I2C_Master_Transmit()) are being called from stm32f4xx_hal.h

	//hi2c1 - The variable to the I2C handler which is needed later in the Write and Read I2C function.
	//hi2c1 is defined in the stm32f4xx_hal.h and being called here via extern I2C_HandleTypeDef hi2c1;.
	extern I2C_HandleTypeDef hi2c1;

	//Master sends I2C write command via pointer *Data from the Sensor API.
	//The function returns HAL_OK (=0) when there is no error and -1 when there is an error.
	int WriteI2C_Bus(struct TransferData *Data)
	{
		//Initialization of intial Error = 0
		int Error = 0;

		//Define an array of 3 Bytes to be sent as I2C Write Command as shown in Fig. 10 in the Datasheet Page 7
		uint8_t WData[3]={Data->RegisterAddress, Data->WData[0], Data->WData[1]};

		//Send I2C Write Command as shown in Fig. 10 in the Datasheet Page 7 with Error checking.
		/*Format defined by STM:
		*HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout).
		*HAL_I2C_Master_Transmit() is used for transmitting data to the I2C device. It takes following arguments:
		*
		*I2C_HandleTypeDef *hi2c - is the pointer to the i2c handler. hi2c1 is defined in the stm32f4xx_hal.h and being called here via extern I2C_HandleTypeDef *hi2c1;.
		*uint16_t DevAddress - is the Address of the I2C device (Need to be shifted by 1 to left since the input of function expects 8 bits).
		*uint8_t *pData  - is the pointer to the data to be transmitted.
		*uint16_t Size  - is the size of the transmitted data in bytes.
		*uint32_t Timeout - timeout in millisecond in case of any error.
		*Return Error.
		*/
		Error = HAL_I2C_Master_Transmit(&hi2c1, (Data->Slave_Address)<<1, WData, 3, 100);

		//Return -1 when there is error and return HAL_OK (= 0) when no error
		if (Error != HAL_OK)
		{
			return -1;
		}
		else
		{
			return HAL_OK;
		}
	}

	//Master sends I2C Read command and save the read data via pointer *Data.
	//The function returns HAL_OK (=0) when no error and -1 when there is error.
	int ReadI2C_Bus (struct TransferData *Data)
	{
		//Initialization of intial Error = 0
		int Error = 0;

		//Send I2C Read Command as shown in Fig. 10 in the Datasheet Page 7 with Error checking.
		/*Format defined by STM:
		*HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c1, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout).
		*HAL_I2C_Mem_Read () is used for reading data from the I2C device. It has been used instead of HAL_I2C_Master_Receive() because it sends restart condition
		*while the latter which sends stop condition and thus not working. It takes following arguments:
		*
		*I2C_HandleTypeDef *hi2c - is the pointer to the i2c handler.
		*uint16_t DevAddress - is the Address of the I2C device (Need to be shifted by 1 to left since the input of function expects 8 bits).
		*uint16_t MemAddress - is the Internal memory address in the slave which is the register address.
		*uint16_t MemAddSize - the size of memory address (in Byte) which is the size of register address (In the case of Vishay's Sensor always 1 Byte).
		*uint8_t *pData  - is the pointer to the data to be received.
		*uint16_t Size  - is the size of the received data in bytes.
		*uint32_t Timeout - timeout in millisecond in case of any error.
		*Return Error.
		*
		*/
		Error = HAL_I2C_Mem_Read(&hi2c1, (Data->Slave_Address)<<1, Data->RegisterAddress, 1,Data->RData,2,100);

		//Return -1 when there is error and return HAL_OK (= 0) when no error
		if (Error !=HAL_OK)
		{
			return -1;
		}
		else
		{
			return HAL_OK;
		}
	}

	//Master sends I2C Gesture Read command and save the read data via pointer *Data.
	//The function returns HAL_OK (=0) when no error and -1 when there is error.
    int ReadI2C_Bus_Gesture_Mode(struct GestureTransferData *Data)
	{
		//Initialization of intial Error = 0
		int Error = 0;

		//Send I2C Gesture Read Command as shown in the Application Note Page 19 with Error checking.
		/*Format defined by STM:
		*HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout).
		*HAL_I2C_Master_Receive () is used for reading data from the I2C device. It has been used instead of HAL_I2C_Mem_Read() because no restart condition is *needed.
		*It takes following arguments:
		*
		*I2C_HandleTypeDef *hi2c - is the pointer to the i2c handler. hi2c1 is defined in the stm32f4xx_hal.h and being called here via extern I2C_HandleTypeDef *hi2c1;.
		*uint16_t DevAddress - is the Address of the I2C device (Need to be shifted by 1 to left since the input of function expects 8 bits).
		*uint8_t *pData  - is the pointer to the data to be received.
		*uint16_t Size  - is the size of the received data in bytes (For Gesture Stream 6 Bytes are needed).
		*uint32_t Timeout - timeout in millisecond in case of any error.
		*Return Error.
		*
		*/
		Error = HAL_I2C_Master_Receive(&hi2c1,(Data->Slave_Address)<<1,Data->RData,6,100);

		//Return -1 when there is error and return HAL_OK (= 0) when no error
		if (Error != HAL_OK)
		{
			return -1;
		}
		else
		{
			return HAL_OK;
		}
	}
#endif

/* Infineon PSoC6 ModusToolbox specific I2C API call */
#ifdef Cypress

    /* RDK2 Arduino I2C Object */
    extern cyhal_i2c_t I2C_scb3;

    /* RDK2 Arduino I2C Mutex */
	#ifdef FREERTOS_APP
    extern SemaphoreHandle_t i2c_mutex;
	#endif

	//Master sends I2C write command via pointer *Data from the Sensor API.
	//The function returns 0 when no error and -1 when there is error.
	int WriteI2C_Bus(struct TransferData *Data)
	{
		cy_rslt_t result;
		uint8_t i2c_data[3] = {0};

		#ifndef FREERTOS_APP
		return -1; //Not implemented
		#else
		xSemaphoreTake(i2c_mutex, portMAX_DELAY);
		i2c_data[0] = Data->RegisterAddress;
		i2c_data[1] = Data->WData[0];
		i2c_data[2] = Data->WData[1];
		result = cyhal_i2c_master_write( &I2C_scb3, (uint16_t)Data->Slave_Address, i2c_data, 3, 10, true );
		if (result != CY_RSLT_SUCCESS)
		{
			xSemaphoreGive(i2c_mutex);
			return -1;
		}
		xSemaphoreGive(i2c_mutex);
		#endif

		return 0;
	}

	//Master sends I2C Read command and save the read data via pointer *Data.
	//The function returns 0 upon completion.
	int ReadI2C_Bus(struct TransferData *Data)
	{
		cy_rslt_t result;

		#ifndef FREERTOS_APP
		return -1; //Not implemented
		#else

		xSemaphoreTake(i2c_mutex, portMAX_DELAY);

		result = cyhal_i2c_master_write( &I2C_scb3, (uint16_t)Data->Slave_Address, &Data->RegisterAddress, 1, 10, false );
		if (result != CY_RSLT_SUCCESS)
		{
			xSemaphoreGive(i2c_mutex);
			return -1;
		}
		result = cyhal_i2c_master_read( &I2C_scb3, (uint16_t)Data->Slave_Address, Data->RData, 2, 10, true );
		if (result != CY_RSLT_SUCCESS)
		{
			xSemaphoreGive(i2c_mutex);
			return -1;
		}
		xSemaphoreGive(i2c_mutex);
		#endif

		return 0;
	}

	//Master sends I2C Gesture Read command and save the read data via pointer *Data.
	//The function returns 0 upon completion.
	int ReadI2C_Bus_Gesture_Mode(struct GestureTransferData *Data)
	{
		cy_rslt_t result;

		#ifndef FREERTOS_APP
		return -1; //Not implemented
		#else

		xSemaphoreTake(i2c_mutex, portMAX_DELAY);

		result = cyhal_i2c_master_read( &I2C_scb3, (uint16_t)Data->Slave_Address, Data->RData, 6, 10, true );
		if (result != CY_RSLT_SUCCESS)
		{
			xSemaphoreGive(i2c_mutex);
			return -1;
		}
		xSemaphoreGive(i2c_mutex);

		#endif

		return 0;
	}
#endif

//Arduino/Teensy/Adafruit or MCU that supports Arduino specific I2C API call
#ifdef Arduino
	//All of the I2C API functions (For Example: Wire.write()) are being called from i2c_t3.h / Wire.h

	//Master sends I2C write command via pointer *Data send from the Sensor API.
	//The function returns 0 when no error and -1 when there is error.
	int WriteI2C_Bus(struct TransferData *Data)
	{
		//Initialization of intial Error = 0
		int Error = 0;

		//Arduino/Teensy/Adafruit could allow 2 parallel I2C bus to be used simultaneously.
		//Select_I2C_BUS is defined in Main_User.cpp.
		switch (Data->Select_I2C_Bus)
		{
			//Case I2C Bus 1
			case 1:
				//Send I2C Write Command as shown in Fig. 10 in the Datasheet Page 7.
				//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
				Wire.begin();

				/*Step 2)  Send the 7-bit slave address to begin a transmission to the slave.
				*Wire.beginTransmission(uint8_t SlaveAddress) - Begin a transmission to the I2C slave device with the given address.
				*uint8_t SlaveAddress - the 7-bit address of the device to transmit to.
				*/
				Wire.beginTransmission(Data->Slave_Address);

				/*Step 3) Write data to the slave.
				*Wire.write(uint8_t value) - Writes data from a slave device in response to a request from a master, or queues bytes for transmission from a
				*master to slave device (in-between calls to beginTransmission() and endTransmission()).
				*uint8_t value - write 8-bit data like the register address to be written in the sensor and its corresponding 2 x 1 Byte values.
				*Sequence has to follow I2C Write Command as shown in Fig. 10 in the Datasheet Page 7 - Register Address, WData0, WData1.
				*/
				Wire.write(Data->RegisterAddress);
				Wire.write(Data->WData[0]);
				Wire.write(Data->WData[1]);

				//Step 4) Ends a transmission to a slave device that was begun by beginTransmission() and transmits the bytes that were queued by write().
				//Return error status (1 byte), which indicates the status of the transmission: 0 - success, !0 - there is error.
				Error = Wire.endTransmission();

				//Return -1 when there is error
				if(Error != 0)
				{
					return -1;
				}

				break;
			#ifdef i2ct3
				//Case I2C Bus 2
				case 2:
					//Send I2C Write Command as shown in Fig. 10 in the Datasheet Page 7.
					//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
					Wire1.begin();

					/*Step 2)  Send the 7-bit slave address to begin a transmission to the slave.
					*Wire.beginTransmission(uint8_t SlaveAddress) - Begin a transmission to the I2C slave device with the given address.
					*uint8_t SlaveAddress - the 7-bit address of the device to transmit to.
					*/
					Wire1.beginTransmission(Data->Slave_Address);

					/*Step 3) Write data to the slave.
					*Wire.write(uint8_t value) - Writes data from a slave device in response to a request from a master, or queues bytes for transmission from a
					*master to slave device (in-between calls to beginTransmission() and endTransmission()).
					*uint8_t value - write 8-bit data like the register address to be written in the sensor and its corresponding 2 x 1 Byte values.
					*Sequence has to follow I2C Write Command as shown in Fig. 10 in the Datasheet Page 7 - Register Address, WData0, WData1.
					*/
					Wire1.write(Data->RegisterAddress);
					Wire1.write(Data->WData[0]);
					Wire1.write(Data->WData[1]);

					//Step 4) Ends a transmission to a slave device that was begun by beginTransmission() and transmits the bytes that were queued by write().
					//Return error status (1 byte), which indicates the status of the transmission: 0 - success, !0 - there is error.
					Error = Wire1.endTransmission();

					//Return -1 when there is error
					if(Error != 0)
					{
						return -1;
					}

					break;
			#endif

			//Other Cases I2C Bus set to default
			default:
				//Send I2C Write Command as shown in Fig. 10 in the Datasheet Page 7.
				//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
				Wire.begin();

				/*Step 2) Send the 7-bit slave address to begin a transmission to the slave.
				*Wire.beginTransmission(uint8_t SlaveAddress) - Begin a transmission to the I2C slave device with the given address.
				*uint8_t SlaveAddress - the 7-bit address of the device to transmit to.
				*/
				Wire.beginTransmission(Data->Slave_Address);

				/*Step 3) Write data to the slave.
				*Wire.write(uint8_t value) - Writes data from a slave device in response to a request from a master, or queues bytes for transmission from a
				*master to slave device (in-between calls to beginTransmission() and endTransmission()).
				*uint8_t value - write 8-bit data like the register address to be written in the sensor and its corresponding 2 x 1 Byte values.
				*Sequence has to follow I2C Write Command as shown in Fig. 10 in the Datasheet Page 7 - Register Address, WData0, WData1.
				*/
				Wire.write(Data->RegisterAddress);
				Wire.write(Data->WData[0]);
				Wire.write(Data->WData[1]);

				//Step 4) Ends a transmission to a slave device that was begun by beginTransmission() and transmits the bytes that were queued by write().
				//Return error status (1 byte), which indicates the status of the transmission: 0 - success, !0 - there is error.
				Error = Wire.endTransmission();

				//Return -1 when there is error
				if(Error != 0)
				{
					return -1;
				}

				break;
		}
		return 0;
	}

	//Master sends I2C Read command and save the read data via pointer *Data.
	//The function returns 0 when no error and -1 when there is error.
	int ReadI2C_Bus(struct TransferData *Data)
	{
		//Initialization of intial Error = 0
		int Error = 0;

		//Arduino/Teensy/Adafruit could allow 2 parallel I2C bus to be used simultaneously.
		//Select_I2C_BUS is defined in Main_User.cpp.
		switch (Data->Select_I2C_Bus)
		{

			//Case I2C Bus 1
			case 1:
				//Send I2C Read Command as shown in Fig. 10 in the Datasheet Page 7.
				//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
				Wire.begin();

				/*Step 2) Send the 7-bit slave address to begin a transmission to the slave.
				*Wire.beginTransmission(uint8_t SlaveAddress) - Begin a transmission to the I2C slave device with the given address.
				*uint8_t SlaveAddress - the 7-bit address of the device to transmit to.
				*/
				Wire.beginTransmission(Data->Slave_Address);

				/*Step 3) Send the register address.
				*Wire.write(uint8_t value) - Writes data from a slave device in response to a request from a master, or queues bytes for transmission from a master *to slave device (in-between calls to beginTransmission() and endTransmission()).
				*uint8_t value - write 8-bit data like the register address to be written in the sensor.
				*/
				Wire.write(Data->RegisterAddress);

				/*Step 4) Send restart condition.
				*Wire.endTransmission(false) - With false as input, endTransmission() sends a restart message after transmission. The bus will not be released, which *prevents another master device from transmitting between messages. This allows one master device to send multiple transmissions while in control.
				*Return error status (1 byte), which indicates the status of the transmission: 0 - success, !0 - there is error.
				*/
				Error = Wire.endTransmission(false);

				//Return -1 when there is error
				if(Error != 0)
				{
					return -1;
				}

				/*Step 5) Request Data from slave.
				*Wire.requestFrom(uint8_t SlaveAddress, uint8_t Quantity, bool Stop) - Used by the master to request bytes from a slave device.
				*SlaveAddress: the 7-bit address of the device to request bytes from.
				*Quantity: the number of bytes to request. For Read Command, 2 Bytes are required.
				*Stop : boolean. true (true as declared in i2c_t3.h/Wire.h) will send a stop message after the request, releasing the bus.
				*/
				Wire.requestFrom(Data->Slave_Address, 2,true);

				/*Step 6) Read data from slave.
				*Wire.read() - Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
				*Read the 2 Bytes Data from the Sensor by calling it 2 times and store it in the RData Array.
				*/
				Data->RData[0] = Wire.read();
				Data->RData[1] = Wire.read();

				break;
			#ifdef i2ct3
				//Case I2C Bus 2
				case 2:
					//Send I2C Read Command as shown in Fig. 10 in the Datasheet Page 7.
					//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
					Wire1.begin();

					/*Step 2) Send the 7-bit slave address to begin a transmission to the slave.
					*Wire.beginTransmission(uint8_t SlaveAddress) - Begin a transmission to the I2C slave device with the given address.
					*uint8_t SlaveAddress - the 7-bit address of the device to transmit to.
					*/
					Wire1.beginTransmission(Data->Slave_Address);

					/*Step 3) Send the register address.
					*Wire.write(uint8_t value) - Writes data from a slave device in response to a request from a master, or queues bytes for transmission from a master *to slave device (in-between calls to beginTransmission() and endTransmission()).
					*uint8_t value - write 8-bit data like the register address to be written in the sensor.
					*/
					Wire1.write(Data->RegisterAddress);

					/*Step 4) Send restart condition.
					*Wire.endTransmission(false) - With false as input, endTransmission() sends a restart message after transmission. The bus will not be released, which *prevents another master device from transmitting between messages. This allows one master device to send multiple transmissions while in control.
					*Return error status (1 byte), which indicates the status of the transmission: 0 - success, !0 - there is error.
					*/
					Error = Wire1.endTransmission(false);

					//Return -1 when there is error
					if(Error != 0)
					{
						return -1;
					}

					/*Step 5) Request Data from slave.
					*Wire.requestFrom(uint8_t SlaveAddress, uint8_t Quantity, bool Stop) - Used by the master to request bytes from a slave device.
					*SlaveAddress: the 7-bit address of the device to request bytes from.
					*Quantity: the number of bytes to request. For Read Command, 2 Bytes are required.
					*Stop : boolean. true (true as declared in i2c_t3.h/Wire.h) will send a stop message after the request, releasing the bus.
					*/
					Wire1.requestFrom(Data->Slave_Address, 2,true);

					/*Step 6) Read data from slave.
					*Wire.read() - Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
					*Read the 2 Bytes Data from the Sensor by calling it 2 times and store it in the RData Array.
					*/
					Data->RData[0] = Wire1.read();
					Data->RData[1] = Wire1.read();

					break;
			#endif

			//Other Cases I2C Bus set to default
			default:
				//Send I2C Read Command as shown in Fig. 10 in the Datasheet Page 7.
				//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
				Wire.begin();

				/*Step 2) Send the 7-bit slave address to begin a transmission to the slave.
				*Wire.beginTransmission(uint8_t SlaveAddress) - Begin a transmission to the I2C slave device with the given address.
				*uint8_t SlaveAddress - the 7-bit address of the device to transmit to.
				*/
				Wire.beginTransmission(Data->Slave_Address);

				/*Step 3) Send the register address.
				*Wire.write(uint8_t value) - Writes data from a slave device in response to a request from a master, or queues bytes for transmission from a master *to slave device (in-between calls to beginTransmission() and endTransmission()).
				*uint8_t value - write 8-bit data like the register address to be written in the sensor.
				*/
				Wire.write(Data->RegisterAddress);

				/*Step 4) Send restart condition.
				*Wire.endTransmission(false) - With false as input, endTransmission() sends a restart message after transmission. The bus will not be released, which *prevents another master device from transmitting between messages. This allows one master device to send multiple transmissions while in control.
				*Return error status (1 byte), which indicates the status of the transmission: 0 - success, !0 - there is error.
				*/
				Error = Wire.endTransmission(false);

				//Return -1 when there is error
				if(Error != 0)
				{
					return -1;
				}

				/*Step 5) Request Data from slave.
				*Wire.requestFrom(uint8_t SlaveAddress, uint8_t Quantity, bool Stop) - Used by the master to request bytes from a slave device.
				*SlaveAddress: the 7-bit address of the device to request bytes from.
				*Quantity: the number of bytes to request. For Read Command, 2 Bytes are required.
				*Stop : boolean. true (true as declared in i2c_t3.h/Wire.h) will send a stop message after the request, releasing the bus.
				*/
				Wire.requestFrom(Data->Slave_Address, 2,true);

				/*Step 6) Read data from slave.
				*Wire.read() - Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
				*Read the 2 Bytes Data from the Sensor by calling it 2 times and store it in the RData Array.
				*/
				Data->RData[0] = Wire.read();
				Data->RData[1] = Wire.read();

				break;
		}

		return 0;
	}

	//Master sends I2C Gesture Read command and save the read data via pointer *Data.
	//The function returns 0 upon completion.
	int ReadI2C_Bus_Gesture_Mode(struct GestureTransferData *Data)
	{
		//Arduino/Teensy/Adafruit could allow 2 parallel I2C bus to be used simultaneously.
		//Select_I2C_BUS is defined in Main_User.cpp.
		switch (Data->Select_I2C_Bus)
		{
			//Case I2C Bus 1
			case 1:
				//Send I2C Gesture Read Command as shown in the Application Note Page 19.
				//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
				Wire.begin();

				/*Step 2) Request Data from slave.
				*Wire.requestFrom(uint8_t SlaveAddress, uint8_t Quantity, bool Stop) - Used by the master to request bytes from a slave device.
				*SlaveAddress: the 7-bit address of the device to request bytes from.
				*Quantity: the number of bytes to request. For Gesture Read Command, 6 Bytes are required.
				*Stop : boolean. true (true as declared in i2c_t3.h/Wire.h) will send a stop message after the request, releasing the bus.
				*/
				Wire.requestFrom(Data->Slave_Address, 6,true);

				/*Step 3) Read data from slave.
				*Wire.read() - Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
				*Read the 6 Bytes Data from the Sensor by calling it 6 times and store it in the RData Array.
				*/
				Data->RData[0] = Wire.read();
				Data->RData[1] = Wire.read();
				Data->RData[2] = Wire.read();
				Data->RData[3] = Wire.read();
				Data->RData[4] = Wire.read();
				Data->RData[5] = Wire.read();

				break;
			#ifdef i2ct3
				//Case I2C Bus 2
				case 2:
					//Send I2C Gesture Read Command as shown in the Application Note Page 19.
					//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
					Wire1.begin();

					/*Step 2) Request Data from slave.
					*Wire.requestFrom(uint8_t SlaveAddress, uint8_t Quantity, bool Stop) - Used by the master to request bytes from a slave device.
					*SlaveAddress: the 7-bit address of the device to request bytes from.
					*Quantity: the number of bytes to request. For Gesture Read Command, 6 Bytes are required.
					*Stop : boolean. true (true as declared in i2c_t3.h/Wire.h) will send a stop message after the request, releasing the bus.
					*/
					Wire1.requestFrom(Data->Slave_Address, 6,true);

					/*Step 3) Read data from slave.
					*Wire.read() - Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
					*Read the 6 Bytes Data from the Sensor by calling it 6 times and store it in the RData Array.
					*/
					Data->RData[0] = Wire1.read();
					Data->RData[1] = Wire1.read();
					Data->RData[2] = Wire1.read();
					Data->RData[3] = Wire1.read();
					Data->RData[4] = Wire1.read();
					Data->RData[5] = Wire1.read();

					break;
			#endif

			//Other Cases I2C Bus set to default
			default:
				//Send I2C Gesture Read Command as shown in the Application Note Page 19.
				//Step 1) Initiate the Wire library and join the I2C bus as a master or slave. This should normally be called only once.
				Wire.begin();

				/*Step 2) Request Data from slave.
				*Wire.requestFrom(uint8_t SlaveAddress, uint8_t Quantity, bool Stop) - Used by the master to request bytes from a slave device.
				*SlaveAddress: the 7-bit address of the device to request bytes from.
				*Quantity: the number of bytes to request. For Gesture Read Command, 6 Bytes are required.
				*Stop : boolean. true (true as declared in i2c_t3.h/Wire.h) will send a stop message after the request, releasing the bus.
				*/
				Wire.requestFrom(Data->Slave_Address, 6,true);

				/*Step 3) Read data from slave.
				*Wire.read() - Reads a byte that was transmitted from a slave device to a master after a call to requestFrom().
				*Read the 6 Bytes Data from the Sensor by calling it 6 times and store it in the RData Array.
				*/
				Data->RData[0] = Wire.read();
				Data->RData[1] = Wire.read();
				Data->RData[2] = Wire.read();
				Data->RData[3] = Wire.read();
				Data->RData[4] = Wire.read();
				Data->RData[5] = Wire.read();

				break;

		}
		return 0;
	}
#endif
