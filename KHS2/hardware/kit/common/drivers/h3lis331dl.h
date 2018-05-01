#ifndef H3LIS331DL_H
#define H3LIS331DL_H

//#include "em_device.h"
#include <stdbool.h>

#include "halconfig_h3lis331dl.h"

#ifdef __cplusplus
extern "C" {
#endif

//*******************************   DEFINES   *********************************

// I2C device address for H3lis331dl
#define H3LIS331DL_ADDR      0x82

// Device ID value for H3lis331dl
#define H3LIS331DL_DEVICE_ID 0x0D

//************************   H3LIS331DL - ACCELEROMETER   *********************

//************************   REGISTER ADDRESS   *******************************

#define H3LIS331DL_WHO_AM_I					0x0F

#define H3LIS331DL_CTRL_REG1				0x20
#define H3LIS331DL_CTRL_REG2				0x21
#define H3LIS331DL_CTRL_REG3				0x22
#define H3LIS331DL_CTRL_REG4				0x23
#define H3LIS331DL_CTRL_REG5				0x24

#define H3LIS331DL_HP_FILTER_RESET			0x25
#define H3LIS331DL_REFERENCE				0x26
#define H3LIS331DL_STATUS_REG				0x27

#define H3LIS331DL_OUT_X_L					0x28
#define H3LIS331DL_OUT_X_H					0x29
#define H3LIS331DL_OUT_Y_L					0x2A
#define H3LIS331DL_OUT_Y_H					0x2B
#define H3LIS331DL_OUT_Z_L					0x2C
#define H3LIS331DL_OUT_Z_H					0x2D

#define H3LIS331DL_INT1_CFG					0x30
#define H3LIS331DL_INT1_SRC					0x31
#define H3LIS331DL_INT1_THS					0x32
#define H3LIS331DL_INT1_DURATION			0x33

#define H3LIS331DL_INT2_CFG					0x34
#define H3LIS331DL_INT2_SRC					0x35
#define H3LIS331DL_INT2_THS					0x36
#define H3LIS331DL_INT2_DURATION			0x37


//************************   REGISTER VALUES   ********************************
#define H3LIS331DL_WHO_AM_I_VALUE			0x32

//*********************   REGISTER PARAMETERS   *******************************

//H3LIS331DL_CTRL_REG1	PARAMETERS
#define H3LIS331DL_CTRL_REG1_PM0				0x00	//Power down
#define H3LIS331DL_CTRL_REG1_PM1				0x20	//Normal Mode - ODR
#define H3LIS331DL_CTRL_REG1_PM2				0x40	//Low Power - 0.5 Hz
#define H3LIS331DL_CTRL_REG1_PM3				0x60	//Low Power - 1 Hz
#define H3LIS331DL_CTRL_REG1_PM4				0x80	//Low Power - 2 Hz
#define H3LIS331DL_CTRL_REG1_PM5				0xA0	//Low Power - 5 Hz
#define H3LIS331DL_CTRL_REG1_PM6				0xC0	//Low Power - 10 Hz

#define H3LIS331DL_CTRL_REG1_DR0				0x00	//ODR - 50 Hz	: Low-pass filter - 37 Hz
#define H3LIS331DL_CTRL_REG1_DR1				0x08	//ODR - 100 Hz	: Low-pass filter - 74 Hz
#define H3LIS331DL_CTRL_REG1_DR2				0x10	//ODR - 400 Hz	: Low-pass filter - 292 Hz
#define H3LIS331DL_CTRL_REG1_DR3				0x18	//ODR - 1000 Hz	: Low-pass filter - 780 Hz

#define H3LIS331DL_CTRL_REG1_ZEN				0x04	//Enable Z-axis
#define H3LIS331DL_CTRL_REG1_YEN				0x02	//Enable Y-axis
#define H3LIS331DL_CTRL_REG1_XEN				0x01	//Enable X-axis

//H3LIS331DL_CTRL_REG2	PARAMETERS
#define H3LIS331DL_CTRL_REG2_BOOT				0x80	//Reboot Memory Content

#define H3LIS331DL_CTRL_REG2_HPM0				0x00	//High-Pass Filter - Normal Mode
#define H3LIS331DL_CTRL_REG2_HPM1				0x20	//High-Pass Filter - Reference Signal
#define H3LIS331DL_CTRL_REG2_HPM2				0x40	//High-Pass Filter - Normal Mode

#define H3LIS331DL_CTRL_REG2_FDS				0x10	//Filtered Data Selection - 0:Internal Filter Bypassed,1:Data from internal filter sent to output

#define H3LIS331DL_CTRL_REG2_HPEN2				0x80	//High-Pass Filter enabled for interrupt 2 source - 0:Filter Bypassed,1:Filter Enabled
#define H3LIS331DL_CTRL_REG2_HPEN1				0x40	//High-Pass Filter enabled for interrupt 1 source - 0:Filter Bypassed,1:Filter Enabled

														//High-Pass Filter Cutoff Frequency
														// DR = 50,		100,	400,	1000 Hz
#define H3LIS331DL_CTRL_REG2_HPCF0				0x00	//		1, 		2, 		8, 		20
#define H3LIS331DL_CTRL_REG2_HPCF1				0x01	//		0.5,	1, 		4, 		10
#define H3LIS331DL_CTRL_REG2_HPCF2				0x02	//		0.25,	0.5,	2,		5
#define H3LIS331DL_CTRL_REG2_HPCF3				0x03	//		0.125,	0.25,	1,		2.5

//H3LIS331DL_CTRL_REG3	PARAMETERS
#define H3LIS331DL_CTRL_REG3_IHL				0x80	//Interrupt - 0:Active Low, 1:Active High
#define H3LIS331DL_CTRL_REG3_PP_OD				0x40	//Interrupt Pin - 0:Push-Pull,1:Open Drain
#define H3LIS331DL_CTRL_REG3_LIR2				0x20	//Interrupt 2 - 0:Not Latched,1:Latched

#define H3LIS331DL_CTRL_REG3_I2_CFG0			0x00	//Interrupt 2 Source
#define H3LIS331DL_CTRL_REG3_I2_CFG1			0x08	//Interrupt 1 Source or Interrupt 2 Source
#define H3LIS331DL_CTRL_REG3_I2_CFG2			0x10	//Data Ready
#define H3LIS331DL_CTRL_REG3_I2_CFG3			0x18	//Boot Running

#define H3LIS331DL_CTRL_REG3_LIR1				0x04	//Interrupt 1 - 0:Not Latched,1:Latched

#define H3LIS331DL_CTRL_REG3_I1_CFG0			0x00	//Interrupt 1 Source
#define H3LIS331DL_CTRL_REG3_I1_CFG1			0x01	//Interrupt 1 Source or Interrupt 2 Source
#define H3LIS331DL_CTRL_REG3_I1_CFG2			0x02	//Data Ready
#define H3LIS331DL_CTRL_REG3_I1_CFG3			0x03	//Boot Running

//H3LIS331DL_CTRL_REG4	PARAMETERS
#define H3LIS331DL_CTRL_REG4_BDU				0x80	//Block Data Update - 0:Continuous Update,1:Output Registers not updated between MSB and LSB readin
#define H3LIS331DL_CTRL_REG4_BLE				0x40	//Big/Little Endian Data Selectrion - 0: LSB,1:MSB

#define H3LIS331DL_CTRL_REG4_FS0				0x00	//Full Scale Selection - +-100g
#define H3LIS331DL_CTRL_REG4_FS1				0x10	//Full Scale Selection - +-200g
#define H3LIS331DL_CTRL_REG4_FS2				0x30	//Full Scale Selection - +-400g

#define H3LIS331DL_CTRL_REG4_SIM				0x01	//SPI Serial Interface Mode Selection - 0:4-Wire Interface,1:3-Wire Interface

//H3LIS331DL_CTRL_REG5	PARAMETERS
#define H3LIS331DL_CTRL_REG5_TURNON0			0x00	//Sleep-To-Wake Function Disabled
#define H3LIS331DL_CTRL_REG5_TURNON1			0x03	//Turned On - Device Is In Low-Power Mode

//H3LIS331DL_INT1_CFG	PARAMETERS
#define H3LIS331DL_INT1_CFG_AOI					0x80	//AND/OR Combination Of Interrupt Levels - 0:OR,1:AND
#define H3LIS331DL_INT1_CFG_ZHIE				0x20	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT1_CFG_ZLIE				0x10	//Enable Interrupt - 0:Disabled,1:Enabled

#define H3LIS331DL_INT1_CFG_YHIE				0x08	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT1_CFG_YLIE				0x04	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT1_CFG_XHIE				0x02	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT1_CFG_XLIE				0x01	//Enable Interrupt - 0:Disabled,1:Enabled

//H3LIS331DL_INT1_THS	PARAMETERS
#define H3LIS331DL_INT1_THS_0					0x00
#define H3LIS331DL_INT1_THS_5					0x05
#define H3LIS331DL_INT1_THS_10					0x0A
#define H3LIS331DL_INT1_THS_20					0x14
#define H3LIS331DL_INT1_THS_40					0x28
#define H3LIS331DL_INT1_THS_80					0x50
#define H3LIS331DL_INT1_THS_160					0xA0
#define H3LIS331DL_INT1_THS_255					0xFF

//H3LIS331DL_INT1_DURATION	PARAMETERS
#define H3LIS331DL_INT1_DURATION_0				0x00
#define H3LIS331DL_INT1_DURATION_5				0x05
#define H3LIS331DL_INT1_DURATION_10				0x0A
#define H3LIS331DL_INT1_DURATION_20				0x14
#define H3LIS331DL_INT1_DURATION_40				0x28
#define H3LIS331DL_INT1_DURATION_80				0x50
#define H3LIS331DL_INT1_DURATION_160			0xA0
#define H3LIS331DL_INT1_DURATION_255			0xFF

//H3LIS331DL_INT2_CFG	PARAMETERS
#define H3LIS331DL_INT2_CFG_AOI					0x80	//AND/OR Combination Of Interrupt Levels - 0:OR,1:AND
#define H3LIS331DL_INT2_CFG_ZHIE				0x20	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT2_CFG_ZLIE				0x10	//Enable Interrupt - 0:Disabled,1:Enabled

#define H3LIS331DL_INT2_CFG_YHIE				0x08	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT2_CFG_YLIE				0x04	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT2_CFG_XHIE				0x02	//Enable Interrupt - 0:Disabled,1:Enabled
#define H3LIS331DL_INT2_CFG_XLIE				0x01	//Enable Interrupt - 0:Disabled,1:Enabled

//H3LIS331DL_INT2_THS	PARAMETERS
#define H3LIS331DL_INT2_THS_0					0x00
#define H3LIS331DL_INT2_THS_5					0x05
#define H3LIS331DL_INT2_THS_10					0x0A
#define H3LIS331DL_INT2_THS_20					0x14
#define H3LIS331DL_INT2_THS_40					0x28
#define H3LIS331DL_INT2_THS_80					0x50
#define H3LIS331DL_INT2_THS_160					0xA0
#define H3LIS331DL_INT2_THS_255					0xFF

//H3LIS331DL_INT2_DURATION	PARAMETERS
#define H3LIS331DL_INT2_DURATION_0				0x00
#define H3LIS331DL_INT2_DURATION_5				0x05
#define H3LIS331DL_INT2_DURATION_10				0x0A
#define H3LIS331DL_INT2_DURATION_20				0x14
#define H3LIS331DL_INT2_DURATION_40				0x28
#define H3LIS331DL_INT2_DURATION_80				0x50
#define H3LIS331DL_INT2_DURATION_160			0xA0
#define H3LIS331DL_INT2_DURATION_255			0xFF

//H3LIS331DL Communication Mode
#define H3LIS331DL_COMM_MODE_SPI			0x01
#define H3LIS331DL_COMM_MODE_I2C			0x02

//*****************************   TYPEDEFS   **********************************

// Return Message
typedef enum {
	H3lis331dlSuccess,
	H3lis331dlFailure,
	H3lis331dlInvalidArgument,
	H3lis331dlCommModeNotSetup,
	H3lis331dlNotInitialized
}ReturnMsgH3lis331dl;

//**************************   PUBLIC FUNCTION DECLARATIONS   *****************

void SetI2CH3lis331dl(void);

ReturnMsgH3lis331dl InitH3lis331dl(void);
ReturnMsgH3lis331dl DetectH3lis331dl(void);

ReturnMsgH3lis331dl GetAccelDataH3lis331dl(uint8_t* data);

/*
bool sleepH3lis331dl(void);
bool sleepTiltH3lis331dl(void);
bool sleepDoubleTapH3lis331dl(void);
bool sleepWristTiltH3lis331dl(void);
bool wakeH3lis331dl(void);

bool getH3lis331dlAccelData(uint8_t* );
bool getH3lis331dlGyroData(uint8_t* );
bool getH3lis331dlTempData(uint8_t*);
 */

#ifdef __cplusplus
}
#endif

#endif // H3LIS331DL_H
