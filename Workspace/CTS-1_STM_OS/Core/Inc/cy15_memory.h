//-------------------------------------INFO---------------------------------------
// NAME: cy15_memory.h
// DESC: Header file for the SPI drivers for theCY15B108QN memory module
//--------------------------------------------------------------------------------

//----------------------------------INCLUDES--------------------------------------
//--------------------------------------------------------------------------------

//-----------------------------------MACROS---------------------------------------
//--------------------------------------------------------------------------------
#define maxMemoryAddress 0x100000
#define maxChunkSize 1024
#define numberOfModules 4
//----------------------------------VARIABLES-------------------------------------
//--------------------------------------------------------------------------------
cy15ModuleStruct cy15MemoryModules[numberOfModules];
int currentModule = 0;
//-----------------------------------STRUCTS--------------------------------------
//--------------------------------------------------------------------------------
enum cy15ResponseEventEnum{
	CY15_EVENT_SUCCESS,
	CY15_ID_ERROR,
	CY15_SIZE_ERROR,
	CY15_EVENT_ERROR,
	CY15_NULL_DATA_ERROR,
	CY15_EVENT_CRC_ERROR,
	CY15_EVENT_COUNT
};

enum cy15ChunkDataEnum{
	EXP_DATA,
	GPS_DATA,
	CAMERA_DATA,
	MEM_LOG_DATA,
	DATA_COUNT
};

struct cy15ChunkStruct{
	CY15_CHUNK_TYPE id;
	uint length;
	uint8 *data;
	uint32 checksum;
};

struct cy15ModuleStruct{
	uint8 head = 0;
	uint8 tail = 0;
};

//----------------------------------FUNCTIONS-------------------------------------
//--------------------------------------------------------------------------------
cy15ResponseEventEnum memWrite(memChunkTypeId id, uint8 *data, uint size);
cy15ResponseEventEnum memRead(memChunk *data);
static uint8 memCreateChecksum(uint8 *data);
static uint8 memWriteOp(uint8 * data, uint8* address, uint length);
static uint8 memReadOp(uint8 * data_buffer, uint8* address);
//---------------------------------DEFINITIONS------------------------------------
//--------------------------------------------------------------------------------

/**
 *@public
 *@brief Create and writes a memChunk into the memory.
 */
cy15ResponseEventEnum memWrite(cy15ChunkDataEnum id, uint8 *data, uint size);

uint memWriteOp(uint8* data, uint8* address, uint length);
	//send write enable op code
	//send write address
	//send bytes to write

uint32 memCreateChecksum(uint8 *data);
	//checksum compute
	//return resulting checksum

/**
 * @public
 * @brief Reads a memoryChunk from the memory
 */
cy15ResponseEventEnum memRead(memChunk *data);

uint memWriteOp(uint8 * data, uint8* address, uint length);




