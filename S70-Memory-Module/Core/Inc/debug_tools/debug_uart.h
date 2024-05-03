// debug_uart.h
// Functions for debug printing to the Debug UART interface.

#ifndef __INCLUDE_GUARD__DEBUG_UART_H__
#define __INCLUDE_GUARD__DEBUG_UART_H__

#include "main.h"
#include <stdint.h>

void debug_uart_print_str(const char *str);
void debug_uart_print_str_new_line(const char *str);
void INT_TO_STRING(int num, char *str);
int STRING_TO_INT(const char *str);

#endif // __INCLUDE_GUARD__DEBUG_UART_H__
