#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @index: Current index in the format string
 * @list: List of arguments
 *
 * Return: Precision
 */
int get_precision(const char *format, int *index, va_list list)
{
	int curr_index = *index + 1;
	int precision = -1;

	if (format[curr_index] != '.')
		return precision;

	precision = 0;

	for (curr_index += 1; format[curr_index] != '\0'; curr_index++)
	{
		if (is_digit(format[curr_index]))
		{
			precision *= 10;
			precision += format[curr_index] - '0';
		}
		else if (format[curr_index] == '*')
		{
			curr_index++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*index = curr_index - 1;

	return precision;
}

