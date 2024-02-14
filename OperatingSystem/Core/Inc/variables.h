#include <stdint.h>

// defines places to write to. 
// in terminal.h
extern uint8_t internal_response_buffer[500]; // internal buffer for reading response of code

typedef enum
{
	TERM_ANY,
	TERM_UART1,
	TERM_UART2,
	TERM_NONE, // no terminal to write to
	TERM_INTERNAL_BUFFER, // FIXME: make this do something
} Terminal_stream;


// defined in common.h
extern uint8_t call[6];
extern uint8_t callSsid; //device ssid
extern uint8_t dest[7]; //destination address for own beacons. Should be APNV01-0 for VP-Digi, but can be changed. SSID MUST remain 0.

extern const uint8_t *versionString; //version string
//const uint8_t *versionString = (const uint8_t*)"VP-Digi v. 1.2.6\r\nThe open-source standalone APRS digipeater controller and KISS TNC\r\n";

extern uint8_t autoReset; // multiplied by 360000 and assigned to autoResetTimer
extern uint32_t autoResetTimer; // timer that when autoResetTimer time has passed triggers auto restart (NVIC_SystemReset())
extern uint8_t kissMonitor; // indicated whether we are in kiss monitoring mode or not (0 or 1)

//defined in beacon.h
typedef struct
{
	uint8_t enable; //enable beacon
	uint32_t interval; //interval in seconds
	uint32_t delay; //delay in seconds
	uint8_t data[101]; //information field
	uint8_t path[15]; //path, 2 parts max, e.g. WIDE1<sp>1SP2<sp><sp><sp>2<NUL>, <NUL> can be at byte 0, 7 and 14
	uint32_t next; //next beacon timestamp
} Beacon;

extern Beacon beacon[8];

//defined in digipeater.h
typedef struct
{
	uint8_t alias[8][6]; //digi alias list
	uint8_t ssid[4]; //ssid list for simple aliases
	uint8_t max[4]; //max n to digipeat
	uint8_t rep[4]; //min n to replace
	uint8_t traced; //tracing for each alias, 0 - untraced, 1 - traced
	uint8_t enableAlias; //enabling each alias, 0 - disabled, 1 - enabled
	uint8_t enable : 1; //enable whole digi
	uint8_t viscous; //visous-delay enable for each alias
	uint8_t directOnly; //direct-only enable for each alias
	uint8_t dupeTime; //duplicate filtering time in seconds
	uint8_t callFilter[20][7]; //callsign filter array
	uint8_t callFilterEnable; //enable filter by call for every alias
	uint8_t filterPolarity : 1; //filter polarity: 0 - blacklist, 1- whitelist
} Digi;

extern Digi digi; //digipeater state

//defined in dra_system.h
#define DRA_RESPONSE_BUF_SIZE 100
extern uint8_t latest_dra_response_buf[DRA_RESPONSE_BUF_SIZE];


// defined in mboss_handler
//referenced in beacon.c and mboss_handler.c

// APRS = Automatic Packet Reporting System
typedef enum {
	RF_APRS_MODE_INACTIVE = 0,
	RF_APRS_MODE_DIGIPEAT = 1,
	RF_APRS_MODE_STORE_AND_FORWARD = 2,
} RF_APRS_Mode_t;

extern RF_APRS_Mode_t current_aprs_mode;
extern uint32_t timestamp_sec_at_boot;
extern uint32_t uptime_at_last_success_failure_led_on;

// defined in sys_reboot_reason.h

//referenced in main.c and sys_reboot_reason.c
/// @brief  Possible STM32 system reset causes
typedef enum reset_cause_e
{
    RESET_CAUSE_UNKNOWN = 0,
    RESET_CAUSE_LOW_POWER_RESET,
    RESET_CAUSE_WINDOW_WATCHDOG_RESET,
    RESET_CAUSE_INDEPENDENT_WATCHDOG_RESET,
    RESET_CAUSE_SOFTWARE_RESET,
    RESET_CAUSE_POWER_ON_POWER_DOWN_RESET,
    RESET_CAUSE_EXTERNAL_RESET_PIN_RESET,
    RESET_CAUSE_BROWNOUT_RESET,
} reset_cause_t;
extern reset_cause_t this_boot_reset_cause; // NOTES FROM CODE: store once at boot because it can only be fetched once via `reset_cause_get()

