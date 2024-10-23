/*
 * fatuser.h
 *
 *  Created on: Oct 23, 2024
 *      Author: diego
 */

#ifndef INC_FATUSER_H_
#define INC_FATUSER_H_

#include <stdint.h>

void FATFS_Init();
void FATFS_Run();
void FATFS_Scan(char* path);

#endif /* INC_FATUSER_H_ */
