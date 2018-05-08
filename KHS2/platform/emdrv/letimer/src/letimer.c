#include "em_core.h"
#include "em_cmu.h"
#include "em_letimer.h"
#include "letimer.h"
#include "native_gecko.h"
#include "app_extsignals.h"

#ifndef LETIMER_TIMER
#define LETIMER_TIMER LETIMER_TIMER0
#endif

#if (LETIMER_TIMER == LETIMER_TIMER0) && (LETIMER_COUNT >= 1)
  #define LETIMER             LETIMER0
  #define LETIMER_CLK         cmuClock_LETIMER0
  #define LETIMER_IRQ         LETIMER0_IRQn
  #define LETIMER_IRQHandler  LETIMER0_IRQHandler
#endif

#define LETIMER_MAX   0xFFFF

static uint64_t leCounter = 0;

void LETIMER_IRQHandler(void){

	//LFACLK = 32 768
	if (LETIMER_IntGet(LETIMER) & LETIMER_IF_COMP0){
		CORE_ATOMIC_SECTION(
			LETIMER_CompareSet(LETIMER, 0, (LETIMER_CounterGet(LETIMER) - 32));
			LETIMER_IntClear(LETIMER, LETIMER_IFC_COMP0);
		)
		leCounter++;

		gecko_external_signal(APP_DATA_1_MS_TIMER);
	}
}

Ecode_t InitLeTimer(void){

	LETIMER_Init_TypeDef leTimerInit = LETIMER_INIT_DEFAULT;

	CMU_ClockEnable(LETIMER_CLK, true);
	LETIMER_Init(LETIMER, &leTimerInit);

	LETIMER_IntDisable(LETIMER, LETIMER_IEN_COMP0);
	NVIC_ClearPendingIRQ(LETIMER_IRQ);
	NVIC_EnableIRQ(LETIMER_IRQ);

	return ECODE_EMDRV_LETIMER_OK;
}
Ecode_t StartLeTimer(void){

  CORE_ATOMIC_SECTION(
	LETIMER_CompareSet(LETIMER, 0, (LETIMER_CounterGet(LETIMER) - 32));
    LETIMER_IntClear(LETIMER, LETIMER_IFC_COMP0);
    LETIMER_IntEnable(LETIMER, LETIMER_IEN_COMP0);
  )

  return ECODE_EMDRV_LETIMER_OK;
}
uint64_t GetLeCounter(void){
	return leCounter;
}
