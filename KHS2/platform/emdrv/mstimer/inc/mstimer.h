#ifndef __MSTIMER_H
#define __MSTIMER_H

#include <stdint.h>
#include "ecode.h"
#include "mstimer_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ECODE_EMDRV_MSTIMER_OK ( ECODE_OK ) ///< Success return value.

Ecode_t MSTIMER_Init(void);
Ecode_t StartMSTIMER(void);
uint64_t GetMsCounter(void);

#ifdef __cplusplus
}
#endif

#endif
