//-------------------------------------INFO---------------------------------------
// NAME: cy15_memory.h
// DESC: Header file for the SPI drivers for theCY15B108QN memory module
//--------------------------------------------------------------------------------

//----------------------------------INCLUDES--------------------------------------
//--------------------------------------------------------------------------------
#include "stdint.h"
#include "stdlib.h"

//-----------------------------------MACROS---------------------------------------
//--------------------------------------------------------------------------------
#define maxMemoryAddress 0x100000
#define maxChunkSize 1024
#define numberOfModules

//-----------------------------------STRUCTS--------------------------------------
//--------------------------------------------------------------------------------
typedef enum cy15ResponseEventEnum {
	CY15_EVENT_SUCCESS,
	CY15_ID_ERROR,
	CY15_SIZE_ERROR,
	CY15_EVENT_ERROR,
	CY15_NULL_DATA_ERROR,
	CY15_EVENT_CRC_ERROR,
	CY15_EVENT_COUNT
} cy15ResponseEventEnum;

typedef enum cy15ChunkDataEnum {
	EXP_DATA, GPS_DATA, CAMERA_DATA, MEM_LOG_DATA, DATA_COUNT
} cy15ChunkDataEnum;

typedef struct cy15ChunkStruct {
	cy15ChunkDataEnum id;
	uint32_t length;
	uint8_t *data;
	uint32_t checksum;
} cy15ChunkStruct;

typedef struct cy15ModuleStruct {
	uint8_t head;
	uint8_t tail;
} cy15ModuleStruct;

//----------------------------------VARIABLES-------------------------------------
//--------------------------------------------------------------------------------
int currentModule = 0;
cy15ModuleStruct cy15MemoryModules[numberOfModules];

//----------------------------------FUNCTIONS-------------------------------------
//--------------------------------------------------------------------------------
//---------------------------------DEFINITIONS------------------------------------
//--------------------------------------------------------------------------------
cy15ResponseEventEnum memWrite(cy15ChunkDataEnum id, uint8_t *data,
		uint32_t size);
cy15ResponseEventEnum memRead(cy15ChunkStruct *data);

static uint32_t memCreateChecksum(uint32_t crc, const char *buf, uint32_t len);

static uint8_t memWriteOp(uint8_t *data, uint8_t *address, uint32_t length, uint32_t bankNumber);

static uint8_t memReadOp(uint8_t *data_buffer, uint8_t *address);

cy15ResponseEventEnum memWriteC(cy15ChunkDataEnum id, uint8_t *data,
		uint32_t size);

cy15ResponseEventEnum memRead(cy15ChunkStruct *data);

