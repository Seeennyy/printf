#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char – Prnts char needed to be print
 * @types: arg lists
 * @buffer: array handled to print
 * @flags:  Outclaculate falgs
 * @width: mr Width
 * @precision: secification of pre
 * @size: Size  of specifier
 * Return: how many chars printed 
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string – string need to be printed
 * @types: arg lists
 * @buffer: array handled to print
 * @flags: Outclaculate flags
 * @width: mr width.
 * @precision: secification of pre
 * @size: Size of specifier
 * Return: how many char printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, m;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (m = width - length; m > 0; m--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (m = width - length; m > 0; m--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent – percent sign to be printed
 * @types: arg lists
 * @buffer: handled buffer to be printed
 * @flags:  outCalculates flags
 * @width: mr width.
 * @precision: specification of pre
 * @size: Size of specifier
 * Return: how many chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: arg lists
 * @buffer: handled buffer to be printed
 * @flags:  outCalculates flags
 * @width: mr width.
 * @precision: specification of pre
 * @size: Size of specifier
 * Return: how many chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int m = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[m--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[m--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, m, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: arg lists
 * @buffer: handled buffer to be printed
 * @flags:  outCalculates flags
 * @width: mr width.
 * @precision: specification of pre
 * @size: Size of specifier
 * Return: how many chars printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

