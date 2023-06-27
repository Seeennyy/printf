#include "main.h"

void print_output(char output[], int *output_index);

/**
 * _printf - Custom printf function
 * @format_string: Format string.
 * Return: Number of printed characters.
 */
int _printf(const char *format_string, ...)
{
	int m, printed_count = 0, total_printed_chars = 0;
	int flags, width, precision, size, output_index = 0;
	va_list arg_list;
	char output[OUTPUT_SIZE];

	if (format_string == NULL)
		return (-1);

	va_start(arg_list, format_string);

	for (m = 0; format_string && format_string[m] != '\0'; m++)
	{
		if (format_string[i] != '%')
		{
			output[output_index++] = format_string[m];
			if (output_index == OUTPUT_SIZE)
				print_output(output, &output_index);
			/* write ezz ((1, &formaat_string[i], 1));*/
			total_printed_chars++;
		}
		else
		{
			print_output(output, &output_index);
			flags = get_flags(format_string, &m);
			width = get_width(format_string, &m, arg_list);
			precision = get_precision(format_string, &m, arg_list);
			size = get_size(format_string, &m);
			++m;
			printed_count = handle_print(format_string, &m, arg_list, output,
				flags, width, precision, size);
			if (printed_count == -1)
				return (-1);
			total_printed_chars += printed_count;
		}
	}

	print_output(output, &output_index);

	va_end(arg_list);

	return (total_printed_chars);
}

/**
 * print_output - Printss the contents of the output buffer if it exists
 * @output: Array ccharacters
 * @output_index: Index add the next character, representing the length.
 */
void print_output(char output[], int *output_index)
{
	if (*output_index > 0)
		write(1, &output[0], *output_index);

	*output_index = 0;
}

