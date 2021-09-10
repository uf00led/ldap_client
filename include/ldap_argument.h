/*
=========================================================
ldap_argument.h
For working with arguments of the command line
=========================================================
*/

#ifndef LDAP_ARGUMENT_H
#define LDAP_ARGUMENT_H

//Include headers section
#include "../include/ldap_string.h"

//Include standart lib section
#include <getopt.h>
#include <stddef.h>

typedef struct BindUser BindUser;
typedef struct option   Option; 

struct BindUser
{
    char ldap_url[64];
    char ldap_bind_user[64];
    char ldap_bind_passwd[64];
    char ldap_search_filter[64];
};

static Option long_options[] = 
{
    {"url"  ,  optional_argument, NULL, 'u'},
    {"login",  required_argument, NULL, 'l'},
    {"passwd", required_argument, NULL, 'p'},
    {"search", optional_argument, NULL, 's'},
    {NULL,     0,                 NULL,  0 }
};

void ArgumentHandler(int argc, char * argv[], BindUser * user_data);

#endif //LDAP_ARGUMENT_H