/*
 * receive.ch
 *  Created on: Jul 4, 2022
 *      Author: mswel
 */

#ifndef INC_RECEIVE_H_
#define INC_RECEIVE_H_
#define CRC32_POLYNOMIAL 0xEDB88320L

enum Info{
	Sync = 0,
	Message = 1,
	Port = 2,
	Sequence = 3,
	IdleTime = 4,
	TimeStatus = 5,
	Week = 6,
	Seconds = 7,
	ReceiverStatus = 8,
	Reserved = 9,
	ReceiverSWVersion = 10
};

char** gpsParseReceive(char* received);

/* --------------------------------------------------------------------------
From OEM7_Commands_Logs_Manual.pdf
Calculate a CRC value to be used by CRC calculation functions.
-------------------------------------------------------------------------- */
CRC32Value(int i);

/* --------------------------------------------------------------------------
From OEM7_Commands_Logs_Manual.pdf
Calculates the CRC-32 of a block of data all at once
ulCount - Number of bytes in the data block
ucBuffer - Data block
-------------------------------------------------------------------------- */
CalculateBlockCRC32( unsigned long ulCount, unsigned char*ucBuffer );

#endif /* INC_RECEIVE_H_ */


