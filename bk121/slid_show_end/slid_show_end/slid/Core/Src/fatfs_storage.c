
#include "fatfs_storage.h"


uint8_t sector[512];
FATFS fs;
FILINFO fno;
DIR dir;
FIL F;
const uint8_t SlidesCheck[2] =
  {
    0x42, 0x4D
  };
uint32_t BytesRead = 0;


uint32_t Storage_Init(void)
{
  BSP_SD_Init();
  
  /****************** FatFs Volume Access ******************************/
  if(f_mount(&fs, (TCHAR const*)"",0))
  {
    return 1;
  }
  return 0;
}


uint32_t Storage_OpenReadFile(uint8_t *Address, const char* BmpName, uint32_t *totalSize)
{
  uint32_t index = 0, size = 0, i1 = 0;
  uint32_t BmpAddress;
  FIL F1;

  if (f_open(&F1, (TCHAR const*)BmpName, FA_READ) != FR_OK)
  {
    while(1)
    {
    } 
  }
  if (f_read (&F1, sector, 30, (UINT *)&BytesRead) != FR_OK)
  {
    while(1)
    {
    } 
  }


  BmpAddress = (uint32_t)sector;

  /* Read bitmap size */
  size = *(uint16_t *) (BmpAddress + 2);
  size |= (*(uint16_t *) (BmpAddress + 4)) << 16;  
  *totalSize = size;
 
  /* Get bitmap data address offset */
  index = *(uint16_t *) (BmpAddress + 10);
  index |= (*(uint16_t *) (BmpAddress + 12)) << 16;  
  
  f_close (&F1);
  
  f_open (&F1, (TCHAR const*)BmpName, FA_READ);

  do
  {
    if (size < 256*2)
    {
      i1 = size;
    }
    else
    {
      i1 = 256*2;
    }
    size -= i1;
    f_read (&F1, sector, i1, (UINT *)&BytesRead);


    for (index = 0; index < i1; index++)
    {
      *(__IO uint8_t*) (Address) = *(__IO uint8_t *)BmpAddress;
      
      BmpAddress++;
      Address++;
    }  
    
    BmpAddress = (uint32_t)sector;
  }
  while (size > 0);

  f_close (&F1);
  
  return 1;
}


uint32_t Storage_CheckBitmapFile(const char* BmpName, uint32_t *FileLen)
{
  if(f_mount(&fs, (TCHAR const*)"",0))
  {
    return 1;
  }
  if(f_open (&F, (TCHAR const*)BmpName, FA_READ))
  {
    return 2;
  }
  
  f_read (&F, sector, 6, (UINT *)&BytesRead);
  
  if (Buffercmp((uint8_t *)SlidesCheck, (uint8_t *) sector, 2) != 0)
  {
    return 3;
  }
  return 0;
}


uint32_t Storage_GetDirectoryBitmapFiles(const char* DirName, char* Files[])
{
  FRESULT res;
  uint32_t index = 0;

  /* Open filesystem */
  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
  {
    return 0;
  }

  /* Start to search for wave files */
  res = f_findfirst(&dir, &fno, DirName, "*.bmp");

  /* Repeat while an item is found */
  while (fno.fname[0])
  {
    if(res == FR_OK)
    {
      if(index < MAX_BMP_FILES)
      {
        sprintf (Files[index++], "%s", fno.fname);
      }
      /* Search for next item */
      res = f_findnext(&dir, &fno);
    }
    else
    {
      index = 0;
      break;
    }
  }

  f_closedir(&dir);

  return index;
}


uint8_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while (BufferLength--)
  {
    if (*pBuffer1 != *pBuffer2)
    {
      return 1;
    }

    pBuffer1++;
    pBuffer2++;
  }

  return 0;
}

