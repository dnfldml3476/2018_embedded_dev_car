#ifndef __DATA_H_
#define __DATA_H_

#include <stdio.h>
#include <cjson/cJSON.h>

typedef struct cJSON
{
    struct cJSON *next;
