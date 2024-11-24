
#ifndef __FAT_FS_STORAGE_H
#define __FAT_FS_STORAGE_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "ff.h"
#include "main.h"

uint32_t Storage_Init (void);
uint32_t Storage_OpenReadFile(uint8_t *Address, const char* BmpName);
uint32_t Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[]);
uint32_t Storage_CheckBitmapFile(const char* BmpName, uint32_t *FileLen);
uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

#define MAX_BMP_FILES     25
#define MAX_BMP_FILE_NAME 11

#ifdef __cplusplus
}
#endif

#endif /* __FAT_FS_STORAGE_H */
