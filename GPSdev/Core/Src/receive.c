/*
 * receive.c
 *
 *  Created on: Jul 4, 2022
 *      Author: mswel
 */


#include "receive.h"

char** gpsParseReceive(char* received){
	if(received[0] != '#'){
		return NULL;
	}

	char** toReturn = (char**) malloc(sizeof(char*) * 11);
	char* current = received;
	int cursor = 0;
	int index = 0;
	int fieldStart = 0;
	while((*current) != '*'){
		if((*current) == ',' || (*current) ==';'){
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
}
