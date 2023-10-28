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
#define ADCS_MAGIC_NUMBER 0x5A; // Used to make sure that the reset command is valid

//Identifiers of Start of Message and End of Message - Section 4.2 of Firmware Manual
// 0x1F | 0x7F ....... | 0x1F 0xFF
#define ADCS_ESC_CHARACTER 0X1F;
#define ADCS_START_OF_MESSAGE 0x7F;
#define ADCS_END_OF_MESSAGE 0xFF;

// Telecommand IDs - Section 6.1.1 Table 9 of Firmware Manual
#define TC_RESET 1; // must be followed by ADCS_MAGIC_NUMBER to confirm reset
#define TC_RESET_LOG_POINTER 4;
#define TC_ADVANCE_LOG_POINTER 5;
#define TC_RESET_BOOT_REGISTERS 6;
#define TC_FORMAT_SD 33;  // must be followed by ADCS_MAGIC_NUMBER to confirm format
#define TC_ERASE_FILE 108;
#define TC_LOAD_FILE_DOWNLOAD_BLOCK 112;
#define TC_ADVANCE_FILELIST_READ_PTR 113;
#define TC_INIT_FILE_UPLOAD 114;
#define TC_FILE_UPLOAD_PACKET 115;
#define TC_FINALIZE_UPLOAD_BLOCK 116;
#define TC_RESET_UPLOAD_BLOCK 117;
#define TC_RESET_FILELIST_READ_PTR 118;
#define TC_INIT_DOWNLOAD_BURST 119;

// Telemetry Frame IDs - Section 6.1.2 Table 26 of Firmware Manual
#define TLF_IDENTIFICATION 128;
#define TLF_BOOT_RUNNING_PROGRAM_STATUS 129;
#define TLF_BOOT_INDEX_STATUS 130;
#define TLF_LAST_LOGGED_EVENT 141;
#define TLF_FORMAT_SD 234;
#define TLF_TC_ACK 240;
#define TLF_FILE_DOWNLOAD_BUFFER 241;
#define TLF_DOWNLOAD_BLOCK_READY 242;
#define TLF_FILE_INFO 243;
#define TLF_INIT_UPLOAD_COMPLETE 244;
#define TLF_UPLOAD_BLOCK_COMPLETE 245;
#define TLF_BLOCK_CHECSUM 246;

#endif /* INC_ADCS_TYPES_H_ */
