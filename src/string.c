#include "ec/string.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

ec_vector ec_string_split(ec_string string, char divider)
{
    ec_vector result = ec_vector_create(sizeof(char *));

    ec_string word_start = string;

    while (true)
    {
        int length = 0;

        while (*(word_start + length) != divider && *(word_start + length) != 0)
        {
            length++;
        }

        char *word = malloc(length + 1);
        memcpy(word, word_start, length);
        word[length] = 0;

        ec_vector_push(&result, &word);

        if (*(word_start + length) == 0)
        {
            break;
        }

        word_start = word_start + length + 1;
    }

    return result;
}

ec_string ec_string_trim(ec_string string)
{
    ec_string start = string + strspn(string, " \t\n\r");
    ec_string end = string + strlen(string) - 1;

    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')
    {
        end--;
    }

    size_t length = end - start + 1;

    char *result = malloc(length + 1);
    memcpy(result, start, length);
    result[length] = 0;

    return result;
}

ec_string ec_string_concat(ec_string a, ec_string b)
{
    size_t a_length = strlen(a);
    size_t b_length = strlen(b);

    char *string = malloc(sizeof(char) * (a_length + b_length) + 1);

    memcpy(string, a, a_length);
    memcpy(string + a_length, b, b_length);
    string[a_length + b_length] = 0;

    return string;
}

ec_string ec_string_format(ec_string format, ...)
{
    va_list args;
    va_start(args, format);

    va_list args_copy_1;
    va_copy(args_copy_1, args);

    va_list args_copy_2;
    va_copy(args_copy_2, args);

    int size = vsnprintf(NULL, 0, format, args_copy_1) + 1;

    char *result = malloc(size * sizeof(char));

    vsnprintf(result, size, format, args_copy_2);

    va_end(args);
    va_end(args_copy_1);
    va_end(args_copy_2);

    return result;
}

void ec_string_free(ec_string string) { free((char *)string); }
