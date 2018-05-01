#ifndef    S23LC1024_H
#define    S23LC1024_H

#include <stdbool.h>
#include <stdint.h>
#include "bg_types.h"

#include "halconfig_23lc1024.h"
#include "payloadbuffer.h"

#define SRAM23LC1024

#define INSTRUCTION_WRMR	0x01	//Write Mode Register
#define INSTRUCTION_WRITE	0x02	//Write data to memory array beginning at selected address
#define INSTRUCTION_READ	0x03	//Read data from memory array beginning at selected address
#define INSTRUCTION_RDMR	0x05	//Read Mode Register

#define INSTRUCTION_EQIO	0x38	//Enter Quad I/O access (enter SQI bus mode)
#define INSTRUCTION_EDIO	0x3B	//Enter Dual I/O access (enter SDI bus mode)
#define INSTRUCTION_RSTIO	0xFF	//Reset Dual and Quad I/O access (revert tp SPI bus mode)

#define SRAM23LC1024_ADDRESS_MAX	0x1FFFF		//Max Address Value
#define SRAM23LC1024_ADDRESS_MIN	0x00000		//Min Address Value

// variable
#define    TRUE     		1
#define    FALSE    		0

// Support I/O mode
#define    SIO              0
#define    DIO              1
#define    QIO              2


//*****************************   TYPEDEFS   **********************************

// Return Message
typedef enum {
	Msg23lc1024Success,
	Msg23lc1024Failure,
	Msg23lc1024InvalidArgument,
	Msg23lc1024CommModeNotSetup,
	Msg23lc1024CommPortNotSetup,
	Msg23lc1024NotInitialized,
	Msg23lc1024TimeOut,
	Msg23lc1024Busy,
	Msg23lc1024Invalid,
	Msg23lc1024QuadNotEnable
}ReturnMsg23lc1024;


//**************************   FUNCTION DECLARATIONS   ************************

void Set23lc1024(void);
void Init23lc1024(void);
bool Detect23lc1024(void);

void WritePayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize);
void ReadPayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize);

void writeBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize);
void readBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize);

#endif    // end of S23LC1024_H

