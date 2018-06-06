#ifndef __DATA_H_
#define __DATA_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <base64.h>
#include <camera.h>
#include <cjson/cJSON.h>

#define MSG_CNT 3


typedef struct Userinfo
{
    char *message_id;
    char *name;
    char *image;
    int length;
    char *result;
}Userinfo;

typedef struct SignalStart
{
    char *message_id;
    int car_speed;
    char *result;
}SignalStart;

cJSON *UserAuth; // user_auth json object
char *recv_message; // it is message from phone
Userinfo user_info;
SignalStart signal_start;

void test_read();
int parse_msg(int id);
int parse_userinfo();
int parse_signal();
int identify_msg();
int save_img(char *filename, char *text, int size);
int make_userauth(int val); // val is success = 1 fail = 0


#endif
