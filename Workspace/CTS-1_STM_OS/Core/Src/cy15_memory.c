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
 *
 * @param 	id 		Next data chunk identifier
 * @param 	data 	Data to split into separate chunks
 * @param 	size	Total size of incoming date to be split
 */
cy15ResponseEventEnum memWrite(cy15ChunkDataEnum id, uint8_t *data, uint32_t size){

	// Check valid arguments (never trust strangers)
	if(id > DATA_COUNT){
		return CY15_ID_ERROR;
	}else if(data == NULL){
		return CY15_NULL_DATA_ERROR;
	}

	seqNum = 1;
	bytesWritten = 0;
	while(bytesWritten < size){
		// Create cy15ChunkStruct
		cy15ChunkStruct newChunk;
		newChunk.id = id;

		// Check if a chunk can fit in memory in its default size
		if((cy15MemoryModules[currentModule].tail - cy15MemoryModules[currentModule].head) >= maxChunkSize){
			newChunk.length = maxChunkSize;
			newChunk.sequenceNum = seqNum++;
			memcpy(newChunk.data, data, maxChunkSize);
			newChunk.checksum = memCreateChecksum(0, newChunk.data, maxChunkSize);
			bytesWritten+=newChunk.length;
			//Write chunk to memory
			memWriteOp();	// Update
			// move data pointer by maxChunkSize (data we copied over)
			cy15MemoryModules[currentModule].tail+=bytesWritten;
		}
		// Create a chunk that fits in the case there is enough space to create a chunk that still has space for data
		else if((cy15MemoryModules[currentModule].tail - cy15MemoryModules[currentModule].head) >= minChunkSize){
			uint32_t thisChunkSize = cy15MemoryModules[currentModule].tail - cy15MemoryModules[currentModule].head;
			newChunk.length = thisChunkSize;
			newChunk.sequenceNum = seqNum++;
			memcpy(newChunk.data, data, thisChunkSize);
			newChunk.checksum = memCreateChecksum(0, newChunk.data, thisChunkSize);
			bytesWritten+=newChunk.length;
			// Write chunk to memory
			memWriteOp();	// Update
			// move data pointer by thisChunkSize (data that we copied over)
			cy15MemoryModules[currentModule].tail+=bytesWritten;
		}
		// No space available in memory allocate space
		else{
			// Allocate space from the Head by deleting 1 memory chunk and move the head PTR to next memChunk
			// Go through diff modules
			uint8_t currentHeadPtr = cy15MemoryModules[currentModule].head;
			cy15MemoryModules[currentModule].head += cy15MemoryModules[currentModule].head.length;
			free(currentHeadPtr);
			// Make SPI call to read memory chunk
			// Delete created chunk from memory for garbage collection??
		}
	}

	// All of the data was written successfully
	if( bytesWritten == size ){
		return CY15_EVENT_SUCCESS;
	}
	// Error writing data to memory
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
