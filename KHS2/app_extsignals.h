#ifndef APP_EXTSIGNALS_H
#define APP_EXTSIGNALS_H

#ifdef __cplusplus
extern "C" {
#endif

//*******************************   ENUMS   ***********************************

typedef enum {
	//32 BitMask
	APP_DATA_1_MS_TIMER		= 0x0001,
	APP_DATA_LOW_ACCEL_GYRO = 0x0002,
	APP_DATA_HIGH_ACCEL		= 0x0004
	//						= 0x0008
	//						= 0x0010
	//						= 0x0020
} extSignals_t;

#endif //APP_EXTSIGNALS_H
