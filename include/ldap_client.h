/*
======================================================================
ldap_client.h
Simple ldap client functions based on modified (reduced) ldap.h
======================================================================
*/

#ifndef LDAP_CLIENT_H
#define LDAP_CLIENT_H

//Include headers section
#include "ldap/ldap.h"
#include "ldap_argument.h"

void SetDefaultPar   (char *  parameter,    const char * parameter_name, const char * default_parameter);
void StatusChecker   (LDAP ** ldap_handler, char * function_name,        char * success_msg, const int return_value, const int unbinding);
void LdapInit        (LDAP ** ldap_handler, char * ldap_url);
void LdapSetOptionInt(LDAP ** ldap_handler, char * function_descr, const int option, const int    value);
void LdapSetOptionStr(LDAP ** ldap_handler, char * function_descr, const int option, const char * value);
void LdapStartTls    (LDAP ** ldap_handler);
void LdapBind        (LDAP ** ldap_handler, char * ldap_bind_user, char * ldap_bind_passwd);
void LdapSearch      (LDAP ** ldap_handler, const char * ldap_search_filter);
void LdapClient      (BindUser * ldap_user);

#endif //LDAP_CLIENT_H