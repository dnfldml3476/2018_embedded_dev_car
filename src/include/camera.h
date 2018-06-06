#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <stdio.h>
#include <stdlib.h>
#include <pigpio.h>
#include <sys/wait.h>
#include <car.h>
#include <unistd.h>

#define SWITCH_PINNO 26
#define USER_FILENAME "user_img.jpg"
#define PIC_FILENAME "picture_img.jpg"

int PICTURE_ON;

void camera_init();
void camera_rising_func(int gpio,int level,uint32_t tick);

#endif
