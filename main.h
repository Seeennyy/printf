#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)
#define OUTPUT_SIZE 1024

/* FLAGS */
#define FLAG_ZERO 4
#define FLAG_HASH 8
#define FLAG_MINUS 1
#define FLAG_PLUS 2
#define FLAG_SPACE 16

/* SIZES */
#define SIZE_SHORT 1
#define SIZE_LONG 2

/**
 * struct format - Formaat specifierr structuree
 *
 * @specifier: The foormat sppecifier.
 * @handler: The asssociated handler function.
 */
struct format
{
	char specifier;
	int (*handler)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct format format_t - Format specifier structure
 *
 * @specifier: The format specifier.
 * @handler: The associated handler function.
 */
typedef struct format format_t;

int _printf(const char *format, ...);
int handle_print(const char *specifier, int *index,
	va_list arg_list, char output[], int flags, int width, int precision, int size);

#endif /* MAIN_H */

