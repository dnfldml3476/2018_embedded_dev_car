#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pigpio.h>
#include "car.h"
#include "camera.h"
//#include "face.h"
#include "server.h"



void init() {
  /*  if(gpioInitialise() < 0){
         fprintf(stderr, "pigpio initialisation failed.\n");
         exit(-1);
    }*/
    car_init();
    camera_init();
   // face_init();
}


int main(int argc, char *argv[]) {
    init();
    
    //init();
    //connect();
    //move_left();

    /*
     printf("%d\n", gpioSetPWMrange(GPIN25,default_range));
     printf("%d\n", gpioSetPWMrange(GPIN19,default_range));
     printf("%d\n", gpioPWM(GPIN19,130));
     printf("%d\n", gpioPWM(GPIN25,130));
             
     printf("%d\n", gpioGetPWMdutycycle(GPIN25));
     printf("%d\n", gpioGetPWMdutycycle(GPIN19));
           
     printf("%d\n", gpioGetPWMrange(GPIN25));
     printf("%d\n", gpioGetPWMrange(GPIN19));
     */

    forward(300000);
    move_right(350000);
    forward(300000);
    move_right(350000);
    forward(300000);
    move_right(350000);
    forward(300000);
    move_right(350000);
    stop();

    //gpioTerminate();
    return 0;
}
