#ifndef __LETIMER_H__
#define __LETIMER_H__

#include "stdint.h"
#include "ecode.h"
#include "letimer_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ECODE_EMDRV_LETIMER_OK ( ECODE_OK ) ///< Success return value.

Ecode_t InitLeTimer(void);
Ecode_t StartLeTimer(void);
uint64_t GetLeCounter(void);


#ifdef __cplusplus
}
#endif

#endif
