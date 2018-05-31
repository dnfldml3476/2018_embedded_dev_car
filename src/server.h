#ifndef __SERVER_H_
#define __SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>
#include <bluetooth/rfcomm.h>
#include <cjson/cJSON.h>


char input[1024];

int _str2uuid( const char *uuid_str, uuid_t *uuid );
int init_server();

char *read_server(int client);
void write_server(int client, char *message);

#endif
