/*
======================================================================
ldap_client.c
Simple ldap client functions based on modified (reduced) ldap.h
======================================================================
*/

//Include headers section
#include "../include/ldap_client.h"
#include "../include/ldap_string.h"
#include "../include/ldap_argument.h"
#include "../include/file_output.h"

//Include standart lib section
#include <stdio.h>
#include <stdlib.h>

//Default setting section
#define DEFAULT_LDAP_URL    "ldap://localhost:389"
#define DEFAULT_LOGIN       "admin"
#define DEFAULT_PASSWD      "admin"

#define LDAP_SEARCH_BASE_DC "dc=Domain,dc=net"

#define MAKE_UNBINDING      0x10
#define DONT_MAKE_UNBINDING 0x20

//Constant section
const char * CACERT_FILE_PATH          = "/etc/ldap/ca_certs.pem";
const char * LDAP_SEARCH_RESULT_ATTR[] = {"uid", "cn", "sn", "givenName", "gecos", "displayName", NULL};

const int    LDAP_USE_VERSION          = LDAP_VERSION3;  
ber_int_t    LDAP_SEARCH_SCOPE         = LDAP_SCOPE_SUBTREE;

void SetDefaultPar(char * parameter, const char * parameter_name, const char * default_parameter)
{
    if ((parameter == NULL) || (parameter[0] == '\0'))
    {
        strcpy(parameter, default_parameter);
        printf("\x1b[35m[WARNING]:\x1b[0m Parameter \"%s\" was changed to \"%s\"\n", parameter_name, default_parameter);
    }
}

void StatusChecker(LDAP ** ldap_handler, char * function_name, char * success_msg, const int return_value, const int unbinding)
{
    if (return_value != LDAP_SUCCESS)
    {
        printf("\x1b[31m[FAILURE]:\x1b[0m %s wasn't executed\n%s\n", function_name, ldap_err2string(return_value));
        if (unbinding == MAKE_UNBINDING) ldap_unbind_ext_s(*ldap_handler, NULL, NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\x1b[32m[SUCCESS]:\x1b[0m %s\n", success_msg);
    }
}

void LdapInit(LDAP ** ldap_handler, char * ldap_url)
{
    SetDefaultPar(ldap_url, "LDAP_URL", "ldap://localhost:389");
    int return_value = ldap_initialize(ldap_handler, ldap_url);
    StatusChecker(ldap_handler, "ldap_initilize(...)", "The URL of the LDAP server was connected", return_value, DONT_MAKE_UNBINDING);
}

void LdapSetOptionInt(LDAP ** ldap_handler, char * function_descr, const int option, const int value)
{
    int return_value = ldap_set_option(*ldap_handler, option, &value);
    StatusChecker(ldap_handler, function_descr, ConcatIn("The LDAP option ", function_descr, " was set"), return_value, DONT_MAKE_UNBINDING);
}

void LdapSetOptionStr(LDAP ** ldap_handler, char * function_descr, const int option, const char * value)
{
    int return_value = ldap_set_option(*ldap_handler, option, &value);
    StatusChecker(ldap_handler, function_descr, ConcatIn("The LDAP option ", function_descr, " was set"), return_value, DONT_MAKE_UNBINDING);
}

void LdapStartTls(LDAP ** ldap_handler)
{
    int return_value = ldap_start_tls_s(*ldap_handler, NULL, NULL);
    StatusChecker(ldap_handler, "ldap_start_tls_s(...)", "STARTTLS was initilized on port 389", return_value, DONT_MAKE_UNBINDING);
} 

void LdapBind(LDAP ** ldap_handler, char * ldap_bind_user, char * ldap_bind_passwd)
{
    BerValue   bind_credentials;
    BerValue * serv_credentials;
    
    SetDefaultPar(ldap_bind_user,   "LDAP_LOGIN" , "admin");
    SetDefaultPar(ldap_bind_passwd, "LDAP_PASSWD", "admin");

    bind_credentials.bv_val = (char*)ldap_bind_passwd;
    bind_credentials.bv_len = strlen(ldap_bind_passwd);

    int return_value = ldap_sasl_bind_s(*ldap_handler, Concat(ldap_bind_user, ",dc=Domain,dc=net"), LDAP_SASL_SIMPLE, &bind_credentials, NULL, NULL, &serv_credentials);
    StatusChecker(ldap_handler, "ldap_sasl_bind_s(...)", ConcatIn("User \"", ldap_bind_user, "\" was bound to the LDAP server"), return_value, MAKE_UNBINDING);
}

void LdapSearch(LDAP ** ldap_handler, const char * ldap_search_filter)
{
    if ((ldap_search_filter != NULL) && (ldap_search_filter[0] != '\0'))
    {
        LDAPMessage * search_result;
        int return_value = ldap_search_ext_s(*ldap_handler, LDAP_SEARCH_BASE_DC, LDAP_SEARCH_SCOPE, ldap_search_filter, 
                                            (char **)LDAP_SEARCH_RESULT_ATTR, 0, NULL, NULL, NULL, 500, &search_result);
        
        StatusChecker(ldap_handler, "ldap_search_ext_s(...)", "The search was initiated", return_value, MAKE_UNBINDING);
        printf("Total results: %d\n", ldap_count_entries(*ldap_handler, search_result));

        LDAPMessage * search_result_entry;
        for (search_result_entry = ldap_first_entry(*ldap_handler, search_result); search_result_entry != NULL;
            search_result_entry = ldap_next_entry (*ldap_handler, search_result_entry))
        {
            printf("DN: %s\n", ldap_get_dn(*ldap_handler, search_result_entry));
            
            BerElement * ber;
            char * search_result_entry_attr;

            for (search_result_entry_attr = ldap_first_attribute(*ldap_handler, search_result, &ber); search_result_entry_attr != NULL;
                 search_result_entry_attr = ldap_next_attribute (*ldap_handler, search_result, ber))
            {
                BerValue ** values = ldap_get_values_len(*ldap_handler, search_result_entry, search_result_entry_attr);
                if (values != NULL)
                {
                    for (int number = 0; number < ldap_count_values_len(values); number++)
                    {
                        printf("\t%s: %s\n", search_result_entry_attr, values[number]->bv_val);
                    }

                    ldap_value_free_len(values);
                }

                ldap_memfree(search_result_entry_attr);
            }

            if (ber != NULL) ber_free(ber, 0);
        }

        ldap_msgfree(search_result); 
    } 
}

void LdapClient(BindUser * ldap_user)
{
    if ((ldap_user->ldap_url[0]         == '\0') && (ldap_user->ldap_bind_user[0]     == '\0') &&
        (ldap_user->ldap_bind_passwd[0] == '\0') && (ldap_user->ldap_search_filter[0] == '\0'))
    {
        FileOutput("src/textfiles/help.txt"); 
    }
    else
    {
        LDAP * ldap_handler;
        LdapInit(&ldap_handler, ldap_user->ldap_url);
        LdapSetOptionInt(&ldap_handler, "ldap_set_option(PROTOCOL_VERSION)", LDAP_OPT_PROTOCOL_VERSION,   LDAP_USE_VERSION);
        LdapSetOptionInt(&ldap_handler, "ldap_set_option(TLS_REQCERT)",      LDAP_OPT_X_TLS_REQUIRE_CERT, LDAP_OPT_X_TLS_ALLOW);
        LdapSetOptionStr(&ldap_handler, "ldap_set_option(CACERTFILE)",       LDAP_OPT_X_TLS_CACERTFILE,   CACERT_FILE_PATH);
        
        LdapStartTls(&ldap_handler);
        LdapBind(&ldap_handler, ldap_user->ldap_bind_user, ldap_user->ldap_bind_passwd);
        LdapSearch(&ldap_handler, ldap_user->ldap_search_filter);
        ldap_unbind_ext_s(ldap_handler, NULL, NULL);   
    }
}