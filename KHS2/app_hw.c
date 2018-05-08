#include "app_hw.h"

#include "app_timer.h"
#include "app_extsignals.h"

#include "s23lc1024.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"

//**************************   STATIC VARIABLES   *****************************

static uint8_t errorFlags = 0x00;
static int counter = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static void appHwInitHighAccelSens(void){


}

static void updateAppHwInitSramErrorFlag(void){

	if(Detect23lc1024() == Msg23lc1024Success){
		errorFlags ^= ERROR_FLAG_SRAM;
	#if DEBUG_ENABLE
		RETARGET_WriteString("23lc1024 Detected: true", 23);
	#endif
	}
#if DEBUG_ENABLE
	else{
		RETARGET_WriteString("23lc1024 Detected: false", 24);
	}
#endif
}
static void updateAppHwInitLowAccelSensErrorFlag(void){

	if(DetectLsm6dsl() == MsgLsm6dslSuccess){
		errorFlags ^= ERROR_FLAG_LOW_GYRO_ACCEL;
	#if DEBUG_ENABLE
		RETARGET_WriteString("Lsm6dsl Detected: true", 22);
	#endif
	}
#if DEBUG_ENABLE
	else{
		RETARGET_WriteString("Lsm6dsl Detected: false", 23);
	}
#endif
}
static void updateAppHwInitHighAccelSensErrorFlag(void){

	if(DetectH3lis331dl() == MsgH3lis331dlSuccess){
		errorFlags ^= ERROR_FLAG_HIGH_ACCEL;
	#if DEBUG_ENABLE
		RETARGET_WriteString("H3lis331dl Detected: true", 25);
	#endif
	}
#if DEBUG_ENABLE
	else{
		RETARGET_WriteString("H3lis331dl Detected: false", 26);
	}
#endif
}

static void updateAppHwErrorFlags(void){

#if HAL_SPI_ENABLE
	updateAppHwInitSramErrorFlag();
#endif
#if HAL_I2C_ENABLE
	updateAppHwInitLowAccelSensErrorFlag();
	updateAppHwInitHighAccelSensErrorFlag();
#endif
}

//**************************   PUBLIC FUNCTION DEFINIITIONS   *****************

void InitAppHw(void){

	//Start AppHwTick
	//gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(HWTIMER_PERIOD), HW_TIMER, false);

#if HAL_SPI_ENABLE
	Init23lc1024();
#endif
#if HAL_I2C_ENABLE
	InitLsm6dsl();
	InitH3lis331dl();
#endif

	updateAppHwErrorFlags();
}
void AppHwTick(void){

	//static int secs = 0;
	//char str[10];
	counter++;

	if (counter%10 == 0){
		//secs++;
		//sprintf(str, "%i", secs);
	    //appUiWriteString(str);
		//KhsDataCharUpdate();
	  }

	//gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(HWTIMER_PERIOD), HW_TIMER, false);
}

uint8_t GetAppHwErrorFlags(void){
	return errorFlags;
}


