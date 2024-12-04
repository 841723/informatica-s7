/*
 * BSP_aux.h
 *
 *  Created on: Nov 24, 2024
 *      Author: diego
 */

#ifndef INC_BSP_AUX_H_
#define INC_BSP_AUX_H_

#include "ff_gen_drv.h"
#include "fatfs_storage.h"
#include "sd_diskio.h"
#include "BSP_aux.h"

void BSP_DisplayImage(uint8_t index, char* pDirectoryFiles[25], uint8_t ubNumberOfFiles, uint8_t transparencyFade, uint8_t displayFilename);

void BSP_DisplayButtons(void);

#endif /* INC_BSP_AUX_H_ */
