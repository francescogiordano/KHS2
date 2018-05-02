#ifndef APP_HW_H
#define APP_HW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void InitAppHw(void);
void appHwTick(void);

bool GetAppHwErrorFlag(void);

#ifdef __cplusplus
};
#endif

#endif /* APP_HW_H */
