/*
 * debug_utilities.h
 *
 *  Created on: Jul. 10, 2023
 *      Author: Saksham Puri
 */

#ifndef INC_DEBUG_UTILITIES_H_
#define INC_DEBUG_UTILITIES_H_

// -----------------------------INCLUDES-----------------------------
#include <stdint.h>
// -----------------------------FUNCTIONS-----------------------------

void PRINT_STRING_UART(void *, uint8_t);
void PRINT_NEW_LINE();
void INT_TO_STRING(int, char*);
int STRING_TO_INT(const char *str);

#endif /* INC_DEBUG_UTILITIES_H_ */
