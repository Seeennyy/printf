#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a character
 * @ch: Character to be printed
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int handle_write_char(char ch, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[index++] = ch;
	buffer[index] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';

		for (index = 0; index < width - 1; index++)
			buffer[BUFF_SIZE - index - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - index - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - index - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a number
 * @is_negative: Indicator if the number is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Buffer array to handle printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padding = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		extra_char = '-';
	else if (flags & F_PLUS)
		extra_char = '+';
	else if (flags & F_SPACE)
		extra_char = ' ';

	return (write_num(index, buffer, flags, width, precision,
		length, padding, extra_char));
}

/**
 * write_num - Writes a number using a buffer
 * @index: Index at which the number starts in the buffer
 * @buffer: Buffer array
 * @flags: Flags specifier
 * @width: Width specifier
 * @precision: Precision specifier
 * @length: Number length
 * @padding: Padding character
 * @extra_char: Extra character
 *
 * Return: Number of printed characters
 */
int write_num(int index, char buffer[],
	int flags, int width, int precision,
	int length, char padding, char extra_char)
{
	int i, padding_start = 1;

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no characters are printed */
	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' '; /* width is displayed with padding ' ' */
	if (precision > 0 && precision < length)
		padding = ' ';
	while (precision > length)
		buffer[--index] = '0', length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ') /* Assign extra character to the left of buffer */
		{
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ') /* Assign extra character to the left of buffer */
		{
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0') /* Assign extra character to the left of padding */
		{
			if (extra_char)
				buffer[--padding_start] = extra_char;
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[index], length - (1 - padding_start)));
		}
	}
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsigned - Writes an unsigned number
 * @is_negative: Number indicating if the number is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Buffer array
 * @flags: Flags specifier
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written characters
 */
int write_unsigned(int is_negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the buffer's right and starts at position 'index' */
	int length = BUFF_SIZE - index - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0); /* printf(".0d", 0)  no characters are printed */

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flags & F_MINUS) /* Assign extra character to the left of buffer [buffer > padding] */
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else /* Assign extra character to the left of padding [padding > buffer] */
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Buffer array
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padding: Character representing the padding
 * @extra_char: Character representing the extra character
 * @padding_start: Index at which padding should start
 *
 * Return: Number of written characters
 */
int write_pointer(char buffer[], int index, int length,
	int width, int flags, char padding, char extra_char, int padding_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flags & F_MINUS && padding == ' ') /* Assign extra character to the left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ') /* Assign extra character to the left of buffer */
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & F_MINUS) && padding == '0') /* Assign extra character to the left of padding */
		{
			if (extra_char)
				buffer[--padding_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[index], length - (1 - padding_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}

