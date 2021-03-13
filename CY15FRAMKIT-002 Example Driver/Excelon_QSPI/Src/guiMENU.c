/******************************************************************************
* Project Name		: CY15FRAMKIT-002
* Version			: 1.0
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
/** @file guiMENU.c
 *	
 *	@brief Definition for accessing QSPI FRAM GUI commands
 *	@author	NILE
 *	@date 6/22/2018	
 *	Rev 1.1
 */
#include "guiMENU.h"
#include "qspiFRAM.h"

extern uint8_t databuffer[8192];
extern operating_mode FRAM;

void TestFRAMRegisters (void)
{
	uint8_t reg;
	uint32_t i, errors ;
	uint8_t idReg[8];
	uint8_t idregFactory[8] = {0x50, 0x51, 0x82, 0x06, 0x00, 0x00, 0x00,0x00};	
	FRAM_Interface_Reset();
	FRAM_Set_Memory_Latency(2);
	FRAM_Set_Register_Latency(2);		
	FRAM_SPIEN();
	FRAM_WREN();
	errors=0;
	
	printf("\n\r*********************************************************************");
	printf("\n\rStart Of Register Testing\n\r");
		printf("\n\r*********************************************************************\n\r");
	printf("\n\rTesting SPI\n\r");
	FRAM_RDSR1(&reg);
	printf("\n\rSR1=");
	printf(" %02x",reg);
	if(reg!=0x02) errors++;

	FRAM_RDSR2(&reg);
		printf("\n\rSR2=");
	printf(" %02x",reg);
	if(reg!=0x00) errors++;
	
	FRAM_RDCR1(&reg);
		printf("\n\rCR1=");
	printf(" %02x",reg);
	if(reg!=0x20) errors++;
	
	FRAM_RDCR2(&reg);
		printf("\n\rCR2=");
	printf(" %02x",reg);
	if(reg!=0x00) errors++;
	FRAM_RDCR4(&reg);
		printf("\n\rCR4=");
	printf(" %02x",reg);
	if(reg!=0x08) errors++;
	
	FRAM_RDCR5(&reg);
		printf("\n\rCR5=");
	printf(" %02x",reg);
	if(reg!=0x80) errors++;
	
	if (errors>0) 
		printf("\n\rResult: FAIL!!");
	else 
		printf("\n\rResult: Pass");
	
		FRAM_DID(idReg);
		errors=0;
		for (i=0;i<8;i++)
			{	
				if(idReg[i]!=idregFactory[i]) errors++;
			}
	if (errors==0) 
	{guiReadID();guiReadSN();}
	else 
		printf("\n\rID Reg Mis-match");
	
		printf("\n\r*********************************************************************\n\r");
		printf("\n\n\rTesting DPI\n\r");
	errors=0;
	FRAM_Interface_Reset();
	FRAM_Set_Memory_Latency(2);
	FRAM_Set_Register_Latency(2);		
	FRAM_DPIEN();
	FRAM_WREN();
		FRAM_RDSR1(&reg);
	printf("\n\rSR1=");
	printf(" %02x",reg);
	if(reg!=0x02) errors++;

	FRAM_RDSR2(&reg);
		printf("\n\rSR2=");
	printf(" %02x",reg);
	if(reg!=0x00) errors++;
	
	FRAM_RDCR1(&reg);
		printf("\n\rCR1=");
	printf(" %02x",reg);
	if(reg!=0x20) errors++;
	
	FRAM_RDCR2(&reg);
		printf("\n\rCR2=");
	printf(" %02x",reg);
	if(reg!=0x10) errors++;
	FRAM_RDCR4(&reg);
		printf("\n\rCR4=");
	printf(" %02x",reg);
	if(reg!=0x08) errors++;
	
	FRAM_RDCR5(&reg);
		printf("\n\rCR5=");
	printf(" %02x",reg);
	if(reg!=0x80) errors++;
	
	if (errors>0) 
		printf("\n\rResult: FAIL!!");
	else 
		printf("\n\rResult: Pass");
	
		FRAM_DID(idReg);
		errors=0;
		for (i=0;i<8;i++)
			{	
				if(idReg[i]!=idregFactory[i]) errors++;
			}
	if (errors==0) 
	{guiReadID(); guiReadSN();}
	else 
		printf("\n\rID Reg Mis-match");
	
		printf("\n\r*********************************************************************\n\r");
			printf("\n\n\rTesting QPI\n\r");
	errors=0;
	FRAM_Interface_Reset();
	FRAM_Set_Memory_Latency(2);
	FRAM_Set_Register_Latency(2);		
	FRAM_QPIEN();
	FRAM_WREN();
		FRAM_RDSR1(&reg);
	printf("\n\rSR1=");
	printf(" %02x",reg);
	if(reg!=0x02) errors++;

	FRAM_RDSR2(&reg);
		printf("\n\rSR2=");
	printf(" %02x",reg);
	if(reg!=0x00) errors++;
	
	FRAM_RDCR1(&reg);
		printf("\n\rCR1=");
	printf(" %02x",reg);
	if(reg!=0x20) errors++;
	
	FRAM_RDCR2(&reg);
		printf("\n\rCR2=");
	printf(" %02x",reg);
	if(reg!=0x40) errors++;
	FRAM_RDCR4(&reg);
		printf("\n\rCR4=");
	printf(" %02x",reg);
	if(reg!=0x08) errors++;
	
	FRAM_RDCR5(&reg);
		printf("\n\rCR5=");
	printf(" %02x",reg);
	if(reg!=0x80) errors++;
	
	if (errors>0) 
		printf("\n\rResult: FAIL!!");
	else 
		printf("\n\rResult: Pass");
	
		FRAM_DID(idReg);
		errors=0;
		for (i=0;i<8;i++)
			{	
				if(idReg[i]!=idregFactory[i]) errors++;
			}
	if (errors==0) 
	{guiReadID(); guiReadSN();}
	else 
		printf("\n\rID Reg Mis-match");
	
		
	FRAM_SPIEN();
	FRAM_Interface_Reset();
	FRAM_Set_Memory_Latency(0);
	FRAM_Set_Register_Latency(0);		
	
				printf("\n\n\rEnd Of Register Testing\n\r");
				
				printf("*********************************************************************\n\r");
	
}



void TestFRAMSPI(void)
{

uint32_t address, length;
uint8_t latency,latency_max;
uint32_t i, errors ;
address = 0;
length = 4096;
latency_max=16;
	printf("\n\r*********************************************************************");
	printf("\n\rStart Of Memory Testing\n\r");
			printf("\n\r*********************************************************************\n\r");
FRAM_Set_Memory_Latency(0);		
	
	FRAM_Interface_Reset();
	printf("\n\rTesting SPI\n\r");
	printf("\n\rPerforming Write tests\n\r");
	
			FRAM_WREN();
			for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Write(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rSPI Write:\tFail");
				else
					printf("\n\rSPI Write:\tPass");
				
				
				
						for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Fast_Write(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rFast Write:\tFail");
				else
					printf("\n\rFast Write:\tPass");	
				
				
				for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_DIW(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rDIW Write:\tFail");
				else
					printf("\n\rDIW Write:\tPass");	
				
				
						for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_DIOW(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rDIOW Write:\tFail");
				else
					printf("\n\rDIOW Write:\tPass");
				
				
				
						for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_QIW(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rQIW Write:\tFail");
				else
					printf("\n\rQIW Write:\tPass");
				
				
						for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_QIOW(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rQIOW Write:\tFail");
				else
					printf("\n\rQIOW Write:\tPass");
		
		printf("\n\n\rPerforming Read tests for all latencies and all SPI opcodes\n\r");
				
			length = 256;	
			for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Write(address, databuffer,length);
				
			//	printf("\n\rSPI Read Latency - Result: ");
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_Read(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				}
				if (errors>0)
					printf("\n\rSPI Read:\tFail");
				else
					printf("\n\rSPI Read:\tPass");
				
				
				for(i=0;i<length;i++)
			databuffer[i]=0;
		
			//	printf("\n\rFast Read Latency - Result: ");
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_FastRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				
				}
						if (errors>0)
					printf("\n\rSPI Fast Read:\tFail");
				else
					printf("\n\rSPI Fast Read:\tPass");
				
							for(i=0;i<length;i++)
					databuffer[i]=0;
		
			//	printf("\n\rDOR Read Latency - Result: ");
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_DORRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
			
				}
				if (errors>0)
					printf("\n\rSPI DOR Read:\tFail");
				else
					printf("\n\rSPI DOR Read:\tPass");
				
				
										for(i=0;i<length;i++)
			databuffer[i]=0;
		
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_DIORRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
					
				}
				
					if (errors>0)
					printf("\n\rSPI DIOR Read:\tFail");
					else
					printf("\n\rSPI DIOR Read:\tPass");
				
										for(i=0;i<length;i++)
			databuffer[i]=0;
			
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_QORRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
						
				}
				
					if (errors>0)
					printf("\n\rSPI QOR Read:\tFail");
				else
					printf("\n\rSPI QOR Read:\tPass");
				
										for(i=0;i<length;i++)
			databuffer[i]=0;

				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_QIORRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
						
				}
					if (errors>0)
					printf("\n\rSPI QIOR Read:\tFail");
				else
					printf("\n\rSPI QIOR Read:\tPass");
				
				
				
}



void TestFRAMDPI(void)
{

uint32_t address, length;
uint8_t latency,latency_max;
uint32_t i, errors ;
address = 0;
length = 4096;
latency_max=16;
FRAM_Set_Memory_Latency(0);		
	
			FRAM_Interface_Reset();
			printf("\n\n\rTesting DPI\n\r");
			printf("\n\rPerforming Write tests\n\r");
			FRAM_WREN();
			FRAM_Set_Memory_Latency(2);
			FRAM_Set_Register_Latency(2);
			FRAM_DPIEN();
	
			for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Write(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rDPI Write:\tFail");
				else
					printf("\n\rDPI Write:\tPass");
				
				
				
				for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Fast_Write(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rDPI Fast Write:\tFail");
				else
					printf("\n\rDPI Fast Write:\tPass");	
				
				
						
				
				
				
				
				
							
		printf("\n\n\rPerforming Read tests for all latencies in DPI\n\r");
				
			length = 256;	
			for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Write(address, databuffer,length);
				
			//	printf("\n\rSPI Read Latency - Result: ");
				for (latency=2;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_Read(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				}
				if (errors>0)
					printf("\n\rDPI Read:\tFail");
				else
					printf("\n\rDPI Read:\tPass");
				
				
				for(i=0;i<length;i++)
			databuffer[i]=0;
		
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_FastRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				
				}
						if (errors>0)
					printf("\n\rDPI Fast Read:\tFail");
				else
					printf("\n\rDPI Fast Read:\tPass");
				
							for(i=0;i<length;i++)
					databuffer[i]=0;
		
				FRAM_Set_Memory_Latency(0);
				FRAM_Set_Register_Latency(0);
				FRAM_SPIEN();
				
				
				
}

void TestFRAMQPI(void)
{

uint32_t address, length;
uint8_t latency,latency_max;
uint32_t i, errors ;
address = 0;
length = 4096;
latency_max=16;
FRAM_Set_Memory_Latency(0);		
	
			FRAM_Interface_Reset();
			printf("\n\n\rTesting QPI\n\r");
			printf("\n\rPerforming Write tests\n\r");
			FRAM_WREN();		
			FRAM_Set_Memory_Latency(2);
			FRAM_Set_Register_Latency(2);
			FRAM_QPIEN();
	
			for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Write(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rQPI Write:\tFail");
				else
					printf("\n\rQPI Write:\tPass");
				
				
				
				for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Fast_Write(address, databuffer, length);
			for(i=0;i<length;i++)
			databuffer[i]=0;
			errors=0;
			FRAM_Read(address,databuffer,length);
			for(i=0;i<length;i++)
			{if (databuffer[i] != i%256) errors++;	}
				if (errors>0)
					printf("\n\rQPI Fast Write:\tFail");
				else
					printf("\n\rQPI Fast Write:\tPass");	
				
				
						
				
				
				
				
				
							
		printf("\n\n\rPerforming Read tests for all latencies in QPI\n\r");
				
			length = 256;	
			for(i=0;i<length;i++)
			databuffer[i]=i%256;
			FRAM_Write(address, databuffer,length);
				
				for (latency=2;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_Read(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				}
				if (errors>0)
					printf("\n\rQPI Read:\tFail");
				else
					printf("\n\rQPI Read:\tPass");
				
				
				for(i=0;i<length;i++)
			databuffer[i]=0;
		
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_FastRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				
				}
						if (errors>0)
					printf("\n\rQPI Fast Read:\tFail");
				else
					printf("\n\rQPI Fast Read:\tPass");
				
							for(i=0;i<length;i++)
					databuffer[i]=0;
		
				
							for(i=0;i<length;i++)
			databuffer[i]=0;
		
				for (latency=0;latency<latency_max;latency++)
				
				{
					for(i=0;i<length;i++)
					databuffer[i]=0;
					errors=0;
					FRAM_Set_Memory_Latency(latency);
					FRAM_QIORRead(address,databuffer,length);
					for(i=0;i<length;i++)
					{if (databuffer[i] != i%256) errors++;	}
				
				}
						if (errors>0)
					printf("\n\rQPI QIOR Read:\tFail");
				else
					printf("\n\rQPI QIOR Read:\tPass");
				
							for(i=0;i<length;i++)
					databuffer[i]=0;
				
				FRAM_Set_Memory_Latency(0);
				FRAM_Set_Register_Latency(0);
				FRAM_SPIEN();
				
				printf("\n\n\rEnd Of Memory Testing\n\r");
				
				printf("*********************************************************************\n\r");
}


void guiReadSR1(void)
{
	uint8_t reg;
	FRAM_RDSR1(&reg);
	printf("\nSR1=");
	printf("%02x\n",reg);
	FRAM.SR1_Reg = reg;

}
void guiReadSR2(void)
{
	uint8_t reg;
	FRAM_RDSR2(&reg);
	printf("\nSR2=");
	printf("%02x\n",reg);
	FRAM.SR2_Reg = reg;


}

void guiReadCR1(void)
{
	uint8_t reg;
	FRAM_RDCR1(&reg);
	printf("\nCR1=");
	printf("%02x\n",reg);
	FRAM.CR1_Reg = reg;
}

void guiReadCR2(void)
{
	uint8_t reg;
	FRAM_RDCR2(&reg);
	printf("\nCR2=");
	printf("%02x\n",reg);
	FRAM.CR2_Reg = reg;
}

void guiReadCR4(void)
{
	uint8_t reg;
	FRAM_RDCR4(&reg);
	printf("\nCR4=");
	printf("%02x\n",reg);
	FRAM.CR4_Reg = reg;

}

void guiReadCR5(void)
{
	uint8_t reg;
	FRAM_RDCR5(&reg);
	printf("\nCR5=");

	printf("%02x\n",reg);
	FRAM.CR5_Reg = reg;
}



void guiReadID (void)
{
	uint8_t i, idReg[8];
	FRAM_DID(idReg);
	printf("\n\rID Reg: ");
	for (i=0;i<8;i++)
	{
		printf("%02x",idReg[i]);
		FRAM.ID_Reg[i]=idReg[i];
	}
}

void guiReadUID (void)
{
	uint8_t i, uidReg[8];
	FRAM_RUID(uidReg);
	printf("\n\rID Reg: ");
	for (i=0;i<8;i++)
	{
		printf("%02x",uidReg[i]);
		FRAM.UID_Reg[i]=uidReg[i];
	}



}

void guiReadSN (void)
{
	uint8_t i;
	FRAM_RDSN();
	printf("\n\rSN Reg: ");
	for (i=0;i<8;i++)
	{
		printf("%02x",FRAM.SN_Reg[i]);
		
	}


}

void guiWriteSN (void)
{
	uint8_t i, SNReg[8];
	FRAM_RDSN();
	printf("\n\rCurrent SN Reg: ");
	for (i=0;i<8;i++)
	{
		printf("%02x",FRAM.SN_Reg[i]);
	}
	printf("\n\rEnter New SN Value: ");
	for (i=0;i<8;i++)
	{
		scanf("%02" SCNx8,&SNReg[i]);
	}
	FRAM_WREN();
	FRAM_WRSN(SNReg);

}


////////////////////////////////////////Read GUI APIs//////////////////////////////////

void guiFRAMRead (uint32_t address, uint32_t read_length)
{
	uint8_t latency;
	uint32_t i;

	
	printf("\n\rRead Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to read (Length in integer):");
	scanf("%d",&read_length);
			if (FRAM.mode != SPI) 
				{
					FRAM_Get_Memory_Latency();
					if(FRAM.Memory_Latency<2)
					{	
					printf("\n\rSet Memory Latency greater than 1:");
					scanf("%2" SCNu8,&latency);
					FRAM_Set_Memory_Latency(latency);
					}
						printf("\n\rReading with Latency: %d",FRAM.Memory_Latency);
				}	
				
		
				FRAM_Read(address,databuffer,read_length);
				
				printf("\n\rData:");
				
				for (i=0;i<read_length;i++)
				printf("%02x ",databuffer[i]);
			
}

void guiFRAMFastRead (uint32_t address,	uint32_t read_length)
{
//	uint8_t latency;
	uint32_t i;

	//uint8_t *read_data = malloc(packetsize);
	printf("\n\rRead Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to read (Length in integer):");
	scanf("%d",&read_length);
					FRAM_Get_Memory_Latency();
					printf("\n\rReading with Latency: %d",FRAM.Memory_Latency);
				
				
				
				FRAM_FastRead(address,databuffer,read_length);
				
				printf("\n\rOutput Data:");
				
				for (i=0;i<read_length;i++)
				printf("%02x ",databuffer[i]);


}

void guiFRAMDORRead (uint32_t address,	uint32_t read_length)
{

//uint8_t latency;
	uint32_t i;

	//uint8_t *read_data = malloc(packetsize);
	printf("\n\rRead Address(Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to read (Length in integer):");
	scanf("%d",&read_length);
					FRAM_Get_Memory_Latency();
					printf("\n\rReading with Latency: %d",FRAM.Memory_Latency);
				
				
				
				FRAM_DORRead(address,databuffer,read_length);
				
				printf("\n\rOutput Data:");
				
				for (i=0;i<read_length;i++)
				printf("%02x ",databuffer[i]);

}


void guiFRAMDIORRead (uint32_t address,	uint32_t read_length)
{

//uint8_t latency;
	uint32_t i;

	//uint8_t *read_data = malloc(packetsize);
	printf("\n\rRead Address(Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to read (Length in integer):");
	scanf("%d",&read_length);
					FRAM_Get_Memory_Latency();
					printf("\n\rReading with Latency: %d",FRAM.Memory_Latency);
				
				
				
				FRAM_DIORRead(address,databuffer,read_length);
				
				printf("\n\rOutput Data:");
				
				for (i=0;i<read_length;i++)
				printf("%02x ",databuffer[i]);

}


void guiFRAMQORRead (uint32_t address,	uint32_t read_length)
{

//uint8_t latency;
	uint32_t i;

	//uint8_t *read_data = malloc(packetsize);
	printf("\n\rRead Address(Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to read (Length in integer):");
	scanf("%d",&read_length);
					FRAM_Get_Memory_Latency();
					printf("\n\rReading with Latency: %d",FRAM.Memory_Latency);
				
				
				
				FRAM_QORRead(address,databuffer,read_length);
				
				printf("\n\rOutput Data:");
				
				for (i=0;i<read_length;i++)
				printf("%02x ",databuffer[i]);

}


void guiFRAMQIORRead (uint32_t address,	uint32_t read_length)
{

//uint8_t latency;
	uint32_t i;

	//uint8_t *read_data = malloc(packetsize);
	printf("\n\rRead Address(Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to read (Length in integer):");
	scanf("%d",&read_length);
					FRAM_Get_Memory_Latency();
					printf("\n\rReading with Latency: %d",FRAM.Memory_Latency);
				
				
				
				FRAM_QIORRead(address,databuffer,read_length);
				
				printf("\n\rOutput Data:");
				
				for (i=0;i<read_length;i++)
				printf("%02x ",databuffer[i]);

}




//////////////////////////////Write GUI APIs/////////////////////////////////////////////////////

void guiFRAMWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	//uint8_t latency;
	uint32_t i;
	//uint8_t *write_data = malloc(packetsize);
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
//	write_length = 4;
//	printf("\n\rWrite Address is:%d",address);
	
//	printf("\n\rWrite Length is:%d",write_length);
		printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
		printf("\n\r6: Add=Data\n\rWaiting for Input: ");
		scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_Write(address,databuffer,write_length);
				

			
}

void guiFRAMFastWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	//uint8_t latency;
	uint32_t i;
	//uint8_t *write_data = malloc(packetsize);
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
//	write_length = 4;
//	printf("\n\rWrite Address is:%d",address);
	
//	printf("\n\rWrite Length is:%d",write_length);
		printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
		printf("\n\r6: Add=Data\n\rWaiting for Input: ");
		scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_Fast_Write(address,databuffer,write_length);
				

			
}



void guiFRAMDIWWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	//uint8_t latency;
	uint32_t i;
	//uint8_t *write_data = malloc(packetsize);
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
//	write_length = 4;
//	printf("\n\rWrite Address is:%d",address);
	
//	printf("\n\rWrite Length is:%d",write_length);
		printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
		printf("\n\r6: Add=Data\n\rWaiting for Input: ");
		scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_DIW(address,databuffer,write_length);
				

			
}


void guiFRAMDIOWWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	//uint8_t latency;
	uint32_t i;
	//uint8_t *write_data = malloc(packetsize);
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
//	write_length = 4;
//	printf("\n\rWrite Address is:%d",address);
	
//	printf("\n\rWrite Length is:%d",write_length);
		printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
		printf("\n\r6: Add=Data\n\rWaiting for Input: ");
		scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_DIOW(address,databuffer,write_length);
				

			
}


void guiFRAMQIWWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	//uint8_t latency;
	uint32_t i;
	//uint8_t *write_data = malloc(packetsize);
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
//	write_length = 4;
//	printf("\n\rWrite Address is:%d",address);
	
//	printf("\n\rWrite Length is:%d",write_length);
		printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
		printf("\n\r6: Add=Data\n\rWaiting for Input: ");
		scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_QIW(address,databuffer,write_length);
				

			
}



void guiFRAMQIOWWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	//uint8_t latency;
	uint32_t i;
	//uint8_t *write_data = malloc(packetsize);
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
//	write_length = 4;
//	printf("\n\rWrite Address is:%d",address);
	
//	printf("\n\rWrite Length is:%d",write_length);
		printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
		printf("\n\r6: Add=Data\n\rWaiting for Input: ");
		scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_QIOW(address,databuffer,write_length);
				

			
}

void guiFRAMDDRWrite (uint32_t address, uint32_t write_length)
{
	uint8_t data;
	uint32_t i;
	printf("\n\rWrite Address (Integer equivalent):");
	scanf("%d",&address);
	printf("\n\rLength to write(Length in integer):");
	scanf("%d",&write_length);
	printf("\nSelect data pattern\n\r0: Solid 0\n\r1: Solid 1\n\r2: 0xAA\n\r3: 0x55\n\r4: AA->55->AA->55\n\r5: 55->AA->55->AA");
	printf("\n\r\6: Add=Data\n\rWaiting for Input: ");
	scanf("%02" SCNu8,&data);

	switch (data)
	{
		case 0: {data = 0x00;
								for(i=0;i<write_length;i++)
								databuffer[i]=data;
								break;
						}
		
		case 1: {
							data = 0xFF; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;
		
						}
		
		case 2: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 3: {	data = 0x55; 
							for(i=0;i<write_length;i++)
								databuffer[i]=data;
							break;}
		
		case 4: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0:databuffer[i] = 0xAA; break;
								case 1: databuffer[i] = 0x55; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}
		
			case 5: {
							data = 0xAA; 
							for(i=0;i<write_length;i++)
								switch (i%2)
								{
								case 0: databuffer[i] = 0x55; break;
								case 1: databuffer[i] = 0xAA; break;
								default: databuffer[i] = 0xFF; break;
								}
							

							break;}					
			case 6: {
							
							for(i=0;i<write_length;i++)
								databuffer[i]=i;
							

							break;}				
							
		default: {data = 0xFF; 
							for(i=0;i<write_length;i++)
							databuffer[i]=data;
		
		break;}
	}
	
	

			FRAM_WREN();	
			FRAM_DDRWrite(address,databuffer,write_length);
				
			
}



void guiWriteAnyReg(void)
{
	uint32_t address;
	uint8_t reg_data;
printf("\n\rReg Address:");
	scanf("%d",&address);
	
	printf("\n\rReg Value:");
	scanf("%2" SCNu8,&reg_data);
	FRAM_WRAR(address,&reg_data);
}


void guiReadAnyReg(void)
{
	uint32_t address;
	uint8_t reg_data;
printf("\n\rReg Address:");
	scanf("%d",&address);
	FRAM_RDAR(address,&reg_data);
	printf("\n\rRead Reg Value:%02x\n",reg_data);

}


void guiSetMemLatency(void)
{
	uint8_t reg_data;
printf("\n\rEnter Memory Latency:");
	scanf("%2" SCNu8,&reg_data);
	FRAM_Set_Memory_Latency(reg_data);

}
void guiGetMemLatency(void)
{

	FRAM_Get_Memory_Latency();
printf("\n\rCurrent Memory Latency:%d",FRAM.Memory_Latency);
	
	
}


void guiSetRegLatency(void)
{
uint8_t reg_data;
printf("\n\rEnter Register Latency:");
	scanf("%2" SCNu8,&reg_data);
	FRAM_Set_Register_Latency(reg_data);

}
void guiGetRegLatency(void)
{
FRAM_Get_Register_Latency();
printf("\n\rCurrent Register Latency:%d",FRAM.Reg_Latency);
}


void Display_Menu_Commands (void)
{
	
	printf("\n\rFollowing Commands are supported in GUI\n\r");
	printf("\n\r*********************************************************************\r");
	printf("\n\r\t\t\tQSPI Opcodes Supported");
	printf("\n\r*********************************************************************\n\r");
	printf("\n\r			Opcodes\t\t		Description\t\t\n\r");
	printf("\n\t05\t\tRead Status Register 1\n\r");
	printf("\t07\t\tRead Status Register 2\n\r");
	printf("\t35\t\tRead Configuration Register 1\n\r");
	printf("\t3F\t\tRead Configuration Register 2\n\r");
	printf("\t45\t\tRead Configuration Register 4\n\r");
	printf("\t5E\t\tRead Configuration Register 5\n\r");
	printf("\t71\t\tWrite Any Register\n\r");
	printf("\t65\t\tRead Any Register\n\r");
	printf("\t9F\t\tRead ID Register\n\r");
	printf("\tC3\t\tRead Serial Number Register\n\r");
	printf("\tC2\t\tWrite Serial Number Register.\n\r\t\t\tEnter each byte seperated by a space\n\r");
	printf("\n\t4C\t\tRead Unique ID Register\n\r");
	printf("\t06\t\tIssue Write Enable\n\r");
	printf("\t04\t\tIssue Write Disable\n\r");
	printf("\t02\t\tInitiate Memory Write with Opcode 0x02\n\r");
	printf("\tDA\t\tInitiate Memory Fast Write with Opcode 0xDA\n\r");
	printf("\tA2\t\tInitiate Memory Write in DIW with Opcode 0xA2\n\r");
	printf("\tA1\t\tInitiate Memory Write in DIOW with Opcode 0xA1\n\r");
	printf("\t32\t\tInitiate Memory Write in QIW with Opcode 0x32\n\r");
	printf("\tD2\t\tInitiate Memory Write in QIOW with Opcode 0xD2\n\r");
	printf("\t03\t\tInitiate Memory Read with Opcode 0x03\n\r");
	printf("\t0B\t\tInitiate Memory Fast Read with Opcode 0x0B\n\r");
	printf("\t3B\t\tInitiate Memory Read in DOR with Opcode 0x3B\n\r");
	printf("\tBB\t\tInitiate Memory Read in DIOR with Opcode 0xBB\n\r");
	printf("\t6B\t\tInitiate Memory Read in QOR with Opcode 0x6B\n\r");
	printf("\tEB\t\tInitiate Memory Read in QIOR with Opcode 0xEB\n\r");
	printf("\n\r*********************************************************************\r");
	printf("\n\r\t\t\tSpecial Functions");
	printf("\n\r*********************************************************************\n\r");
	printf("\n\r	Special Commands\t\tDescription\t\t\n\r");
	printf("\t999\t\tPerforms Interface Reset.\n\r\t\t\tAll Registers restored to default\n\r");
	printf("\n\t111\t\tChanges the interface mode to SPI\n\r\t\t\tfor ST controller and F-RAM\n\r");
	printf("\n\t222\t\tChanges the interface mode to DPI\n\r\t\t\tfor ST controller and F-RAM\n\r");
	printf("\n\t444\t\tChanges the interface mode to QPI\n\r\t\t\tfor ST controller and F-RAM\n\r");
	printf("\n\t801\t\tRead Memory Latency value in F-RAM\n\r");
	printf("\t802\t\tSet Memory Latency value in F-RAM\n\r");
	printf("\t803\t\tRead Register Latency value in F-RAM\n\r");
	printf("\t804\t\tSet Memory Latency value in F-RAM\n\r");
	printf("\t123\t\tPerform Basic F-RAM Testing\n\r");
	printf("\n\r*********************************************************************\n\r");



}



void GUI_Menu(void)
{
uint32_t Opcode;
uint32_t address;
uint32_t length;	
	printf("\n\rEnter an Opcode/Command (000 for supported Features): \n\r");
	printf("Opcode/Command: ");
	scanf("%x",&Opcode);
	
	switch (Opcode)
	{
		case RDSR1: 									{ guiReadSR1(); break;}
		case RDSR2: 									{ guiReadSR2(); break;}
		case RDCR1: 									{ guiReadCR1(); break;}
		case RDCR2: 									{ guiReadCR2(); break;}
		case RDCR4: 									{ guiReadCR4(); break;}
		case RDCR5: 									{ guiReadCR5(); break;}
		case DID: 										{ guiReadID(); break;}
		case RUID: 										{ guiReadUID(); break;}
		case RDSN:										{ guiReadSN(); break;}
		case WRSN:										{ guiWriteSN(); break;}
		case READ: 										{ guiFRAMRead(address,length);	break;}	
		case FAST_READ:	 							{ guiFRAMFastRead(address,length);	break;}	
		case DOR_READ:	 							{ guiFRAMDORRead(address,length);	break;}	
		case DIOR_READ:	 							{ guiFRAMDIORRead(address,length);	break;}	
		case QOR_READ:	 							{ guiFRAMQORRead(address,length);	break;}	
		case QIOR_READ:	 							{ guiFRAMQIORRead(address,length);	break;}	
		
		case WRITE:	 									{ guiFRAMWrite(address,length);	break;}
		case FAST_WRITE:	 						{ guiFRAMFastWrite(address,length);	break;}
		case DIW:	 										{ guiFRAMDIWWrite(address,length);	break;}
		case DIOW:	 									{ guiFRAMDIOWWrite(address,length);	break;}
		case QIW:	 										{ guiFRAMQIWWrite(address,length);	break;}
		case QIOW:	 									{ guiFRAMQIOWWrite(address,length);	break;}
		
		case WRITE_ENABLE_CMD:	 			{ FRAM_WREN();break;}
		
		case WRAR:										{ guiWriteAnyReg(); break;}
		case RDAR:										{ guiReadAnyReg(); break;}
		
		case 0x444:										{FRAM_QPIEN(); break;}
		case 0x222:										{FRAM_DPIEN(); break;}
		case 0x111:										{FRAM_SPIEN(); break;}
		case 0x999:										{FRAM_Interface_Reset(); break;}
		case 0x801:										{guiGetMemLatency(); break;}
		case 0x803:										{guiGetRegLatency(); break;}
		case 0x802:										{guiSetMemLatency(); break;}
		case 0x804:										{guiSetRegLatency(); break;}
		case 0x123:										{
																		//guiReadID();
																		FRAM_Interface_Reset();
																		TestFRAMRegisters();
																		TestFRAMSPI(); 
																		TestFRAMDPI(); 
																		TestFRAMQPI(); 
																		FRAM_Interface_Reset();
																		break;
														}
		case 0x000: 								{Display_Menu_Commands(); break;}
		
		
		default: printf("\nIllegal Opcode\n"); break;
		
	}

}
