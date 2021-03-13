/******************************************************************************
* Project Name		: CY15FRAMKIT-002
* Version			: 1.0
* IDE Used	    	: Keil uVision 5.23
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
 *  @brief Definition for accessing QSPI FRAM opcodes
 *  @author	NILE
 *  @date 1/22/2018  
 *  Rev 1.1
 */
 
/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/

#include "qspiFRAM.h"
#include "quadspi.h"
/******************************************************************************/

operating_mode FRAM;	//Global Varibale. Must be decalred as Extern in main.c

uint8_t databuffer[8192];	// For testing only

/************************************************************************************/
/* bool FRAM_Interface_Reset(void);																									*/
/* Return: OperationSuccess or OperationFail																				*/
/* This function Resets the device interface by writing 0x00 to all registers  					*/
/* This is achieved by sending register write command in all modes (SPI, DPI & QPI)	*/
/* This function uses the factory default value of ID reg. 															*/
/* If your device has a different ID register value, please update this function					*/
/* F-RAM device retains operating mode over power Cycles. It is recommended 				*/
/* to create a sub-routine as a part of initilization to ensure that device gets		*/
/* configured in a known mode.																											*/
/************************************************************************************/
	bool FRAM_Interface_Reset(void)
		
		{
					uint8_t Register[5] = {0x00, 0x00, 0x00, 0x00,0x00};
					FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
					FRAM.data_width			= QSPI_DATA_1_LINE;
					FRAM.add_width			= QSPI_ADDRESS_1_LINE;
					FRAM_WREN();
					FRAM_WRAR(SR1_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR1_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR2_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR4_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR5_Address, &Register[0]);
	
					
					//FRAM_WRR(Register,5);
					if(Read_ID(SPI,0)) 
						{
							FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
							FRAM.data_width			= QSPI_DATA_1_LINE;
							FRAM.add_width			= QSPI_ADDRESS_1_LINE;
							FRAM.mode_width			= QSPI_ALTERNATE_BYTES_1_LINE;		
							FRAM.mode = SPI;
							return OperationSuccess;
						}
						
					else
						{
							FRAM.opcode_width 	= QSPI_INSTRUCTION_2_LINES;	
							FRAM.data_width			= QSPI_DATA_2_LINES;
							FRAM.add_width			= QSPI_ADDRESS_2_LINES;
					FRAM_WREN();
					FRAM_WRAR(SR1_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR1_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR2_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR4_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR5_Address, &Register[0]);
							
							//FRAM_WRR(Register,5);
							
							FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
							FRAM.data_width			= QSPI_DATA_1_LINE;
							FRAM.add_width			= QSPI_ADDRESS_1_LINE;
							if(Read_ID(SPI,0)) 
								{
									FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
									FRAM.data_width			= QSPI_DATA_1_LINE;
									FRAM.add_width			= QSPI_ADDRESS_1_LINE;
									FRAM.mode_width			=QSPI_ALTERNATE_BYTES_1_LINE;
									return OperationSuccess;
								}
								else 
								{
											FRAM.opcode_width 	= QSPI_INSTRUCTION_4_LINES;	
											FRAM.data_width			= QSPI_DATA_4_LINES;
											FRAM.add_width			= QSPI_ADDRESS_4_LINES;
					FRAM_WREN();
					FRAM_WRAR(SR1_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR1_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR2_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR4_Address, &Register[0]);
					FRAM_WREN();
					FRAM_WRAR(CR5_Address, &Register[0]);
										//	FRAM_WRR(Register,5);
											FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
											FRAM.data_width			= QSPI_DATA_1_LINE;
											FRAM.add_width			= QSPI_ADDRESS_1_LINE;
											if(Read_ID(SPI,0)) 
											
											{
												FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
												FRAM.data_width			= QSPI_DATA_1_LINE;
												FRAM.add_width			= QSPI_ADDRESS_1_LINE;
												FRAM.mode_width			=QSPI_ALTERNATE_BYTES_1_LINE;
												return OperationSuccess;
											}
											else return OperationFail;					//This will never be executed
								
								}
						}
		}
		
/************************************************************************************/

		
/****************************************************************************************/
/* void Read_Device_Status(void)																												*/
/* Return: No Return value																															*/
/* This function reads the Status/Configuration register values into operating_mode variable */
/* This is achieved by sending register write command in all modes (SPI, DPI & QPI)			*/
/* This function assumes that the device is configured in a known mode												*/
/****************************************************************************************/

void Read_Device_Status(void)
{
		FRAM_RDSR1(&FRAM.SR1_Reg);
		FRAM_RDSR2(&FRAM.SR2_Reg);
		FRAM_RDCR1(&FRAM.CR1_Reg);	
		FRAM_RDCR2(&FRAM.CR2_Reg);	
		FRAM_RDCR4(&FRAM.CR4_Reg);
		FRAM_RDCR5(&FRAM.CR5_Reg);	
		FRAM_RDSN();
		FRAM.Memory_Latency		 = 	(FRAM.CR1_Reg & Mem_Lat_Mask_And)>>Mem_Lat_Pos;
		FRAM.Reg_Latency			 = 	(FRAM.CR5_Reg & Reg_Lat_Mask_And)>>Reg_Lat_Pos;	
		FRAM.PROTECT_MEM			 =	(FRAM.SR1_Reg & Block_Prot_Mask_And)>>Block_Prot_Pos;
		FRAM.PROT_Direction		 = 	(FRAM.SR1_Reg & TBProt_Mask_And) >> TBProt_Pos;	
}
/****************************************************************************************/


/****************************************************************************************/
/* bool Read_ID(uint8_t IOMode, uint8_t Reg_lat)																				*/
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint8_t IOMode  - Variable of type device_mode (SPI, DPI or QPI)					*/
/* Argument 2: uint8_t Reg_lat - Value used as register Latency to read ID reg. 				*/
/* Allowed Range : (0<=Reg_Lat<=3)																											*/
/* This function reads ID register of Device in mode IOMode with register Latency Reg_Lat	  */
/* function also compares the value with Factory default ID register value.									*/
/* This function needs to be updated for idregFactory varable for a new ID register value		*/
/* On successful match of ID register, this function configures part in correct access mode	*/
/****************************************************************************************/

bool Read_ID(uint8_t IOMode, uint8_t Reg_lat)
	
	{
	
		QSPI_CommandTypeDef sCommand;
		uint8_t idReg[8];
		uint8_t errors,i;
		uint8_t idregFactory[8] = {0x50, 0x51, 0x82, 0x06, 0x00, 0x00, 0x00,0x00};			//Update this value with ID register in datasheet
		switch (IOMode)
				{
					case SPI:
					FRAM.mode = SPI;	
					sCommand.InstructionMode	 = QSPI_INSTRUCTION_1_LINE;	
					sCommand.DataMode					= QSPI_DATA_1_LINE;
					sCommand.AddressMode 			 = QSPI_ADDRESS_1_LINE;
					break;
					
					case DPI:
					FRAM.mode = DPI;	
					sCommand.InstructionMode	 = QSPI_INSTRUCTION_2_LINES;	
					sCommand.DataMode					= QSPI_DATA_2_LINES;
					sCommand.AddressMode 			 = QSPI_ADDRESS_2_LINES;
					break;
					
					case QPI:
					FRAM.mode = QPI;
					sCommand.InstructionMode	 = QSPI_INSTRUCTION_4_LINES;	
					sCommand.DataMode					= QSPI_DATA_4_LINES;
					sCommand.AddressMode 			 = QSPI_ADDRESS_4_LINES;
					break;
					
				}
	
				
				
					sCommand.Instruction			 = DID;
					sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
					sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
					sCommand.DummyCycles			 = Reg_lat;
					sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
					sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
					sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
					sCommand.NbData						= 8;
					HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
					HAL_QSPI_Receive(&hqspi, idReg, timeout_1us);
	
					errors=0;
	
					for (i=0;i<8;i++)
						{	
							if(idReg[i]!=idregFactory[i]) errors++;
						}
						
						
						if(errors==0)
						{
							FRAM.opcode_width = sCommand.InstructionMode;
							FRAM.data_width = sCommand.DataMode;
							FRAM.add_width = sCommand.AddressMode;
							FRAM.Reg_Latency = Reg_lat;
							return OperationSuccess;
						}	
							
						else 
							return OperationFail;				//This will never be executed
	}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_WREN(void)																																	*/
/* Return: No Return value																															*/
/* This function issues WREN opcode (0x06) to the device to enable register/memory Writes	  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/

void FRAM_WREN(void)
	
{
	QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= WRITE_ENABLE_CMD;
	sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= QSPI_DATA_NONE;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);

}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_WRDI(void)																																	*/
/* Return: No Return value																															*/
/* This function issues WRDI opcode (0x04) to the device to disable register/memory Writes	  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_WRDI(void)
	
{
	QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= WRITE_DISABLE_CMD;
	sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= QSPI_DATA_NONE;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);

}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDSR1 (uint8_t *StatusReg)																									*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *StatusReg - Pointer uint8_t variable from calling function			*/
/* This function issues RDSR1 opcode to the device to read SR1 register value				  			*/
/* Value read from device is stored in operating_mode variable's SR1 field						  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/

void FRAM_RDSR1 (uint8_t *StatusReg)
	
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= RDSR1;
	sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= FRAM.Reg_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= 1;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, StatusReg, timeout_1us);
	FRAM.SR1_Reg = *StatusReg;
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDSR2 (uint8_t *StatusReg)																									*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *StatusReg - Pointer uint8_t variable from calling function			*/
/* This function issues RDSR2 opcode to the device to read SR1 register value				  			*/
/* Value read from device is stored in operating_mode variable's SR2 field						  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_RDSR2 (uint8_t *StatusReg)
	
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= RDSR2;
	sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= FRAM.Reg_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= 1;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, StatusReg, timeout_1us);
	FRAM.SR2_Reg = *StatusReg;
}

/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDCR1 (uint8_t *StatusReg)																									*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *StatusReg - Pointer uint8_t variable from calling function			*/
/* This function issues RDCR1 opcode to the device to read CR1 register value				  			*/
/* Value read from device is stored in operating_mode variable's CR1 field						  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_RDCR1 (uint8_t *ConfigReg)
	
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = RDCR1;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Reg_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 1;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, ConfigReg, timeout_1us);
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDCR2 (uint8_t *StatusReg)																									*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *StatusReg - Pointer uint8_t variable from calling function			*/
/* This function issues RDCR2 opcode to the device to read CR2 register value				  			*/
/* Value read from device is stored in operating_mode variable's CR2 field						  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_RDCR2 (uint8_t *ConfigReg)
	
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = RDCR2;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Reg_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 1;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, ConfigReg, timeout_1us);
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDCR4 (uint8_t *StatusReg)																									*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *StatusReg - Pointer uint8_t variable from calling function			*/
/* This function issues RDCR4 opcode to the device to read CR4 register value				  			*/
/* Value read from device is stored in operating_mode variable's CR4 field						  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_RDCR4 (uint8_t *ConfigReg)
	
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = RDCR4;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Reg_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 1;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, ConfigReg, timeout_1us);
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDCR5 (uint8_t *StatusReg)																									*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *StatusReg - Pointer uint8_t variable from calling function			*/
/* This function issues RDCR5 opcode to the device to read CR5 register value				  			*/
/* Value read from device is stored in operating_mode variable's CR5 field						  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_RDCR5 (uint8_t *ConfigReg)
	
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = RDCR5;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Reg_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 1;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, ConfigReg, timeout_1us);
}


/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_DID (uint8_t *IDreg)																												*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *IDreg - Pointer uint8_t array from calling function							*/
/* This function issues DID opcode to the device to read ID register value				 		 				*/
/* Returned value should match the Factory programmed ID reg value in Datasheet				  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_DID (uint8_t *IDreg)
	{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction				= DID;
	sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= FRAM.Reg_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= 8;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, IDreg, timeout_1us);
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RUID (uint8_t *UIDreg)																											*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *UIDreg - Pointer uint8_t array from calling function						*/
/* This function issues RUID opcode to the device to read Unique ID register value		 				*/
/* Returned value should match the Factory programmed UID reg value in Datasheet			  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/	

void FRAM_RUID (uint8_t *UIDreg)
	{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction															= RUID;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Reg_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 8;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, UIDreg, timeout_1us);
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDSN (void)																																*/
/* Return: No Return value																															*/
/* This function issues RDSN opcode to the device to read Serial Number register value				*/
/* SN is user configurable. Read value should match the value written by WRSN function			  */
/* Value read from device is stored in operating_mode variable's SN_Reg array 					*/
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/	

void FRAM_RDSN (void)
	{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = RDSN;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Reg_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 8;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, FRAM.SN_Reg, timeout_1us);
}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDSN (uint8_t *SNreg)																																*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *SNreg -  uint8_t array with new Serial number value							*/
/* This function issues WRSN opcode to the device to Write Serial Number register value			*/
/* SN is user configurable. Device must be write enabled before issuing this command	  */
/* Value *SNreg gets written to the device's Serial Number field (8-byte)			 					*/
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/

void FRAM_WRSN (uint8_t *SNreg)
{
QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= WRSN;
	sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= 8;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi,SNreg, timeout_1us);
	
}
/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_Read (uint32_t address, uint8_t *read_data, uint32_t read_length)					*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues READ opcode to the device to perform read														*/
/* For QPI and DPI mode, minimum of 2 memory latency must be set												*/
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/

bool FRAM_Read(uint32_t address, uint8_t *read_data, uint32_t read_length)
{
	
	if((FRAM.mode!=SPI) && (FRAM.Memory_Latency<2)) return OperationFail;
	
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= FRAM.Memory_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= read_length;


	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
	
	
	return OperationSuccess;

}
/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_FastRead (uint32_t address, uint8_t *read_data, uint32_t read_length)			*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues FAST_READ opcode to the device to perform Fast Read									*/
/* The transaction includes Opcode, 3-byte address, Mode byte, Latency cycles (optional)*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
bool FRAM_FastRead(uint32_t address, uint8_t *read_data, uint32_t read_length)
{
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= FAST_READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= FRAM.Memory_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= read_length;


		
HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
			
return OperationSuccess;

}

/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_DORRead (uint32_t address, uint8_t *read_data, uint32_t read_length)				*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues DOR_READ opcode to the device to perform Fast Read	in Extended SPI		*/
/* The transaction includes Opcode, 3-byte address, Mode byte, Latency cycles (optional)*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* This function assumes that the device is configured in SPI mode														*/
/* Modes Supported: SPI. returns a Fail if mode is DPI, QPI															*/
/****************************************************************************************/
bool FRAM_DORRead(uint32_t address, uint8_t *read_data, uint32_t read_length)
{


	if((FRAM.mode!=SPI)) return OperationFail;

	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 	= DOR_READ;
	sCommand.AddressMode			 	= QSPI_ADDRESS_1_LINE;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_1_LINE;
	sCommand.DataMode						= QSPI_DATA_2_LINES;
	sCommand.DummyCycles			 	= FRAM.Memory_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= read_length;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;

	
		
	return OperationSuccess;

}

/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_DIORRead (uint32_t address, uint8_t *read_data, uint32_t read_length)			*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues DIOR_READ opcode to the device to perform Fast Read	in Extended SPI	*/
/* The transaction includes Opcode, 3-byte address, Mode byte, Latency cycles (optional)*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* This function assumes that the device is configured in SPI mode														*/
/* Modes Supported: SPI. returns a Fail if mode is DPI, QPI															*/
/****************************************************************************************/
bool FRAM_DIORRead(uint32_t address, uint8_t *read_data, uint32_t read_length)
{


if((FRAM.mode!=SPI)) return OperationFail;
	
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 	= DIOR_READ;
	sCommand.AddressMode			 	= QSPI_ADDRESS_2_LINES;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_2_LINES;
	sCommand.DataMode						= QSPI_DATA_2_LINES;
	sCommand.DummyCycles			 	= FRAM.Memory_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= read_length;


		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
	
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;	
	
	return OperationSuccess;

}
/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_QORRead (uint32_t address, uint8_t *read_data, uint32_t read_length)				*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues QOR_READ opcode to the device to perform Fast Read	in Extended SPI		*/
/* The transaction includes Opcode, 3-byte address, Mode byte, Latency cycles (optional)*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* This function assumes that the device is configured in SPI mode														*/
/* Modes Supported: SPI. returns a Fail if mode is DPI, QPI															*/
/* I/O2 and I/O3 of the F-RAM device is used for Data transfer											*/
/****************************************************************************************/
bool FRAM_QORRead(uint32_t address, uint8_t *read_data, uint32_t read_length)
{


	if((FRAM.mode!=SPI)) return OperationFail;
	
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 	= QOR_READ;
	sCommand.AddressMode			 	= QSPI_ADDRESS_1_LINE;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_1_LINE;
	sCommand.DataMode						= QSPI_DATA_4_LINES;
	sCommand.DummyCycles			 	= FRAM.Memory_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= read_length;

	FRAM_QUAD_ENABLE();

		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
	
	FRAM_QUAD_DISABLE();

	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
		
	return OperationSuccess;


}

/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_QIORRead (uint32_t address, uint8_t *read_data, uint32_t read_length)			*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues QIOR_READ opcode to the device to perform Fast Read	in Extended SPI	*/
/* The transaction includes Opcode, 3-byte address, Mode byte, Latency cycles (optional)*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* This function assumes that the device is configured in SPI or QPI mode										*/
/* Modes Supported: SPI, QPI. returns a Fail if mode is DPI	 														*/
/* I/O2 and I/O3 of the F-RAM device is used for Address/Mode/Data transfer				*/
/****************************************************************************************/
bool FRAM_QIORRead(uint32_t address, uint8_t *read_data, uint32_t read_length)
{

	if(FRAM.mode==DPI) return OperationFail;   //QIOR is supported both in Extended SPI as well as QPI.
	
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= FRAM.opcode_width;;
	sCommand.Instruction			 	= QIOR_READ;
	sCommand.AddressMode			 	= QSPI_ADDRESS_4_LINES;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_4_LINES;
	sCommand.DataMode						= QSPI_DATA_4_LINES;
	sCommand.DummyCycles			 	= FRAM.Memory_Latency;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= read_length;

	FRAM_QUAD_ENABLE();												//Sets QUAD bit in F-RAM

		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
	
	FRAM_QUAD_DISABLE();										//Resets QUAD bit in F-RAM

	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
		
	return OperationSuccess;



}
/****************************************************************************************/

/****************************************************************************************/
/* NOT Tested in Ver 1.0 of this package																								*/
/* bool FRAM_DDRFastRead (uint32_t address, uint8_t *read_data, uint32_t read_length)		*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *read_data - Pointer to read buffer															*/
/* Argument 1: uint32_t read_length -  Number of Bytes to be read from device						*/
/* This function issues DDRFAST_READ opcode to the device to perform Fast Read	in in DDR			*/
/* The transaction includes Opcode, 3-byte address, Mode byte, Latency cycles (optional)*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* This function assumes that the device is configured in SPI or QPI mode										*/
/* Modes Supported:QPI																			 														*/
/* I/O2 and I/O3 of the F-RAM device is used for Opcode/Mode/Address/Data transfer	*/
/****************************************************************************************/


bool FRAM_DDRFastRead(uint32_t address, uint8_t *read_data, uint32_t read_length)
{


if((FRAM.mode!=QPI)) return OperationFail;	//Supported only in QSPI
	
	
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = DDRFAST_READ;
	sCommand.AddressMode			 = FRAM.add_width;
	sCommand.Address		 			 = address;
	sCommand.AddressSize			 = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode = FRAM.mode_width;
	sCommand.DataMode					= FRAM.data_width;
	sCommand.DummyCycles			 = FRAM.Memory_Latency;
	sCommand.DdrMode					 = QSPI_DDR_MODE_ENABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= read_length;


		
HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
HAL_QSPI_Receive(&hqspi, read_data, timeout_20us);
	
	
		
return OperationSuccess;

}
/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_Write (uint32_t address, uint8_t *write_data, uint32_t write_length)				*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues WRITE opcode to the device to perform Write operation								*/
/* The transaction includes Opcode, 3-byte address and data of length write_length			*/
/* Modes Supported: SPI, DPI, QPI 																											*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/


bool FRAM_Write(uint32_t address, uint8_t *write_data, uint32_t write_length)
	
{
	if((FRAM.mode!=SPI)) return OperationFail;
	QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= WRITE;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;


		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_20us);
	
	
		
return OperationSuccess;

}

/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_DIW (uint32_t address, uint8_t *write_data, uint32_t write_length)					*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues DIW opcode to the device to perform Write operation									*/
/* The transaction includes Opcode, 3-byte address and data of length write_length			*/
/* Modes Supported: SPI. Returns a Fail if mode is DPI or QPI														*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/
bool FRAM_DIW(uint32_t address, uint8_t *write_data, uint32_t write_length)
{
	if((FRAM.mode!=SPI)) return OperationFail;
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 	= DIW;
	sCommand.AddressMode			 	= QSPI_ADDRESS_1_LINE;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_1_LINE;
	sCommand.DataMode						= QSPI_DATA_2_LINES;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;


		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_20us);
	
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
	
return OperationSuccess;

}

/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_DIOW (uint32_t address, uint8_t *write_data, uint32_t write_length)				*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues DIOW opcode to the device to perform Write operation									*/
/* The transaction includes Opcode, 3-byte address and data of length write_length			*/
/* Modes Supported: SPI. Returns a Fail if mode is DPI or QPI														*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/
bool FRAM_DIOW(uint32_t address, uint8_t *write_data, uint32_t write_length)
{
	if((FRAM.mode!=SPI)) return OperationFail;
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 = DIOW;
	sCommand.AddressMode			 = QSPI_ADDRESS_2_LINES;
	sCommand.Address		 			 = address;
	sCommand.AddressSize			 = QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_2_LINES;
	sCommand.DataMode					= QSPI_DATA_2_LINES;
	sCommand.DummyCycles			 = 0;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= write_length;


		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_20us);
	
	sCommand.InstructionMode	 = FRAM.opcode_width;
	sCommand.Instruction			 = READ;
	sCommand.AddressMode			 = FRAM.add_width;
	sCommand.AlternateByteMode = FRAM.mode_width;
	sCommand.DataMode					= FRAM.data_width;	
		
return OperationSuccess;

}
/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_QIW (uint32_t address, uint8_t *write_data, uint32_t write_length)					*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues QIW opcode to the device to perform Write operation									*/
/* The transaction includes Opcode, 3-byte address and data of length write_length			*/
/* Modes Supported: SPI. Returns a Fail if mode is DPI or QPI														*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/
bool FRAM_QIW(uint32_t address, uint8_t *write_data, uint32_t write_length)
{
	if((FRAM.mode!=SPI)) return OperationFail;
	
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 	= QIW;
	sCommand.AddressMode			 	= QSPI_ADDRESS_1_LINE;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_1_LINE;
	sCommand.DataMode						= QSPI_DATA_4_LINES;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;

	FRAM_QUAD_ENABLE();						//Sets QUAD bit in F-RAM	
			
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_20us);
		
	FRAM_QUAD_DISABLE();					//Resets QUAD bit in F-RAM

	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
	
return OperationSuccess;
}


/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_QIOW (uint32_t address, uint8_t *write_data, uint32_t write_length)				*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues QIOW opcode to the device to perform Write operation									*/
/* The transaction includes Opcode, 3-byte address and data of length write_length			*/
/* Modes Supported: SPI. Returns a Fail if mode is DPI or QPI														*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/

bool FRAM_QIOW(uint32_t address, uint8_t *write_data, uint32_t write_length)
{
	if((FRAM.mode!=SPI)) return OperationFail;
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction			 	= QIOW;
	sCommand.AddressMode			 	= QSPI_ADDRESS_4_LINES;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_4_LINES;
	sCommand.DataMode						= QSPI_DATA_4_LINES;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;

	FRAM_QUAD_ENABLE();					//Sets QUAD bit in F-RAM

		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_20us);
	
	FRAM_QUAD_DISABLE();				//Resets QUAD bit in F-RAM

	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= READ;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
		
	return OperationSuccess;
}

/****************************************************************************************/

/****************************************************************************************/
/* bool FRAM_Fast_Write (uint32_t address, uint8_t *write_data, uint32_t write_length)	*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues FAST_WRITE opcode to the device to perform Fast Write operation			*/
/* The transaction includes Opcode, 3-byte address, mode and data of length write_length*/
/* Modes Supported: SPI, DPI, QPI																												*/
/*	This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode		*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/

bool FRAM_Fast_Write(uint32_t address, uint8_t *write_data, uint32_t write_length)
{
	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= FAST_WRITE;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;


			
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_20us);
				
	return OperationSuccess;

}
/****************************************************************************************/

/****************************************************************************************/
/* NOT Tested in Ver 1.0 of this package																								*/
/* bool FRAM_DDRWrite (uint32_t address, uint8_t *write_data, uint32_t write_length)		*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues DDRWRITE opcode to the device to perform  DDR Write operation				*/
/* The transaction includes Opcode, 3-byte address mode and data of length write_length	*/
/* Modes Supported: SPI, DPI, QPI																												*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/

bool FRAM_DDRWrite(uint32_t address, uint8_t *write_data, uint32_t write_length)
{

	QSPI_CommandTypeDef sCommand;
	
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= DDRWRITE;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_ENABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;


			
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Transmit(&hqspi, write_data, timeout_1us);
		
		
			
	return OperationSuccess;

}
/****************************************************************************************/

/****************************************************************************************/
/* NOT Tested in Ver 1.0 of this package																								*/
/* bool FRAM_DDRFastWrite (uint32_t address, uint8_t *write_data, uint32_t write_length)*/	
/* Return: OperationSuccess or OperationFail																						*/
/* Argument 1: uint32_t address - F-RAM memory address																	*/
/* Argument 1: uint8_t *write_data - Pointer to write buffer														*/
/* Argument 1: uint32_t write_length -  Number of Bytes to be written to the device			*/
/* This function issues DDRFWRITE opcode to the device to perform  DDR Fast Write operation	*/
/* The transaction includes Opcode, 3-byte address mode and data of length write_length	*/
/* Modes Supported: SPI, DPI, QPI																												*/
/* This function by default transfers mode byte as 0x02 to avoid entering in to XIP mode			*/
/* Device must be Write Enabled (WEL latch must be set) before memory write operation		*/
/****************************************************************************************/


bool FRAM_DDRFastWrite(uint32_t address, uint8_t *write_data, uint32_t write_length)
{

	QSPI_CommandTypeDef sCommand;
	sCommand.InstructionMode	 	= FRAM.opcode_width;
	sCommand.Instruction			 	= DDRFWRITE;
	sCommand.AddressMode			 	= FRAM.add_width;
	sCommand.Address		 			 	= address;
	sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
	sCommand.AlternateBytesSize = QSPI_ALTERNATE_BYTES_8_BITS;
	sCommand.AlternateBytes			= 0x02;
	sCommand.AlternateByteMode 	= FRAM.mode_width;
	sCommand.DataMode						= FRAM.data_width;
	sCommand.DummyCycles			 	= 0;
	sCommand.DdrMode					 	= QSPI_DDR_MODE_ENABLE;
	sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData							= write_length;


		
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, write_data, timeout_20us);
	return OperationSuccess;

}

/******************************************************************************/
/* This function will be documented in Ver 2.0 of this driver									    */
/******************************************************************************/
device_mode Detect_Mode(void)
{
	QSPI_CommandTypeDef sCommand;
	uint8_t idReg[8];
	uint8_t errors,i;
	uint8_t idregFactory[8] = {0x50, 0x51, 0x82, 0x06, 0x00, 0x00, 0x00,0x00F};
	
	sCommand.InstructionMode	 = QSPI_INSTRUCTION_1_LINE;
	sCommand.Instruction															= DID;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= QSPI_DATA_1_LINE;
	sCommand.DummyCycles			 = 0;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 8;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, idReg, timeout_20us);
	errors=0;
	
		for (i=0;i<8;i++)
		{	
		if(idReg[i]!=idregFactory[i]) errors++;
		}
		if(errors==0)
		{	
		FRAM.mode = SPI;
		FRAM.opcode_width = QSPI_INSTRUCTION_1_LINE;
		FRAM.add_width = QSPI_ADDRESS_1_LINE;
		FRAM.data_width = QSPI_DATA_1_LINE;
		FRAM.mode_width			=QSPI_ALTERNATE_BYTES_1_LINE;
		return SPI;
		}
			else
		{
		
		
	sCommand.InstructionMode	 = QSPI_INSTRUCTION_2_LINES;
	sCommand.Instruction															= DID;
	sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
	sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
	sCommand.DataMode					= QSPI_DATA_2_LINES;
	sCommand.DummyCycles			 = 0;
	sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
	sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
	sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
	sCommand.NbData						= 8;
	
	HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
	HAL_QSPI_Receive(&hqspi, idReg, timeout_20us);
	errors=0;
		
			for (i=0;i<8;i++)
		{	
		if(idReg[i]!=idregFactory[i]) errors++;
		}
		if(errors==0)
			{	
				FRAM.mode = DPI;
				FRAM.opcode_width = QSPI_INSTRUCTION_2_LINES;
				FRAM.add_width = QSPI_ADDRESS_2_LINES;
				FRAM.data_width = QSPI_DATA_2_LINES;
				FRAM.mode_width	=QSPI_ALTERNATE_BYTES_2_LINES;
				return DPI;
			}
		else
			
			{
			
				sCommand.InstructionMode	 = QSPI_INSTRUCTION_4_LINES;
				sCommand.Instruction															= DID;
				sCommand.AddressMode			 = QSPI_ADDRESS_NONE;
				sCommand.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE;
				sCommand.DataMode					= QSPI_DATA_4_LINES;
				sCommand.DummyCycles			 = 3;
				sCommand.DdrMode					 = QSPI_DDR_MODE_DISABLE;
				sCommand.DdrHoldHalfCycle	= QSPI_DDR_HHC_ANALOG_DELAY;
				sCommand.SIOOMode					= QSPI_SIOO_INST_EVERY_CMD;
				sCommand.NbData						= 8;
				
				HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
				HAL_QSPI_Receive(&hqspi, idReg, timeout_1us);
				errors=0;
					
						for (i=0;i<8;i++)
							{	
								if(idReg[i]!=idregFactory[i]) errors++;
							}
						if(errors==0)
							{	
								FRAM.mode = QPI;
								FRAM.opcode_width = QSPI_INSTRUCTION_4_LINES;
								FRAM.add_width = QSPI_ADDRESS_4_LINES;
								FRAM.data_width = QSPI_DATA_4_LINES;
								FRAM.mode_width			=QSPI_ALTERNATE_BYTES_4_LINES;
								return QPI;
							}
			
				}
		
		
		
		}

return SPI;

}

/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_WRR(uint8_t *Register, uint8_t No_of_bytes)																*/
/* Return: No Return value																															*/
/* Argument 1: uint8_t *Register - Array with new value(s) to be written to device 			*/
/* Argument 2: uint8_t No_of_bytes - # of registers to be written												*/
/* This function issues WRR opcode to the device to Write into device registers. 						*/
/* Refer Device datasheet for usage of WRR opcode																			  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/* Device must be Write Enabled (WEL latch must be set) before register write operation	*/
/****************************************************************************************/
	
void FRAM_WRR(uint8_t *Register, uint8_t No_of_bytes)
{
			QSPI_CommandTypeDef sCommand;
			sCommand.InstructionMode	 	= FRAM.opcode_width;
			sCommand.Instruction			 	= WRR;
			sCommand.AddressMode			 	= QSPI_ADDRESS_NONE;
			sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
			sCommand.DataMode						= FRAM.data_width;
			sCommand.DummyCycles			 	= 0;
			sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
			sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
			sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
			sCommand.NbData							= No_of_bytes;
			
			HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
			HAL_QSPI_Transmit(&hqspi, Register, timeout_1us);
			
	
}


/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_WRAR(uint32_t Reg_address, uint8_t *New_Reg_Data)													*/
/* Return: No Return value																															*/
/* Argument 1: uint32_t Reg_address - Address of register to be updated						 			*/
/* Argument 2: uint8_t *New_Reg_Data- New value to be udpated in register								*/
/* This function issues WRAR opcode to the device to Write into device registers. 			*/
/* Refer Device datasheet for usage of WRAR opcode																		  */
/* This function assumes that the device is configured in a known mode									*/
/* Modes Supported: SPI, DPI, QPI																												*/
/* Device must be Write Enabled (WEL latch must be set) before register write operation	*/
/* It is recommended to avoid using this function to prevent inadvertent register updates*/
/* Users can instead use individual parameter update functions to modify registers			*/
/****************************************************************************************/
void FRAM_WRAR(uint32_t Reg_address, uint8_t *New_Reg_Data)
{
			QSPI_CommandTypeDef sCommand;
			sCommand.InstructionMode	 	= FRAM.opcode_width;
			sCommand.Instruction			 	= WRAR;
			sCommand.AddressMode			 	= FRAM.add_width;
			sCommand.Address		 			 	= Reg_address;
			sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
			sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
			sCommand.DataMode						= FRAM.data_width;
			sCommand.DummyCycles			 	= 0;
			sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
			sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
			sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
			sCommand.NbData							= 1;
				
		
		
			HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
			HAL_QSPI_Transmit(&hqspi, New_Reg_Data, timeout_1us);

	
}
	
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_RDAR(uint32_t Reg_address, uint8_t *New_Reg_Data)													*/
/* Return: No Return value																															*/
/* Argument 1: uint32_t Reg_address - Address of register to be read 							 			*/
/* Argument 2: uint8_t *New_Reg_Data- Value of register																	*/
/* This function issues RDAR opcode to the device to Write into device registers. 						*/
/* Refer device datasheet for usage of WRAR opcode																		  */
/* This function assumes that the device is configured in a known mode												*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
	
void FRAM_RDAR(uint32_t Reg_address, uint8_t *New_Reg_Data)
{
			QSPI_CommandTypeDef sCommand;
			sCommand.InstructionMode	 	= FRAM.opcode_width;
			sCommand.Instruction			 	= RDAR;
			sCommand.AddressMode			 	= FRAM.add_width;
			sCommand.Address		 			 	= Reg_address;
			sCommand.AddressSize			 	= QSPI_ADDRESS_24_BITS;
			sCommand.AlternateByteMode 	= QSPI_ALTERNATE_BYTES_NONE;
			sCommand.DataMode						= FRAM.data_width;
			sCommand.DummyCycles			 	= FRAM.Reg_Latency;
			sCommand.DdrMode					 	= QSPI_DDR_MODE_DISABLE;
			sCommand.DdrHoldHalfCycle		= QSPI_DDR_HHC_ANALOG_DELAY;
			sCommand.SIOOMode						= QSPI_SIOO_INST_EVERY_CMD;
			sCommand.NbData							= 1;
			
			HAL_QSPI_Command(&hqspi, &sCommand, timeout_1us);
			HAL_QSPI_Receive(&hqspi, New_Reg_Data, timeout_1us);

	
}
	
	
/****************************************************************************************/

	
/****************************************************************************************/
/* bool FRAM_Set_Memory_Latency(uint8_t New_latency)																		*/
/* Return: OperationSuccess	or OperationFail																						*/
/* Argument 1: uint8_t New_latency - New value of memory latency 							 					*/
/* This function updates the memory latency value MLC[3:0] with value provided to function		*/
/* Memory latency cannot be greater than 15																						  */
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
	
	
bool FRAM_Set_Memory_Latency(uint8_t New_latency)
	
{
	if (New_latency>15) return OperationFail;
			uint8_t CR1_temp =0x00;
			FRAM_RDCR1(&FRAM.CR1_Reg);	
			CR1_temp = FRAM.CR1_Reg & 0x0F;
			CR1_temp = CR1_temp | (New_latency<<Mem_Lat_Pos);
			FRAM_WREN();
			FRAM_WRAR(CR1_Address,&CR1_temp);
			FRAM.Memory_Latency = New_latency;
			return OperationSuccess;
	
}
/****************************************************************************************/

	
/****************************************************************************************/
/* bool FRAM_Set_Register_Latency(uint8_t New_latency)																	*/
/* Return: OperationSuccess	or OperationFail																						*/
/* Argument 1: uint8_t New_latency - New value of register latency						 					*/
/* This function updates the register latency value RLC[3:0] with value provided to function	*/
/* Register latency cannot be greater than 3																						*/
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/	
		
bool FRAM_Set_Register_Latency(uint8_t New_latency)
{
			uint8_t CR5_temp =0x00;
		
			FRAM_RDCR5(&FRAM.CR5_Reg);	
			CR5_temp = FRAM.CR5_Reg & 0x3F;
			CR5_temp = CR5_temp | (New_latency<<Reg_Lat_Pos);
			FRAM_WREN();
			FRAM_WRAR(CR5_Address,&CR5_temp);
			FRAM.Reg_Latency = New_latency;
			return OperationSuccess;
}

/******************************************************************************************************/

	
/******************************************************************************************************/
/* void FRAM_Get_Memory_Latency(void)																																	*/
/* Return: No return value																																											*/
/* Argument 1: No arguments					 																																				*/
/* This function updates the operating_mode variable's Memory_Latency variable with device's MLC value*/
/* Modes Supported: SPI, DPI, QPI																																			*/
/******************************************************************************************************/	
void FRAM_Get_Memory_Latency(void)
	
{
			FRAM_RDCR1(&FRAM.CR1_Reg);
			FRAM.Memory_Latency = (FRAM.CR1_Reg & Mem_Lat_Mask_And)>>Mem_Lat_Pos;

}
/******************************************************************************************************/
/* void FRAM_Get_Register_Latency(void)																																	*/
/* Return: No return value																																										*/
/* Argument 1: No arguments					 																																				*/
/* This function updates the operating_mode variable's Reg_Latency variable with device's RLC value	*/
/* Modes Supported: SPI, DPI, QPI																																			*/
/******************************************************************************************************/	

void FRAM_Get_Register_Latency(void)
{

			FRAM_RDCR5(&FRAM.CR5_Reg);	
			FRAM.Reg_Latency = (FRAM.CR5_Reg & Reg_Lat_Mask_And)>>Reg_Lat_Pos;	

}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_QPIEN(void)																																*/
/* Return: No Return value																																				*/
/* Argument 1: No Arguments						 																													*/
/* This function updates device operation mode to QPI by setting QPI bit in CR2					*/
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/	
void FRAM_QPIEN(void)
{
			FRAM.QPI_DPI=0x40;
			FRAM_WREN();
			FRAM_WRAR(CR2_Address,&FRAM.QPI_DPI);
			FRAM.opcode_width 	= QSPI_INSTRUCTION_4_LINES;	
			FRAM.data_width			= QSPI_DATA_4_LINES;
			FRAM.add_width			= QSPI_ADDRESS_4_LINES;
			FRAM.mode_width 		= QSPI_ALTERNATE_BYTES_4_LINES;
			FRAM.mode = QPI;
			

}


/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_DPIEN(void)																																*/
/* Return: No return value																																				*/
/* Argument 1: No argruments						 																													*/
/* This function updates device operation mode to DPI by setting DPI bit in CR2					*/
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/

void FRAM_DPIEN(void)
{

			FRAM.QPI_DPI=0x10;
			FRAM_WREN();
			FRAM_WRAR(CR2_Address,&FRAM.QPI_DPI);
			FRAM.opcode_width 	= QSPI_INSTRUCTION_2_LINES;	
			FRAM.data_width			= QSPI_DATA_2_LINES;
			FRAM.add_width			= QSPI_ADDRESS_2_LINES;
			FRAM.mode_width			= QSPI_ALTERNATE_BYTES_2_LINES;	
			FRAM.mode = DPI;

}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_SPIEN(void)																																*/
/* Return: No return value																																					*/
/* Argument 1: No arguments					 																													*/
/* This function updates device operation mode to SPI by re-setting QPI andDPI bit in CR2*/
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/

void FRAM_SPIEN(void)
{

			FRAM.QPI_DPI=0x00;
			FRAM_WREN();
			FRAM_WRAR(CR2_Address,&FRAM.QPI_DPI);
			FRAM.opcode_width 	= QSPI_INSTRUCTION_1_LINE;	
			FRAM.data_width			= QSPI_DATA_1_LINE;
			FRAM.add_width			= QSPI_ADDRESS_1_LINE;
			FRAM.mode_width			= QSPI_ALTERNATE_BYTES_1_LINE;
			FRAM.mode = SPI;




}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_QUAD_ENABLE(void)																													*/
/* Return: No return value																																					*/
/* Argument 1: No arguments						 																													*/
/* This function sets QUAD bit of device																									*/
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_QUAD_ENABLE(void)
{

	
	
			uint8_t CR1_temp =0x00;
		
			FRAM_RDCR1(&FRAM.CR1_Reg);	
			CR1_temp = FRAM.CR1_Reg | 0x02;
			FRAM_WREN();
			FRAM_WRAR(CR1_Address,&CR1_temp);
			FRAM.CR1_Reg = CR1_temp;
	

}
/****************************************************************************************/

	
/****************************************************************************************/
/* void FRAM_QUAD_DISABLE(void)																													*/
/* Return: No return value																																					*/
/* Argument 1: No arguments						 																													*/
/* This function resets QUAD bit of device																								*/
/* This function assumes that the device is configured in a known mode												*/
/* This function is self sufficient and will not disturb any other register bits							*/
/* Modes Supported: SPI, DPI, QPI																												*/
/****************************************************************************************/
void FRAM_QUAD_DISABLE(void)
{
			uint8_t CR1_temp =0x00;
		
			FRAM_RDCR1(&FRAM.CR1_Reg);	
			CR1_temp = FRAM.CR1_Reg & 0xFD;
			FRAM_WREN();
			FRAM_WRAR(CR1_Address,&CR1_temp);
			FRAM.CR1_Reg = CR1_temp;


}
/****************************************************************************************/
/*End of File																																						*/
/****************************************************************************************/
