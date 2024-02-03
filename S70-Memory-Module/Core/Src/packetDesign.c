/*
 * packetDesign.c
 *
 *  Created on: Jul. 31, 2023
 *      Author: Saksham Puri
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../Inc/PacketEnum.h"

void DECODE_PACKET_0(void *);
void CREATE_PACKET_0(void *);
void CREATE_PACKET_1();
void CREATE_PACKET_2();
void TEST_WRITE_PACKET(void *, void *, packet_type);

void *enumFunctions[] = {CREATE_PACKET_0, CREATE_PACKET_1, CREATE_PACKET_2};


//This function would take the data from OS, and decode it to store it into struct
void DECODE_PACKET_0(void * buffer) {

}

//Function to create a packet from given buffer, and then return a buffer with hex values
void CREATE_PACKET_0(void * buffer) {
	char testBuffer[100] = {0};
	char testBuffer2[100] = {0};

	memset(testBuffer, 0x0, 100);
	memset(testBuffer2, 0x0, 100);

	DECODE_PACKET_0(buffer);

	tel t;

	t.secondsSinceBoot = 12;
	t.temperature = 3.2;
	t.type = PowerSystems;

	uint8_t typeSize = sizeof(t.type);
	uint8_t secondsSize = sizeof(t.secondsSinceBoot);

	memcpy(testBuffer, &t, sizeof(t));

	size_t i = 0;
	uint8_t del_size = 0;

	//Storing it in HEX, Doubles use Big-Endian Values
	while (i < sizeof(t) + 3) {
		if (i == 0) { // if i == 0, add starting character
			sprintf(testBuffer2 + (i * 2), "%02X", '}'); //7D
			del_size++;
		}
		else if (i < typeSize + 1) { // If i < 2, accessing i == 1, buffer indices 0
			sprintf(testBuffer2 + (i * 2), "%02X", testBuffer[i-del_size]);
		}
		else if (i == typeSize + 1) { // If i == 2, add a delimiter
			sprintf(testBuffer2 + (i * 2), "%02X", '!'); //21
			del_size++;
		}
		else if (i < secondsSize + typeSize + 2) { // If i < 7, accessing i == 3, 4, 5, 6, buffer indices 1, 2, 3, 4
			sprintf(testBuffer2 + (i * 2), "%02X", testBuffer[i-del_size]);
		}
		else if (i == secondsSize + typeSize + 2) { // i == 7, add a delimiter
			sprintf(testBuffer2 + (i * 2), "%02X", '!');
			del_size++;
		}
		else { // If i > 7, accessing i == 8, 9, ..., 15, buffer indices 5, 6, ... ,12
			sprintf(testBuffer2 + (i * 2), "%02X", testBuffer[i-del_size]);
		}
		i++;
	}
}

void CREATE_PACKET_1() {

}

void CREATE_PACKET_2() {

}

//Recieve a type of data, and write it into module
void TEST_WRITE_PACKET(void * addr, void * buffer, packet_type type) {
	packet_type (*function)(void *);
	function = enumFunctions[type];
	function(buffer);
}

void TEST_READ_PACKET(void * buffer) {

}
