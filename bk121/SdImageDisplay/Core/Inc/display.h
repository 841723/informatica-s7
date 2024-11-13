/*
 * display.h
 *
 *  Created on: Nov 13, 2024
 *      Author: diego
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include <stdint.h>
#include <main.h>
#include "stm32f7xx_hal.h"



HAL_StatusTypeDef Display_Image_DMA2D(uint16_t* src, uint16_t width, uint16_t height);

#endif /* INC_DISPLAY_H_ */
