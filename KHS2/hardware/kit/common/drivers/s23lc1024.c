#include "s23lc1024.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static void setCSLow(void){
	GPIO_PinOutClear( SRAM23LC_PORT_CS, SRAM23LC_PIN_CS );
}
static void setCSHigh(void){
   GPIO_PinOutSet( SRAM23LC_PORT_CS, SRAM23LC_PIN_CS );
}

static void sendByte(uint8_t byte_value){

	USART_SpiTransfer(SRAM23LC_USART, byte_value);
}
static uint8_t getByte(void){

	return USART_SpiTransfer( SRAM23LC_USART, 0xff );
}

static void rstio23lc1024(void){

    setCSLow();

    sendByte(INSTRUCTION_RSTIO);

    setCSHigh();
}
static void rdmr23lc1024(void){

    setCSLow();

    sendByte(INSTRUCTION_RDMR);

    setCSHigh();
}

//**************************   PUBLIC FUNCTION DEFINIITIONS   *****************

void Set23lc1024(void){
   USART_InitSync_TypeDef init = USART_INITSYNC_DEFAULT;
   init.enable = usartDisable;
   init.baudrate = SRAM23LC_BAUDRATE;
   init.msbf     = true;

   CMU_ClockEnable(SRAM23LC_USART_CLK, true);
   //CMU_ClockEnable(cmuClock_GPIO, true);

   USART_InitSync(SRAM23LC_USART, &init);

   SRAM23LC_USART->ROUTELOC0 = ( (SRAM23LC_LOC_RX << _USART_ROUTELOC0_RXLOC_SHIFT)
                           	   | (SRAM23LC_LOC_TX << _USART_ROUTELOC0_TXLOC_SHIFT)
							   | (SRAM23LC_LOC_SCLK << _USART_ROUTELOC0_CLKLOC_SHIFT) );

   SRAM23LC_USART->ROUTEPEN  = (  USART_ROUTEPEN_RXPEN
                            	| USART_ROUTEPEN_TXPEN
								| USART_ROUTEPEN_CLKPEN );

   // IO config
   GPIO_PinModeSet( SRAM23LC_PORT_MOSI, SRAM23LC_PIN_MOSI, gpioModePushPull, 1 );
   GPIO_PinModeSet( SRAM23LC_PORT_MISO, SRAM23LC_PIN_MISO, gpioModeInput,    0 );
   GPIO_PinModeSet( SRAM23LC_PORT_SCLK, SRAM23LC_PIN_SCLK, gpioModePushPull, 1 );
   GPIO_PinModeSet( SRAM23LC_PORT_CS,   SRAM23LC_PIN_CS,   gpioModePushPull, 1 );

   USART_Enable(SRAM23LC_USART, usartEnable);
}
void Init23lc1024(void){
	rstio23lc1024();		//Reset device
	rdmr23lc1024();			//Set in Read Mode
}
bool Detect23lc1024(void){
	bool result = Msg23lc1024Success;

	uint8_t addressBytes[3] = {0x00, 0x00, 0x00};
	uint8_t dataBytes[8]	= {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
	uint8_t readBytes[8]	= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	//Clear memory
	WriteBytes23lc1024(addressBytes, readBytes, 8);
	//Write Sample
	WriteBytes23lc1024(addressBytes, dataBytes, 8);
	//Read Sample
	ReadBytes23lc1024(addressBytes, readBytes, 8);

	for(int i=0; i<8; i++){
		if(dataBytes[i] != readBytes[i]){
			result = Msg23lc1024Failure;
		}
	}
	return result;
}

void WritePayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize){
    // Chip select go low to start a flash command
    setCSLow();

    //Instruction
    sendByte(INSTRUCTION_WRITE);

    //Address 24-bit
    sendByte(header.IdByte1);
    sendByte(header.IdByte0);
    sendByte(0x00);

    //Data
    sendByte(header.IdByte1);
    sendByte(header.IdByte0);
    sendByte(header.CountByte1);
    sendByte(header.CountByte0);

    for(int i=0; i<dataSize; i++){
        sendByte(dataBytes[i]);
    }

    // Chip select go high to end a flash command
    setCSHigh();
}
void ReadPayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize){
    // Chip select go low to start a flash command
    setCSLow();

    //Instruction
    sendByte(INSTRUCTION_READ);

    //Address 24-bit
    sendByte(header.IdByte1);
    sendByte(header.IdByte0);
    sendByte(0x00);

    //Data
    header.IdByte1 = getByte();
    header.IdByte0 = getByte();
	header.CountByte1 = getByte();
	header.CountByte0 = getByte();

    for(int i=0; i<dataSize; i++){
    	dataBytes[i] = getByte();
    }

    // Chip select go high to end a flash command
    setCSHigh();
}

void WriteBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize){
    // Chip select go low to start a flash command
    setCSLow();

    sendByte(INSTRUCTION_WRITE);

    for(int i=0; i<3; i++){
        sendByte(addressBytes3[i]);
    }

    for(int i=0; i<dataSize; i++){
        sendByte(dataBytes[i]);
    }

    // Chip select go high to end a flash command
    setCSHigh();
}
void ReadBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize){

    // Chip select go low to start a flash command
    setCSLow();

    sendByte(INSTRUCTION_READ);

    for(int i=0; i<3; i++){
        sendByte(addressBytes3[i]);
    }

    for(int i=0; i<dataSize; i++){
    	dataBytes[i] = getByte();
    }

    // Chip select go high to end a flash command
    setCSHigh();
}


