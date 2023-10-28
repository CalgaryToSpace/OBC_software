/*
 * adcs_types.h
 *
 *  Created on: Oct 28, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_ADCS_TYPES_H_
#define INC_ADCS_TYPES_H_

//Bit 7 of Telecommand and Telemetry Request - Section 4.1 of Firmware Manual
#define ADCS_Telecommand 0;
#define ADCS_Telemetery_Request 1;

//ADCS Magic Number defined in Section 5.1 Table 10 of Firmware Manual
#define ADCS_MAGIC_NUMBER 0x5A;

//Identifiers of Start of Message and End of Message
#define ADCS_SOM 0x7F;
#define ADCS_EOM 0xFF;

#endif /* INC_ADCS_TYPES_H_ */
