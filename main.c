//Include headers section
#include "include/ldap_string.h"
#include "include/ldap_client.h"

int main(int argc, char * argv[])
{
    BindUser user = {'\0', '\0', '\0', '\0'};
    ArgumentHandler(argc, argv, &user);
    LdapClient(&user);
    return 0;
}
