/*
 * adcs_types.c
 *
 *  Created on: Mar 7, 2024
 *      Author: Nadeem Moosa, Saksham Puri, Zachary Uy
 */

#include <adcs_types.h>

void ADCS_Reset(I2C_HandleTypeDef *hi2c) {
	// returns telecommand error flag
	uint8_t data_send[1] = {ADCS_MAGIC_NUMBER};
	I2C_telecommand_wrapper(hi2c, TC_RESET, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Identification(I2C_HandleTypeDef *hi2c) {
	I2C_telemetry_wrapper(hi2c, TLF_IDENTIFICATION, ADCS_output, 8, ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Program_Status(I2C_HandleTypeDef *hi2c) {
	// checks whether the bootloader or ADCS is running
	// returns 0x01 for ADCS, 0x02 for bootloader
	I2C_telemetry_wrapper(hi2c, TLF_BOOT_RUNNING_PROGRAM_STATUS, ADCS_output, 6, ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Communication_Status(I2C_HandleTypeDef *hi2c) {
	// returns I2C communication status of the ADCS (Table 37)
	// bit 0 is 1 if TC buffer was overrun while receiving a telecommand
	// bit 3 is 1 if the number of data clocked out was more than the telemetry package
	// bit 4 is 1 if the telecommand sent exceeded the buffer size
	// other bits are for UART and CAN; ignore them
	I2C_telemetry_wrapper(hi2c, TLF_BOOT_RUNNING_PROGRAM_STATUS, ADCS_output, 6, ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Deploy_Magnetometer(I2C_HandleTypeDef *hi2c) {
	// Deploys the magnetometer boom
	uint8_t data_send[1] = {0xFF};
	I2C_telecommand_wrapper(hi2c, TC_DEPLOY_MAGNETOMETER_BOOM, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Disable(I2C_HandleTypeDef *hi2c) {
	// Disables the ADCS
	uint8_t data_send[1] = {ADCS_RUN_MODE_OFF};
	I2C_telecommand_wrapper(hi2c, TC_ADCS_RUN_MODE, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Enable_On(I2C_HandleTypeDef *hi2c) {
	// Enables the ADCS in always-on mode
	uint8_t data_send[1] = {ADCS_RUN_MODE_ENABLED};
	I2C_telecommand_wrapper(hi2c, TC_ADCS_RUN_MODE, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Enable_Triggered(I2C_HandleTypeDef *hi2c) {
	// Enables the ADCS in triggered mode
	uint8_t data_send[1] = {ADCS_RUN_MODE_TRIGGERED};
	I2C_telecommand_wrapper(hi2c, TC_ADCS_RUN_MODE, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Clear_Errors(I2C_HandleTypeDef *hi2c) {
	// Clears error flags
	// NOTE: THERE IS ANOTHER, SEPARATE CLEAR ERROR FLAG TC FOR THE BOOTLODER (TC_BL_CLEAR_ERRORS)
	uint8_t data_send[1] = {0b11000000};
	I2C_telecommand_wrapper(hi2c, TC_CLEAR_ERRORS, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Attitude_Control_Mode(I2C_HandleTypeDef *hi2c, uint8_t mode) {
	// Sets the ADCS attitude control mode
	// Possible values for mode given in Section 6.3 Table 77 of Firmware Reference Manual (ranges from 0 to 15)
	uint8_t data_send[3] = {mode, 0xFF, 0xFF};
	I2C_telecommand_wrapper(hi2c, TC_SET_ATTITUDE_CONTROL_MODE, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Enable_Manual_Control(I2C_HandleTypeDef *hi2c) {
	// allows to run ADCS_Set_Magnetorquer_Output and ADCS_Set_Wheel_Speed
	ADCS_Attitude_Control_Mode(hi2c, 0);
}

void ADCS_Enable_Detumbling_Control(I2C_HandleTypeDef *hi2c) {
	ADCS_Attitude_Control_Mode(hi2c, 1);
}

void ADCS_Stop_Reaction_Wheels(I2C_HandleTypeDef *hi2c) {
	ADCS_Attitude_Control_Mode(hi2c, 12);
}


void ADCS_Attitude_Estimation_Mode(I2C_HandleTypeDef *hi2c, uint8_t mode) {
	// Sets the ADCS attitude estimation mode
	// Possible values for mode given in Section 6.3 Table 80 of Firmware Reference Manual (ranges from 0 to 7)
	uint8_t data_send[1] = {mode};
	I2C_telecommand_wrapper(hi2c, TC_SET_ATTITUDE_ESTIMATION_MODE, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_TC_Ack(I2C_HandleTypeDef *hi2c) {
	I2C_telemetry_wrapper(hi2c, TLF_TC_ACK, ADCS_output, 4, ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Run_Once(I2C_HandleTypeDef *hi2c) {
	// requires ADCS_Enable_Triggered to have run first
	// (if ADCS_Enable_On has run instead, then this is unnecessary)
	uint8_t data_send[0];
	I2C_telecommand_wrapper(hi2c, TC_TRIGGER_ADCS_LOOP, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Use_Main_Magnetorquer(I2C_HandleTypeDef *hi2c) {
	uint8_t data_send[1] = {0};
	I2C_telecommand_wrapper(hi2c, TC_SET_MODE_OF_MAGNETOMETER_OPERATION, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Use_Redundant_Magnetorquer(I2C_HandleTypeDef *hi2c) {
	uint8_t data_send[1] = {1};
	I2C_telecommand_wrapper(hi2c, TC_SET_MODE_OF_MAGNETOMETER_OPERATION, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Use_Main_Magnetorquer_With_Alternate_Microcontroller(I2C_HandleTypeDef *hi2c) {
	uint8_t data_send[1] = {2};
	I2C_telecommand_wrapper(hi2c, TC_SET_MODE_OF_MAGNETOMETER_OPERATION, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Set_Magnetorquer_Output(I2C_HandleTypeDef *hi2c, uint16_t x_duty, uint16_t y_duty, uint16_t z_duty) {
	// only valid after ADCS_Enable_Manual_Control is run
	// for the duty equations, raw parameter value is obtained using the formula: (raw parameter) = (formatted value)*1000.0
	// duty >> 8 gives upper byte, duty & 0x00FF gives lower byte
	uint8_t data_send[6] = {x_duty & 0x00FF, x_duty >> 8, y_duty & 0x00FF, y_duty >> 8, z_duty & 0x00FF, z_duty >> 8};
	I2C_telecommand_wrapper(hi2c, TC_SET_MAGNETORQUER_OUTPUT, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}

void ADCS_Set_Wheel_Speed(I2C_HandleTypeDef *hi2c, uint16_t x_speed, uint16_t y_speed, uint16_t z_speed) {
	// only valid after ADCS_Enable_Manual_Control is run
	// for the duty equations, raw parameter value is in rpm
	// duty >> 8 gives upper byte, duty & 0x00FF gives lower byte
	uint8_t data_send[6] = {x_speed & 0x00FF, x_speed >> 8, y_speed & 0x00FF, y_speed >> 8, z_speed & 0x00FF, z_speed >> 8};
	I2C_telecommand_wrapper(hi2c, TC_SET_WHEEL_SPEED, data_send, sizeof(data_send), ADCS_INCLUDE_CHECKSUM);
}




/**
 * I2C_telecommand_wrapper
 * REQUIRES:
 *  - hi2c points to valid I2C handle (ex. &hi2c1)
 *  - id is a valid telecommand ID (see Firmware Reference Manual)
 *  - data points to array of uint8_t with length at least data_length (should contain the correct number of bytes for the given telecommand ID)
 *  - include_checksum is either ADCS_INCLUDE_CHECKSUM or ADCS_NO_CHECKSUM
 * PROMISES:
 * 	- sends telecommand to ADCS and checks that it has been acknowledged
 * 	- returns the error flag from the result of the transmission
 */
void I2C_telecommand_wrapper(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum) {
    uint8_t TC_err_flag;

    do {
		// Send telecommand
		send_I2C_telecommand(hi2c, id, data, data_length, include_checksum);

		// Poll Acknowledge Telemetry Format until the Processed flag equals 1.
		uint8_t processed = 0;
		while (!processed) {
			ADCS_TC_Ack(hi2c);
			processed = ADCS_output[1] & 1;
		}

		// Confirm telecommand validity by checking the TC Error flag of the last read TC Acknowledge Telemetry Format.
		TC_err_flag = ADCS_output[2];

    } while (TC_err_flag == 0x04);  // if the checksum doesn't check out, keep resending the request

}

/**
 * I2C_telemetry_wrapper
 * REQUIRES:
 *  - hi2c points to valid I2C handle (ex. &hi2c1)
 *  - id is a valid telemetry request ID (see Firmware Reference Manual)
 *  - data points to array of uint8_t with length at least data_length (should contain the correct number of bytes for the given telemetry request ID)
 *  - include_checksum is either ADCS_INCLUDE_CHECKSUM or ADCS_NO_CHECKSUM
 * PROMISES:
 * 	- Return value is 1 if checksum value doesn't match, 0 for any other successful transmission (including with no checksum)
 * 	- data array filled with result of transmission
 */
void I2C_telemetry_wrapper(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum) {
    // Send telemetry request (data gets stored to input data array)
	uint8_t checksum_check = send_I2C_telemetry_request(hi2c, id, data, data_length, include_checksum);

	while (checksum_check == 1) {
		// if the checksum doesn't check out, keep resending the request
		checksum_check = send_I2C_telemetry_request(hi2c, id, data, data_length, include_checksum);
	}
}


/**
 * send_I2C_telecommand
 * REQUIRES:
 *  - hi2c points to valid I2C handle (ex. &hi2c1)
 *  - id is a valid telecommand ID (see Firmware Reference Manual)
 *  - data points to array of uint8_t with length at least data_length (should contain the correct number of bytes for the given telecommand ID)
 *  - include_checksum is either ADCS_INCLUDE_CHECKSUM or ADCS_NO_CHECKSUM
 * PROMISES:
 * 	- Transmits data to the ADCS over I2C
 */
void send_I2C_telecommand(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum) {
	// Telecommand Format:
	// ADCS_ESC_CHARACTER, ADCS_START_MESSAGE [uint8_t TLM/TC ID], ADCS_ESC_CHARACTER, ADCS_END_MESSAGE
	// The defines in adcs_types.h already include the 7th bit of the ID to distinguish TLM and TC

	//Allocate only required memory
	uint8_t buf[data_length + include_checksum]; // add additional bit for checksum if needed

	// Fill buffer with Data if transmitting a Telecommand
	for (int i = 0; i < data_length; i++) {
		buf[i] = data[i];
	}

	// include checksum following data if enabled
	if (include_checksum) {buf[data_length] = COMMS_Crc8Checksum(data, data_length);}

	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // wait until ready
	HAL_I2C_Mem_Write_IT(hi2c, ADCS_I2C_ADDRESS << 1, id, 1, buf, sizeof(buf));
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // wait until finished
	//HAL_I2C_Master_Transmit(hi2c, ADCS_I2C_ADDRESS, buf, sizeof(buf), HAL_MAX_DELAY);

	/* When sending a command to the CubeACP, it is possible to include an 8-bit CRC checksum.
	For instance, when sending a command that has a length of 8 bytes, it is possible to include a
	9th byte that is computed from the previous 8 bytes. The extra byte will be interpreted as a
	checksum and used to validate the message. If the checksum fails, the command will be
	ignored. For I2C communication, the Tc Error Status in the Telecommand Acknowledge telemetry frame
	(Table 39: Telecommand Acknowledge Telemetry Format) will have a value of 4. */

}

/**
 * send_I2C_telemetry_request
 * REQUIRES:
 *  - hi2c points to valid I2C handle (ex. &hi2c1)
 *  - id is a valid telemetry request ID (see Firmware Reference Manual)
 *  - data points to array of uint8_t with length at least data_length (should contain the correct number of bytes for the given telemetry request ID)
 *  - include_checksum is either ADCS_INCLUDE_CHECKSUM or ADCS_NO_CHECKSUM
 * PROMISES:
 * 	- Return value is 1 if checksum value doesn't match, 0 for any other successful transmission (including with no checksum)
 * 	- data array filled with result of transmission
 */
uint8_t send_I2C_telemetry_request (I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum) {
	// Telemetry Request Format:
	// Note: requires a repeated start condition; data_length is number of bits to read.
	// [start], ADCS_I2C_WRITE, id, [start] ADCS_I2C_READ, [read all the data], [stop]
	// The defines in adcs_types.h already include the 7th bit of the ID to distinguish TLM and TC

	/* When requesting telemetry through I2C, it is possible to read one extra byte past the allowed
	length of the telemetry frame. In this case, the extra byte will also be an 8-bit checksum
	computed by the CubeACP and can be used by the interfacing OBC to validate the message.*/

	//Allocate only required memory
	uint8_t temp_data[data_length + include_checksum];
		// temp data used for checksum checking

	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // wait until ready
	HAL_I2C_Mem_Read_IT(hi2c, ADCS_I2C_ADDRESS << 1, id, 1, temp_data, sizeof(temp_data));
	// read the data using the EEPROM protocol (handled by built-in Mem_Read function)
		// ADCS_I2C_ADDRESS << 1 = ADCS_I2C_WRITE, and (ADCS_I2C_ADDRESS << 1) | 0x01 = ADCS_I2C_READ
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // wait until finished

	for (int i = 0; i < data_length; i++) {
			// populate external data, except for checksum byte
			data[i] = temp_data[i];
	}

	if (include_checksum) {
		uint8_t checksum = temp_data[data_length];
		uint8_t checksum_test = COMMS_Crc8Checksum(data, data_length);
		if (checksum != checksum_test) {
			return 1;
		}
	}

	return 0;

}

uint8_t send_UART_telecommand(UART_HandleTypeDef *huart, uint8_t id, uint8_t* data, uint32_t data_length) {
	// WARNING: DEPRECATED FUNCTION
	// This function is incomplete, and will not be updated.
	// USE AT YOUR OWN RISK.

	// Telemetry Request or Telecommand Format:
	// ADCS_ESC_CHARACTER, ADCS_START_MESSAGE [uint8_t TLM/TC ID], ADCS_ESC_CHARACTER, ADCS_END_MESSAGE
	// The defines in adcs_types.h already include the 7th bit of the ID to distinguish TLM and TC
	// data bytes can be up to a maximum of 8 bytes; data_length ranges from 0 to 8

	//Check id to identify if it's Telecommand or Telemetry Request
	uint8_t telemetry_request = id & 0b10000000; // 1 = TLM, 0 = TC

	//Allocate only required memory by checking first bit of ID
	uint8_t buf[5 + (!telemetry_request)*data_length];

	//Fill buffer with ESC, SOM and ID
	buf[0] = ADCS_ESC_CHARACTER;
	buf[1] = ADCS_START_MESSAGE;
	buf[2] = id;

	if (telemetry_request) {
		//If transmitting Telemetry Request
		//Fill buffer with ESC and EOM without data_length
		buf[3] = ADCS_ESC_CHARACTER;
		buf[4] = ADCS_END_MESSAGE;
	} else {
		//Fill buffer with Data if transmitting a Telecommand
		for (int i = 0; i < data_length; i++) {
			buf[i + 3] = data[i];
		}
		//Fill buffer with ESC and EOM
		buf[3 + data_length] = ADCS_ESC_CHARACTER;
		buf[4 + data_length] = ADCS_END_MESSAGE;
	}

	//Transmit the TLM or TC via UART
	HAL_UART_Transmit(huart, buf, strlen((char*)buf), HAL_MAX_DELAY);

	//receiving from telecommand: data is one byte exactly
	//receiving from telemetry request: data is up to 8 bytes

	//Allocate only required memory
	uint8_t buf_rec[6 + (telemetry_request)*(data_length-1)];

	//Start receiving acknowledgment or reply from the CubeComputer
	HAL_UART_Receive(huart, buf_rec, strlen((char*)buf_rec), HAL_MAX_DELAY);

	if (telemetry_request) {
		//Ignoring ESC, EOM, SOM and storing the rest of the values in data
		for (int i = 3; i < sizeof(buf_rec)-2; i++) {
			// put the data into the data array excluding TC ID or TLM ID
			data[i-3] = buf_rec[i];
		}

		return TC_ERROR_NONE;
	}

	return buf_rec[3]; // buf_rec[3] contains the TC Error Flag

  // The reply will contain two data bytes, the last one being the TC Error flag.
  // The receipt of the acknowledge will indicate that another telecommand may be sent.
  // Sending another telecommand before the acknowledge will corrupt the telecommand buffer.
}


// CRC initialisation
// init lookup table for 8-bit crc calculation

uint8_t CRC8Table[256];

void COMMS_Crc8Init()
	{
	int val;
	for (int i = 0; i < 256; i++)
	{
		val = i;
		for (int j = 0; j < 8; j++)
		{
			if (val & 1)
			val ^= CRC_POLY;
			val >>= 1;
		}
		CRC8Table[i] = val;
	}
}



/***************************************************************************//**
* Calculates an 8-bit CRC value
*
* @param[in] buffer
* the buffer containing data for which to calculate the crc value
* @param[in] len
* the number of bytes of valid data in the buffer
******************************************************************************/
uint8_t COMMS_Crc8Checksum(uint8_t* buffer, uint16_t len)
{
	if (len == 0) return 0xff;

	uint16_t i;
	uint8_t crc = 0;

	for (i = 0; i < len; i++)
		crc = CRC8Table[crc ^ buffer[i]];

	return crc;
}


//Debug function to print a new line (\n) in UART
void PRINT_NEW_LINE(UART_HandleTypeDef *huart) {
    char buf[] = "\r\n";
    HAL_UART_Transmit(huart, (uint8_t*) buf, strlen(buf), 100);
}

//Debug function to print a given string to UART
void PRINT_STRING_UART(UART_HandleTypeDef *huart, void *string) {

//    char *buff = (char*) string;
    HAL_UART_Transmit(huart, (uint8_t*) string, strlen((char*) string), 100);
    PRINT_NEW_LINE(huart);
//    memset(string, 0, strlen((char*) string));
}

