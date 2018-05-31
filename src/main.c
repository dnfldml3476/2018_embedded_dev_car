#include <stdio.h>
#include "init.h"
#include "server.h"
#include "car.h"



int main(int argc, char *argv[]) {

     if(gpioInitialise() < 0){
         printf("pigpio initialisation failed.\n");
         exit(-1);
     }

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

    gpioTerminate();
    return 0;
}
