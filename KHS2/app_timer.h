#ifndef APP_TIMER_H
#define APP_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

//*****************   Public Macros and Definitions   *************************

// Timer Frequency used
#define TIMER_CLK_FREQ ((uint32)32768)
// Convert msec to timer ticks
#define TIMER_MS_2_TIMERTICK(ms) ((TIMER_CLK_FREQ * ms) / 1000)
// Stop timer
#define TIMER_STOP 0

// Timer periodical call frequency in ms
#define HWTIMER_PERIOD           	 				10000
#define KHS_DATA_CHAR_UPDATE_TIMER_PERIOD			100
#define SHUTDOWN_TIMER_PERIOD						2000


// Application timer enumeration
typedef enum {
  /** Advertisement timer.
   *  This is a single-shot timer used to wait some time with advertisement stopped until changes
   *  are registered in stack and we can advertise again with a different user defined advertising
   *  message. */
  ADV_TIMER = 0,
  HW_TIMER,
  KHS_DATA_CHAR_UPDATE_TIMER,
  SHUTDOWN_TIMER
} appTimer_t;

#endif // APP_TIMER_H
