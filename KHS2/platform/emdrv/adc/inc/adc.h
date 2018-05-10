#ifndef __ADC_H__
#define __ADC_H__

#include "stdint.h"
#include "ecode.h"
#include "adc_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#define ECODE_EMDRV_ADC_OK ( ECODE_OK ) // Success return value

Ecode_t InitAdc(void);
uint32_t GetSingleAdc(void);


#ifdef __cplusplus
}
#endif

#endif // __ADC_H__
