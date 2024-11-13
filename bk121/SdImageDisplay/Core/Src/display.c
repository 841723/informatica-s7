/*
 * display.c
 *
 *  Created on: Nov 13, 2024
 *      Author: diego
 */

#include <display.h>


HAL_StatusTypeDef Display_Image_DMA2D(uint16_t* src, uint16_t width, uint16_t height) {
    DMA2D_HandleTypeDef hdma2d;

    // Configura DMA2D
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M;
    hdma2d.Init.ColorMode = DMA2D_RGB565;
    hdma2d.Init.OutputOffset = 0;

    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK) {
        return HAL_ERROR;
    }

    // Inicia la transferencia de la imagen al framebuffer
    HAL_DMA2D_Start(&hdma2d, (uint32_t)src, FRAME_BUFFER_ADDRESS, width, height);

    // Espera hasta que se complete la transferencia
    HAL_DMA2D_PollForTransfer(&hdma2d, HAL_MAX_DELAY);

    return HAL_OK;
}