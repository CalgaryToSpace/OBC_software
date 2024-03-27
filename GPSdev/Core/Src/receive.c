/*
 * receive.c
 *
 *  Created on: Jul 4, 2022
 *      Author: mswel
 */


#include "receive.h"
#include "gps_types.h"

void receive_log(int wait){
	uint8_t rec[1000] = "";
	HAL_UART_Receive(&huart3, rec, 1000, wait);

	HAL_UART_Transmit(&hlpuart1, rec, 1000, HAL_MAX_DELAY);
	return (void *) 0;

}

char** gpsParseReceive(char* received){
	if(received[0] != '#'){											// Messages should start with "#'
		return (void *) 0;
	}

	char** toReturn = (char**) malloc(sizeof(char*) * 11);			// Allocate mem for fields of the response
	char* current = received + 1;									// Do not include the starting "#"
	int cursor = 0;
	int index = 0;
	int fieldStart = 0;

	// Loop through all the characters of the message.
	// Once a segment is passed, look back to see how
	// big it was and then add all the member characters
	// to the return variable.

	while((*current) != '*'){										// "*" indicates the end of the fields
		if((*current) == ',' || (*current) ==';'){					// Fields are seperated by "," or ";"
			toReturn[index] = (char*) malloc((sizeof(char) * (cursor - fieldStart)) + 1);
			int j = 0;
			for(int i = fieldStart; i < cursor; i++){
				toReturn[index][j] = received[i];
				j++;
			}
			toReturn[j] = '\n';
			fieldStart = cursor + 1;
			cursor += 1;
			index += 1;
		}
		else{
			cursor += 1;
		}
	}
	//TODO - implement CRC check


	return toReturn;
}


unsigned long CRC32Value(int i){
	int j;
	unsigned long ulCRC;
    ulCRC = i;
    for (j = 8 ; j > 0; j--) {
    	if ( ulCRC & 1 ){
    		ulCRC = (ulCRC >> 1) ^ CRC32_POLYNOMIAL;
    	}
    	else{
            ulCRC >>= 1;
    	}
    }
    return ulCRC;
}


unsigned long CalculateBlockCRC32(unsigned long ulCount, unsigned char*ucBuffer){
	unsigned long ulTemp1;
	unsigned long ulTemp2;
	unsigned long ulCRC = 0;
	while (ulCount-- != 0) {
		ulTemp1 = (ulCRC >> 8) & 0x00FFFFFFL;
        ulTemp2 = CRC32Value(((int) ulCRC ^ *ucBuffer++) & 0xFF);
        ulCRC = ulTemp1 ^ ulTemp2;
	}
	return( ulCRC );
}

