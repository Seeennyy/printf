#include "main.h"

/**
 * get_width – width calculator
 * @format: str to print arg
 * @i: arg to be printed
 * @list: arg lists
 *
 * Return: width.
 */
int get_width(const char *format, int *m, va_list list)
{
	int curr_m;
	int width = 0;

	for (curr_m = *m + 1; format[curr_m] != '\0'; curr_m++)
	{
		if (is_digit(format[curr_m]))
		{
			width *= 10;
			width += format[curr_m] - '0';
		}
		else if (format[curr_m] == '*')
		{
			curr_m++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*m = curr_m - 1;

	return (width);
}

