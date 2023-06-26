#include <stdio.h>
#include "main.h"

/**
 * print_char -  handels char "c" case after % operator in _printf
 * @ap: pointer to cchar
 * Return: 1 when it is on (success) mode
 */
int print_c(va_list ap)
{
	char ch = va_arg(ap, int);

	putchar(ch);
	return (1);
}

/**
 * print_string - handels the string "s" after the % operator in _printf
 * @ap: pointer to first c of the string
 * Return: the string length on (success)
 */

int print_string(va_list ap)
{
	int char_count = 0;
	char *str = va_arg(ap, char *);

    while (*str)
    {
        putchar(*str);
        str++;
        char_count++;
    }
	return (char_count);
}
/**
 * print_modulus - handless the operator % case afterr the % operatorr in _printf
 * @ap: To match other handlerr functions standards
 * Return: 1 ez
 */

int print_modulus(va_list ap __attribute__((unused)))
{
	putchar('%');
	return (1);
}

