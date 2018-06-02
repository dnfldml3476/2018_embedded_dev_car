#ifndef __DATA_H_
#define __DATA_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#define MSG_CNT 3

typedef struct Userinfo
{
    struct cJSON *message_id;
    struct cJSON *data;
    struct cJSON *name;
    struct cJSON *image;
    struct cJSON *result;
}Userinfo;

typedef struct SignalStart
{
    struct cJSON *message_id;
    struct cJSON *data;
    struct cJSON *carspeed;
    struct cJSON *result;
}SingalStart;

typedef struct UserAuth
{
    struct cJSON *message_id;
    struct cJSON *data;
    struct cJSON *ret;
    struct cJSON *result;
}UserAuth;

void test_read();
int parse_msg(int id);
int parse_userinfo();
int identify_msg(char *recv);


#endif
