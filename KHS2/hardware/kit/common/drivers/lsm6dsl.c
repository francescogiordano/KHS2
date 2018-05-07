#include "lsm6dsl.h"

#include <stddef.h>

#include "i2cspm.h"
#include "em_cmu.h"

//**************************   STATIC VARIABLES   *****************************

static uint8_t commMode = 0;
static bool portSetupFlag = false;
static bool initializedFlag = false;
static I2C_TypeDef *i2cPort = 0;
static uint8_t i2cAddr = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static ReturnMsgLsm6dsl i2cWriteReadLsm6dsl(uint8_t command, uint8_t* data, uint8_t dataLength){
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_write_data[1];

	if(portSetupFlag){
		seq.addr  = i2cAddr;
		seq.flags = I2C_FLAG_WRITE_READ;

		// Select command to issue
		i2c_write_data[0] = command;
		seq.buf[0].data   = i2c_write_data;
		seq.buf[0].len    = 1;

		// Select location/length of data to be read
		seq.buf[1].data = data;
		seq.buf[1].len  = dataLength;

		ret = I2CSPM_Transfer(i2cPort, &seq);

		if (ret != i2cTransferDone) {
			*data = 0;
			msg = MsgLsm6dslFailure;
		}
	}
	else{
		msg = MsgLsm6dslCommPortNotSetup;
	}

	return msg;
}
static ReturnMsgLsm6dsl i2cWriteLsm6dsl(uint8_t command, uint8_t data){
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	if(portSetupFlag){
		I2C_TransferSeq_TypeDef    seq;
		I2C_TransferReturn_TypeDef ret;
		uint8_t                    i2c_write_data[2];

		seq.addr  = i2cAddr;
		seq.flags = I2C_FLAG_WRITE;
		/* Select command to issue */
		i2c_write_data[0] = command;
		i2c_write_data[1] = data;
		seq.buf[0].data   = i2c_write_data;
		seq.buf[0].len    = 2;

		ret = I2CSPM_Transfer(i2cPort, &seq);

		if (ret != i2cTransferDone){
			msg = MsgLsm6dslFailure;
		}
	}
	else{
		msg = MsgLsm6dslCommPortNotSetup;
	}
	return msg;
}


//**************************   PUBLIC FUNCTION DEFINIITIONS   *****************

void SetI2CLsm6dsl(void){
	commMode = LSM6DSL_COMM_MODE_I2C;

	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(LSM6DSL_I2C_CLK, true);

	init.refFreq = 0;	// Use currently configured reference clock
	init.freq = LSM6DSL_FREQUENCY;
	init.clhr = i2cClockHLRStandard;

	i2cPort = LSM6DSL_I2C_PORT;
	i2cAddr = LSM6DSL_DEVICE_ADDR;

	I2C_Init(LSM6DSL_I2C_PORT, &init);

	// IO config
	// Output value must be set to 1 to not drive lines low.
	// Set SCL first, to ensure it is high before changing SDA.
	GPIO_PinModeSet(LSM6DSL_SCL_PORT, LSM6DSL_SCL_PIN, gpioModeWiredAndPullUp, 1);
	GPIO_PinModeSet(LSM6DSL_SDA_PORT, LSM6DSL_SDA_PIN, gpioModeWiredAndPullUp, 1);


	/* In some situations, after a reset during an I2C transfer, the slave
	 device may be left in an unknown state. Send 9 clock pulses to
	 set slave in a defined state. */

	int i;
	for(i = 0; i < 9; i++){
		GPIO_PinOutSet(LSM6DSL_SCL_PORT, LSM6DSL_SCL_PIN);
		GPIO_PinOutClear(LSM6DSL_SCL_PORT, LSM6DSL_SCL_PIN);
	}

	LSM6DSL_I2C_PORT->ROUTEPEN  = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	LSM6DSL_I2C_PORT->ROUTELOC0 = (LSM6DSL_SDA_LOC << _I2C_ROUTELOC0_SDALOC_SHIFT) | (LSM6DSL_SCL_LOC << _I2C_ROUTELOC0_SCLLOC_SHIFT);

	portSetupFlag = true;
}

ReturnMsgLsm6dsl InitLsm6dsl(void) {
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	//Reset Device
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL3_C, LSM6DSL_SW_RESET) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Enable LPF1 For Gyro
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL4_C, LSM6DSL_LPF1_SEL_G) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Set Normal/Low Power Mode Gyroscope
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL7_G, LSM6DSL_G_HM_MODE_DISABLE) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Set 208Hz Gyroscope & Set To Scale 1000dps - 35 mdps/LSB
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL2_G, LSM6DSL_ODR_G_208HZ | LSM6DSL_FS_G_1000DPS) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Set Normal/Low Power Mode Gyroscope & Set LPF1 Value For Gyro
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL6_C, LSM6DSL_XL_HM_MODE_DISABLE | LSM6DSL_FTYPE_3) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Set 208Hz Accelerometer & Set To 4G Scale - .122 mg/LSB - Normal/Low power mode noise 2.0 mg
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL1_XL, LSM6DSL_ODR_XL_208HZ | LSM6DSL_FS_XL_4G | LSM6DSL_LPF1_BW_SEL) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Linear acceleration LPF ODR/50
	if(i2cWriteLsm6dsl(LSM6DSL_CTRL8_XL, LSM6DSL_LPF2_XL_EN | LSM6DSL_HPCF_XL_0 | LSM6DSL_INPUT_COMPOSITE) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}

	//Interrupt Configuration
	/*
	//Enable Gyroscope & Accelerometer Data Ready Interrupts
	if(i2cWriteLsm6dsl(LSM6DSL_INT1_CTRL, INT1_DRDY_G | INT1_DRDY_XL) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}
	*/

	//Enable Fifo In Continuous Modes
	if(i2cWriteLsm6dsl(LSM6DSL_FIFO_CTRL_5, LSM6DSL_ODR_FIFO_208HZ | LSM6DSL_FIFO_MODE_CONTINOUS) != MsgLsm6dslSuccess) {
		msg = MsgLsm6dslFailure;
	}


	if(msg == MsgLsm6dslFailure) {
	#if DEBUG_ENABLE
		RETARGET_WriteString("Init Fail", 9);
	#endif
	}
	else{
		initializedFlag = true;
	}

	return msg;
}
ReturnMsgLsm6dsl DetectLsm6dsl(void){
	ReturnMsgLsm6dsl msg = MsgLsm6dslNotDetected;

	uint8_t i2c_read_data[1];

	if(i2cWriteReadLsm6dsl(LSM6DSL_WHO_AM_I, i2c_read_data, 1) != MsgLsm6dslSuccess){
		msg = MsgLsm6dslFailure;
	}
	else {
		if(i2c_read_data[0] == LSM6DSL_WHO_AM_I_VALUE){
			msg = MsgLsm6dslSuccess;
		}
	}
	return msg;
}

ReturnMsgLsm6dsl GetAccelGyroDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	if(initializedFlag == true){
		if(i2cWriteReadLsm6dsl(LSM6DSL_OUTX_L_G, data, 12) != MsgLsm6dslSuccess){
			msg = MsgLsm6dslFailure;
		}
	}
	else{
		msg = MsgLsm6dslNotInitialized;
	}
	return msg;
}

ReturnMsgLsm6dsl GetAccelDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	if(initializedFlag == true){
		if(i2cWriteReadLsm6dsl(LSM6DSL_OUTX_L_XL, data, 6) != MsgLsm6dslSuccess){
			msg = MsgLsm6dslFailure;
		}
	}
	else{
		msg = MsgLsm6dslNotInitialized;
	}
	return msg;
}
ReturnMsgLsm6dsl GetGyroDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	if(initializedFlag == true){
		if(i2cWriteReadLsm6dsl(LSM6DSL_OUTX_L_G, data, 6) != MsgLsm6dslSuccess){
			msg = MsgLsm6dslFailure;
		}
	}
	else{
		msg = MsgLsm6dslNotInitialized;
	}
	return msg;
}
ReturnMsgLsm6dsl GetTempDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = MsgLsm6dslSuccess;

	if(initializedFlag == true){
		if(i2cWriteReadLsm6dsl(LSM6DSL_OUT_TEMP_L, data, 2) != MsgLsm6dslSuccess){
			msg = MsgLsm6dslFailure;
		}
	}
	else{
		msg = MsgLsm6dslNotInitialized;
	}
	return msg;
}
