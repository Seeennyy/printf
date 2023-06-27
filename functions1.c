#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned_number - Prints an unsigned number
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_unsigned_number(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);

	number = convert_sized_unsigned(number, size);

	if (number == 0)
		output_buffer[i--] = '0';

	output_buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		output_buffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return write_unsigned(0, i, output_buffer, flags, width, precision, size);
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal_number - Prints an unsigned number in octal notation
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_octal_number(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int initial_number = number;

	UNUSED(width);

	number = convert_sized_unsigned(number, size);

	if (number == 0)
		output_buffer[i--] = '0';

	output_buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		output_buffer[i--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & FLAG_HASH && initial_number != 0)
		output_buffer[i--] = '0';

	i++;

	return write_unsigned(0, i, output_buffer, flags, width, precision, size);
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal_number - Prints an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal_number(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	return print_hexa_number(args, "0123456789abcdef", output_buffer,
		flags, 'x', width, precision, size);
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexadecimal_upper_number - Prints an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexadecimal_upper_number(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	return print_hexa_number(args, "0123456789ABCDEF", output_buffer,
		flags, 'X', width, precision, size);
}

/************** PRINT HEX NUMBER IN LOWER OR UPPER **************/
/**
 * print_hexa_number - Prints a hexadecimal number in lower or upper case
 * @args: List of arguments
 * @mapping: Array of values to map the number to
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @flag_char: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_hexa_number(va_list args, char mapping[], char output_buffer[],
	int flags, char flag_char, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int initial_number = number;

	UNUSED(width);

	number = convert_sized_unsigned(number, size);

	if (number == 0)
		output_buffer[i--] = '0';

	output_buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		output_buffer[i--] = mapping[number % 16];
		number /= 16;
	}

	if (flags & FLAG_HASH && initial_number != 0)
	{
		output_buffer[i--] = flag_char;
		output_buffer[i--] = '0';
	}

	i++;

	return write_unsigned(0, i, output_buffer, flags, width, precision, size);
}

