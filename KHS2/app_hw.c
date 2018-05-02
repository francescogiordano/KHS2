/* BG stack headers */
#include "bg_types.h"

/* STK header files. */
#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif
#include "bsp.h"

/* Temp sensor and I2C*/
#if defined(HAL_CONFIG)
#include "i2cspmhalconfig.h"
#else
#include "i2cspmconfig.h"
#endif
#include "i2cspm.h"

/* application specific headers */
#include "advertisement.h"
#include "app_ui.h"

/* Own headers*/
#include <app_timer.h>
#include "app_extsignals.h"
#include "app_hw.h"
#include "app_ble.h"
#include "wdog.h"

#include "s23lc1024.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"

//**************************   STATIC VARIABLES   *****************************

static bool sramErrorFlag = false;
static bool lowAccelGyroSensErrorFlag = false;
static bool highAccelSensErrorFlag = false;

static int counter = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static bool appHwInitSram(void){
	bool result = false;

	if(Detect23lc1024() == Msg23lc1024Success){
		result = true;
	}

	return result;
}
static bool appHwInitLowAccelGyroSens(void){
	bool result = false;

	if(DetectLsm6dsl() == MsgLsm6dslSuccess){
		result = true;
		RETARGET_WriteString("Lsm6dsl Detected: true", 22);
	}
	else{
		RETARGET_WriteString("Lsm6dsl Detected: false", 23);
	}
	return result;
}
static bool appHwInitHighAccelSens(void){
	bool result = false;

	if(DetectH3lis331dl() == MsgH3lis331dlSuccess){
		result = true;
		RETARGET_WriteString("H3lis331dl Detected: true", 25);
	}
	else{
		RETARGET_WriteString("H3lis331dl Detected: false", 26);
	}
	return result;
}

//**************************   PUBLIC FUNCTION DEFINIITIONS   *****************

void InitAppHw(void){

#if HAL_SPI_ENABLE
	Init23lc1024();
#endif

#if HAL_I2C_ENABLE
	InitLsm6dsl();
	InitH3lis331dl();
#endif

  gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(HWTIMER_PERIOD), HW_TIMER, false);

  if(!appHwInitSram()){
	  sramErrorFlag = true;
  }
  if(!appHwInitLowAccelGyroSens()){
	  lowAccelGyroSensErrorFlag = true;
  }
  if(!appHwInitHighAccelSens()){
	  highAccelSensErrorFlag = true;
  }
}
void appHwTick(void){

	//static int secs = 0;
	//char str[10];
	counter++;

	if (counter%10 == 0){
		//secs++;
		//sprintf(str, "%i", secs);
	    //appUiWriteString(str);
		KhsDataCharUpdate();
	  }

	//gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(HWTIMER_PERIOD), HW_TIMER, false);
}

bool GetAppHwErrorFlag(void){
	bool result = false;

	if(sramErrorFlag || lowAccelGyroSensErrorFlag || highAccelSensErrorFlag){
		result = true;
	}
	return result;
}
