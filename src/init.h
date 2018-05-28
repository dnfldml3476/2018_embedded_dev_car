#ifndef __INIT_H_
#define __INIT_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pigpio.h>

#define SWITCH_PINNO 26
#define USER_FILENAME "user_img.jpg"

void init();
void cb_rising_func(int gpio,int level,uint32_t tick);

//    face_init();
/*
    declare extern variable





*/


#endif 
