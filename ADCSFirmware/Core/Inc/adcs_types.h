/*
 * adcs_types.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_ADCS_TYPES_H_
#define INC_ADCS_TYPES_H_

//Bit 7 of Telecommand and Telemetry Request - Section 4.1 of Firmware Manual
#define ADCS_TELECOMMAND 0;
#define ADCS_TELEMETRY_REQUEST 1;

//ADCS Magic Number defined in Section 5.1 Table 10 of Firmware Manual
#define ADCS_MAGIC_NUMBER 0x5A;

//Identifiers of Start of Message and End of Message - Section 4.2 of Firmware Manual
// 0x1F | 0x7F ....... | 0x1F 0xFF
#define ADCS_ESC_CHARACTER 0X1F;
#define ADCS_START_OF_MESSAGE 0x7F;
#define ADCS_END_OF_MESSAGE 0xFF;

#endif /* INC_ADCS_TYPES_H_ */
