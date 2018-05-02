/* standard headers */
#include <stdint.h>
#include <stdio.h>

/* Include feature header */
#include "boards.h"
#include "ble-configuration.h"
#include "board_features.h"

/* BG stack headers*/
#include "bg_types.h"
#include "native_gecko.h"
#include "infrastructure.h"

/* HAL configuration */
#include "hal-config.h"

#include "em_gpio.h"

/* application specific header files*/
#include <app_timer.h>

/* Own header */
#include "app_ui.h"

/** UI Timer periodical call frequency in ms. */
#define APP_UITIMER_PERIOD            100
#define APP_RC_DISCHARGE_PERIOD       2

//**************************   FUNCTION DECLARATIONS   ************************

void appUiInit(uint16_t devId){

  /* Initialize buttons */
  /* Start repeating (auto-load) timer */
  gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(APP_UITIMER_PERIOD), UI_TIMER, false);
}

void appUiTick(void){
  gecko_cmd_hardware_set_soft_timer(TIMER_MS_2_TIMERTICK(APP_UITIMER_PERIOD), UI_TIMER, false);
}
