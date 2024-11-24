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

void BSP_DisplayImage(uint8_t index, char* pDirectoryFiles[25], uint8_t ubNumberOfFiles)
{
	uint8_t path[30];
	// lastLayer->layer in which is displayed the image we don't want to see
	uint8_t lastLayer = (actualLayer + 1) & 1;

	// actualLayer -> layer in which we want to display image

	BSP_LCD_SetTransparency(lastLayer,0);
	BSP_LCD_SetTransparency(actualLayer, 255);


	sprintf ((char*)path, "%-11.11s", pDirectoryFiles[++index]);
	uint8_t *uwInternelBuffer= (uint8_t *)0xC0260000;
	Storage_OpenReadFile(uwInternelBuffer, (const char*)path);

	BSP_LCD_SelectLayer(lastLayer);
	BSP_LCD_DrawBitmap(0, 0, uwInternelBuffer);


	actualLayer ++;
	actualLayer %=2;
}
