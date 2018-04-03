#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#include "hal-config.h"
#else
#include "bspconfig.h"
#endif

#include "board_features.h"

#include "em_cmu.h"

#include "em_usart.h"

#include "bsp.h"

void InitBoard(void){

  // Enable GPIO clock source
  CMU_ClockEnable(cmuClock_GPIO, true);
}
