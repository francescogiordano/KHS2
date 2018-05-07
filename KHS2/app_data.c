#include "native_gecko.h"
#include "letimer.h"
#include "gpiointerrupt.h"

#include "app_extsignals.h"
#include "payloadbuffer.h"
#include "lsm6dsl.h"
#include "halconfig_lsm6dsl.h"
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

static void lowAccelGyroAppDataInterrupt(uint8_t pin){

	gecko_external_signal(APP_DATA_LOW_ACCEL_GYRO);

	//Test
	//LowAccelGyroAppDataProcessRead();
}
static void highAccelAppDataInterrupt(uint8_t pin){
	if(indexHighAccel == 0){
		timeStampHighAccel = GetLeCounter();
	}
	gecko_external_signal(APP_DATA_HIGH_ACCEL);

	//Test
	//HighAccelGyroAppDataProcessRead();
}

//**************************   FUNCTION DEFINITIONS   *************************

void InitAppData(void){

#if HAL_I2C_ENABLE

#if DEBUG_ENABLE
	RETARGET_WriteString("Data Init", 9);
#endif

	//Enable Sensor Interrupts
	/*
	GPIO_PinModeSet(LSM6DSL_INT_1_PORT, LSM6DSL_INT_1_PIN, gpioModeInput, 0);
	GPIO_IntConfig(LSM6DSL_INT_1_PORT, LSM6DSL_INT_1_PIN, true, false, true);

	GPIO_PinModeSet(H3LIS331DL_INT_2_PORT, H3LIS331DL_INT_2_PIN, gpioModeInput, 0);
	GPIO_IntConfig(H3LIS331DL_INT_2_PORT, H3LIS331DL_INT_2_PIN, true, false, true);

	//GPIOINT_CallbackRegister(BSP_LSM6DSL_INT_1_PIN, lowAccelGyroAppDataInterrupt);
	//GPIOINT_CallbackRegister(H3LIS331DL_INT_PIN, highAccelAppDataInterrupt);
	GPIOINT_Init();
	*/
#endif

}

void LowAccelGyroAppDataProcessRead(void){

	uint8_t tempData[APP_DATA_LENGTH_LOW_ACCEL_GYRO];

	//Beginning of buffer - Load Data Type, Time Stamp
	if(indexLowAccelGyro == 0){
		timeStampLowAccelGyro = GetLeCounter();

		lowAccelGyroBuffer[0] = APP_DATA_TYPE_LOW_ACCEL_GYRO;
		lowAccelGyroBuffer[1] = timeStampLowAccelGyro >> 24;
		lowAccelGyroBuffer[2] = timeStampLowAccelGyro >> 16;
		lowAccelGyroBuffer[3] = timeStampLowAccelGyro >> 8;
		lowAccelGyroBuffer[4] = timeStampLowAccelGyro;

		indexLowAccelGyro = APP_DATA_LENGTH_BLE_HEADER;
	}

	GetAccelGyroDataLsm6dsl(tempData);	//tempData Data Order - GX_L,GX_H,GY_L,GY_H,GZ_L,GZ_H,XX_L,XX_H,XY_L,XY_H,XZ_L,XZ_H

	//Middle of buffer - Load & Rearrange Data - GX_H,GX_L,GYH_GY_L,etc
	lowAccelGyroBuffer[indexLowAccelGyro + 0] = tempData[1];
	lowAccelGyroBuffer[indexLowAccelGyro + 1] = tempData[0];
	lowAccelGyroBuffer[indexLowAccelGyro + 2] = tempData[3];
	lowAccelGyroBuffer[indexLowAccelGyro + 3] = tempData[2];
	lowAccelGyroBuffer[indexLowAccelGyro + 4] = tempData[5];
	lowAccelGyroBuffer[indexLowAccelGyro + 5] = tempData[4];
	lowAccelGyroBuffer[indexLowAccelGyro + 6] = tempData[7];
	lowAccelGyroBuffer[indexLowAccelGyro + 7] = tempData[6];
	lowAccelGyroBuffer[indexLowAccelGyro + 8] = tempData[9];
	lowAccelGyroBuffer[indexLowAccelGyro + 9] = tempData[8];
	lowAccelGyroBuffer[indexLowAccelGyro + 10] = tempData[11];
	lowAccelGyroBuffer[indexLowAccelGyro + 11] = tempData[10];

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
	if(indexHighAccel == 0){
		timeStampHighAccel = GetLeCounter();

		highAccelBuffer[0] = APP_DATA_TYPE_HIGH_ACCEL;
		highAccelBuffer[1] = timeStampHighAccel >> 24;
		highAccelBuffer[2] = timeStampHighAccel >> 16;
		highAccelBuffer[3] = timeStampHighAccel >> 8;
		highAccelBuffer[4] = timeStampHighAccel;

		indexHighAccel = APP_DATA_LENGTH_BLE_HEADER;
	}

	GetAccelDataH3lis331dl(tempData);	//tempData Data Order - X_L,X_H,Y_L,Y_H,Z_L,Z_H

	//Middle of buffer - Load & Rearrange Data - X_H,X_L,Y_H,Y_L,etc
	highAccelBuffer[indexHighAccel + 0] = tempData[1];
	highAccelBuffer[indexHighAccel + 1] = tempData[0];
	highAccelBuffer[indexHighAccel + 2] = tempData[3];
	highAccelBuffer[indexHighAccel + 3] = tempData[2];
	highAccelBuffer[indexHighAccel + 4] = tempData[5];
	highAccelBuffer[indexHighAccel + 5] = tempData[4];

	indexHighAccel += APP_DATA_LENGTH_HIGH_ACCEL;

	//End of buffer - Place buffer in memory, reset buffer
	if(indexHighAccel > APP_DATA_LENGTH_BLE_MAX - APP_DATA_LENGTH_HIGH_ACCEL){
		PutPayloadBuffer(highAccelBuffer, APP_DATA_LENGTH_BLE_MAX, putPayloadCounterHighAccel);
		putPayloadCounterHighAccel++;
		indexHighAccel = 0;
	}
}


