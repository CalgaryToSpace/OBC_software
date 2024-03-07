/*
 * adcs_types.c
 *
 *  Created on: Mar 7, 2024
 *      Author: Nadeem Moosa, Saksham Puri, Zachary Uy
 */

#include <adcs_types.h>

uint8_t I2C_telecommand_wrapper(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length) {
    // Send telecommand
    send_I2C_telecommand(hi2c, id, data, data_length);

    // Poll Acknowledge Telemetry Format until the Processed flag equals 1.
    uint8_t processed = 0;
    uint8_t tc_ack[4];
    while (!processed) {
        send_I2C_telemetry_request(hi2c, TLF_TC_ACK, tc_ack, 4);
        processed = tc_ack[1] & 1;
    }

    // Confirm telecommand validity by checking the TC Error flag of the last read TC Acknowledge Telemetry Format.
    uint8_t TC_err_flag = tc_ack[2];

    return TC_err_flag;
}

void send_I2C_telecommand(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length) {
	// Telecommand Format:
	// ADCS_ESC_CHARACTER, ADCS_START_MESSAGE [uint8_t TLM/TC ID], ADCS_ESC_CHARACTER, ADCS_END_MESSAGE
	// The defines in adcs_types.h already include the 7th bit of the ID to distinguish TLM and TC
	// data bytes can be up to a maximum of 8 bytes; data_length ranges from 0 to 8

	//Allocate only required memory
	uint8_t buf[2 + data_length];

	buf[0] = ADCS_I2C_WRITE;
	buf[1] = id;

	// Fill buffer with Data if transmitting a Telecommand
	for (int i = 0; i < data_length; i++) {
		buf[i + 2] = data[i];
	}

	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // implement delay for interrupt
	HAL_I2C_Master_Seq_Transmit_IT(hi2c, ADCS_I2C_ADDRESS << 1, buf, sizeof(buf)/sizeof(uint8_t), I2C_FIRST_AND_LAST_FRAME);
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // delay again until ready

}

void send_I2C_telemetry_request (I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length) {
	// Telemetry Request Format:
	// Note: requires a repeated start condition; data_lenth is number of bits to read.
	// [start], ADCS_I2C_WRITE, id, [start] ADCS_I2C_READ, [read all the data], [stop]
	// The defines in adcs_types.h already include the 7th bit of the ID to distinguish TLM and TC
	// data bytes can be up to a maximum of 8 bytes; data_length ranges from 0 to 8

	//Allocate only required memory
	uint8_t buf[2];

	buf[0] = ADCS_I2C_WRITE;
	buf[1] = id;

	uint8_t read_buf[1];
	read_buf[0] = ADCS_I2C_READ;

	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {} // delay until ready

	HAL_I2C_Master_Seq_Transmit_IT(hi2c, ADCS_I2C_ADDRESS << 1, buf, sizeof(buf)/sizeof(uint8_t), I2C_FIRST_AND_NEXT_FRAME);
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {}
	HAL_I2C_Master_Seq_Transmit_IT(hi2c, ADCS_I2C_ADDRESS << 1, read_buf, sizeof(read_buf)/sizeof(uint8_t), I2C_FIRST_AND_NEXT_FRAME);
	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {}
	// I2C_FIRST_AND_NEXT_FRAME has start condition, no stop condition, and allows for continuing on with another I2C Seq command

	HAL_I2C_Master_Seq_Receive_IT(hi2c, ADCS_I2C_ADDRESS << 1, data, data_length, I2C_LAST_FRAME);
	// This is my best guess at receiving data_length bytes of data and ending with a stop condition
	// But I will admit I don't really understand the XferOptions part of any of these commands

	while (HAL_I2C_GetState(hi2c) != HAL_I2C_STATE_READY) {}

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

