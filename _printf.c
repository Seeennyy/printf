#include <stdio.h>
#include <stdarg.h>
#include "main.h"



/**
 * _printf - printss bbased onn foormat,
 * emulatess builttinn printf
 * @format: identtifiier too loook foor
 * Return: string lenggth
 */

int _printf(const char *format, ...)
{
	va_list ap;
	int i, str_count = 0;

	format_funcs formats[] = {
		{ 'c', print_char }, { 's', print_string }, { '%', print_modulus }, {'d', print_number},
		{'i', print_number}, {'b', print_binary}, { 0, NULL }
	};
	if (format == NULL)
	{
		return (-1);
	}
	va_start(ap, format);

    while (*format)
    {
        if (*format != '%')
        {
            putchar(*format);
            str_count += 1;
        }
        else
        {
            format++;
            i = 0;
            while (formats[i].first_case)
            {
                if (formats[i].first_case == *format)
                    str_count += formats[i].func(ap);
                i++;
            }
        }
        format++;
    }
	va_end(ap);
	return (counter);
}

