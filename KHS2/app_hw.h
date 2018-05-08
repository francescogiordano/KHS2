#ifndef APP_HW_H
#define APP_HW_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bg_types.h"

#define ERROR_FLAG_SRAM				0x80
#define ERROR_FLAG_LOW_GYRO_ACCEL	0x40
#define ERROR_FLAG_HIGH_ACCEL		0x20

void InitAppHw(void);
void AppHwTick(void);

uint8_t GetAppHwErrorFlags(void);

#ifdef __cplusplus
};
#endif

#endif // APP_HW_H
