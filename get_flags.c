#include "main.h"

/**
 * get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @index: Current index in the format string
 * Return: Flags
 */
int get_flags(const char *format, int *index)
{
	int j, curr_index;
	int flags = 0;
	const char FLAG_CHARS[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAG_VALUES[] = {FLAG_MINUS, FLAG_PLUS, FLAG_ZERO, FLAG_HASH, FLAG_SPACE, 0};

	for (curr_index = *index + 1; format[curr_index] != '\0'; curr_index++)
	{
		for (j = 0; FLAG_CHARS[j] != '\0'; j++)
		{
			if (format[curr_index] == FLAG_CHARS[j])
			{
				flags |= FLAG_VALUES[j];
				break;
			}
		}

		if (FLAG_CHARS[j] == 0)
			break;
	}

	*index = curr_index - 1;

	return flags;
}

