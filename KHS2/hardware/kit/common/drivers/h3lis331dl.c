#include "h3lis331dl.h"

#include <stddef.h>

#include "i2cspm.h"
#include "em_cmu.h"


//*******************************   DEFINES   ***********************************

// H3lis331dl Read Temperature Command
#define H3LIS331DL_READ_TEMP       0xE0  // Read previous T data from RH measurement command
// H3lis331dl Read RH Command
#define H3LIS331DL_READ_RH         0xE5  // Perform RH (and T) measurement.
// H3lis331dl Read RH (no hold) Command
#define H3LIS331DL_READ_RH_NH      0xF5  // Perform RH (and T) measurement in no hold mode.
// H3lis331dl Read Thermistor Command
#define H3LIS331DL_READ_VIN        0xEE  // Perform thermistor measurement.
// H3lis331dl Read ID
#define H3LIS331DL_READ_ID1_1      0xFA
#define H3LIS331DL_READ_ID1_2      0x0F
#define H3LIS331DL_READ_ID2_1      0xFC
#define H3LIS331DL_READ_ID2_2      0xC9
// H3lis331dl Read Firmware Revision
#define H3LIS331DL_READ_FWREV_1    0x84
#define H3LIS331DL_READ_FWREV_2    0xB8

//**************************   STATIC VARIABLES   ******************************

static uint8_t commMode = 0;
static bool portSetupFlag = false;
static bool initializedFlag = false;
static I2C_TypeDef *i2cPort = 0;
static uint8_t i2cAddr = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static ReturnMsgH3lis331dl i2cWriteReadH3lis331dl(uint8_t command, uint8_t *data, uint16_t dataLength){
	ReturnMsgH3lis331dl msg = H3lis331dlSuccess;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_read_data[2];
	uint8_t                    i2c_write_data[1];

	if(commMode == H3LIS331DL_COMM_MODE_I2C){
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
			msg = H3lis331dlFailure;
		}
	}
	else{
		msg = H3lis331dlCommModeNotSetup;
	}

	return msg;
}
static ReturnMsgH3lis331dl i2cReadH3lis331dl (uint32_t *data){
	ReturnMsgH3lis331dl msg = H3lis331dlSuccess;

	if(commMode == H3LIS331DL_COMM_MODE_I2C){
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
			msg = H3lis331dlFailure;
		}

		*data = ((uint32_t) i2c_read_data[0] << 8) + (i2c_read_data[1] & 0xfc);
	}
	else{
		msg = H3lis331dlCommModeNotSetup;
	}

	return msg;
}
static ReturnMsgH3lis331dl i2cWriteH3lis331dl(uint8_t command){
	ReturnMsgH3lis331dl msg = H3lis331dlSuccess;

	if(commMode == H3LIS331DL_COMM_MODE_I2C){
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
			msg = H3lis331dlFailure;
		}
	}
	else{
		msg = H3lis331dlCommModeNotSetup;
	}

	return msg;
}

static int32_t h3lis331dl_Measure(I2C_TypeDef *i2c, uint8_t addr, uint32_t *data, uint8_t command){
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_read_data[2];
  uint8_t                    i2c_write_data[1];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_WRITE_READ;
  /* Select command to issue */
  i2c_write_data[0] = command;
  seq.buf[0].data   = i2c_write_data;
  seq.buf[0].len    = 1;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 2;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    *data = 0;
    return((int) ret);
  }

  *data = ((uint32_t) i2c_read_data[0] << 8) + (i2c_read_data[1] & 0xfc);

  return((int) 2);
}
static int32_t h3lis331dl_StartNoHoldMeasure(I2C_TypeDef *i2c, uint8_t addr, uint8_t command){
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_read_data[2];
  uint8_t                    i2c_write_data[1];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_WRITE;
  /* Select command to issue */
  i2c_write_data[0] = command;
  seq.buf[0].data   = i2c_write_data;
  seq.buf[0].len    = 1;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 0;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    return((int) ret);
  }

  return((int) 0);
}
static int32_t h3lis331dl_ReadNoHoldData(I2C_TypeDef *i2c, uint8_t addr, uint32_t *data)
{
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_read_data[2];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_READ;
  /* Select command to issue */
  seq.buf[0].data = i2c_read_data;
  seq.buf[0].len  = 2;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 2;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    *data = 0;
    return((int) ret);
  }

  *data = ((uint32_t) i2c_read_data[0] << 8) + (i2c_read_data[1] & 0xfc);

  return((int) 2);
}
static int32_t h3lis331dl_WriteUserReg2(I2C_TypeDef *i2c, uint8_t addr, int8_t data){

	I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_read_data[2];
  uint8_t                    i2c_write_data[2];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_WRITE;
  /* Select command to issue */
  i2c_write_data[0] = 0x50;
  i2c_write_data[1] = data;
  seq.buf[0].data   = i2c_write_data;
  seq.buf[0].len    = 2;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 0;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    return((int) ret);
  }

  return((int) 0);
}

//**************************   FUNCTION DEFINIITIONS   *****************

void SetI2CH3lis331dl(void){
	commMode = H3LIS331DL_COMM_MODE_I2C;

	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(H3LIS331DL_I2C_CLK, true);

	init.refFreq = 0;	// Use currently configured reference clock
	init.freq = H3LIS331DL_FREQUENCY;
	init.clhr = i2cClockHLRStandard;

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
	ReturnMsgH3lis331dl msg = H3lis331dlSuccess;

	if(commMode == H3LIS331DL_COMM_MODE_SPI){

	}
	else if(commMode == H3LIS331DL_COMM_MODE_I2C){
		//H3lis331dlFailure;

		I2C_TransferSeq_TypeDef    seq;
		I2C_TransferReturn_TypeDef ret;
		uint8_t                    i2c_read_data[8];
		uint8_t                    i2c_write_data[2];

		seq.addr  = i2cAddr;
		seq.flags = I2C_FLAG_WRITE_READ;
		/* Select command to issue */
		i2c_write_data[0] = H3LIS331DL_READ_ID2_1;
		i2c_write_data[1] = H3LIS331DL_READ_ID2_2;
		seq.buf[0].data   = i2c_write_data;
		seq.buf[0].len    = 2;
		/* Select location/length of data to be read */
		seq.buf[1].data = i2c_read_data;
		seq.buf[1].len  = 8;

		ret = I2CSPM_Transfer(i2cPort, &seq);

		if (ret != i2cTransferDone) {
			msg = H3lis331dlFailure;
		}
		/*
		else if (NULL != deviceId) {
			*deviceId = i2c_read_data[0];
		}
		*/
	}
	else{
		msg = H3lis331dlCommModeNotSetup;
	}

	return msg;
}
ReturnMsgH3lis331dl InitH3lis331dl(void) {
	ReturnMsgH3lis331dl msg = H3lis331dlSuccess;

	if(commMode == H3LIS331DL_COMM_MODE_SPI){
		/*
		uint8_t tx_data[2];
		uint8_t	rx_data[2];

		uint32_t temp = 0;

		serialType = type;
		lsm6dslSpiCsPin = spiCsPin;

		//Reset Device
		tx_data[0] = (H3LIS331DL_CTRL3_C | SPI_WRITE_DATA);
		tx_data[1] = H3LIS331DL_SW_RESET;
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)){		//Check if SPI communication
			errorFlag = 1;
		}
		delay_ms(5);

		tx_data[0] = (H3LIS331DL_WHO_AM_I | SPI_READ_DATA);
		tx_data[1] = 0x00;
		if(rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)){		//Check if SPI communication
			errorFlag = 1;
		}
		if (rx_data[1] != H3LIS331DL_WHO_AM_I_VALUE) {		//Check if SPI Chip Valid
			errorFlag = 1;								//value = 0x00;

			temp = rx_data[1];
			printUSART0("H3LIS331DL_WHO_AM_I FAIL: [%h]\n", &temp);
		}

		//Enable LPF1 For Gyro
		tx_data[0] = (H3LIS331DL_CTRL4_C | SPI_WRITE_DATA);
		tx_data[1] = H3LIS331DL_LPF1_SEL_G;
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set Normal/Low Power Mode Gyroscope
		tx_data[0] = (H3LIS331DL_CTRL7_G | SPI_WRITE_DATA);
		tx_data[1] = (H3LIS331DL_G_HM_MODE_DISABLE);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set 416Hz Gyroscope & Set To Scale 1000dps - 35 mdps/LSB
		tx_data[0] = (H3LIS331DL_CTRL2_G | SPI_WRITE_DATA);
		tx_data[1] = (H3LIS331DL_ODR_G_416HZ | H3LIS331DL_FS_G_1000DPS);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set Normal/Low Power Mode Gyroscope & Set LPF1 Value For Gyro
		tx_data[0] = (H3LIS331DL_CTRL6_C | SPI_WRITE_DATA);
		tx_data[1] = (H3LIS331DL_XL_HM_MODE_DISABLE | H3LIS331DL_FTYPE_3);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set 416Hz Accelerometer & Set To 4G Scale - .122 mg/LSB - Normal/Low power mode noise 2.0 mg
		tx_data[0] = (H3LIS331DL_CTRL1_XL | SPI_WRITE_DATA);
		//tx_data[1] = (H3LIS331DL_ODR_XL_12HZ | H3LIS331DL_FS_XL_2G);
		tx_data[1] = (H3LIS331DL_ODR_XL_416HZ | H3LIS331DL_FS_XL_4G | H3LIS331DL_LPF1_BW_SEL);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Linear acceleration LPF ODR/50
		tx_data[0] = (H3LIS331DL_CTRL8_XL | SPI_WRITE_DATA);
		tx_data[1] = (H3LIS331DL_LPF2_XL_EN | H3LIS331DL_HPCF_XL_0 | H3LIS331DL_INPUT_COMPOSITE);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}
		*/
	}
	else if(commMode == H3LIS331DL_COMM_MODE_I2C){
		if(DetectH3lis331dl() == H3lis331dlSuccess){

			initializedFlag = 1;
		}
		else{
			msg = H3lis331dlNotInitialized;
		}
	}
	else {
		msg = H3lis331dlCommModeNotSetup;
	}

	return msg;
}

ReturnMsgH3lis331dl GetAccelDataH3lis331dl(uint8_t* data){
	ReturnMsgH3lis331dl msg = H3lis331dlSuccess;

	if(initializedFlag == true){
		if(commMode == H3LIS331DL_COMM_MODE_SPI){

		}
		else if(commMode == H3LIS331DL_COMM_MODE_I2C){
			msg = i2cReadH3lis331dl(data);
		}
		else{
			msg = H3lis331dlCommModeNotSetup;
		}
	}
	else{
		msg = H3lis331dlNotInitialized;
	}
	return msg;
}
