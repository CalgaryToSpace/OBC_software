/******************************************************************************
* Project Name		: CY15FRAMKIT-002
* Version		: 1.0
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
/** @file guiMENU.h
 *  
 *  @brief Header File for accessing QSPI FRAM GUI commands
 *  @author	NILE
 *  @date 6/22/2018  
 *  Rev 1.1
 */
 
#include "usart.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdbool.h>
#include <inttypes.h>

void TestFRAMSPI(void);
void TestFRAMDPI(void);
void TestFRAMQPI(void);
void TestFRAMRegisters (void);

void GUI_Menu(void);
void guiReadSR1(void);
void guiReadSR2(void);
void guiReadCR1(void);
void guiReadCR2(void);
void guiReadCR4(void);
void guiReadCR5(void);
void guiReadID (void);
void guiReadUID (void);

void guiFRAMRead (uint32_t address,	uint32_t read_length);
void guiFRAMFastRead (uint32_t address,	uint32_t read_length);
void guiFRAMDORRead (uint32_t address,	uint32_t read_length);
void guiFRAMDIORRead (uint32_t address,	uint32_t read_length);
void guiFRAMQORRead (uint32_t address,	uint32_t read_length);
void guiFRAMQIORRead (uint32_t address,	uint32_t read_length);


void guiFRAMWrite (uint32_t address,	uint32_t read_length);
void guiFRAMFastWrite (uint32_t address,	uint32_t read_length);
void guiFRAMDIWWrite (uint32_t address,	uint32_t read_length);
void guiFRAMDIOWWrite (uint32_t address,	uint32_t read_length);
void guiFRAMQIWWrite (uint32_t address,	uint32_t read_length);
void guiFRAMQIOWWrite (uint32_t address,	uint32_t read_length);

void guiFRAMDDRWrite (uint32_t address,	uint32_t read_length);
void guiFRAMDDRFastWrite (uint32_t address,	uint32_t read_length);
void guiFRAMDDRQIOWWrite (uint32_t address,	uint32_t read_length);




void guiReadSN (void);
void guiWriteSN (void);
void guiWriteAnyReg(void);
void guiReadAnyReg(void);
void guiSetMemLatency(void);
void guiGetMemLatency(void);
void guiSetRegLatency(void);
void guiGetRegLatency(void);
void Display_Menu_Commands (void);


