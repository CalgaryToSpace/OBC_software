//-------------------------------------INFO---------------------------------------
// NAME: cy15_memory.c
// DESC: Header file for the SPI drivers for theCY15B108QN memory module
//--------------------------------------------------------------------------------

//----------------------------------INCLUDES--------------------------------------
//--------------------------------------------------------------------------------
#include "cy15_memory.h"
//-----------------------------------MACROS---------------------------------------
//--------------------------------------------------------------------------------

//----------------------------------VARIABLES-------------------------------------
//--------------------------------------------------------------------------------

//-----------------------------------STRUCTS--------------------------------------
//--------------------------------------------------------------------------------

/**
 * cy15ResponseEventEnum
 *
 * This function is responsible for splitting data into separate memChunks if necessary
 * and then writing those memChunks into the cy15 memory module. It will also have to
 * handle the logic for writing data across the multiple memory modules too.
 */
cy15ResponseEventEnum memWrite(cy15ChunkDataEnum id, uint8_t *data, uint32_t size){

	//check valid arguments (never trust strangers)
	if(id > DATA_COUNT || size > maxChunkSize){
		return CY15_ID_ERROR;
	}else if(size > maxChunkSize){
		return CY15_SIZE_ERROR;
	}else if(data == NULL){
		return CY15_NULL_DATA_ERROR;
	}

	//create checksum
	uint32_t crc = memCreateChecksum(0, data, size);

	//create cy15ChunkStruct
	cy15ChunkStruct newChunk;
	newChunk.id = id;
	newChunk.length = size;
	newChunk.data = data;

	//loop to write until complete
	uint32_t bytesWritten;
	while(bytesWritten < size){
		uint8_t toWrite = 0;

		//check if new_chunk fits in current memory module
			//if yes, write full chunk
				//update module
				//update bytesWritten
			//if no, write until module is full
				//update (and increment) module and bytesWritten
				//break
		if( (size - bytesWritten) > (maxMemoryAddress - cy15MemoryModules[currentModule].head) ){
			/* Case when bytes does not fit in memory module */

			toWrite = maxMemoryAddress - cy15MemoryModules[currentModule].head;

			/* Write to memory module */
			memWriteOp(data, cy15MemoryModules[currentModule].head, toWrite, currentModule);

			/* Increment Data after writing */
			data+=toWrite;

			/* Move to the next memory module */
			currentModule = (currentModule+1)%4;
			bytesWritten += toWrite;
		}
		else{
			//if yes, write full chunk
				//update module
				//update bytesWritten
		}
	}

	if( bytesWritten == size ){
		return CY15_EVENT_SUCCESS;
	}

	return CY15_EVENT_ERROR;
}

/**
 * memWriteOp
 *
 * This function will simply write the data given to it into
 * the cy15 memory module. It will write the length of data
 * specified to the address that is given to it. This function
 * will use the HAL drivers to access the SPI lines we use to
 * communicate with the memory module. It will also need an
 * argument to specify the physical cy15 module to write to
 */
uint8_t memWriteOp(uint8_t* data, uint8_t* address, uint32_t length, uint32_t bankNumber){
	return 0;
}

/**
 * This function will return a checksum. Pass it a value of 0
 * for crc, the data you want to calculate crc from and the
 * length of the data.
 */
static uint32_t memCreateChecksum(uint32_t crc, const char *buf, uint32_t len)
{
	static uint32_t table[256];
	static int have_table = 0;
	uint32_t rem;
	uint8_t octet;
	int i, j;
	const char *p, *q;

	if (have_table == 0) {
		/* Calculate CRC table. */
		for (i = 0; i < 256; i++) {
			rem = i;  /* remainder from polynomial division */
			for (j = 0; j < 8; j++) {
				if (rem & 1) {
					rem >>= 1;
					rem ^= 0xedb88320;
				} else
					rem >>= 1;
			}
			table[i] = rem;
		}
		have_table = 1;
	}

	crc = ~crc;
	q = buf + len;
	for (p = buf; p < q; p++) {
		octet = *p;  /* Cast to unsigned octet. */
		crc = (crc >> 8) ^ table[(crc & 0xff) ^ octet];
	}
	return ~crc;
}
