/*
=========================================================
file_output.c
For working with file output
=========================================================
*/

//Include headers section
#include "../include/file_output.h"

//Include headers section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void FileOutput(const char * file_location)
{
    FILE * file = fopen(file_location, "rt");
    char buffer[SIZE] = {0}; 
    char * text = NULL;
    size_t num = 0;

    if (file == NULL) 
    {
        printf("\x1b[31m[FAILURE]:\x1b[0m Please, go to the folder with the executable file\n");
    }
    else
    {
        while (fgets(buffer, SIZE, file) != NULL)
        {
            if (num % 2 == 0) text = (char *)realloc(text, SIZE * (num + 2));
            strcat(text, buffer);
            ++num;
        }

        printf("%s", text);

        fclose(file);
        free(text);
    }
}