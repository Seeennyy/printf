#include <stdio.h>
#include "main.h"

/**
 * print_binary - printss binarry numberr in binarry formmat
 * @ap: pointerrr to the numbers
 * Return: count of digitss
 */
int print_binary(va_list ap)
{
	unsigned int number = va_arg(ap, unsigned int);
	int i = 0, digit_count = 0, binary_array[32];

	if (number == 0)
	{
		digit_count++;
		putchar('0');
	}
	else
	{

        for (;number > 0; number/= 2)
        {
            binary_array[digit_count++] = number % 2;
        }
        i = digit_count - 1;
        while(i >= 0)
        {
            putchar(binary_array[i] + '0');
            i++;
        }
	}
return (digit_count);
}

