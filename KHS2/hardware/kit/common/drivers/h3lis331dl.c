#include "h3lis331dl.h"

#include <stddef.h>

#include "i2cspm.h"
#include "em_cmu.h"


//*******************************   DEFINES   ***********************************

//**************************   STATIC VARIABLES   ******************************

static uint8_t commMode = 0;
static bool portSetupFlag = false;
static bool initializedFlag = false;
static I2C_TypeDef *i2cPort = 0;
static uint8_t i2cAddr = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static ReturnMsgH3lis331dl i2cWriteReadH3lis331dl(uint8_t command, uint8_t *data, uint16_t dataLength){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_read_data[2];
	uint8_t                    i2c_write_data[1];

	seq.addr  = i2cAddr;
	seq.flags = I2C_FLAG_WRITE_READ;

	/* Select command to issue */
	i2c_write_data[0] = command;
	seq.buf[0].data   = i2c_write_data;
	seq.buf[0].len    = 1;

	/* Select location/length of data to be read */
	seq.buf[1].data = data;
	seq.buf[1].len  = dataLength;

	ret = I2CSPM_Transfer(i2cPort, &seq);

	if (ret != i2cTransferDone) {
		*data = 0;
		msg = MsgH3lis331dlFailure;
	}

	return msg;
}
static ReturnMsgH3lis331dl i2cReadH3lis331dl (uint32_t *data){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_read_data[2];

	seq.addr  = i2cAddr;
	seq.flags = I2C_FLAG_READ;
	/* Select command to issue */
	seq.buf[0].data = i2c_read_data;
	seq.buf[0].len  = 2;
	/* Select location/length of data to be read */
	seq.buf[1].data = i2c_read_data;
	seq.buf[1].len  = 2;

	ret = I2CSPM_Transfer(i2cPort, &seq);

	if (ret != i2cTransferDone) {
		*data = 0;
		msg = MsgH3lis331dlFailure;
	}

	*data = ((uint32_t) i2c_read_data[0] << 8) + (i2c_read_data[1] & 0xfc);

	return msg;
}
static ReturnMsgH3lis331dl i2cWriteH3lis331dl(uint8_t command){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_read_data[2];
	uint8_t                    i2c_write_data[1];

	seq.addr  = i2cAddr;
	seq.flags = I2C_FLAG_WRITE;
	/* Select command to issue */
	i2c_write_data[0] = command;
	seq.buf[0].data   = i2c_write_data;
	seq.buf[0].len    = 1;
	/* Select location/length of data to be read */
	seq.buf[1].data = i2c_read_data;
	seq.buf[1].len  = 0;

	ret = I2CSPM_Transfer(i2cPort, &seq);

	if (ret != i2cTransferDone){
		msg = MsgH3lis331dlFailure;
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

	i2cPort = H3LIS331DL_I2C_PORT;
	i2cAddr = H3LIS331DL_DEVICE_ADDR;

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
}

ReturnMsgH3lis331dl DetectH3lis331dl(void){

	ReturnMsgH3lis331dl msg = MsgH3lis331dlNotDetected;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_write_data[1];
	uint8_t                    i2c_read_data[1];


	seq.addr  = i2cAddr;
	seq.flags = I2C_FLAG_WRITE_READ;
	// Select command to write
	i2c_write_data[0] = H3LIS331DL_WHO_AM_I;
	seq.buf[0].data   = i2c_write_data;
	seq.buf[0].len    = 1;
	// Select location of data to read
	seq.buf[1].data = i2c_read_data;
	seq.buf[1].len  = 1;

	ret = I2CSPM_Transfer(i2cPort, &seq);


	if (ret != i2cTransferDone) {
		msg = MsgH3lis331dlFailure;
	}
	else {
		if(seq.buf[1].data[0] == H3LIS331DL_WHO_AM_I_VALUE){
			msg = MsgH3lis331dlSuccess;
		}
	}
	return msg;
}
ReturnMsgH3lis331dl InitH3lis331dl(void) {
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	return msg;
}

ReturnMsgH3lis331dl GetAccelDataH3lis331dl(uint8_t* data){
	ReturnMsgH3lis331dl msg = MsgH3lis331dlSuccess;

	if(initializedFlag == true){
		msg = i2cReadH3lis331dl(data);
	}
	else{
		msg = MsgH3lis331dlNotInitialized;
	}
	return msg;
}
