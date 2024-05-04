#include "main.h"
#include "debug_tools/debug_uart.h"

#include <stdint.h>
#include <string.h>

void debug_uart_print_str(const char *str)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void debug_uart_print_str_mem(const char *str)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

// Function to convert an integer to a string
void INT_TO_STRING(int num, char *str)
{
    int i = 0;
    int is_negative = 0;

    // Handle negative numbers
    if (num < 0)
    {
        is_negative = 1;
        num = -num;
    }

    // Convert each digit to a character and store in the string in reverse order
    do
    {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    // Add a '-' character if the number was negative
    if (is_negative)
    {
        str[i++] = '-';
    }

    // Add null terminator to the string
    str[i] = '\0';

    // Reverse the string
    int j = 0;
    i--;
    while (j < i)
    {
        char temp = str[j];
        str[j] = str[i];
        str[i] = temp;
        j++;
        i--;
    }
}

int STRING_TO_INT(const char *str)
{
    int result = 0;
    int sign = 1; // Positive by default

    // Handle negative sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    // Iterate through each character in the string
    while (*str != '\0')
    {
        // Ensure character is a digit
        if (*str >= '0' && *str <= '9')
        {
            // Convert character to digit and update result
            result = result * 10 + (*str - '0');
        }
        else
        {
            // Invalid character encountered, return 0 or handle error
            return 0;
        }
        str++; // Move to the next character
    }

    // Apply sign to result and return
    return result * sign;
}