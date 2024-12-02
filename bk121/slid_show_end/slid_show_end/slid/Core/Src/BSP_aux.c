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
	BUTTONS_LAYER = 1,
};

uint8_t buttons = 1;


void BSP_DisplayButtons(void)
{
	if (!buttons) return;
	uint8_t rad = 30;
	uint8_t xpad = 5;


	BSP_LCD_SetTextColor(((uint32_t)0xFFFF0000));
	BSP_LCD_FillCircle(rad+xpad,272/2+rad/2,rad);
	BSP_LCD_FillCircle(480-rad-xpad,272/2+rad/2,rad);
	BSP_LCD_SetTransparency(BUTTONS_LAYER, 200);
}

void BSP_DeleteButtons(void)
{
	if (!buttons) return;
	BSP_LCD_SelectLayer(BUTTONS_LAYER);
	BSP_LCD_Clear(0);
}


void BSP_DisplayImage(uint8_t index, char* pDirectoryFiles[25], uint8_t ubNumberOfFiles)
{
	uint8_t path[30];

//	BSP_DeleteButtons();
	for (int i = 255; i>0; i--)
	{
		BSP_LCD_SetTransparency(IMAGES_LAYER, i);
		HAL_Delay(1);
	}

	sprintf ((char*)path, "/%-11.11s", pDirectoryFiles[index]);
	uint8_t *uwInternelBuffer= (uint8_t *)0xC0260000;
	Storage_OpenReadFile(uwInternelBuffer, (const char*)path);

	BSP_LCD_SelectLayer(IMAGES_LAYER);
	BSP_LCD_Clear(((uint32_t)0xFF000000));
	BSP_LCD_DrawBitmap(0, 0, uwInternelBuffer);

	for (int i = 0; i<255; i++)
	{
		BSP_LCD_SetTransparency(IMAGES_LAYER, i);
		HAL_Delay(1);
	}
//	BSP_DisplayButtons();
}
