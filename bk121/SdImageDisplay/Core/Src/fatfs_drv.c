/*
 * fatfs_drv.c
 *
 *  Created on: Oct 23, 2024
 *      Author: diego
 */

#include <fatfs_drv.h>
#include <string.h>
#include <stdio.h>
#include "fatfs.h"

FRESULT res; /* FatFs function common result code */
uint32_t byteswritten; /* File write/read counts */
uint8_t wtext[] = "STM32 FATFS works great!"; /* File write buffer */
uint8_t rtext[_MAX_SS];/* File read buffer */

void FATFS_Init() {
	if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) != FR_OK)
	{
		Error_Handler();
	}
}

void FATFS_Run() {

	if(f_mkfs((TCHAR const*)SDPath, FM_ANY, 0, rtext, sizeof(rtext)) != FR_OK)
	{
		Error_Handler();
	}
	else
	{
		//Open file for writing (Create)
		if(f_open(&SDFile, "test1.tmp", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
		{
			Error_Handler();
		}
		else
		{

			//Write to the text file
			res = f_write(&SDFile, wtext, strlen((char *)wtext), (void *)&byteswritten);
			if((byteswritten == 0) || (res != FR_OK))
			{
				Error_Handler();
			}
			else
			{

				f_close(&SDFile);
			}
		}
	}
	f_mount(&SDFatFS, (TCHAR const*)NULL, 0);
}

void FATFS_Scan(char* path, char filenames[8][64]) {
	DIR dir;
	FILINFO fno;
    FRESULT res;
    unsigned int idx = 0;

    res = f_opendir(&dir, path);  // Open directory
    if (res == FR_OK) {
        while (1) {
            res = f_readdir(&dir, &fno);  // Read a directory item
            if (res != FR_OK || fno.fname[0] == 0) {
                break;  // No more items
            }

            if (fno.fattrib & AM_DIR) {
                // If it's a directory, you can optionally recurse into it
            } else {
                // Check if the file is an image
                if (strstr(fno.fname, "AABUILDING.BMP")) {
                    // Full file path (assuming 'path' is the current directory)
                    sprintf(filenames[idx], "%s", fno.fname);
                    idx++;
                    // Read and display the image
                    //  Read_Image_File(buffer);
                }
            }
        }
        f_closedir(&dir);  // Close the directory
    }
}


FRESULT FATFS_Read_Image_From_SD(const char *filename, uint8_t *buffer) {
    FATFS fs;
	FIL file;
    UINT bytesRead = 0;


    res = f_mount(&fs, "", 1);
    if (res != FR_OK) {
		return res;
	}

    FRESULT res = f_open(&file, filename, FA_READ);
    if (res != FR_OK) {
        return res;
    }

    // Leer datos de la imagen en el buffer
    res = f_read(&file, buffer, IMAGE_SIZE, &bytesRead);
    if (res != FR_OK || bytesRead == 0) {
        f_close(&file);
        return res; // Error de lectura
    }

	buffer[bytesRead] = '\0';
    f_close(&file);

    f_mount(NULL, "", 1);

    return FR_OK;  // Éxito
}
