/*
 * BSP_aux.c
 *
 *  Created on: Nov 24, 2024
 *      Author: diego
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

enum Layer {
	IMAGES_LAYER = 0,
};

uint32_t *size;

void BSP_DisplayImage(uint8_t index, char* pDirectoryFiles[25], uint8_t ubNumberOfFiles, uint8_t transparencyFade, uint8_t displayFilename)
{
	uint8_t path[30], displayedNameSize[50];

	if (transparencyFade)
	{
		for (int i = 255; i>0; i--)
		{
			BSP_LCD_SetTransparency(IMAGES_LAYER, i);
			HAL_Delay(1);
		}
	}
	else
	{
		BSP_LCD_SetTransparency(IMAGES_LAYER, 0);
	}

	sprintf ((char*)path, "/%-28.28s", pDirectoryFiles[index]);
	uint8_t *uwInternelBuffer= (uint8_t *)0xC0260000;
	Storage_OpenReadFile(uwInternelBuffer, (const char*)path, size);

	BSP_LCD_Clear(((uint32_t)0xFF000000));
	BSP_LCD_DrawBitmap(0, 0, uwInternelBuffer);


	if (displayFilename)
	{
		sprintf ((char*)path, "/%s - %luB", pDirectoryFiles[index], *size);
		BSP_LCD_DisplayStringAtLine(0, (uint8_t*)path);
	}


	if (transparencyFade)
	{
		for (int i = 0; i<255; i++)
		{
			BSP_LCD_SetTransparency(IMAGES_LAYER, i);
			HAL_Delay(1);
		}
	}
	else
	{
		BSP_LCD_SetTransparency(IMAGES_LAYER, 255);
	}
}
