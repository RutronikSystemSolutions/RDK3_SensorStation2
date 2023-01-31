/*
 * pca9554.h
 *
 *  Created on: Jan 12, 2023
 *      Author: Gintaras
 */

#ifndef PCA9554_PCA9554_H_
#define PCA9554_PCA9554_H_

/*RDK2 platform includes*/
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

#define PCA9554_DEV_ADDRESS						UINT8_C(0x27)

#ifndef PCA9554_RET_TYPE
#define PCA9554_RET_TYPE                      	int8_t
#endif

#define PCA9554_INPUT_CMD						UINT8_C(0)
#define PCA9554_OUTPUT_CMD						UINT8_C(1)
#define PCA9554_POLARITY_CMD					UINT8_C(2)
#define PCA9554_CONFIG_CMD						UINT8_C(3)

#define PCA9554_OK                              INT8_C(0)
#define PCA9554_COM_ERR                        	INT8_C(-1)

PCA9554_RET_TYPE pca9554_pins_write(uint8_t address, uint8_t pins);
PCA9554_RET_TYPE pca9554_pins_read(uint8_t address, uint8_t* pins);
PCA9554_RET_TYPE pca9554_read_config_dir(uint8_t address, uint8_t* pins);
PCA9554_RET_TYPE pca9554_read_config_pol(uint8_t address, uint8_t* pins);
PCA9554_RET_TYPE pca9554_write_config_dir(uint8_t address, uint8_t pins);
PCA9554_RET_TYPE pca9554_write_config_pol(uint8_t address, uint8_t pins);

#endif /* PCA9554_PCA9554_H_ */
