#ifndef __CAR_H_
#define __CAR_H_

#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>

#define GPIN23 23
#define GPIN24 24
#define GPIN25 25
#define GPIN6 6
#define GPIN13 13
#define GPIN19 19

void car_init();
void forward(int time);
void backward(int time);
void move_right(int time);
void move_left(int time);
void stop();

void move_car();
#endif


