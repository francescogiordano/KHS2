#include "board.h"

#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#include "hal-config.h"
#else
#include "bspconfig.h"
#endif

#include "pti.h"

/*
#include "board_features.h"
#include "em_cmu.h"
#include "em_usart.h"
#include "bsp.h"
*/

#include "s23lc1024.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"


void InitBoard(void){

	// Enable PTI
	configEnablePti();

	#if defined(HAL_SPIDISPLAY_ENABLE)
		// Enable SPI display if requested
		GPIO_PinModeSet(BSP_SPIDISPLAY_ENABLE_PORT, BSP_SPIDISPLAY_ENABLE_PIN, gpioModePushPull, HAL_SPIDISPLAY_ENABLE);
	#endif // HAL_SPIDISPLAY_ENABLE

	// Enable GPIO clock source
	//CMU_ClockEnable(cmuClock_GPIO, true);

	Init23lc1024();
	InitLsm6dsl();
	InitH3lis331dl();
}
