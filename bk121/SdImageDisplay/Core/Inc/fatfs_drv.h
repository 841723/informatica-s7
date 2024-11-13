/*
 * fatfs_drv.h
 *
 *  Created on: Oct 23, 2024
 *      Author: diego
 */

#ifndef INC_FATFS_DRV_H_
#define INC_FATFS_DRV_H_

#include <stdint.h>
#include <main.h>
#include "fatfs.h"

void FATFS_Init();
void FATFS_Run();
void FATFS_Scan(char* path, char filenames[8][64]);

FRESULT FATFS_Read_Image_From_SD(const char *filename, uint8_t *buffer, uint32_t bufsize);


#endif /* INC_FATFS_DRV_H_ */
