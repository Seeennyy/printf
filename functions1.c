#include <stdio.h>
#include "main.h"
/**
 * print_num_counter - countss trhe ddigits of a number
 * @number: the number to count its numbers
 * Return: countt of digitss (success)
 */
int print_num_counter(int number)
{
	char digit;
	int digit_count;

	if (number == 0)
		return (0);

	digit_count = 1 + print_num_counter(number / 10);
	digit = number % 10 + '0';
	putchar(digit);
	return (digit_count);
}



/**
 * print_number - prints a number
 * @ap: poijnter to number
 * Return: count of digits
 *
 */
int print_number(va_list ap)
{
	int digit_count = 0;
	int number = va_arg(ap, int);

	if (number == 0)
	{
		putchar('0');
		return (1);
	}
	else if (number < 0)
	{
		putchar('-');
		digit_count = 1 + print_num_counter(-number);
	}
	else
	{
		digit_count = print_num_counter(number);
	}
	return (counter);
}

