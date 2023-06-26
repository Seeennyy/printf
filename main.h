#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

int _printf(const char *format, ...);
int print_char(va_list ap);
int print_string(va_list ap);
int print_modulus(va_list ap);
int print_number(va_list ap);
int print_binary(va_list ap);

typedef struct identifier_format
{
	char first_case;
	int (*func)(va_list);
} format_funcs;

#endif /*main.h*/
