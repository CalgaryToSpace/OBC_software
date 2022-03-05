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
cy15ResponseEventEnum memWrite(cy15ChunkDataEnum id, uint8 *data, uint size){

	//check valid arguments (never trust strangers)
	if(id > DATA_COUNT || size > 1024){
		return CY15_ID_ERROR;
	}else if(size > 1024){
		return CY15_SIZE_ERROR;
	}else if(data == NULL){
		return CY15_NULL_DATA_ERROR;
	}

	//create checksum
	uint32 crc = memCreateChecksum(data);

	//create cy15ChunkStruct
	cy15ChunkStruct newChunk = new cy15ChunkStruct(id, size, data, crc);

	//loop to write until complete
	uint bytesWritten;
	while(bytesWritten < size){
		uint8 toWrite = 0;

		//check if new_chunk fits in current memory module
			//if yes, write full chunk
				//update module
				//update bytesWritten
			//if no, write until module is full
				//update (and increment) module and bytesWritten
				//break
		if( (size - bytesWritten) > (maxMemoryAddress - cy15MemoryModules[currentModule].head) ){
			toWrite = maxMemoryAddress - cy15MemoryModules[currentModule].head;

			//FIND WAY TO INCREMENT DATA
			memWriteOp(data, cy15MemoryModules[currentModule].head, toWrite);

			currentModule = (currentModule+1)%4;
			bytesWritten += toWrite;
		}
	}
		//call memWriteOp to write to memory module
	//return success/fail


	return CY15_EVENT_ERROR;
}

uint memWriteOp(uint8* data, uint8* address, uint length){
	//send write enable op code
	//send write address
	//send bytes to write
}

uint32 memCreateChecksum(uint8 *data){
	//checksum compute
	//return resulting checksum
}

/**
 * @public
 * @brief Reads a memoryChunk from the memory
 */
cy15ResponseEventEnum memRead(memChunk *data){

}




