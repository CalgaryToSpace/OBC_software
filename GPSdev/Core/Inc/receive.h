/*
 * receive.ch
 *  Created on: Jul 4, 2022
 *      Author: mswel
 */

#ifndef INC_RECEIVE_H_
#define INC_RECEIVE_H_

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

#endif /* INC_RECEIVE_H_ */


