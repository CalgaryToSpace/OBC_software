//-------------------------------------INFO---------------------------------------
// NAME: cy15_memory.c
// DESC: Header file for the SPI drivers for theCY15B108QN memory module
//--------------------------------------------------------------------------------

//----------------------------------INCLUDES--------------------------------------
//--------------------------------------------------------------------------------

//-----------------------------------MACROS---------------------------------------
//--------------------------------------------------------------------------------

//----------------------------------VARIABLES-------------------------------------
//--------------------------------------------------------------------------------

//-----------------------------------STRUCTS--------------------------------------
//--------------------------------------------------------------------------------

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
