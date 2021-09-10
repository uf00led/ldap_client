/*
=========================================================
ldap_string.c
For working with strings in C
=========================================================
*/

//Include headers section
#include "../include/ldap_string.h"

//Include standart lib section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * Concat(char * str1, char * str2)
{
    char * result = malloc(sizeof(str1) + sizeof(str2) + 1);

    if (!result) 
    {
        printf("\x1b[31m[FAILURE]:\x1b[0m Failed to stitch lines\n");
        return NULL;
    }

    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char * ConcatIn(char * str1, char * str2, char * str3)
{
    char * result1 = calloc(sizeof(str1) + sizeof(str2) + 1, 1);
    result1 = Concat(str1, str2);

    char * result2 = calloc(sizeof(result1) + sizeof(str3) + 1, 1);
    result2 = Concat(result1, str3); 

    return result2;
}