#include "board.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#include "hal-config.h"
#else
#include "bspconfig.h"
#endif

#include "pti.h"

#include "board_features.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "bsp.h"

#include "s23lc1024.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"

void InitBoard(void){

	// Enable PTI
	//configEnablePti();

	// Enable GPIO clock source
	CMU_ClockEnable(cmuClock_GPIO, true);

#if	HAL_SPI_ENABLE
  //RETARGET_WriteString("MCU Enter", 9);
  Set23lc1024();
  //RETARGET_WriteString("MCU Exit", 8);
#endif

#if (HAL_I2C_ENABLE)
  SetI2CLsm6dsl();
  SetI2CH3lis331dl();
#endif

}
