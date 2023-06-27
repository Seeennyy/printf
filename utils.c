#include "main.h"

/**
 * is_printable – char evaluation
 * @c: evalulated char
 *
 * Return: 1 if c could be printed, 0 if not
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code – Append in headeimal code -o buffer
 * @buffer: char arrays
 * @m: Index at start to be appending.
 * @ascii_code: CODE of assci.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int m)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[m++] = '\\';
	buffer[m++] = 'x';

	buffer[m++] = map_to[ascii_code / 16];
	buffer[m] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verified if char a digit
 * @c: evaluated char
 *
 * Return: 1 digit ,yes  0 if not
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - specified size
 * @num: Nmber casted.
 * @size: Nmber indicator
 *
 * Return: Casted value of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

