#include "board.h"

#include "hal-config.h"

#include "pti.h"
#include "em_cmu.h"

#include "s23lc1024.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"
#include "adc.h"

void InitBoard(void){

	// Enable PTI
	//configEnablePti();

	// Enable GPIO clock source
	CMU_ClockEnable(cmuClock_GPIO, true);

	InitAdc();

#if	HAL_SPI_ENABLE
	Set23lc1024();
#endif

#if (HAL_I2C_ENABLE)
	SetI2CLsm6dsl();
	SetI2CH3lis331dl();
#endif
}
