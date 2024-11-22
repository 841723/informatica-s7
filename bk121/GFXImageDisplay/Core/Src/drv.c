/***
 * @file drv.c
 * @brief Source file for the driver.
 */

#include "../Inc/drv.h"

void drv_init(void) {
    int i = 4;
    for (int j = 0; j < i; j++) {
        printf("drv_init: %d\n", j);
    }
}

// bool loadBitmapFromSD(const char* filePath, touchgfx::BitmapId& bmpId)
// {
//     FIL file;
//     UINT bytesRead;

//     // Abre el archivo en la tarjeta SD
//     if (f_open(&file, filePath, FA_READ) != FR_OK) {
//         printf("Error al abrir el archivo BMP: %s\n", filePath);
//         return false;
//     }

//     // Lee el contenido del archivo BMP al buffer
//     if (f_read(&file, bmpBuffer, BMP_BUFFER_SIZE, &bytesRead) != FR_OK) {
//         printf("Error al leer el archivo BMP\n");
//         f_close(&file);
//         return false;
//     }

//     f_close(&file);

//     // Crea un bitmap dinámico en TouchGFX usando el buffer
//     bmpId = Bitmap::dynamicBitmapCreate(width, height, Bitmap::RGB888);
//     if (bmpId == BITMAP_INVALID) {
//         printf("Error al crear el bitmap dinámico\n");
//         return false;
//     }

//     uint8_t* dynamicBitmapData = Bitmap::dynamicBitmapGetAddress(bmpId);
//     memcpy(dynamicBitmapData, bmpBuffer, bytesRead);
//     return true;
// }
