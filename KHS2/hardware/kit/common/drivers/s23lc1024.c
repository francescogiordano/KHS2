#include "s23lc1024.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_cmu.h"


/* Fallback to loc 11 if no location is defined for backwards compatibility */
#ifndef SRAM23LC_LOC_RX
#define SRAM23LC_LOC_RX            _USART_ROUTELOC0_RXLOC_LOC11
#endif
#ifndef SRAM23LC_LOC_SCLK
#define SRAM23LC_LOC_SCLK          _USART_ROUTELOC0_CLKLOC_LOC11
#endif
#ifndef SRAM23LC_LOC_TX
#define SRAM23LC_LOC_TX            _USART_ROUTELOC0_TXLOC_LOC11
#endif
/* Fallback to baudrate of 8 MHz if not defined for backwards compatibility */
#ifndef SRAM23LC_BAUDRATE
#define SRAM23LC_BAUDRATE   8000000
#endif

//**************************   STATIC FUNCTION DEFINIITIONS   *****************

static void Wait_Flash_WarmUp(){
    volatile int time_cnt = FlashFullAccessTime;
    while( time_cnt > 0 ){
        time_cnt--;
    }
}
static void Initial_Spi(){
   // Wait flash warm-up
   Wait_Flash_WarmUp();
}
static void setCSLow(){
	GPIO_PinOutClear( SRAM23LC_PORT_CS, SRAM23LC_PIN_CS );
}
static void setCSHigh(){
   GPIO_PinOutSet( SRAM23LC_PORT_CS, SRAM23LC_PIN_CS );
}

static void sendByte( uint8_t byte_value, uint8_t transfer_type )
{
   switch( transfer_type )
   {
#ifdef SIO
   case SIO: // Single I/O
      USART_SpiTransfer( SRAM23LC_USART, byte_value );
      break;
#endif
#ifdef DIO
   case DIO: // Dual I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef QIO
   case QIO: // Quad I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef PIO
    case PIO: // Parallel I/O
       //--- IO mode not supported! ---//
       break;
#endif
#ifdef DTSIO
   case DTSIO: // Double transfer rate Single I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef DTDIO
   case DTDIO: // Double transfer rate Dual I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef DTQIO
   case DTQIO: // Double transfer rate Quad I/O
      //--- IO mode not supported! ---//
      break;
#endif
   default:
      break;
   }
}
static uint8_t getByte( uint8_t transfer_type )
{
   uint8_t data_buf = 0;

   switch( transfer_type )
   {
#ifdef SIO
   case SIO: // Single I/O
      //--- insert your code here for single IO receive. ---//
      data_buf = USART_SpiTransfer( SRAM23LC_USART, 0xff );
      break;
#endif
#ifdef DIO
   case DIO: // Dual I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef QIO
    case QIO: // Quad I/O
       //--- IO mode not supported! ---//
       break;
#endif
#ifdef PIO
   case PIO: // Parallel I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef DTSIO
   case DTSIO: // Double transfer rate Single I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef DTDIO
   case DTDIO: // Double transfer rate Dual I/O
      //--- IO mode not supported! ---//
      break;
#endif
#ifdef DTQIO
   case DTQIO: // Double transfer rate Qual I/O
      //--- IO mode not supported! ---//
#endif
   default:
      break;
   }

    return data_buf;
}

/*
 * Function:       IsFlashBusy
 * Arguments:      None.
 * Description:    Check status register WIP bit.
 *                 If  WIP bit = 1: return TRUE ( Busy )
 *                             = 0: return FALSE ( Ready ).
 * Return Message: TRUE, FALSE
 */
static bool IsFlashBusy( void ){
    uint8_t  gDataBuffer;
    SRAM23LC_RDSR( &gDataBuffer );
    if( (gDataBuffer & FLASH_WIP_MASK)  == FLASH_WIP_MASK ){
        return TRUE;
    }
    else{
        return FALSE;
    }
}
/*
 * Function:       InsertDummyCycle
 * Arguments:      dummy_cycle, number of dummy clock cycle
 * Description:    Insert dummy cycle of SCLK
 * Return Message: None.
 */
static void InsertDummyCycle( uint8_t dummy_cycle )
{
   int i;

   for( i = 0; i < dummy_cycle/8; i++ )
   {
      USART_SpiTransfer( SRAM23LC_USART, 0xff );
   }
}
/*
 * Function:       WaitFlashReady
 * Arguments:      ExpectTime, expected time-out value of flash operations.
 *                 No use at non-synchronous IO mode.
 * Description:    Synchronous IO:
 *                 If flash is ready return TRUE.
 *                 If flash is time-out return FALSE.
 *                 Non-synchronous IO:
 *                 Always return TRUE
 * Return Message: TRUE, FALSE
 */
static bool WaitFlashReady( uint32_t ExpectTime )
{
#ifndef NON_SYNCHRONOUS_IO
    volatile uint32_t temp = 0;
    while( IsFlashBusy() )
    {
        if( temp > ExpectTime )
        {
            return FALSE;
        }
        temp = temp + 1;
    }
    return TRUE;
#else
    return TRUE;
#endif
}
/*
 * Function:       WaitRYBYReady
 * Arguments:      ExpectTime, expected time-out value of flash operations.
 *                 No use at non-synchronous IO mode.
 * Description:    Synchronous IO:
 *                 If flash is ready return TRUE.
 *                 If flash is time-out return FALSE.
 *                 Non-synchronous IO:
 *                 Always return TRUE
 * Return Message: TRUE, FALSE
 */
static bool WaitRYBYReady( uint32_t ExpectTime )
{
#ifndef NON_SYNCHRONOUS_IO
    uint32_t temp = 0;
#ifdef GPIO_SPI
    while( SO == 0 )
#else
    while( GPIO_PinInGet(SRAM23LC_PORT_MISO, SRAM23LC_PIN_MISO) == 0 );
#endif
    {
        if( temp > ExpectTime )
        {
            return FALSE;
        }
        temp = temp + 1;
    }
    return TRUE;

#else
    return TRUE;
#endif
}
/*
* Function:       IsFlashQIO
 * Arguments:      None.
 * Description:    If flash QE bit = 1: return TRUE
 *                                 = 0: return FALSE.
 * Return Message: TRUE, FALSE
 */
static bool IsFlashQIO( void )
{
#ifdef FLASH_NO_QE_BIT
    return TRUE;
#else
    uint8_t  gDataBuffer;
    SRAM23LC_RDSR( &gDataBuffer );
    if( (gDataBuffer & FLASH_QE_MASK) == FLASH_QE_MASK )
        return TRUE;
    else
        return FALSE;
#endif
}
/*
 * Function:       IsFlash4Byte
 * Arguments:      None
 * Description:    Check flash address is 3-byte or 4-byte.
 *                 If flash 4BYTE bit = 1: return TRUE
 *                                    = 0: return FALSE.
 * Return Message: TRUE, FALSE
 */
static bool IsFlash4Byte( void )
{
#ifdef FLASH_CMD_RDSCUR
    #ifdef FLASH_4BYTE_ONLY
        return TRUE;
    #elif FLASH_3BYTE_ONLY
        return FALSE;
    #else
        uint8_t  gDataBuffer;
        SRAM23LC_RDSCUR( &gDataBuffer );
        if( (gDataBuffer & FLASH_4BYTE_MASK) == FLASH_4BYTE_MASK )
            return TRUE;
        else
            return FALSE;
    #endif
#else
    return FALSE;
#endif
}
/*
 * Function:       SendFlashAddr
 * Arguments:      flash_address, 32 bit flash memory address
 *                 io_mode, I/O mode to transfer address
 *                 addr_4byte_mode,
 * Description:    Send flash address with 3-byte or 4-byte mode.
 * Return Message: None
 */
static void SendFlashAddr( uint32_t flash_address, uint8_t io_mode, bool addr_4byte_mode )
{
    /* Check flash is 3-byte or 4-byte mode.
       4-byte mode: Send 4-byte address (A31-A0)
       3-byte mode: Send 3-byte address (A23-A0) */
    if( addr_4byte_mode == TRUE ){
        sendByte( (flash_address >> 24), io_mode ); // A31-A24
    }
    /* A23-A0 */
    SendByte( (flash_address >> 16), io_mode );
    SendByte( (flash_address >> 8), io_mode );
    SendByte( (flash_address), io_mode );
}
/*
 * Function:       GetDummyCycle
 * Arguments:      default_cycle, default dummy cycle
 *                 fsptr, pointer of flash status structure
 * Description:    Get dummy cycle for different condition
 *                 default_cycle: Byte3 | Byte2 | Byte1 | Byte0
 *                      DC 1 bit:   x       1       x       0
 *                      DC 2 bit:   11      10      01      00
 *                 Note: the variable dummy cycle only support
                         in some product.
 * Return Message: Dummy cycle value
 */
static uint8_t GetDummyCycle( uint32_t default_cycle )
{
#ifdef FLASH_CMD_RDCR
    uint8_t gDataBuffer;
    uint8_t dummy_cycle = default_cycle;
    SRAM23LC_RDCR( &gDataBuffer );
    #ifdef SUPPORT_CR_DC
        // product support 1-bit dummy cycle configuration
        if( (gDataBuffer & FLASH_DC_MASK) == FLASH_DC_MASK )
            dummy_cycle = default_cycle >> 16;
        else
            dummy_cycle = default_cycle;
    #elif SUPPORT_CR_DC_2bit
        // product support 2-bit dummy cycle configuration
        switch( gDataBuffer & FLASH_DC_2BIT_MASK ){
            case 0x00:
                dummy_cycle = default_cycle;
            break;
            case 0x40:
                dummy_cycle = default_cycle >> 8;
            break;
            case 0x80:
                dummy_cycle = default_cycle >> 16;
            break;
            case 0xC0:
                dummy_cycle = default_cycle >> 24;
            break;
        }
    #else
         // configuration register not support dummy configuration
         dummy_cycle = default_cycle;
    #endif
    return dummy_cycle;
#else
    // default case: return default dummy cycle
    return default_cycle;
#endif
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
	rstio23lc1024();
	rdmr23lc1024();
}
bool Detect23lc1024(void){
	bool result = false;

	return result;
}

void WritePayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize){
    // Chip select go low to start a flash command
    setCSLow();

    //Instruction
    sendByte(INSTRUCTION_WRITE, SIO);

    //Address 24-bit
    sendByte(header.IdByte1, SIO);
    sendByte(header.IdByte0, SIO);
    sendByte(0x00, SIO);

    //Data
    sendByte(header.IdByte1, SIO);
    sendByte(header.IdByte0, SIO);
    sendByte(header.CountByte1, SIO);
    sendByte(header.CountByte0, SIO);

    for(int i=0; i<dataSize; i++){
        sendByte(dataBytes[i], SIO);
    }

    // Chip select go high to end a flash command
    setCSHigh();
}
void ReadPayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize){
    // Chip select go low to start a flash command
    setCSLow();

    //Instruction
    sendByte(INSTRUCTION_READ, SIO);

    //Address 24-bit
    sendByte(header.IdByte1, SIO);
    sendByte(header.IdByte0, SIO);
    sendByte(0x00, SIO);

    //Data
    header.IdByte1 = getByte(SIO);
    header.IdByte0 = getByte(SIO);
	header.CountByte1 = getByte(SIO);
	header.CountByte0 = getByte(SIO);

    for(int i=0; i<dataSize; i++){
    	dataBytes[i] = getByte(SIO);
    }

    // Chip select go high to end a flash command
    setCSHigh();
}


void writeBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize){
    // Chip select go low to start a flash command
    setCSLow();

    sendByte(INSTRUCTION_WRITE, SIO);

    for(int i=0; i<3; i++){
        sendByte(addressBytes3[i], SIO);
    }

    for(int i=0; i<dataSize; i++){
        sendByte(dataBytes[i], SIO);
    }

    // Chip select go high to end a flash command
    setCSHigh();
}
void readBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize){

    // Chip select go low to start a flash command
    setCSLow();

    sendByte(INSTRUCTION_READ, SIO);

    for(int i=0; i<3; i++){
        sendByte(addressBytes3[i], SIO);
    }

    for(int i=0; i<dataSize; i++){
    	dataBytes[i] = getByte(SIO);
    }

    // Chip select go high to end a flash command
    setCSHigh();
}


void rstio23lc1024(void){

	//RETARGET_WriteString("rstio Enter", 11);
    uint8_t  dataTemp;

    // Chip select go low to start a flash command
    setCSLow();

    sendByte( INSTRUCTION_RSTIO, SIO );

    // Chip select go high to end a flash command
    setCSHigh();
    //RETARGET_WriteString("rstio Exit", 10);
}

void rdmr23lc1024(void){

	//RETARGET_WriteString("rdmr Enter", 10);
    uint8_t  dataTemp;

    // Chip select go low to start a flash command
    setCSLow();

    sendByte( INSTRUCTION_RDMR, SIO );
    dataTemp = getByte( SIO );

    // Chip select go high to end a flash command
    setCSHigh();
}






/*
 * Function:       SRAM23LC_RDID
 * Arguments:      Identification, 32 bit buffer to store id
 * Description:    The RDID instruction is to read the manufacturer ID
 *                 of 1-byte and followed by Device ID of 2-byte.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RDID( uint32_t *Identification )
{
    uint32_t temp;
    uint8_t  gDataBuffer[3];

    // Chip select go low to start a flash command
    setCSLow();

    // Send command
    SendByte( FLASH_CMD_RDID, SIO );

    // Get manufacturer identification, device identification
    gDataBuffer[0] = getByte(SIO);
    gDataBuffer[1] = getByte(SIO);
    gDataBuffer[2] = getByte(SIO);

    // Chip select go high to end a command
    setCSHigh();

    // Store identification
    temp =  gDataBuffer[0];
    temp =  (temp << 8) | gDataBuffer[1];
    *Identification =  (temp << 8) | gDataBuffer[2];

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_RES
 * Arguments:      ElectricIdentification, 8 bit buffer to store electric id
 * Description:    The RES instruction is to read the Device
 *                 electric identification of 1-byte.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RES( uint8_t *ElectricIdentification )
{

    // Chip select go low to start a flash command
    setCSLow();

    // Send flash command and insert dummy cycle
    SendByte( FLASH_CMD_RES, SIO );
    InsertDummyCycle( 24 );

    // Get electric identification
    *ElectricIdentification = GetByte( SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_REMS
 * Arguments:      REMS_Identification, 16 bit buffer to store id
 *                 fsptr, pointer of flash status structure
 * Description:    The REMS instruction is to read the Device
 *                 manufacturer ID and electric ID of 1-byte.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_REMS( uint16_t *REMS_Identification, FlashStatus *fsptr )
{
    uint8_t  gDataBuffer[2];

    // Chip select go low to start a flash command
    setCSLow();

    // Send flash command and insert dummy cycle ( if need )
    // ArrangeOpt = 0x00 will output the manufacturer's ID first
    //            = 0x01 will output electric ID first
    SendByte( FLASH_CMD_REMS, SIO );
    InsertDummyCycle( 16 );
    SendByte( fsptr->ArrangeOpt, SIO );

    // Get ID
    gDataBuffer[0] = GetByte( SIO );
    gDataBuffer[1] = GetByte( SIO );

    // Store identification informaion
    *REMS_Identification = (gDataBuffer[0] << 8) | gDataBuffer[1];

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_RDSR
 * Arguments:      StatusReg, 8 bit buffer to store status register value
 * Description:    The RDSR instruction is for reading Status Register Bits.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RDSR( uint8_t *StatusReg )
{
    uint8_t  gDataBuffer;

    // Chip select go low to start a flash command
    setCSLow();

    // Send command
    SendByte( FLASH_CMD_RDSR, SIO );
    gDataBuffer = GetByte( SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    *StatusReg = gDataBuffer;

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_WRSR
 * Arguments:      UpdateValue, 8/16 bit status register value to updata
 * Description:    The WRSR instruction is for changing the values of
 *                 Status Register Bits (and configuration register)
 * Return Message: Msg23lc1024FlashIsBusy, Msg23lc1024FlashTimeOut, Msg23lc1024FlashOperationSuccess
 */
#ifdef SUPPORT_WRSR_CR
ReturnMsg23lc1024 SRAM23LC_WRSR( uint16_t UpdateValue )
#else
ReturnMsg23lc1024 SRAM23LC_WRSR( uint8_t UpdateValue )
#endif
{
    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    // Send command and update value
    SendByte( FLASH_CMD_WRSR, SIO );
    SendByte( UpdateValue, SIO );
#ifdef SUPPORT_WRSR_CR
    SendByte( UpdateValue >> 8, SIO );    // write configuration register
#endif

    // Chip select go high to end a flash command
    setCSHigh();


    if( WaitFlashReady( WriteStatusRegCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;

}
/*
 * Function:       SRAM23LC_RDSCUR
 * Arguments:      SecurityReg, 8 bit buffer to store security register value
 * Description:    The RDSCUR instruction is for reading the value of
 *                 Security Register bits.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RDSCUR( uint8_t *SecurityReg )
{
    uint8_t  gDataBuffer;

    // Chip select go low to start a flash command
    setCSLow();

    //Send command
    SendByte( FLASH_CMD_RDSCUR, SIO );
    gDataBuffer = GetByte( SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    *SecurityReg = gDataBuffer;

    return Msg23lc1024Success;

}
/*
 * Function:       SRAM23LC_WRSCUR
 * Arguments:      None.
 * Description:    The WRSCUR instruction is for changing the values of
 *                 Security Register Bits.
 * Return Message: Msg23lc1024FlashIsBusy, Msg23lc1024FlashOperationSuccess, FlashWriteRegFailed,
 *                 Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_WRSCUR( void )
{
    uint8_t  gDataBuffer;

    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    // Write WRSCUR command
    SendByte( FLASH_CMD_WRSCUR, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( WriteSecuRegCycleTime ) ){

        SRAM23LC_RDSCUR( &gDataBuffer );

        // Check security register LDSO bit
        if( (gDataBuffer & FLASH_LDSO_MASK) == FLASH_LDSO_MASK )
                return Msg23lc1024Success;
        else
                return Msg23lc1024Failure;
    }
    else
        return Msg23lc1024TimeOut;

}
/*
 * Function:       SRAM23LC_RDCR
 * Arguments:      ConfigReg, 8 bit buffer to store Configuration register value
 * Description:    The RDCR instruction is for reading Configuration Register Bits.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RDCR( uint8_t *ConfigReg )
{
    uint8_t  gDataBuffer;

    // Chip select go low to start a flash command
    setCSLow();

    // Send command
    SendByte( FLASH_CMD_RDCR, SIO );
    gDataBuffer = GetByte( SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    *ConfigReg = gDataBuffer;

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_READ
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    The READ instruction is for reading data out.
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_READ( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Chip select go low to start a flash command
    setCSLow();

    // Write READ command and address
    SendByte( FLASH_CMD_READ, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );

    // Set a loop to read data into buffer
    for( index=0; index < byte_length; index++ )
    {
        // Read data one byte at a time
        *(target_address + index) = GetByte( SIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_2READ
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    The 2READ instruction enable double throughput of Serial
 *                 Flash in read mode
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_2READ( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;
    uint8_t  dc;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    dc = GetDummyCycle( DUMMY_CONF_2READ );

    // Chip select go low to start a flash command
    setCSLow();

    // Write 2-I/O Read command and address
    SendByte( FLASH_CMD_2READ, SIO );
    SendFlashAddr( flash_address, DIO, addr_4byte_mode );
    InsertDummyCycle( dc );                    // Wait 4 dummy cycle

    // Set a loop to read data into data buffer
    for( index=0; index < byte_length; index++ )
    {
        *(target_address + index) = GetByte( DIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_4READ
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    The 4READ instruction enable quad throughput of
 *                 Serial Flash in read mode.
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashQuadNotEnable, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_4READ( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index=0;
    uint8_t  addr_4byte_mode;
    uint8_t  dc;


    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

#ifndef NO_QE_BIT
    // Check QE bit
    if( IsFlashQIO() != TRUE )  return Msg23lc1024QuadNotEnable;
#endif

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

     // get dummy cycle number
    dc = GetDummyCycle( DUMMY_CONF_4READ );

    // Chip select go low to start a flash command
    setCSLow();

    // Write 4-I/O Read Array command
    SendByte( FLASH_CMD_4READ, SIO );
    SendFlashAddr( flash_address, QIO, addr_4byte_mode );
    InsertDummyCycle ( dc );            // Wait 6 or 8 dummy cycle

    // Set a loop to read data into flash's buffer
    for( index=0; index < byte_length; index=index + 1 )
    {
        *(target_address + index) = GetByte( QIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_DREAD
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    The DREAD instruction enable double throughput of Serial
 *                 Flash in read mode
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_DREAD( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;
    uint8_t  dc;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;    // 4-byte mode
    else
        addr_4byte_mode = FALSE;   // 3-byte mode

    // get dummy cycle number
    dc = GetDummyCycle( DUMMY_CONF_DREAD );

    // Chip select go low to start a flash command
    setCSLow();

    // Write 2-I/O Read command and address
    SendByte( FLASH_CMD_DREAD, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );
    InsertDummyCycle( dc );                    // Wait 8 dummy cycle

    // Set a loop to read data into data buffer
    for( index=0; index < byte_length; index++ )
    {
        *(target_address + index) = GetByte( DIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_QREAD
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    The QREAD instruction enable quad throughput of
 *                 Serial Flash in read mode.
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashQuadNotEnable, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_QREAD( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index=0;
    uint8_t  addr_4byte_mode;
    uint8_t  dc;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check QE bit
    if( IsFlashQIO() != TRUE )  return Msg23lc1024QuadNotEnable;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // get dummy cycle number
    dc = GetDummyCycle( DUMMY_CONF_QREAD );

    // Chip select go low to start a flash command
    setCSLow();

    // Write 4-I/O Read Array command
    SendByte( FLASH_CMD_QREAD, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );
    InsertDummyCycle ( dc );            // Wait 8 dummy cycle

    // Set a loop to read data into flash's buffer
    for( index=0; index < byte_length; index=index+1)
    {
        *(target_address + index) = GetByte( QIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_FASTREAD
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    The FASTREAD instruction is for quickly reading data out.
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_FASTREAD( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;
    uint8_t  dc;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    dc = GetDummyCycle( DUMMY_CONF_FASTREAD );

    // Chip select go low to start a flash command
    setCSLow();

    // Write Fast Read command, address and dummy cycle
    SendByte( FLASH_CMD_FASTREAD, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );
    InsertDummyCycle ( dc );          // Wait dummy cycle

    // Set a loop to read data into data buffer
    for( index=0; index < byte_length; index++ )
    {
        *(target_address + index) = GetByte( SIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_RDSFDP
 * Arguments:      flash_address, 32 bit flash memory address
 *                 target_address, buffer address to store returned data
 *                 byte_length, length of returned data in byte unit
 * Description:    RDSFDP can retrieve the operating characteristics, structure
 *                 and vendor-specified information such as identifying information,
 *                 memory size, operating voltages and timinginformation of device
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RDSFDP( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Chip select go low to start a flash command
    setCSLow();

    // Write Read SFDP command
    SendByte( FLASH_CMD_RDSFDP, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );
    InsertDummyCycle ( 8 );        // Insert dummy cycle

    // Set a loop to read data into data buffer
    for( index=0; index < byte_length; index++ )
    {
        *(target_address + index) = GetByte( SIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Program Command
 */
/*
 * Function:       SRAM23LC_WREN
 * Arguments:      None.
 * Description:    The WREN instruction is for setting
 *                 Write Enable Latch (WEL) bit.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_WREN( void )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write Enable command = 0x06, Setting Write Enable Latch Bit
    SendByte( FLASH_CMD_WREN, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_WRDI
 * Arguments:      None.
 * Description:    The WRDI instruction is to reset
 *                 Write Enable Latch (WEL) bit.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_WRDI( void )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write Disable command = 0x04, resets Write Enable Latch Bit
    SendByte( FLASH_CMD_WRDI, SIO );

    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_PP
 * Arguments:      flash_address, 32 bit flash memory address
 *                 source_address, buffer address of source data to program
 *                 byte_length, byte length of data to programm
 * Description:    The PP instruction is for programming
 *                 the memory to be "0".
 *                 The device only accept the last 256 byte ( or 32 byte ) to program.
 *                 If the page address ( flash_address[7:0] ) reach 0xFF, it will
 *                 program next at 0x00 of the same page.
 *                 Some products have smaller page size ( 32 byte )
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashIsBusy, Msg23lc1024FlashOperationSuccess,
 *                 Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_PP( uint32_t flash_address, uint8_t *source_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    // Write Page Program command
    SendByte( FLASH_CMD_PP, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );

    // Set a loop to down load whole page data into flash's buffer
    // Note: only last 256 byte ( or 32 byte ) will be programmed
    for( index=0; index < byte_length; index++ )
    {
        SendByte( *(source_address + index), SIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( PageProgramCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;
}
/*
 * Function:       SRAM23LC_4PP
 * Arguments:      flash_address, 32 bit flash memory address
 *                 source_address, buffer address of source data to program
 *                 byte_length, byte length of data to programm
 * Description:    The 4PP instruction is for programming
 *                 the memory to be "0".
 *                 The device only accept the last 256 byte ( one page ) to program.
 *                 If the page address ( flash_address[7:0] ) reach 0xFF, it will
 *                 program next at 0x00 of the same page.
 *                 The different between QPP and 4PP is the IO number during sending address
 * Return Message: Msg23lc1024FlashQuadNotEnable, Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashIsBusy,
 *                 Msg23lc1024FlashOperationSuccess, Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_4PP( uint32_t flash_address, uint8_t *source_address, uint32_t byte_length )
{
    uint32_t index;
    uint8_t  addr_4byte_mode;

    // Check QE bit
    if( !IsFlashQIO() ) return Msg23lc1024QuadNotEnable;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    // Write 4-I/O Page Program command
    SendByte( FLASH_CMD_4PP, SIO );
    SendFlashAddr( flash_address, QIO, addr_4byte_mode );

    // Send source data to flash.
    for( index=0; index < byte_length; index++ )
    {
        SendByte( *(source_address + index), QIO );
    }

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( PageProgramCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;
}
/*
 * Function:       SRAM23LC_SE
 * Arguments:      flash_address, 32 bit flash memory address
 * Description:    The SE instruction is for erasing the data
 *                 of the chosen sector (4KB) to be "1".
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashIsBusy, Msg23lc1024FlashOperationSuccess,
 *                 Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_SE( uint32_t flash_address )
{
    uint8_t  addr_4byte_mode;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    //Write Sector Erase command = 0x20;
    SendByte( FLASH_CMD_SE, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( SectorEraseCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;
}
/*
 * Function:       SRAM23LC_BE32K
 * Arguments:      flash_address, 32 bit flash memory address
 * Description:    The BE32K instruction is for erasing the data
 *                 of the chosen sector (32KB) to be "1".
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashIsBusy, Msg23lc1024FlashOperationSuccess,
 *                 Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_BE32K( uint32_t flash_address )
{
    uint8_t  addr_4byte_mode;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    //Write Block Erase32KB command;
    SendByte( FLASH_CMD_BE32K, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( BlockErase32KCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;
}
/*
 * Function:       SRAM23LC_BE
 * Arguments:      flash_address, 32 bit flash memory address
 * Description:    The BE instruction is for erasing the data
 *                 of the chosen sector (64KB) to be "1".
 * Return Message: Msg23lc1024FlashAddressInvalid, Msg23lc1024FlashIsBusy, Msg23lc1024FlashOperationSuccess,
 *                 Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_BE( uint32_t flash_address )
{
    uint8_t  addr_4byte_mode;

    // Check flash address
    if( flash_address > FlashSize ) return Msg23lc1024Invalid;

    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Check 3-byte or 4-byte mode
    if( IsFlash4Byte() )
        addr_4byte_mode = TRUE;  // 4-byte mode
    else
        addr_4byte_mode = FALSE; // 3-byte mode

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    //Write Block Erase command = 0xD8;
    SendByte( FLASH_CMD_BE, SIO );
    SendFlashAddr( flash_address, SIO, addr_4byte_mode );

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( BlockEraseCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;
}
/*
 * Function:       SRAM23LC_CE
 * Arguments:      None.
 * Description:    The CE instruction is for erasing the data
 *                 of the whole chip to be "1".
 * Return Message: Msg23lc1024FlashIsBusy, Msg23lc1024FlashOperationSuccess, Msg23lc1024FlashTimeOut
 */
ReturnMsg23lc1024 SRAM23LC_CE( void )
{
    // Check flash is busy or not
    if( IsFlashBusy() )    return Msg23lc1024Busy;

    // Setting Write Enable Latch bit
    SRAM23LC_WREN();

    // Chip select go low to start a flash command
    setCSLow();

    //Write Chip Erase command = 0x60;
    SendByte( FLASH_CMD_CE, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    if( WaitFlashReady( ChipEraseCycleTime ) )
        return Msg23lc1024Success;
    else
        return Msg23lc1024TimeOut;
}
/*
 * Function:       SRAM23LC_DP
 * Arguments:      None.
 * Description:    The DP instruction is for setting the
 *                 device on the minimizing the power consumption.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_DP( void )
{
    // Wake up flash in case the device is in deep power down mode already.
    setCSLow();
    InsertDummyCycle ( 20*8 );        // wait for tCRDP=20us  (20 x 8 bit / 8Mbps)
    setCSHigh();
    InsertDummyCycle ( 30*8 );        // wait for tRDP=35us (20 x 8 bit / 8Mbps)
    InsertDummyCycle ( 5*8 );     
	
	// Chip select go low to start a flash command
    setCSLow();

    // Deep Power Down Mode command
    SendByte( FLASH_CMD_DP, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_ENSO
 * Arguments:      None.
 * Description:    The ENSO instruction is for entering the secured OTP mode.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_ENSO( void )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write ENSO command
    SendByte( FLASH_CMD_ENSO, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_EXSO
 * Arguments:      None.
 * Description:    The EXSO instruction is for exiting the secured OTP mode.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_EXSO( void )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write EXSO command = 0xC1
    SendByte( FLASH_CMD_EXSO, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_SBL
 * Arguments:      burstconfig, burst length configuration
 * Description:    To set the Burst length
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_SBL( uint8_t burstconfig )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Send SBL command and config data
    SendByte( FLASH_CMD_SBL, SIO );
    SendByte( burstconfig, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_RSTEN
 * Arguments:      None.
 * Description:    Enable RST command
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RSTEN( void )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write RSTEN command
    SendByte( FLASH_CMD_RSTEN, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_RST
 * Arguments:      fsptr, pointer of flash status structure
 * Description:    The RST instruction is used as a system (software) reset that
 *                 puts the device in normal operating Ready mode.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_RST( FlashStatus *fsptr )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write RST command = 0x99
    SendByte(  FLASH_CMD_RST, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    // Reset current state
    fsptr->ArrangeOpt = FALSE;
    fsptr->ModeReg = 0x00;

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_PGM_ERS_S
 * Arguments:      None
 * Description:    The PGM_ERS_S suspend Sector-Erase, Block-Erase or
 *                 Page-Program operations and conduct other operations.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_PGM_ERS_S( void )
{

    // Chip select go low to start a flash command
    setCSLow();

    // Send program/erase suspend command
    SendByte( FLASH_CMD_PGM_ERS_S, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_PGM_ERS_R
 * Arguments:      None
 * Description:    The PGM_ERS_R resume Sector-Erase, Block-Erase or
 *                 Page-Program operations.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_PGM_ERS_R( void )
{

    // Chip select go low to start a flash command
    setCSLow();

    // Send resume command
    SendByte( FLASH_CMD_PGM_ERS_R, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}
/*
 * Function:       SRAM23LC_NOP
 * Arguments:      None.
 * Description:    The NOP instruction is null operation of flash.
 * Return Message: Msg23lc1024FlashOperationSuccess
 */
ReturnMsg23lc1024 SRAM23LC_NOP( void )
{
    // Chip select go low to start a flash command
    setCSLow();

    // Write NOP command = 0x00
    SendByte( FLASH_CMD_NOP, SIO );

    // Chip select go high to end a flash command
    setCSHigh();

    return Msg23lc1024Success;
}

