#include "h3lis331dl.h"

#include <stddef.h>

#include "i2cspm.h"
#include "em_cmu.h"


//*******************************   DEFINES   ***********************************

//**************************   STATIC VARIABLES   ******************************

static bool portSetupFlag = false;
static bool initializedFlag = false;
static I2C_TypeDef *i2cPortH3lis331dl = 0;
static uint8_t i2cAddrH3lis331dl = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static ReturnMsgH3lis331dl i2cWriteReadH3lis331dl(uint8_t command, uint8_t* data, uint8_t dataLength){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	I2C_TransferSeq_TypeDef    seq;
	static I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_write_data[1];

	if(portSetupFlag){
		seq.addr  = i2cAddrH3lis331dl;
		seq.flags = I2C_FLAG_WRITE_READ;

		/* Select command to issue */
		i2c_write_data[0] = command;
		seq.buf[0].data   = i2c_write_data;
		seq.buf[0].len    = 1;

		/* Select location/length of data to be read */
		seq.buf[1].data = data;
		seq.buf[1].len  = dataLength;

		ret = I2CSPM_Transfer(i2cPortH3lis331dl, &seq);

		if (ret != i2cTransferDone) {
			*data = 0;
			msg = MsgH3lis331dlFailure;
		}
	}
	else{
		msg = MsgH3lis331dlCommPortNotSetup;
	}

	return msg;
}
static ReturnMsgH3lis331dl i2cWriteH3lis331dl(uint8_t command, uint8_t data){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	if(portSetupFlag){
		I2C_TransferSeq_TypeDef    seq;
		I2C_TransferReturn_TypeDef ret;
		uint8_t                    i2c_write_data[2];

		seq.addr  = i2cAddrH3lis331dl;
		seq.flags = I2C_FLAG_WRITE;
		/* Select command to issue */
		i2c_write_data[0] = command;
		i2c_write_data[1] = data;
		seq.buf[0].data   = i2c_write_data;
		seq.buf[0].len    = 2;

		ret = I2CSPM_Transfer(i2cPortH3lis331dl, &seq);

		if (ret != i2cTransferDone){
			msg = MsgH3lis331dlFailure;
		}
	}
	else{
		msg = MsgH3lis331dlCommPortNotSetup;
	}
	return msg;
}


//**************************   FUNCTION DEFINIITIONS   *****************

void SetI2CH3lis331dl(void){

	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(H3LIS331DL_I2C_CLK, true);

	init.refFreq = 0;	// Use currently configured reference clock
	init.freq = H3LIS331DL_FREQUENCY;
	init.clhr = i2cClockHLRStandard;

	i2cPortH3lis331dl = H3LIS331DL_I2C_PORT;
	i2cAddrH3lis331dl = H3LIS331DL_DEVICE_ADDR;

	I2C_Init(H3LIS331DL_I2C_PORT, &init);

	// IO config
	// Output value must be set to 1 to not drive lines low.
	// Set SCL first, to ensure it is high before changing SDA.
	GPIO_PinModeSet(H3LIS331DL_SCL_PORT, H3LIS331DL_SCL_PIN, gpioModeWiredAndPullUp, 1);
	GPIO_PinModeSet(H3LIS331DL_SDA_PORT, H3LIS331DL_SDA_PIN, gpioModeWiredAndPullUp, 1);


	/* In some situations, after a reset during an I2C transfer, the slave
	 device may be left in an unknown state. Send 9 clock pulses to
	 set slave in a defined state. */

	int i;
	for(i = 0; i < 9; i++){
		GPIO_PinOutSet(H3LIS331DL_SCL_PORT, H3LIS331DL_SCL_PIN);
		GPIO_PinOutClear(H3LIS331DL_SCL_PORT, H3LIS331DL_SCL_PIN);
	}

	H3LIS331DL_I2C_PORT->ROUTEPEN  = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	H3LIS331DL_I2C_PORT->ROUTELOC0 = (H3LIS331DL_SDA_LOC << _I2C_ROUTELOC0_SDALOC_SHIFT) | (H3LIS331DL_SCL_LOC << _I2C_ROUTELOC0_SCLLOC_SHIFT);

	portSetupFlag = true;
}

ReturnMsgH3lis331dl InitH3lis331dl(void) {
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	//Reset All Memory
	if(i2cWriteH3lis331dl(H3LIS331DL_CTRL_REG2, H3LIS331DL_CTRL_REG2_BOOT) != MsgH3lis331dlSuccess) {
		msg = MsgH3lis331dlFailure;
	}

	//Set Normal Mode, ODR 1000Hz, Enable All axis
	if(i2cWriteH3lis331dl(H3LIS331DL_CTRL_REG1, H3LIS331DL_CTRL_REG1_PM1 | H3LIS331DL_CTRL_REG1_DR3 | H3LIS331DL_CTRL_REG1_ALLEN) != MsgH3lis331dlSuccess) {
		msg = MsgH3lis331dlFailure;
	}

	//Scale +-400g
	if(i2cWriteH3lis331dl(H3LIS331DL_CTRL_REG4, H3LIS331DL_CTRL_REG4_FS2) != MsgH3lis331dlSuccess) {
		msg = MsgH3lis331dlFailure;
	}

	//Interrupt Configuration
	/*
	//INT2 - Enable Interrupt High On All Axis
	if(i2cWriteH3lis331dl(H3LIS331DL_INT2_CFG, H3LIS331DL_INT2_CFG_ALLHIGHIE) != MsgH3lis331dlSuccess) {
		msg = MsgH3lis331dlFailure;
	}

	//INT2 - Threshold 20/256
	if(i2cWriteH3lis331dl(H3LIS331DL_INT2_THS, H3LIS331DL_INT2_THS_20) != MsgH3lis331dlSuccess) {
		msg = MsgH3lis331dlFailure;
	}

	//INT2 - Duration 5/256
	if(i2cWriteH3lis331dl(H3LIS331DL_INT2_DURATION, H3LIS331DL_INT2_DURATION_5) != MsgH3lis331dlSuccess) {
		msg = MsgH3lis331dlFailure;
	}
	*/

	if(msg == MsgH3lis331dlFailure) {
	#if DEBUG_ENABLE
		RETARGET_WriteString("Init Fail", 9);
	#endif
	}
	else{
		initializedFlag = true;
	}

	return msg;
}
ReturnMsgH3lis331dl DetectH3lis331dl(void){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlNotDetected;

	uint8_t i2c_read_data[1];

	if(i2cWriteReadH3lis331dl(H3LIS331DL_WHO_AM_I, i2c_read_data, 1) != MsgH3lis331dlSuccess){
		msg = MsgH3lis331dlFailure;
	}
	else {
		if(i2c_read_data[0] == H3LIS331DL_WHO_AM_I_VALUE){
			msg = MsgH3lis331dlSuccess;
		}
	}
	return msg;
}

ReturnMsgH3lis331dl GetAccelDataH3lis331dl(uint8_t* data){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	if(initializedFlag == true){
		if(i2cWriteReadH3lis331dl(H3LIS331DL_OUT_X_L_AUTO_INCREMENT, data, 6) != MsgH3lis331dlSuccess){
			msg = MsgH3lis331dlFailure;
		}
	}
	else{
		msg = MsgH3lis331dlNotInitialized;
	}
	return msg;
}
