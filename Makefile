CC      = gcc
CFLAGS  = -c -Wall
LDPATHS = -Xlinker -rpath=lib/libldap.so -Xlinker -rpath=lib/liblber.so
LDFLAGS = -lldap -llber
SOURCES = main.c src/ldap_client.c src/ldap_argument.c src/ldap_string.c src/file_output.c
OBJECTS = $(SOURCES: .c=.o)
EXECUTABLE = ldap_client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDPATHS) $(LDFLAGS)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
