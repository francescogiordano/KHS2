/* BG stack headers */
#include "bg_types.h"

/* STK header files. */
#if defined(HAL_CONFIG)
#include "bsphalconfig.h"
#else
#include "bspconfig.h"
#endif
#include "bsp.h"

/* Temp sensor and I2c*/
#if defined(HAL_CONFIG)
#include "i2cspmhalconfig.h"
#else
#include "i2cspmconfig.h"
#endif
#include "i2cspm.h"
#include "si7013.h"
#include "tempsens.h"

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

/* Text definitions*/
#define APP_HW_SENSOR_FAIL_TEXT         "Failed to detect\nsi7021 sensor."

//**************************   STATIC VARIABLES   *****************************

static bool sramErrorFlag = false;
static bool lowAccelGyroSensErrorFlag = false;
static bool highAccelSensErrorFlag = false;

static int counter = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static void appBtnCback(AppUiBtnEvt_t btn){

  if (APP_UI_BTN_0_SHORT == btn) {
	  KhsDataCharUpdate();
	  KhsDiagInfoCharWrite();
	  //gecko_external_signal(APP_DATA_LOW_ACCEL_GYRO);
  }
  if (APP_UI_BTN_1_SHORT == btn) {
	  KhsHighAccelCharUpdate();
  }
}

static bool appHwInitSram(void){
	bool result = false;

	if(Detect23lc1024() == Msg23lc1024Success){
		result = true;
	}

	return result;
}
static bool appHwInitLowAccelGyroSens(void){
	bool result = false;

	if(DetectLsm6dsl() == Lsm6dslSuccess){
		result = true;
	}
	return result;
}
static bool appHwInitHighAccelSens(void){
	bool result = false;

	if(DetectH3lis331dl() == H3lis331dlSuccess){
		result = true;
	}
	return result;
}

//**************************   PUBLIC FUNCTION DEFINIITIONS   *****************

void InitAppHw(void){

#if HAL_SPI_ENABLE
	Init23lc1024();
#endif

#if HAL_I2C_ENABLE
	RETARGET_WriteString("Init Enter", 10);
	//InitLsm6dsl();
	//InitH3lis331dl();
	RETARGET_WriteString("Init Exit", 9);
#endif

  /* Register button callback */
  appUiBtnRegister(appBtnCback);

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
int32_t appHwReadTm(int32_t* tempData){
  uint32_t rhData = 0;
  return Si7013_MeasureRHAndTemp(I2C0, SI7021_ADDR, &rhData, tempData);
}

bool GetAppHwErrorFlag(void){
	bool result = false;

	if(sramErrorFlag || lowAccelGyroSensErrorFlag || highAccelSensErrorFlag){
		result = true;
	}
	return result;
}
