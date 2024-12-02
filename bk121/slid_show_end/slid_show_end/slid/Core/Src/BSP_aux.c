/*
 * BSP_aux.c
 *
 *  Created on: Nov 24, 2024
 *      Author: diego
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t actualLayer = 0;
uint8_t firstDisplay = 0;

void BSP_DisplayImage(uint8_t index, char* pDirectoryFiles[25], uint8_t ubNumberOfFiles)
{
	uint8_t path[30];
	uint8_t lastLayer = 1;

	if (firstDisplay == 0) {

		firstDisplay = 1;
		actualLayer = 0;


		sprintf ((char*)path, "/%-11.11s", pDirectoryFiles[index]);
		uint8_t *uwInternelBuffer= (uint8_t *)0xC0260000;
		Storage_OpenReadFile(uwInternelBuffer, (const char*)path);

		BSP_LCD_SelectLayer(actualLayer);
		BSP_LCD_DrawBitmap(0, 0, uwInternelBuffer);
	}


	// lastLayer->layer in which is displayed the image we don't want to see
	lastLayer = (actualLayer + 1) & 1;

	BSP_LCD_SetTransparency(lastLayer,0);
	HAL_Delay(2);
	BSP_LCD_SetTransparency(actualLayer, 255);
	HAL_Delay(2);

	++index;
	index %= ubNumberOfFiles;
	sprintf ((char*)path, "/%-11.11s", pDirectoryFiles[index]);
	uint8_t *uwInternelBuffer= (uint8_t *)0xC0260000;
	Storage_OpenReadFile(uwInternelBuffer, (const char*)path);

	BSP_LCD_SelectLayer(lastLayer);
	BSP_LCD_Clear(((uint32_t)0xFF000000));
	BSP_LCD_DrawBitmap(0, 0, uwInternelBuffer);

	actualLayer ++;
	actualLayer %=2;
}
