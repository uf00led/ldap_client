/*
=========================================================
ldap_argument.c
For working with arguments of the command line
=========================================================
*/

//Include headers section
#include "../include/ldap_argument.h"
#include "../include/ldap_string.h"

//Include standart lib section
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ArgumentHandler(int argc, char * argv[], BindUser * user_data)
{
    int opt = 0;
    while((opt = getopt_long(argc, argv, "u:l:p:s:", long_options, NULL)) != -1)
    {
        switch (opt)
        {
            case 'u':
                if ((optarg != NULL) && optarg[0] != '\0')
                {
                    if (!strcmp(optarg, "-l") || !strcmp(optarg, "-p") || !strcmp(optarg, "-s"))
                    {
                        printf("\x1b[31m[FAILURE]:\x1b[0m Please, enter argument after the flag\n");
                        exit(EXIT_FAILURE);
                    }
                    else 
                    {
                        strcpy(user_data->ldap_url, optarg);
                    }
                }

                break;

            case 'l':
                if ((optarg != NULL) && optarg[0] != '\0') 
                {
                    if (!strcmp(optarg, "-u") || !strcmp(optarg, "-p") || !strcmp(optarg, "-s"))
                    {
                        printf("\x1b[31m[FAILURE]:\x1b[0m Please, enter argument after the flag\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        strcpy(user_data->ldap_bind_user, optarg);
                    }
                }

                break;

            case 'p':
                if ((optarg != NULL) && optarg[0] != '\0')
                {
                    if (!strcmp(optarg, "-l") || !strcmp(optarg, "-u") || !strcmp(optarg, "-s"))
                    {
                        printf("\x1b[31m[FAILURE]:\x1b[0m Please, enter argument after the flag\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        strcpy(user_data->ldap_bind_passwd, optarg);
                    }
                }

                break;
            
            case 's':
                if((optarg != NULL) && optarg[0] != '\0')
                {
                    if (!strcmp(optarg, "-l") || !strcmp(optarg, "-p") || !strcmp(optarg, "-u"))
                    {
                        printf("\x1b[31m[FAILURE]:\x1b[0m Please, enter argument after the flag\n");
                        exit(EXIT_FAILURE);
                    }
                    else
                    {
                        if (!strcmp(optarg, "?")) strcpy(user_data->ldap_search_filter, "(uid=*)");
                        else strcpy(user_data->ldap_search_filter, ConcatIn("(", optarg, ")"));
                    }
                    
                }

                break;
        }
    }
}