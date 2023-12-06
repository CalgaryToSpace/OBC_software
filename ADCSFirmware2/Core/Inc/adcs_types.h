/*
 * adcs_types.h
 *
 *  Created on: Oct 28, 2023
 *      Authors: Saksham Puri, Zachary Uy, Nadeem Moosa
 */

#ifndef INC_ADCS_TYPES_H_
#define INC_ADCS_TYPES_H_

//Bit 7 of Telecommand and Telemetry Request - Section 4.1 of Firmware Manual
#define ADCS_TELECOMMAND 0
#define ADCS_TELEMETRY_REQUEST 1

//ADCS Magic Number defined in Section 5.1 Table 10 of Firmware Manual
#define ADCS_MAGIC_NUMBER 0x5A // Used to make sure that the reset command is valid

//Identifiers of Start of Message and End of Message - Section 4.2 of Firmware Manual
// 0x1F | 0x7F ....... | 0x1F 0xFF
#define ADCS_ESC_CHARACTER 0X1F
#define ADCS_START_MESSAGE 0x7F
#define ADCS_END_MESSAGE 0xFF

// CRC defines
#define CRC_POLY 0x91

// Common Telecommand IDs - Section 6.1.1 Table 9 of Firmware Manual
#define TC_RESET 1 // must be followed by ADCS_MAGIC_NUMBER to confirm reset
#define TC_RESET_LOG_POINTER 4
#define TC_ADVANCE_LOG_POINTER 5
#define TC_RESET_BOOT_REGISTERS 6
#define TC_FORMAT_SD 33  // must be followed by ADCS_MAGIC_NUMBER to confirm format
#define TC_ERASE_FILE 108
#define TC_LOAD_FILE_DOWNLOAD_BLOCK 112
#define TC_ADVANCE_FILELIST_READ_PTR 113
#define TC_INIT_FILE_UPLOAD 114
#define TC_FILE_UPLOAD_PACKET 115
#define TC_FINALIZE_UPLOAD_BLOCK 116
#define TC_RESET_UPLOAD_BLOCK 117
#define TC_RESET_FILELIST_READ_PTR 118
#define TC_INIT_DOWNLOAD_BURST 119

// Common Telemetry Frame IDs - Section 6.1.2 Table 26 of Firmware Manual
#define TLF_IDENTIFICATION 128
#define TLF_BOOT_RUNNING_PROGRAM_STATUS 129
#define TLF_BOOT_INDEX_STATUS 130
#define TLF_LAST_LOGGED_EVENT 141
#define TLF_FORMAT_SD 234
#define TLF_TC_ACK 240
#define TLF_FILE_DOWNLOAD_BUFFER 241
#define TLF_DOWNLOAD_BLOCK_READY 242
#define TLF_FILE_INFO 243
#define TLF_INIT_UPLOAD_COMPLETE 244
#define TLF_UPLOAD_BLOCK_COMPLETE 245
#define TLF_BLOCK_CHECKSUM 246
#define TLF_SATSTATE_SRAM_LATCHUP_COUNTERS 142
#define TLF_SATSTATE_EDAC_ERROR_COUNTERS 143
#define TLF_SATSTATE_COMM_STATUS 144

// CubeACP Telecommand IDs - Section 5.3.1 Table 72 of Firmware Manual
#define TC_DEPLOY_MAGNETOMETER_BOOM 7
#define TC_ADCS_RUN_MODE 10
#define TC_CLEAR_ERRORS 12
#define TC_SET_ATTITUDE_CONTROL_MODE 13
#define TC_SET_ATTITUDE_ESTIMATION_MODE 14
#define TC_TRIGGER_ADCS_LOOP 18
#define TC_TRIGGER_ADCS_LOOP_WITH_SIMULATED_SENSOR_DATA 19
#define TC_ASGP4_RUN_MODE 31
#define TC_ASGP4_TRIGGER 32
#define TC_SET_MODE_OF_MAGNETOMETER_OPERATION 56
#define TC_CONVERT_TO_JPG_FILE 57
#define TC_SAVE_IMAGE 80
#define TC_SET_MAGNETORQUER_OUTPUT 16
#define TC_SET_WHEEL_SPEED 17
#define TC_SAVE_CONFIG 63
#define TC_SAVE_ORBIT_PARAMS 64

// Telecommand Error Flags - Section 5.2.2 Figure 6 of Firmware Manual
#define TC_ERROR_NONE 0
#define TC_ERROR_INVALID_ID 1
#define TC_ERROR_WRONG_LENGTH 2
#define TC_ERROR_INVALID_PARAMS 3
#define TC_ERROR_CRC 4

#endif /* INC_ADCS_TYPES_H_ */
