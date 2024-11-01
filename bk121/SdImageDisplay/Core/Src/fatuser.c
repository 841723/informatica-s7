/*
 * fatuser.c
 *
 *  Created on: Oct 23, 2024
 *      Author: diego
 */

#include <string.h>
#include <stdio.h>
#include "fatuser.h"
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
	FATFS_Scan("/");
}

void FATFS_Scan(char* path) {
	DIR dir;
	FILINFO fno;
    FRESULT res;
    char buffer[128];  // Buffer for file paths

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
                if (strstr(fno.fname, ".bmp") || strstr(fno.fname, ".jpg") || strstr(fno.fname, ".jpeg")) {
                    // Full file path (assuming 'path' is the current directory)
                    sprintf(buffer, "%s/%s", path, fno.fname);

                    // Read and display the image
//                    Read_Image_File(buffer);
                }
            }
        }
        f_closedir(&dir);  // Close the directory
    }
}



