
#ifndef __INCLUDE_GUARD__GPS_TYPES_H__
#define __INCLUDE_GUARD__GPS_TYPES_H__

#include <stdint.h>
typedef enum {
	GPS_TIME_STATUS_UNKNOWN             = 20, // Time validity is unknown
	GPS_TIME_STATUS_APPROXIMATE         = 60, // Time is set approximately
	GPS_TIME_STATUS_COARSEADJUSTING     = 80, // Time is approaching coarse precision
	GPS_TIME_STATUS_COARSE              = 100, //This time is valid to coarse precision
	GPS_TIME_STATUS_COARSESTEERING      = 120, // Time is coarse set and is being steered
	GPS_TIME_STATUS_FREEWHEELING        = 130, // Position is lost and the range bias cannot be calculated
	GPS_TIME_STATUS_FINEADJUSTING       = 140, // Time is adjusting to fine precision
	GPS_TIME_STATUS_FINE                = 160, // Time has fine precision
	GPS_TIME_STATUS_FINEBACKUPSTEERING  = 170, // Time is fine set and is being steered by the backup system
	GPS_TIME_STATUS_FINESTEERING        = 180, // Time is fine set and is being steered
	GPS_TIME_STATUS_SATTIME             = 200, // Time from satellite. Only used in logs containing satellite data such as ephemeris and almanac

} GPS_TIME_STATUS_enum_t; //Table 13: GPS Reference Time Status

// Messgae ID: 241, 00x00F1: BESTXYZ
typedef struct {
	uint8_t sync_1; // 0xAA Uchar offset: 0
	uint8_t sync_2; // 0x44 Uchar offset: 1
	uint8_t sync_3; //0x12 Uchar offset: 2
	uint8_t header_length; //header length Uchar offset: 3
	uint16_t msg_id; //message id Ushort offset: 4
	int8_t msg_type; //message type char offset: 6
	uint8_t prt_addr; //port address Uchar offset: 7, table 5
	uint16_t msg_length; //message length Ushort offset: 8
	uint16_t sequence; //seqeunce Ushort offset: 10
	uint8_t idle_time; //idle time Uchar offset: 12
	GPS_TIME_STATUS_enum_t time_status; //time status Enum offset: 12, Table 13: GPS Reference Time Status
	uint16_t week; //GPS reference week number, offset: 14
	int32_t ms; //ms GPSEC, from beginning of reference week, long offset: 16
	uint32_t rcvr_status; //receiver status, Ulong, offset: 20, Table 199
	uint16_t reserved; //reserved for internal use, Ushort, offset: 24
	uint16_t rcvr_version; //0-65535, receiver software build number, Ushort, offset: 24
	uint32_t psol_status; //P-sol status, Enum, see table 92 offset: H
	uint32_t pos_type; //Position type, Enum, see table 93 offset: H+4
	int64_t p_x; //Position coord X (m), Double, offset: H+8
	int64_t p_y; //Position coord Y (m), Double, offset: H+16
	int64_t p_z; //Position coord Z (m), Double, offset: H+24
	int32_t p_x_omega; //Std dev P-X (m), Float, offset: H+32
	int32_t p_y_omega; //Std dev P-Y (m), Float, offset: H+36
	int32_t p_z_omega; //Std dev P-Z (m), Float, offset: H+40
	uint32_t vsol_status; //V-sol status, Enum, see table 92 offset: H+44
	uint32_t vel_type; //velocity type, Enum, see table 93 offset: H+48
	int64_t v_x; //velocity coord X (m), Double, offset: H+52
	int64_t v_y; //velocity coord Y (m), Double, offset: H+60
	int64_t v_z; //velocity coord Z (m), Double, offset: H+68
	int32_t v_x_omega; //Std dev V-X (m), Float, offset: H+76
	int32_t v_y_omega; //Std dev V-Y (m), Float, offset: H+80
	int32_t v_z_omega; //Std dev V-Z (m), Float, offset: H+84
	int8_t stn_id[4]; //Base station identification, Char[4], offset: H+88
	int32_t v_latency; //velocity time tag in seconds (subtract from time for improved results, Float, offset: H+92
	int32_t diff_age; //differential age in seconds, Float, offset: H+96
	int32_t sol_age; //Solution age in seconds, Float, offset: H+100
	uint8_t num_svs; //Number of satellites tracked, Uchar offset: H+104
	uint8_t num_soln_svs; //Number of satellites used in solution, Uchar offset: H+105
	uint8_t num_ggL1; //Number of satellites used in solution, Uchar offset: H+105


} eps_result_system_status_t;


#endif /* __INCLUDE_GUARD__GPS_TYPES_H__ */
