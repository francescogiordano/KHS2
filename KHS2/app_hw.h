#ifndef APP_HW_H
#define APP_HW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void InitAppHw(void);
void AppHwTick(void);

bool GetAppHwErrorFlag(void);
bool GetAppHwInitSramErrorFlag(void);
bool GetAppHwInitLowAccelSensErrorFlag(void);
bool GetAppHwInitHighAccelSensErrorFlag(void);

#ifdef __cplusplus
};
#endif

#endif // APP_HW_H
