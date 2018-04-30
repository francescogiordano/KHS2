#ifndef    S23LC1024_H
#define    S23LC1024_H

#include <stdbool.h>
#include <stdint.h>
#include "bg_types.h"

#include "halconfig_23lc1024.h"

#include "payloadbuffer.h"


#define SRAM23LC1024

/* Note:
   Synchronous IO     : MCU will polling WIP bit after
                        sending prgram/erase command
   Non-synchronous IO : MCU can do other operation after
                        sending prgram/erase command
   Default is synchronous IO
*/
//#define    NON_SYNCHRONOUS_IO

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
#define    BYTE_LEN         8
#define    IO_MASK          0x80
#define    HALF_WORD_MASK	0x0000ffff

/*
  Flash Related Parameter Define
*/

#define    Block_Offset       0x10000     // 64K Block size
#define    Block32K_Offset    0x8000      // 32K Block size
#define    Sector_Offset      0x1000      // 4K Sector size
#define    Page_Offset        0x0100      // 256 Byte Page size
#define    Page32_Offset      0x0020      // 32 Byte Page size (some products have smaller page size)
#define    Block_Num          (FlashSize / Block_Offset)

// Flash control register mask define
// status register
#define    FLASH_WIP_MASK         0x01
#define    FLASH_LDSO_MASK        0x02
#define    FLASH_QE_MASK          0x40
// security register
#define    FLASH_OTPLOCK_MASK     0x03
#define    FLASH_4BYTE_MASK       0x04
#define    FLASH_WPSEL_MASK       0x80
// configuration reigster
#define    FLASH_DC_MASK          0x80
#define    FLASH_DC_2BIT_MASK     0xC0
// other
#define    BLOCK_PROTECT_MASK     0xff
#define    BLOCK_LOCK_MASK        0x01

/*
  System Information Define
*/
#define    CLK_PERIOD                26 // unit: ns
#define    Min_Cycle_Per_Inst        1  // cycle count of one instruction
#define    One_Loop_Inst             10 // instruction count of one loop (estimate)

/*
  Flash ID, Timing Information Define
  (The following information could get from device specification)
*/

#ifdef SRAM23LC1024
#define    FlashID          0xc22814
#define    ElectronicID     0x14
#define    RESID0           0xc214
#define    RESID1           0x14c2
#define    FlashSize        0x100000       // 1 MB
#define    CE_period        15625000       // tCE /  ( CLK_PERIOD * Min_Cycle_Per_Inst *One_Loop_Inst)
#define    tW               40000000       // 40ms
#define    tDP              10000          // 10us
#define    tBP              100000         // 100us
#define    tPP              10000000       // 10ms
#define    tSE              240000000      // 240ms
#define    tBE32            1750000000     // 1.75s
#define    tBE              3500000000     // 3.5s
#define    tPUW             10000000       // 10ms
#define    tWSR             tBP
// Support I/O mode
#define    SIO              0
#define    DIO              1
#define    QIO              2
#endif

// dummy cycle configration
#ifdef DUMMY_CONF_2

#define    DUMMY_CONF_2READ       0x08040804
#define    DUMMY_CONF_4READ       0x0A080406
#define    DUMMY_CONF_FASTREAD    0x08080808
#define    DUMMY_CONF_DREAD       0x08080808
#define    DUMMY_CONF_QREAD       0x08080808

#else

#define    DUMMY_CONF_2READ       0x0A080604
#define    DUMMY_CONF_4READ       0x0A080406
#define    DUMMY_CONF_FASTREAD    0x0A080608
#define    DUMMY_CONF_DREAD       0x0A080608
#define    DUMMY_CONF_QREAD       0x0A080608

#endif

// Flash information define
#define    WriteStatusRegCycleTime     tW / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#define    PageProgramCycleTime        tPP / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#define    SectorEraseCycleTime        tSE / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#define    BlockEraseCycleTime         tBE / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#define    ChipEraseCycleTime          CE_period
#define    FlashFullAccessTime         tPUW / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)

#ifdef tBP
#define    ByteProgramCycleTime        tBP / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#endif
#ifdef tWSR
#define    WriteSecuRegCycleTime       tWSR / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#endif
#ifdef tBE32
#define    BlockErase32KCycleTime      tBE32 / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#endif
#ifdef tWREAW
#define    WriteExtRegCycleTime        tWREAW / (CLK_PERIOD * Min_Cycle_Per_Inst * One_Loop_Inst)
#endif

/*** SRAM23LC series command hex code definition ***/
//ID commands
#define    FLASH_CMD_RDID      0x9F    //RDID (Read Identification)
#define    FLASH_CMD_RES       0xAB    //RES (Read Electronic ID)
#define    FLASH_CMD_REMS      0x90    //REMS (Read Electronic & Device ID)

//Register commands
#define    FLASH_CMD_WRSR      0x01    //WRSR (Write Status Register)
#define    FLASH_CMD_RDSR      0x05    //RDSR (Read Status Register)
#define    FLASH_CMD_WRSCUR    0x2F    //WRSCUR (Write Security Register)
#define    FLASH_CMD_RDSCUR    0x2B    //RDSCUR (Read Security Register)
#define    FLASH_CMD_RDCR      0x15    //RDCR (Read Configuration Register)

//READ commands
#define    FLASH_CMD_READ        0x03    //READ (1 x I/O)
#define    FLASH_CMD_2READ       0xBB    //2READ (2 x I/O)
#define    FLASH_CMD_4READ       0xEB    //4READ (4 x I/O)
#define    FLASH_CMD_FASTREAD    0x0B    //FAST READ (Fast read data)
#define    FLASH_CMD_DREAD       0x3B    //DREAD (1In/2 Out fast read)
#define    FLASH_CMD_QREAD       0x6B    //QREAD (1In/4 Out fast read)
#define    FLASH_CMD_RDSFDP      0x5A    //RDSFDP (Read SFDP)

//Program commands
#define    FLASH_CMD_WREN     0x06    //WREN (Write Enable)
#define    FLASH_CMD_WRDI     0x04    //WRDI (Write Disable)
#define    FLASH_CMD_PP       0x02    //PP (page program)
#define    FLASH_CMD_4PP      0x38    //4PP (Quad page program)

//Erase commands
#define    FLASH_CMD_SE       0x20    //SE (Sector Erase)
#define    FLASH_CMD_BE32K    0x52    //BE32K (Block Erase 32kb)
#define    FLASH_CMD_BE       0xD8    //BE (Block Erase)
#define    FLASH_CMD_CE       0x60    //CE (Chip Erase) hex code: 60 or C7

//Mode setting commands
#define    FLASH_CMD_DP       0xB9    //DP (Deep Power Down)
#define    FLASH_CMD_ENSO     0xB1    //ENSO (Enter Secured OTP)
#define    FLASH_CMD_EXSO     0xC1    //EXSO  (Exit Secured OTP)
#ifdef SBL_CMD_0x77
#define    FLASH_CMD_SBL      0x77    //SBL (Set Burst Length) new: 0x77
#else
#define    FLASH_CMD_SBL      0xC0    //SBL (Set Burst Length) Old: 0xC0
#endif

//Reset commands
#define    FLASH_CMD_RSTEN     0x66    //RSTEN (Reset Enable)
#define    FLASH_CMD_RST       0x99    //RST (Reset Memory)

//Security commands
#ifdef LCR_CMD_0xDD_0xD5
#else
#endif

//Suspend/Resume commands
#define    FLASH_CMD_PGM_ERS_S    0xB0    //PGM/ERS Suspend (Suspends Program/Erase)
#define    FLASH_CMD_PGM_ERS_R    0x30    //PGM/ERS Erase (Resumes Program/Erase)
#define    FLASH_CMD_NOP          0x00    //NOP (No Operation)

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

//*****************************   STRUCTURES   ********************************

// Flash status structure define
struct sFlashStatus{
    /* Mode Register:
     * Bit  Description
     * -------------------------
     *  7   RYBY enable
     *  6   Reserved
     *  5   Reserved
     *  4   Reserved
     *  3   Reserved
     *  2   Reserved
     *  1   Parallel mode enable
     *  0   QPI mode enable
    */
    uint8_t    ModeReg;
    bool     ArrangeOpt;
};

typedef struct sFlashStatus FlashStatus;

//**************************   FUNCTION DECLARATIONS   ************************

void Set23lc1024(void);
void Init23lc1024(void);
bool Detect23lc1024(void);

void WritePayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize);
void ReadPayload23lc1024(PAYLOAD_BUFFER_Header_t header, uint8_t* dataBytes, int dataSize);

void writeBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize);
void readBytes23lc1024(uint8_t* addressBytes3, uint8_t* dataBytes, int dataSize);

void rstio23lc1024(void);
void rdmr23lc1024(void);


/* Flash commands */
ReturnMsg23lc1024 SRAM23LC_RDID( uint32_t *Identification );
ReturnMsg23lc1024 SRAM23LC_RES( uint8_t *ElectricIdentification );
ReturnMsg23lc1024 SRAM23LC_REMS( uint16_t *REMS_Identification, FlashStatus *fsptr );

ReturnMsg23lc1024 SRAM23LC_RDSR( uint8_t *StatusReg );
#ifdef SUPPORT_WRSR_CR
   ReturnMsg23lc1024 SRAM23LC_WRSR( uint16_t UpdateValue );
#else
   ReturnMsg23lc1024 SRAM23LC_WRSR( uint8_t UpdateValue );
#endif
ReturnMsg23lc1024 SRAM23LC_RDSCUR( uint8_t *SecurityReg );
ReturnMsg23lc1024 SRAM23LC_WRSCUR( void );
ReturnMsg23lc1024 SRAM23LC_RDCR( uint8_t *ConfigReg );

ReturnMsg23lc1024 SRAM23LC_READ( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length  );
ReturnMsg23lc1024 SRAM23LC_2READ( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length );
ReturnMsg23lc1024 SRAM23LC_4READ( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length );
ReturnMsg23lc1024 SRAM23LC_FASTREAD( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length );
ReturnMsg23lc1024 SRAM23LC_DREAD( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length );
ReturnMsg23lc1024 SRAM23LC_QREAD( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length );
ReturnMsg23lc1024 SRAM23LC_RDSFDP( uint32_t flash_address, uint8_t *target_address, uint32_t byte_length );

ReturnMsg23lc1024 SRAM23LC_WREN( void );
ReturnMsg23lc1024 SRAM23LC_WRDI( void );
ReturnMsg23lc1024 SRAM23LC_PP( uint32_t flash_address, uint8_t *source_address, uint32_t byte_length );
ReturnMsg23lc1024 SRAM23LC_4PP( uint32_t flash_address, uint8_t *source_address, uint32_t byte_length );

ReturnMsg23lc1024 SRAM23LC_SE( uint32_t flash_address );
ReturnMsg23lc1024 SRAM23LC_BE32K( uint32_t flash_address );
ReturnMsg23lc1024 SRAM23LC_BE( uint32_t flash_address );
ReturnMsg23lc1024 SRAM23LC_CE( void );

ReturnMsg23lc1024 SRAM23LC_DP( void );
ReturnMsg23lc1024 SRAM23LC_ENSO( void );
ReturnMsg23lc1024 SRAM23LC_EXSO( void );
ReturnMsg23lc1024 SRAM23LC_SBL( uint8_t burstconfig );

ReturnMsg23lc1024 SRAM23LC_RSTEN( void );
ReturnMsg23lc1024 SRAM23LC_RST( FlashStatus *fsptr );

ReturnMsg23lc1024 SRAM23LC_PGM_ERS_S( void );
ReturnMsg23lc1024 SRAM23LC_PGM_ERS_R( void );
ReturnMsg23lc1024 SRAM23LC_NOP( void );

#endif    // end of S23LC1024_H

