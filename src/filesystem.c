#include "ec/filesystem.h"

#include <stdio.h>

ec_string ec_read_file(ec_string path)
{
    char *buffer = NULL;
    long length;

    FILE *f = fopen(path, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);

        length = ftell(f);

        fseek(f, 0, SEEK_SET);

        buffer = (char *)malloc(length + 1);

        if (buffer)
        {
            fread(buffer, 1, length, f);
        }

        buffer[length] = 0;

        fclose(f);
    }

    return buffer;
}
