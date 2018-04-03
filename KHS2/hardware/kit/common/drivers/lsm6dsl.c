#include "lsm6dsl.h"

#include <stddef.h>

#include "i2cspm.h"
#include "em_cmu.h"



//*******************************   DEFINES   ***********************************

// Lsm6dsl Read Temperature Command
#define LSM6DSL_READ_TEMP       0xE0  // Read previous T data from RH measurement command
// Lsm6dsl Read RH Command
#define LSM6DSL_READ_RH         0xE5  // Perform RH (and T) measurement.
// Lsm6dsl Read RH (no hold) Command
#define LSM6DSL_READ_RH_NH      0xF5  // Perform RH (and T) measurement in no hold mode.
// Lsm6dsl Read Thermistor Command
#define LSM6DSL_READ_VIN        0xEE  // Perform thermistor measurement.
// Lsm6dsl Read ID
#define LSM6DSL_READ_ID1_1      0xFA
#define LSM6DSL_READ_ID1_2      0x0F
#define LSM6DSL_READ_ID2_1      0xFC
#define LSM6DSL_READ_ID2_2      0xC9
// Lsm6dsl Read Firmware Revision
#define LSM6DSL_READ_FWREV_1    0x84
#define LSM6DSL_READ_FWREV_2    0xB8

//**************************   STATIC VARIABLES   *****************************

static uint8_t commMode = 0;
static bool portSetupFlag = false;
static bool initializedFlag = false;
static I2C_TypeDef *i2cPort = 0;
static uint8_t i2cAddr = 0;

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static ReturnMsgLsm6dsl i2cWriteReadLsm6dsl(uint8_t command, uint8_t *data, uint16_t dataLength){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	I2C_TransferSeq_TypeDef    seq;
	I2C_TransferReturn_TypeDef ret;
	uint8_t                    i2c_read_data[2];
	uint8_t                    i2c_write_data[1];

	if(portSetupFlag){
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
			msg = Lsm6dslFailure;
		}
	}
	else{
		msg = Lsm6dslCommPortNotSetup;
	}

	return msg;
}
static ReturnMsgLsm6dsl i2cReadLsm6dsl (uint32_t *data){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(portSetupFlag){
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
			msg = Lsm6dslFailure;
		}

		*data = ((uint32_t) i2c_read_data[0] << 8) + (i2c_read_data[1] & 0xfc);
	}
	else{
		msg = Lsm6dslCommPortNotSetup;
	}

	return msg;
}
static ReturnMsgLsm6dsl i2cWriteLsm6dsl(uint8_t command){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(portSetupFlag){
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
			msg = Lsm6dslFailure;
		}
	}
	else{
		msg = Lsm6dslCommPortNotSetup;
	}

	return msg;
}



/**************************************************************************//**
 * @brief
 *  Reads data from the Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use (not used).
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] data
 *   The data read from the sensor.
 * @param[in] command
 *   The command to send to device. See the \#define's for details.
 * @return
 *   Returns number of bytes read on success. Otherwise returns error codes
 *   based on the I2CDRV.
 *****************************************************************************/
static int32_t Lsm6dsl_Measure(I2C_TypeDef *i2c, uint8_t addr, uint32_t *data, uint8_t command){
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
  seq.buf[1].data 	= i2c_read_data;
  seq.buf[1].len  	= 2;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    *data = 0;
    return((int) ret);
  }

  *data = ((uint32_t) i2c_read_data[0] << 8) + (i2c_read_data[1] & 0xfc);

  return((int) 2);
}
/**************************************************************************//**
 * @brief
 *  Starts a no hold measurement in the Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use (not used).
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[in] command
 *   The command to send to device. See the \#define's for details.
 * @return
 *   Returns number of bytes read on success. Otherwise returns error codes
 *   based on the I2CDRV.
 *****************************************************************************/
static int32_t Lsm6dsl_StartNoHoldMeasure(I2C_TypeDef *i2c, uint8_t addr, uint8_t command){
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
/**************************************************************************//**
 * @brief
 *  Reads data from the Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use (not used).
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] data
 *   The data read from the sensor.
 * @return
 *   Returns number of bytes read on success. Otherwise returns error codes
 *   based on the I2CDRV.
 *****************************************************************************/
static int32_t Lsm6dsl_ReadNoHoldData(I2C_TypeDef *i2c, uint8_t addr, uint32_t *data)
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
static int32_t Lsm6dsl_WriteUserReg2(I2C_TypeDef *i2c, uint8_t addr, int8_t data){

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


//**************************   PUBLIC FUNCTION DEFINIITIONS   *****************

void SetI2CLsm6dsl(void){
	commMode = LSM6DSL_COMM_MODE_I2C;

	I2C_Init_TypeDef init = I2C_INIT_DEFAULT;

	CMU_ClockEnable(cmuClock_HFPER, true);
	CMU_ClockEnable(LSM6DSL_I2C_CLK, true);

	init.refFreq = 0;	// Use currently configured reference clock
	init.freq = LSM6DSL_FREQUENCY;
	init.clhr = i2cClockHLRStandard;

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
}

ReturnMsgLsm6dsl InitLsm6dsl(void) {
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(commMode == LSM6DSL_COMM_MODE_SPI){
		/*
		uint8_t tx_data[2];
		uint8_t	rx_data[2];

		uint32_t temp = 0;

		serialType = type;
		lsm6dslSpiCsPin = spiCsPin;

		//Reset Device
		tx_data[0] = (LSM6DSL_CTRL3_C | SPI_WRITE_DATA);
		tx_data[1] = LSM6DSL_SW_RESET;
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)){		//Check if SPI communication
			errorFlag = 1;
		}
		delay_ms(5);

		tx_data[0] = (LSM6DSL_WHO_AM_I | SPI_READ_DATA);
		tx_data[1] = 0x00;
		if(rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)){		//Check if SPI communication
			errorFlag = 1;
		}
		if (rx_data[1] != LSM6DSL_WHO_AM_I_VALUE) {		//Check if SPI Chip Valid
			errorFlag = 1;								//value = 0x00;

			temp = rx_data[1];
			printUSART0("LSM6DSL_WHO_AM_I FAIL: [%h]\n", &temp);
		}

		//Enable LPF1 For Gyro
		tx_data[0] = (LSM6DSL_CTRL4_C | SPI_WRITE_DATA);
		tx_data[1] = LSM6DSL_LPF1_SEL_G;
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set Normal/Low Power Mode Gyroscope
		tx_data[0] = (LSM6DSL_CTRL7_G | SPI_WRITE_DATA);
		tx_data[1] = (LSM6DSL_G_HM_MODE_DISABLE);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set 416Hz Gyroscope & Set To Scale 1000dps - 35 mdps/LSB
		tx_data[0] = (LSM6DSL_CTRL2_G | SPI_WRITE_DATA);
		tx_data[1] = (LSM6DSL_ODR_G_416HZ | LSM6DSL_FS_G_1000DPS);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set Normal/Low Power Mode Gyroscope & Set LPF1 Value For Gyro
		tx_data[0] = (LSM6DSL_CTRL6_C | SPI_WRITE_DATA);
		tx_data[1] = (LSM6DSL_XL_HM_MODE_DISABLE | LSM6DSL_FTYPE_3);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Set 416Hz Accelerometer & Set To 4G Scale - .122 mg/LSB - Normal/Low power mode noise 2.0 mg
		tx_data[0] = (LSM6DSL_CTRL1_XL | SPI_WRITE_DATA);
		//tx_data[1] = (LSM6DSL_ODR_XL_12HZ | LSM6DSL_FS_XL_2G);
		tx_data[1] = (LSM6DSL_ODR_XL_416HZ | LSM6DSL_FS_XL_4G | LSM6DSL_LPF1_BW_SEL);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}

		//Linear acceleration LPF ODR/50
		tx_data[0] = (LSM6DSL_CTRL8_XL | SPI_WRITE_DATA);
		tx_data[1] = (LSM6DSL_LPF2_XL_EN | LSM6DSL_HPCF_XL_0 | LSM6DSL_INPUT_COMPOSITE);
		if (rxtxSPI0(2, tx_data, rx_data, lsm6dslSpiCsPin)) {		//Check if SPI communication
			errorFlag = 1;
		}
		*/
	}
	else if(commMode == LSM6DSL_COMM_MODE_I2C){
		if(DetectLsm6dsl() == Lsm6dslSuccess){

			initializedFlag = 1;
		}
		else{
			msg = Lsm6dslNotInitialized;
		}
	}
	else {
		msg = Lsm6dslCommModeNotSetup;
	}

	return msg;
}
ReturnMsgLsm6dsl DetectLsm6dsl(void){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(commMode == LSM6DSL_COMM_MODE_SPI){

	}
	else if(commMode == LSM6DSL_COMM_MODE_I2C){
		//Lsm6dslFailure;

		I2C_TransferSeq_TypeDef    seq;
		I2C_TransferReturn_TypeDef ret;
		uint8_t                    i2c_read_data[8];
		uint8_t                    i2c_write_data[2];

		seq.addr  = i2cAddr;
		seq.flags = I2C_FLAG_WRITE_READ;
		/* Select command to issue */
		i2c_write_data[0] = LSM6DSL_READ_ID2_1;
		i2c_write_data[1] = LSM6DSL_READ_ID2_2;
		seq.buf[0].data   = i2c_write_data;
		seq.buf[0].len    = 2;
		/* Select location/length of data to be read */
		seq.buf[1].data = i2c_read_data;
		seq.buf[1].len  = 8;

		ret = I2CSPM_Transfer(i2cPort, &seq);

		if (ret != i2cTransferDone) {
			msg = Lsm6dslFailure;
		}
		/*
		else if (NULL != deviceId) {
			*deviceId = i2c_read_data[0];
		}
		*/
	}
	else{
		msg = Lsm6dslCommModeNotSetup;
	}

	return msg;
}


ReturnMsgLsm6dsl GetLsm6dslAccelData(uint8_t* accelDataPtr){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if (initializedFlag) {
		if(commMode == LSM6DSL_COMM_MODE_SPI){
			/*
			uint8_t tx_data[8] = { 0 };
			uint8_t rx_data[8] = { 0 };
			bool errorFlag = 1;

			tx_data[0] = (LSM6DSL_OUTX_L_XL | SPI_READ_DATA);
			if (rxtxSPI0(7, tx_data, rx_data, lsm6dslSpiCsPin) == 0) {
				errorFlag = 0;
			}
			//if(sizeof(accelDataPtr) / sizeof(accelDataPtr[0]) >= 6)
			for (int i = 0; i < 6; i++) {
				accelDataPtr[i] = rx_data[i + 1];
			}
			*/
		}
		else if(commMode == LSM6DSL_COMM_MODE_I2C){

		}
	}
	else {
		msg = Lsm6dslNotInitialized;
	}

	return msg;
}


ReturnMsgLsm6dsl GetAccelGyroDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(initializedFlag == true){
		if(commMode == LSM6DSL_COMM_MODE_SPI){

		}
		else if(commMode == LSM6DSL_COMM_MODE_I2C){
			msg = i2cReadLsm6dsl(data);
		}
		else{
			msg = Lsm6dslCommModeNotSetup;
		}
	}
	else{
		msg = Lsm6dslNotInitialized;
	}
	return msg;
}
ReturnMsgLsm6dsl GetAccelDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(initializedFlag == true){
		if(commMode == LSM6DSL_COMM_MODE_SPI){

		}
		else if(commMode == LSM6DSL_COMM_MODE_I2C){
			msg = i2cReadLsm6dsl(data);
		}
		else{
			msg = Lsm6dslCommModeNotSetup;
		}
	}
	else{
		msg = Lsm6dslNotInitialized;
	}
	return msg;
}
ReturnMsgLsm6dsl GetGyroDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(initializedFlag == true){
		if(commMode == LSM6DSL_COMM_MODE_SPI){

		}
		else if(commMode == LSM6DSL_COMM_MODE_I2C){
			msg = i2cReadLsm6dsl(data);
		}
		else{
			msg = Lsm6dslCommModeNotSetup;
		}
	}
	else{
		msg = Lsm6dslNotInitialized;
	}
	return msg;
}
ReturnMsgLsm6dsl GetTempDataLsm6dsl(uint8_t* data){
	ReturnMsgLsm6dsl msg = Lsm6dslSuccess;

	if(initializedFlag == true){
		if(commMode == LSM6DSL_COMM_MODE_SPI){

		}
		else if(commMode == LSM6DSL_COMM_MODE_I2C){
			msg = i2cReadLsm6dsl(data);
		}
		else{
			msg = Lsm6dslCommModeNotSetup;
		}
	}
	else{
		msg = Lsm6dslNotInitialized;
	}
	return msg;
}









/**************************************************************************//**
 * @brief
 *  Reads Firmware Revision from a Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use.
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] fwRev
 *   The internal firmware revision. 0xFF === 1.0
 * @return
 *   Returns zero on OK, non-zero otherwise.
 *****************************************************************************/
int32_t Lsm6dsl_GetFirmwareRevision(I2C_TypeDef *i2c, uint8_t addr, uint8_t *fwRev){
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_write_data[2];
  uint8_t                    i2c_read_data[1];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_WRITE_READ;
  /* Select command to issue */
  i2c_write_data[0] = LSM6DSL_READ_FWREV_1;
  i2c_write_data[1] = LSM6DSL_READ_FWREV_2;
  seq.buf[0].data   = i2c_write_data;
  seq.buf[0].len    = 2;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 1;

  ret = I2CSPM_Transfer(i2c, &seq);

  if (ret != i2cTransferDone) {
    *fwRev = 0;
    return (uint32_t) ret;
  }
  *fwRev = i2c_read_data[0];

  return (uint32_t) i2cTransferDone;
}
/**************************************************************************//**
 * @brief
 * Starts no hold measurement of relative humidity and temperature from a Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use.
 * @param[in] addr
 *   The I2C address of the sensor.
 * @return
 *   Returns zero on OK, non-zero otherwise.
 *****************************************************************************/
int32_t Lsm6dsl_StartNoHoldMeasureRHAndTemp(I2C_TypeDef *i2c, uint8_t addr)
{
  int ret = Lsm6dsl_StartNoHoldMeasure(i2c, addr, LSM6DSL_READ_RH_NH);

  return ret;
}
/**************************************************************************//**
 * @brief
 *  Reads relative humidity and temperature from a Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use.
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] rhData
 *   The relative humidity in percent (multiplied by 1000).
 * @param[out] tData
 *   The temperature in milli-Celsius.
 * @return
 *   Returns zero on OK, non-zero otherwise.
 *****************************************************************************/
int32_t Lsm6dsl_MeasureRHAndTemp(I2C_TypeDef *i2c, uint8_t addr, uint32_t *rhData, int32_t *tData){
  int ret = Lsm6dsl_Measure(i2c, addr, rhData, LSM6DSL_READ_RH);

  if (ret == 2) {
    /* convert to milli-percent */
    *rhData = (((*rhData) * 15625L) >> 13) - 6000;
  } else {
    return -1;
  }

  ret = Lsm6dsl_Measure(i2c, addr, (uint32_t *) tData, LSM6DSL_READ_TEMP);

  if (ret == 2) {
    *tData = (((*tData) * 21965L) >> 13) - 46850; /* convert to milli-degC */
  } else {
    return -1;
  }

  return 0;
}
/**************************************************************************//**
 * @brief
 *  Reads relative humidity and temperature from a Lsm6dsl sensor.
 * @param[in] i2c
 *   The I2C peripheral to use.
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] vData
 *   The data read from the sensor.
 * @return
 *   Returns zero on OK, non-zero otherwise.
 *****************************************************************************/
int32_t Lsm6dsl_MeasureV(I2C_TypeDef *i2c, uint8_t addr, int32_t *vData){
  int ret;
  Lsm6dsl_WriteUserReg2(i2c, addr, 0x0e);
  ret = Lsm6dsl_Measure(i2c, addr, (uint32_t *) vData, LSM6DSL_READ_VIN);
  Lsm6dsl_WriteUserReg2(i2c, addr, 0x09);
  if (ret == 2) {
    /* convert  */
  } else {
    return -1;
  }
  return 0;
}
/**************************************************************************//**
 * @brief
 *   Checks if a Lsm6dsl is present on the I2C bus or not.
 * @param[in] i2c
 *   The I2C peripheral to use (Not used).
 * @param[in] addr
 *   The I2C address to probe.
 * @param[out] deviceId
 *   Write device ID from SNB_3 if device responds. Pass in NULL to discard.
 *   Should be 0x0D for Lsm6dsl, 0x14 for Si7020 or 0x15 for Si7021
 * @return
 *   True if a Si70xx is detected, false otherwise.
 *****************************************************************************/
bool Lsm6dsl_Detect(I2C_TypeDef *i2c, uint8_t addr, uint8_t *deviceId)
{
  I2C_TransferSeq_TypeDef    seq;
  I2C_TransferReturn_TypeDef ret;
  uint8_t                    i2c_read_data[8];
  uint8_t                    i2c_write_data[2];

  seq.addr  = addr;
  seq.flags = I2C_FLAG_WRITE_READ;
  /* Select command to issue */
  i2c_write_data[0] = LSM6DSL_READ_ID2_1;
  i2c_write_data[1] = LSM6DSL_READ_ID2_2;
  seq.buf[0].data   = i2c_write_data;
  seq.buf[0].len    = 2;
  /* Select location/length of data to be read */
  seq.buf[1].data = i2c_read_data;
  seq.buf[1].len  = 8;

  ret = I2CSPM_Transfer(i2c, &seq);
  if (ret != i2cTransferDone) {
    return false;
  }
  if (NULL != deviceId) {
    *deviceId = i2c_read_data[0];
  }
  return true;
}
