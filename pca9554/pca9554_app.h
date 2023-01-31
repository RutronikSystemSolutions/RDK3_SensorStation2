/*
 * pca9554_app.h
 *
 *  Created on: Jan 12, 2023
 *      Author: Gintaras
 */

#ifndef PCA9554_PCA9554_APP_H_
#define PCA9554_PCA9554_APP_H_

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "pca9554.h"

#define PCA9554_POL_CONFIG	UINT8_C(0x00)
#define PCA9554_DIR_CONFIG	UINT8_C(0x00)
#define PCA9554_OUT_CONFIG	UINT8_C(0x00)

#define PCA9554_DIR_NONE	UINT8_C(0x00)
#define PCA9554_DIR_RIGHT	UINT8_C(0x02)
#define PCA9554_DIR_LEFT	UINT8_C(0x01)
#define PCA9554_DIR_UP		UINT8_C(0x04)
#define PCA9554_DIR_DOWN	UINT8_C(0x08)
#define PCA9554_DIR_UPPER	UINT8_C(0x20)
#define PCA9554_DIR_LOWER	UINT8_C(0x10)

/*Function prototypes*/
cy_rslt_t pca9554_configure(void);
cy_rslt_t pca9554_dir_set(uint8_t dir);



#endif /* PCA9554_PCA9554_APP_H_ */
