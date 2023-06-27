#include "main.h"

/*** PRINT CHARACTER ***/

int print_character(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int size)
{
	char c = va_arg(args, int);

	return handle_write_character(c, output_buffer, formatting_flags, output_width, output_precision, size);
}

/*** PRINT STRING ***/

int print_string(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int size)
{
	char *str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";

	int str_length = output_precision >= 0 ? output_precision : (int)strlen(str);
	int padding = output_width > str_length ? output_width - str_length : 0;

	if (!(formatting_flags & FLAG_MINUS))
		while (padding-- > 0)
			*output_buffer++ = ' ';

	while (str_length-- > 0)
		*output_buffer++ = *str++;

	while (padding-- > 0)
		*output_buffer++ = ' ';

	return output_width > str_length ? output_width : str_length;
}

/*** PRINT PERCENT SIGN ***/

int print_percent_sign(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int size)
{
	UNUSED(args);
	UNUSED(formatting_flags);
	UNUSED(output_width);
	UNUSED(output_precision);
	UNUSED(size);

	*output_buffer = '%';
	return 1;
}

/*** PRINT INTEGER ***/

int print_integer(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int size)
{
	long int number = va_arg(args, long int);
	int is_negative = 0;

	number = convert_sized_number(number, size);

	if (number == 0)
	{
		*output_buffer++ = '0';
		return 1;
	}

	if (number < 0)
	{
		is_negative = 1;
		number = -number;
	}

	int number_length = write_number(number, 10, output_buffer);
	return is_negative ? number_length + 1 : number_length;
}

/*** PRINT BINARY ***/

int print_binary(va_list args, char output_buffer[],
	int formatting_flags, int output_width, int output_precision, int size)
{
	unsigned int number = va_arg(args, unsigned int);
	int count = 0;

	if (number == 0)
	{
		*output_buffer++ = '0';
		return 1;
	}

	unsigned int mask = 1 << 31;
	int found_nonzero = 0;

	while (mask > 0)
	{
		int bit = (number & mask) != 0;

		if (bit || found_nonzero)
		{
			*output_buffer++ = '0' + bit;
			count++;
			found_nonzero = 1;
		}

		mask >>= 1;
	}

	return count;
}

