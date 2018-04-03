#include <stdbool.h>
#include "em_device.h"
#include "em_common.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_core.h"
#include "em_timer.h"

#include "mstimer.h"

#define MSTIMER_TIMER0 0
#define MSTIMER_TIMER1 1

#define MSTIMER_WTIMER0 10
#define MSTIMER_WTIMER1 11

#ifndef MSTIMER_TIMER
#define MSTIMER_TIMER MSTIMER_TIMER0
#endif

#if (MSTIMER_TIMER == MSTIMER_TIMER0) && (TIMER_COUNT >= 1)
  #define TIMER             TIMER0
  #define TIMER_CLK         cmuClock_TIMER0
  #define TIMER_IRQ         TIMER0_IRQn
  #define TIMER_IRQHandler  TIMER0_IRQHandler

#elif (MSTIMER_TIMER == MSTIMER_TIMER1) && (TIMER_COUNT >= 2)
  #define TIMER             TIMER1
  #define TIMER_CLK         cmuClock_TIMER1
  #define TIMER_IRQ         TIMER1_IRQn
  #define TIMER_IRQHandler  TIMER1_IRQHandler

#elif (MSTIMER_TIMER == MSTIMER_WTIMER0) && (WTIMER_COUNT >= 1)
  #define TIMER             WTIMER0
  #define TIMER_CLK         cmuClock_WTIMER0
  #define TIMER_IRQ         WTIMER0_IRQn
  #define TIMER_IRQHandler  WTIMER0_IRQHandler

#elif (MSTIMER_TIMER == MSTIMER_WTIMER1) && (WTIMER_COUNT >= 2)
  #define TIMER             WTIMER1
  #define TIMER_CLK         cmuClock_WTIMER1
  #define TIMER_IRQ         WTIMER1_IRQn
  #define TIMER_IRQHandler  WTIMER1_IRQHandler

#else
#error "Illegal MSTIMER TIMER selection"
#endif

// Use 16-bit TOP value for timer, independent of the width of the timer
#define MSTIMER_MAX   0xFFFF

static uint64_t msCounter = 0;

void TIMER_IRQHandler(void){
	if (TIMER_IntGet(TIMER) & TIMER_IF_CC0){
		CORE_ATOMIC_SECTION(
			TIMER_CompareSet(TIMER, 0, (TIMER_CounterGet(TIMER) + 75));
			TIMER_IntClear(TIMER, TIMER_IFC_CC0);
		)
		msCounter++;
	}
}

uint64_t GetMsCounter(void){
	return msCounter;
}

Ecode_t MSTIMER_Init(void){

	TIMER_Init_TypeDef timerInit     = TIMER_INIT_DEFAULT;
	TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;

	timerCCInit.mode = timerCCModeCompare;
	CMU_ClockEnable(TIMER_CLK, true);
	TIMER_TopSet(TIMER, MSTIMER_MAX);
	TIMER_InitCC(TIMER, 0, &timerCCInit);

	// CPU freq = 38 400 000
	// CPU freq with PRESC_DIV16 = 2 400 000
	// HFPerClk = 2 400 000
	// HFPerClk with PRESC_DIV32 = 75 000
	timerInit.prescale = (TIMER_Prescale_TypeDef)_TIMER_CTRL_PRESC_DIV512;

	TIMER_Init(TIMER, &timerInit);

	TIMER_IntDisable(TIMER, TIMER_IEN_CC0);
	NVIC_ClearPendingIRQ(TIMER_IRQ);
	NVIC_EnableIRQ(TIMER_IRQ);

	return ECODE_EMDRV_MSTIMER_OK;
}

Ecode_t StartMSTIMER(void){

  CORE_ATOMIC_SECTION(
	TIMER_CompareSet(TIMER, 0, (TIMER_CounterGet(TIMER) + 75));
    TIMER_IntClear(TIMER, TIMER_IFC_CC0);
    TIMER_IntEnable(TIMER, TIMER_IEN_CC0);
  )

  return ECODE_EMDRV_MSTIMER_OK;
}
