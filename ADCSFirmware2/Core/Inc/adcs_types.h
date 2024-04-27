/*
 * adcs_types.h
 *
 *  Created on: Oct 28, 2023
 *      Authors: Saksham Puri, Zachary Uy, Nadeem Moosa
 */

#include "main.h"
#include <string.h>
#include <stdbool.h>

#ifndef INC_ADCS_TYPES_H_
#define INC_ADCS_TYPES_H_

//Bit 7 of Telecommand and Telemetry Request - Section 4.1 of Firmware Manual
#define ADCS_TELECOMMAND 0
#define ADCS_TELEMETRY_REQUEST 1

//ADCS Magic Number defined in Section 5.1 Table 10 of Firmware Manual
#define ADCS_MAGIC_NUMBER 0x5A // Used to make sure that the reset command is valid

//I2C Write and Read Addresses - Section 5.3 Table 5 of Firmware Manual
#define ADCS_I2C_WRITE 0xAE
#define ADCS_I2C_READ 0xAF
#define ADCS_I2C_ADDRESS 0x57

//Identifiers of UART Start of Message and End of Message - Section 4.2 of Firmware Manual
// 0x1F | 0x7F ....... | 0x1F 0xFF
#define ADCS_ESC_CHARACTER 0x1F
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

// Bootloader Telecommand IDs - Section 6.2.1 Table 60 of Firmware Manua
#define TC_BL_CLEAR_ERRORS 7
#define TC_BL_SET_INDEX 100
#define	TC_BL_RUN_PROGRAM 101
#define TC_BL_READ_INFO 102
#define TC_BL_COPY_TO_FLASH 103

/* Enumerated Values */

// Telecommand Error Flags - Section 5.2.2 Figure 6 of Firmware Manual
typedef enum TC_Error_Flag {
	TC_Error_None,
	TC_Error_Invalid_ID,
	TC_Error_Wrong_Length,
	TC_Error_Invalid_Params,
	TC_Error_CRC
} TC_Error_Flag;

 // ADCS Run Modes - Section 5.3.1 Table 75 of Firmware Manual
typedef enum ADCS_Run_Mode {
	ADCS_Run_Mode_Off,
	ADCS_Run_Mode_Enabled,
	ADCS_Run_Mode_Triggered,
	ADCS_Run_Mode_Simulation
} ADCS_Run_Mode;

// ADCS Reset Causes - Section 6.1.2 Table 28 of Firmware Manual
typedef enum ADCS_Reset_Cause {
    ADCS_Power_On_Reset,
    ADCS_Brown_Out_Detected_On_Regulated_Power,
    ADCS_Brown_Out_Detected_On_Unregulated_Power,
    ADCS_External_Watchdog_Reset,
    ADCS_External_Reset,
    ADCS_Watchdog_Reset,
    ADCS_Lockup_System_Reset,
    ADCS_Lockup_Reset,
    ADCS_System_Request_Reset,
    ADCS_Backup_Brown_Out,
    ADCS_Backup_Mode_Reset,
    ADCS_Backup_Mode_Reset_And_Backup_Brown_Out_Vdd_Regulated,
    ADCS_Backup_Mode_Reset_And_Backup_Brown_Out_Vdd_Regulated_And_Brown_Out_Regulated,
    ADCS_Backup_Mode_Reset_And_Watchdog_Reset,
    ADCS_Backup_Brown_Out_Buvin_And_System_Request_Reset,
    ADCS_Unknown_Reset_Cause
} ADCS_Reset_Cause;

//ADCS Boot Causes - Section 6.1.2 Table 29 of Firmware Manual
typedef enum ADCS_Boot_Cause {
    ADCS_Boot_Cause_Unexpected,
    ADCS_Boot_Cause_Not_Used_1,
    ADCS_Boot_Cause_Communications_Timeout,
    ADCS_Boot_Cause_Commanded,
    ADCS_Boot_Cause_Not_Used_2,
    ADCS_Boot_Cause_SRAM_Latchup
} ADCS_Boot_Cause;

//ADCS Running Programs - Section 6.1.2 Table 30 of Firmware Manual
typedef enum ADCS_Running_Program {
    ADCS_Running_ADCS = 1,
    ADCS_Running_Bootloader = 2
} ADCS_Running_Program;

/* Structs */

typedef struct ADCS_TC_Ack_Struct {
	uint8_t last_id;
	bool processed;
	enum TC_Error_Flag error_flag;
	uint8_t error_index;
} ADCS_TC_Ack_Struct;

typedef struct ADCS_ID_Struct {
	uint8_t node_type;
	uint8_t interface_version;
	uint8_t major_firmware_version;
	uint8_t minor_firmware_version;
	uint16_t seconds_since_startup;
	uint16_t ms_past_second;
} ADCS_ID_Struct;

typedef struct ADCS_Boot_Running_Status_Struct{
    ADCS_Reset_Cause reset_cause;
    ADCS_Boot_Cause boot_cause;
    uint16_t boot_counter;
    ADCS_Running_Program boot_program_index;
    uint8_t major_firmware_version;
    uint8_t minor_firmware_version;
} ADCS_Boot_Running_Status_Struct;

typedef struct ADCS_Comms_Status_Struct{
    uint16_t tc_counter;
    uint16_t tlm_counter;
    bool tc_buffer_overrun;
    bool i2c_tlm_error;
    bool i2c_tc_error;
} ADCS_Comms_Status_Struct;

/* Function Definitions */

#define ADCS_I2C_HANDLE &hi2c1
#define ADCS_INCLUDE_CHECKSUM 1
#define ADCS_NO_CHECKSUM 0
#define WRITE_STRUCT_TO_MEMORY(struct_to_write) // memory module function: write struct to memory

// TC/TLM functions (basic communication)
void I2C_telecommand_wrapper(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum);
void I2C_telemetry_wrapper(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum);
void send_I2C_telecommand(I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum);
uint8_t send_I2C_telemetry_request (I2C_HandleTypeDef *hi2c, uint8_t id, uint8_t* data, uint32_t data_length, uint8_t include_checksum);

// CRC functions
void COMMS_Crc8Init();
uint8_t COMMS_Crc8Checksum(uint8_t* buffer, uint16_t len);

// UART debug functions
uint8_t send_UART_telecommand(UART_HandleTypeDef *huart, uint8_t id, uint8_t* data, uint32_t data_length);
void PRINT_STRING_UART(UART_HandleTypeDef *huart, void *string);
void PRINT_NEW_LINE(UART_HandleTypeDef *huart);

// ADCS functions
void ADCS_Reset(I2C_HandleTypeDef *hi2c);
void ADCS_Identification(I2C_HandleTypeDef *hi2c);
void ADCS_Program_Status(I2C_HandleTypeDef *hi2c);
void ADCS_Communication_Status(I2C_HandleTypeDef *hi2c);
void ADCS_Deploy_Magnetometer(I2C_HandleTypeDef *hi2c);
void ADCS_Set_Run_Mode(I2C_HandleTypeDef *hi2c, ADCS_Run_Mode mode);
void ADCS_Clear_Errors(I2C_HandleTypeDef *hi2c);
void ADCS_Attitude_Control_Mode(I2C_HandleTypeDef *hi2c, uint8_t mode);
void ADCS_Enable_Manual_Control(I2C_HandleTypeDef *hi2c);
void ADCS_Enable_Detumbling_Control(I2C_HandleTypeDef *hi2c);
void ADCS_Stop_Reaction_Wheels(I2C_HandleTypeDef *hi2c);
void ADCS_Attitude_Estimation_Mode(I2C_HandleTypeDef *hi2c, uint8_t mode);
ADCS_TC_Ack_Struct ADCS_TC_Ack(I2C_HandleTypeDef *hi2c);
void ADCS_Run_Once(I2C_HandleTypeDef *hi2c);
void ADCS_Use_Main_Magnetorquer(I2C_HandleTypeDef *hi2c);
void ADCS_Use_Redundant_Magnetorquer(I2C_HandleTypeDef *hi2c);
void ADCS_Use_Main_Magnetorquer_With_Alternate_Microcontroller(I2C_HandleTypeDef *hi2c);
void ADCS_Set_Magnetorquer_Output(I2C_HandleTypeDef *hi2c, uint16_t x_duty, uint16_t y_duty, uint16_t z_duty);
void ADCS_Set_Wheel_Speed(I2C_HandleTypeDef *hi2c, uint16_t x_speed, uint16_t y_speed, uint16_t z_speed);

#endif /* INC_ADCS_TYPES_H_ */
