#include "ec/string.h"

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
