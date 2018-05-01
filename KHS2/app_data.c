#include "native_gecko.h"
#include "letimer.h"
#include "gpiointerrupt.h"

#include "app_extsignals.h"
#include "payloadbuffer.h"
#include "lsm6dsl.h"
#include "h3lis331dl.h"
#include "app_data.h"


//**************************   DEFINES   **************************************

#define APP_DATA_TYPE_LOW_ACCEL_GYRO		1
#define APP_DATA_TYPE_HIGH_ACCEL			2

#define APP_DATA_LENGTH_BLE_MAX				251
#define APP_DATA_LENGTH_BLE_HEADER			5
#define APP_DATA_LENGTH_LOW_ACCEL_GYRO		12
#define APP_DATA_LENGTH_HIGH_ACCEL			6

static uint8_t 	lowAccelGyroBuffer[APP_DATA_LENGTH_BLE_MAX];
static uint8_t 	indexLowAccelGyro = 0;
static uint64_t timeStampLowAccelGyro;
static uint16_t putPayloadCounterLowAccelGyro = 0;
static uint16_t getPayloadCounterLowAccelGyro = 0;

static uint8_t 	highAccelBuffer[APP_DATA_LENGTH_BLE_MAX];
static uint8_t 	indexHighAccel = 0;
static uint64_t timeStampHighAccel;
static uint16_t putPayloadCounterHighAccel = 0;
static uint16_t getPayloadCounterHighAccel = 0;

//**************************   STATIC FUNCTION DEFINITIONS   ******************

static void lowAccelGyroAppDataInterrupt(uint8_t gpioPinNo){
	if(indexLowAccelGyro == 0){
		timeStampLowAccelGyro = GetLeCounter();
	}
	gecko_external_signal(APP_DATA_LOW_ACCEL_GYRO);
}
static void highAccelAppDataInterrupt(uint8_t gpioPinNo){
	if(indexHighAccel == 0){
		timeStampHighAccel = GetLeCounter();
	}
	gecko_external_signal(APP_DATA_HIGH_ACCEL);
}

//**************************   FUNCTION DEFINITIONS   *************************

void InitAppData(void){

#if HAL_I2C_ENABLE
	GPIOINT_CallbackRegister(LSM6DSL_INT_1_PIN, lowAccelGyroAppDataInterrupt);
	GPIOINT_CallbackRegister(H3LIS331DL_INT_PIN, highAccelAppDataInterrupt);
#endif

}

void LowAccelGyroAppDataProcessRead(void){

	uint8_t tempData[APP_DATA_LENGTH_LOW_ACCEL_GYRO];

	//Beginning of buffer - Load Data Type, Time Stamp
	if(indexLowAccelGyro == 0){
		lowAccelGyroBuffer[0] = APP_DATA_TYPE_LOW_ACCEL_GYRO;
		lowAccelGyroBuffer[1] = timeStampLowAccelGyro >> 24;
		lowAccelGyroBuffer[2] = timeStampLowAccelGyro >> 16;
		lowAccelGyroBuffer[3] = timeStampLowAccelGyro >> 8;
		lowAccelGyroBuffer[4] = timeStampLowAccelGyro;

		indexLowAccelGyro = APP_DATA_LENGTH_BLE_HEADER;
	}

	GetAccelGyroDataLsm6dsl(tempData);

	//Middle of buffer - Load Data
	for(int i=0; i<APP_DATA_LENGTH_LOW_ACCEL_GYRO; i++){
		lowAccelGyroBuffer[indexLowAccelGyro + i] = tempData[i];
	}
	indexLowAccelGyro += APP_DATA_LENGTH_LOW_ACCEL_GYRO;

	//End of buffer - Place buffer in memory, reset buffer
	if(indexLowAccelGyro > APP_DATA_LENGTH_BLE_MAX - APP_DATA_LENGTH_LOW_ACCEL_GYRO){
		PutPayloadBuffer(lowAccelGyroBuffer, APP_DATA_LENGTH_BLE_MAX, putPayloadCounterLowAccelGyro);
		putPayloadCounterLowAccelGyro++;
		indexLowAccelGyro = 0;
	}
}
void HighAccelGyroAppDataProcessRead(void){

	uint8_t tempData[APP_DATA_LENGTH_HIGH_ACCEL];

	//Beginning of buffer - Load Data Type, Time Stamp
	if(indexLowAccelGyro == 0){
		highAccelBuffer[0] = APP_DATA_TYPE_HIGH_ACCEL;
		highAccelBuffer[1] = timeStampHighAccel >> 24;
		highAccelBuffer[2] = timeStampHighAccel >> 16;
		highAccelBuffer[3] = timeStampHighAccel >> 8;
		highAccelBuffer[4] = timeStampHighAccel;

		indexHighAccel = APP_DATA_LENGTH_BLE_HEADER;
	}

	GetAccelDataH3lis331dl(tempData);

	//Middle of buffer - Load Data
	for(int i=0; i<APP_DATA_LENGTH_HIGH_ACCEL; i++){
		highAccelBuffer[indexHighAccel + i] = tempData[i];
	}
	indexHighAccel += APP_DATA_LENGTH_HIGH_ACCEL;

	//End of buffer - Place buffer in memory, reset buffer
	if(indexHighAccel > APP_DATA_LENGTH_BLE_MAX - APP_DATA_LENGTH_HIGH_ACCEL){
		PutPayloadBuffer(highAccelBuffer, APP_DATA_LENGTH_BLE_MAX, putPayloadCounterHighAccel);
		putPayloadCounterHighAccel++;
		indexHighAccel = 0;
	}
}


