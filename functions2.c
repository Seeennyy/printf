#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_pointer(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	char padding_char = ' ';
	char extra_char = 0;
	int index = BUFFER_SIZE - 2;
	int length = 2; /* length=2 for '0x' */
	unsigned long int num_addresses;
	char mapping[] = "0123456789abcdef";
	void *addresses = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (addresses == NULL)
		return write(1, "(nil)", 5);

	output_buffer[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addresses = (unsigned long int)addresses;

	while (num_addresses > 0)
	{
		output_buffer[index--] = mapping[num_addresses % 16];
		num_addresses /= 16;
		length++;
	}

	if ((flags & FLAG_ZERO) && !(flags & FLAG_MINUS))
		padding_char = '0';
	if (flags & FLAG_PLUS)
		extra_char = '+', length++;
	else if (flags & FLAG_SPACE)
		extra_char = ' ', length++;

	index++;

	return write_pointer(output_buffer, index, length,
		width, flags, padding_char, extra_char, 1);
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ASCII codes in hexadecimal of non-printable characters
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_non_printable(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return write(1, "(null)", 6);

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			output_buffer[i + offset] = str[i];
		else
			offset += append_hex_code(str[i], output_buffer, i + offset);

		i++;
	}

	output_buffer[i + offset] = '\0';

	return write(1, output_buffer, i + offset);
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints a string in reverse
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_reverse(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(output_buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(args, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}

	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char character = str[i];

		write(1, &character, 1);
		count++;
	}

	return count;
}

/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Prints a string in ROT13
 * @args: List of arguments
 * @output_buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_rot13string(va_list args, char output_buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(args, char *);
	UNUSED(output_buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";

	for (i = 0; str[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == str[i])
			{
				x = output[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}

		if (!input[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}

	return count;
}

