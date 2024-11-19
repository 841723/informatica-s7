/*
 * display.c
 *
 *  Created on: Nov 13, 2024
 *      Author: diego
 */

#include <display.h>

void Test_SDRAM(void);

HAL_StatusTypeDef Display_Image_DMA2D(uint16_t* src, uint16_t width, uint16_t height) {
    DMA2D_HandleTypeDef hdma2d;

    // Configura DMA2D
    hdma2d.Instance = DMA2D;
    hdma2d.Init.Mode = DMA2D_M2M;
    hdma2d.Init.ColorMode = DMA2D_RGB565;
    hdma2d.Init.OutputOffset = 0;

    Test_SDRAM();

    if (HAL_DMA2D_Init(&hdma2d) != HAL_OK) {
        return HAL_ERROR;
    }

    // Inicia la transferencia de la imagen al framebuffer
    if (HAL_DMA2D_Start(&hdma2d, (uint32_t)src, FRAME_BUFFER_ADDRESS, width, height) != HAL_OK) {
    	return HAL_ERROR;
    }

    // Espera hasta que se complete la transferencia
    if (HAL_DMA2D_PollForTransfer(&hdma2d, 1000) != HAL_OK) {
    	return HAL_ERROR;
    }

    return HAL_OK;
}

void Test_SDRAM(void) {
    uint32_t *sdram_addr = (uint32_t *)FRAME_BUFFER_ADDRESS;

    // Escribir valores en la SDRAM
    for (uint32_t i = 0; i < 1024; i++) {
        sdram_addr[i] = i;
    }

    // Verificar valores
    for (uint32_t i = 0; i < 1024; i++) {
        if (sdram_addr[i] != i) {
            return;
        }
    }
}
