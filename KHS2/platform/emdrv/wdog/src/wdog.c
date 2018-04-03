#include "em_cmu.h"
#include "em_wdog.h"

#include "wdog.h"

void InitWdog(void){

  // Enabling clock to the interface of the low energy modules (including the Watchdog)
  CMU_ClockEnable(cmuClock_HFLE, true);

  // Watchdog Initialize settings
  WDOG_Init_TypeDef wdogInit = WDOG_INIT_DEFAULT;
  //wdogInit.debugRun = true;
  //wdogInit.em2Run = true;
  //wdogInit.em3Run = true;
  //wdogInit.em4Block = true;
  wdogInit.swoscBlock = true;
  wdogInit.lock = true;
  wdogInit.perSel = wdogPeriod_2k; // 2049 clock cycles of a 1kHz clock  ~2 seconds period

  // Initializing watchdog with chosen settings
  WDOG_Init(&wdogInit);
}

void LockWdog(void){
	WDOG_Lock();
}

void FeedWdog(void){
	WDOG_Feed();
}



