/******************************************************************************
* Project Name		: CY15FRAMKIT-002
* Version		: 1.1
* IDE Used				: Keil uVision 5.23
* Related Hardware	: NUCLEO-L433RC-P
*******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges.
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement.
*******************************************************************************/
/** @file qspiFRAM.h
 *	
 *	@brief Header File for accessing QSPI FRAM opcodes
 *	@author	NILE
 *	@date 6/22/2018	
 *	Rev 1.1
 */
 
/* Include files																															*/
/******************************************************************************/
#include <stdbool.h>
#include "stm32l4xx_hal.h"

/******************************************************************************/


/******************************************************************************/
/* Device Opcodes																														 */
/******************************************************************************/
/**
 *	@defgroup Device_Opcodes Quad SPI Opcodes
 *	@brief Supported opcodes in this revision of API set
 *	 
 
 
 *@ingroup Device_Opcodes
	* group codes
	*	@{
	 *	
	 */
#define RDSR1									 	0x05 	
#define RDSR2									 	0x07	
#define RDCR1									 	0x35	
#define RDCR2									 	0x3F	
#define RDCR4									 	0x45	
#define RDCR5									 	0x5E	

#define WRR											0x01
#define WRAR										0x71
#define RDAR										0x65

#define DID										 	0x9F
#define RDSN										0xC3
#define WRSN										0xC2
#define RUID										0x4C


#define WRITE_ENABLE_CMD				0x06
#define WRITE_DISABLE_CMD			 	0x04

#define WRITE									 	0x02
#define FAST_WRITE							0xDA
#define DIW											0xA2
#define DIOW										0xA1
#define QIW											0x32
#define QIOW										0xD2
#define DDRWRITE								0xDE					/**Note: Not tested in Ver 1.0*/
#define DDRFWRITE								0xDD					/**Note: Not tested in Ver 1.0*/
#define DDRQIOW									0xD1					/**Note: Not tested in Ver 1.0*/

#define READ										0x03
#define FAST_READ								0x0B
#define DOR_READ								0x3B
#define DIOR_READ								0xBB
#define QOR_READ								0x6B
#define QIOR_READ								0xEB
#define DDRFAST_READ						0x0D					/**Note: Not tested in Ver 1.0*/

 /** @} END of Device_Opcodes*/

/******************************************************************************/
/* Mask options																															*/
/******************************************************************************/
/**
 *	@defgroup Mask_Options Register Mask and Shift definition
 *	@brief Mask Options for performing Bit operations
 *	 
 
 
 *@ingroup Mask_Options
	* group codes
	*	@{
	 *	
	 */
#define Reg_Lat_Pos				6
#define Mem_Lat_Pos				4
#define Quad_Bit_Pos			1
#define Block_Prot_Pos		2
#define TBProt_Pos				5

#define Reg_Lat_Mask_And			0XC0
#define Mem_Lat_Mask_And			0XF0
#define Block_Prot_Mask_And		0X1C
#define TBProt_Mask_And				0X20


 /** @} END of Mask_Options*/
/******************************************************************************/
/* Function call return status																								*/
/******************************************************************************/
#define IsEnabled					(1u) 	
#define IsNotEnabled			(0u) 

#define OperationSuccess	(1u) 	
#define OperationFail			(0u) 

/******************************************************************************/
/* For testing only																													 */
/******************************************************************************/
#define packetsize	6

/******************************************************************************/
/* Timeout delays for QSPI transmit and receive functions																											*/
/******************************************************************************/
#define timeout_1us	(1)
#define timeout_20us	(20)


/******************************************************************************/
/* Device register addresses																									*/
/******************************************************************************/
/**
 *	@defgroup Register_Addresses Register Addresses
 *	@brief 24-bit Register Address in the F-RAM Device
 *	 
 
 
* @ingroup Register_Addresses
	* group codes
	*	@{
	 *	
	 */
#define SR1_Address	0x00000000
#define SR2_Address	0x00000001
#define CR1_Address	0x00000002
#define CR2_Address	0x00000003
#define CR4_Address	0x00000005
#define CR5_Address	0x00000006
/******************************************************************************/
 /** @} END of Register_Addresses*/

/******************************************************************************/
/* Enum for Device operation mode																						 */
/******************************************************************************/
typedef enum
{
		SPI		 = 0U,		/**< Normal SPI mode. */
		DPI		 = 1U,		/**< Dual SPI mode. */
		QPI		 = 2U,		/**< Quad SPI mode. */
	
} device_mode;
/******************************************************************************/


/******************************************************************************/
/* Structure needed to hold status of QSPI FRAM.															*/
/* Declare a global extern variable of type "operating_mode" in main.c				*/
/* to enable access of modes accross functions																*/
/******************************************************************************/


/**
 *	@defgroup operating_mode Operating Mode Structure
 *	@brief This structure holds the global status of the FRAM device in the system. It should be declared as an extern variable in main.c
 *	Declare a global extern variable of type "operating_mode" in main.c to enable access of modes accross functions		
 *	@ingroup operating_mode
 *	
 *	 @{
 *	
 *	
 */
typedef struct
{
		uint8_t mode;							/**	Can be 0, 1 or 2 for SPI, DPI or QPI. */
		uint32_t opcode_width;		/**Number of IOs on which Opcode is trasmitted */																																	
		uint32_t add_width;				/**Number of IOs on which Address is trasmitted */	 
		uint32_t data_width;			/**Number of IOs on which Data is trasmitted */
		uint32_t mode_width;			/**Number of IOs on which Mode byte is trasmitted */
	 
		
		uint8_t read_opcode;			/**This field is not used in current implementation */		
		uint8_t write_opcode;			/**This field is not used in current implementation */	
		uint8_t ID_Reg[8];				/**This field will store the Factory program ID register value. 					*/
															/**The dafault ID reg for the device mounted on Kit is 0x505182067F7F7F7F	*/	
															/**The Reset Interface API in this driver compares the ID register value against this default value to correctly determine 	*/
															/**and reset the operating mode of the device				*/
	
		uint8_t UID_Reg[8];				/**This field will store the Factory program UID register value. 					*/
		uint8_t SN_Reg[8];				/**This field Is used by the APIs to store the current Serial Number of the device	*/
		uint8_t SR1_Reg;					/**This field Is used by the APIs to store the current Status Register 1 value of the device	*/
		uint8_t SR2_Reg;					/**This field Is used by the APIs to store the current Status Register 2 value of the device	*/
		uint8_t CR1_Reg;					/**This field Is used by the APIs to store the current Configuration	Register 1 value of the device	*/
		uint8_t CR2_Reg;					/**This field Is used by the APIs to store the current Configuration	Register 2 value of the device	*/
		uint8_t CR4_Reg;					/**This field Is used by the APIs to store the current Configuration	Register 4 value of the device	*/
		uint8_t CR5_Reg;					/**This field Is used by the APIs to store the current Configuration	Register 5 value of the device	*/
		uint8_t Reg_Latency;			/**This field Is used by the APIs to store the current Register read latency value of the device	*/
		uint8_t Memory_Latency;		/**This field Is used by the APIs to store the current Memory read latency value of the device	*/
		uint8_t PROT_Direction;		/**This field Is used by the APIs to store the current TB_PROT setting value of the device	*/
		uint8_t PROTECT_MEM;			/**This field Is used by the APIs to store the current BP value of the device	*/
		uint8_t QUAD_BIT;					/**This field Is used by the APIs to store the current Quad bit value of the device	*/
		uint8_t QPI_DPI;					/**This field Is used by the APIs to store the current QPI and DPI bit values of the device	*/
		
} operating_mode;			

 /** } END of operating_mode*/

/******************************************************************************/
/* Function Prototypes 																												*/
/******************************************************************************/

/************************************************************************************/
/* bool FRAM_Interface_Reset(void);																									*/
/*This API Resets the device interface by writing 0x00 to all Registers							*/
/* This is achieved by sending Register write command in all modes (SPI, DPI and QPI*/
/* This API uses the factory default value of ID reg. 															*/
/* If your device has a different ID register value, please update this API					*/
/************************************************************************************/
bool FRAM_Interface_Reset(void);


/************************************************************************************/
/* void Read_Device_Status(void);																										*/
/* This API reads the status of all registers in the device. 												*/
/* This API should be executed only after knowing the operating mode of the device	*/
/* User FRAM_Interface_Reset API prior to executing Read_Device_Status()						*/
/************************************************************************************/

void Read_Device_Status(void);

/********************************************************************************************/
/* This API reads the ID register of device.																								*/
/* The operating mode is defined by IOMode	and register by Latency Reg_Lat 								*/
/* The API compares ID register value with Factor default value of 0x505182067F7F7F7F 			*/
/* If user is using an FRAM device with different ID register value, please update this API	*/
/********************************************************************************************/

bool Read_ID(uint8_t IOMode, uint8_t Reg_lat);


/******************************************************************************/
/* Function Prototypes for Device Write Dnable/Disable APIs									 */
/******************************************************************************/
void FRAM_WREN(void);
void FRAM_WRDI(void);


/******************************************************************************/
/* Function Prototypes for Register access APIs															 */
/******************************************************************************/
void FRAM_RDSR1 (uint8_t *StatusReg);
void FRAM_RDSR2 (uint8_t *StatusReg);
void FRAM_RDCR1 (uint8_t *ConfigReg);
void FRAM_RDCR2 (uint8_t *ConfigReg);
void FRAM_RDCR4 (uint8_t *ConfigReg);
void FRAM_RDCR5 (uint8_t *ConfigReg);

void FRAM_RDSN (void);
void FRAM_WRSN (uint8_t *SNreg);
void FRAM_DID (uint8_t *IDreg);
void FRAM_RUID (uint8_t *IDreg);


/******************************************************************************/
/* Function Prototypes for Memory Write opcodes in Single Data Rate mode			*/
/* Memory write commands will fail if the WEL latch is not set in device			*/
/******************************************************************************/
bool FRAM_Write(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_Fast_Write(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_DIW(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_DIOW(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_QIW(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_QIOW(uint32_t address, uint8_t *write_data, uint32_t write_length);


/******************************************************************************/
/* Function Prototypes for Memory Write opcodes in Double Data Rate mode			*/
/* Memory write commands will fail if the WEL latch is not set in device			*/
/* These APIs have not been fully tested in Ver 1.0 of this driver. 					*/
/******************************************************************************/
bool FRAM_DDRWrite(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_DDRQIOW(uint32_t address, uint8_t *write_data, uint32_t write_length);
bool FRAM_DDRFastWrite(uint32_t address, uint8_t *write_data, uint32_t write_length);


/******************************************************************************/
/* Function Prototypes for Memory Read opcodes in Single Data Rate mode			*/
/******************************************************************************/
bool FRAM_Read(uint32_t address, uint8_t *read_data, uint32_t read_length);
bool FRAM_FastRead(uint32_t address, uint8_t *read_data, uint32_t read_length);
bool FRAM_DORRead(uint32_t address, uint8_t *read_data, uint32_t read_length);
bool FRAM_DIORRead(uint32_t address, uint8_t *read_data, uint32_t read_length);
bool FRAM_QORRead(uint32_t address, uint8_t *read_data, uint32_t read_length);
bool FRAM_QIORRead(uint32_t address, uint8_t *read_data, uint32_t read_length);


/******************************************************************************/
/* Function Prototypes for Memory Read opcodes in Double Data Rate mode			*/
/* These APIs have not been fully tested in Ver 1.0 of this driver. 					*/
/******************************************************************************/
bool FRAM_DDRFastRead(uint32_t address, uint8_t *read_data, uint32_t read_length);



/******************************************************************************/
/* This API will be documented in Ver 2.0 of this driver											*/
/******************************************************************************/
device_mode Detect_Mode(void);


/******************************************************************************/
/* Function Prototypes for Register Write opcode (0x05)												*/
/* Rgister Write command will fail if the WEL latch is not set in device			*/
/******************************************************************************/
void FRAM_WRR(uint8_t *Register, uint8_t No_of_bytes);

/******************************************************************************/
/* Function Prototypes for Generic Register Write opcode (0x71)								*/
/* Rgister Write	will fail if the WEL latch is not set in device							*/
/******************************************************************************/
void FRAM_WRAR(uint32_t Reg_address, uint8_t *New_Reg_Data);

/******************************************************************************/
/* Function Prototypes for Generic Register Read opcode (0x65)								*/
/******************************************************************************/
void FRAM_RDAR(uint32_t Reg_address, uint8_t *New_Reg_Data);


/******************************************************************************/
/* Function Prototypes for Updating Memory Read latency value 								*/
/******************************************************************************/
bool FRAM_Set_Memory_Latency(uint8_t New_latency);

/******************************************************************************/
/* Function Prototypes for Updating Register Read latency value 							*/
/******************************************************************************/
bool FRAM_Set_Register_Latency(uint8_t New_latency);

/******************************************************************************/
/* Function Prototypes for reading Memory Read latency value 									*/
/******************************************************************************/
void FRAM_Get_Memory_Latency(void);


/******************************************************************************/
/* Function Prototypes for reading Register Read latency value 								*/
/******************************************************************************/
void FRAM_Get_Register_Latency(void);

/******************************************************************************/
/* Function Prototypes for Setting device operating mode to QPI								*/
/******************************************************************************/
void FRAM_QPIEN(void);

/******************************************************************************/
/* Function Prototypes for Setting device operating mode to DPI								*/
/******************************************************************************/
void FRAM_DPIEN(void);

/******************************************************************************/
/* Function Prototypes for Setting device operating mode to SPI								*/
/******************************************************************************/
void FRAM_SPIEN(void);


/******************************************************************************/
/* Function Prototypes for Setting QUAD bit																		*/
/******************************************************************************/
void FRAM_QUAD_ENABLE(void);


/******************************************************************************/
/* Function Prototypes for Re-setting QUAD bit																*/
/******************************************************************************/
void FRAM_QUAD_DISABLE(void);

/******************************************************************************/
/*End of File																																	*/
/******************************************************************************/
