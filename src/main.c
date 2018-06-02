#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pigpio.h>
#include "car.h"
#include "camera.h"
#include "server.h"
//#include "data.h"

//#include "face.h"

int client;

void init() {
   if(gpioInitialise() < 0){
         fprintf(stderr, "pigpio initialisation failed.\n");
         exit(-1);
    }
    car_init();
    camera_init();
   // face_init();


   /*
    add init_server
    get user_img
    */
}


int main(int argc, char *argv[]) {
    init();

    test_read();

    // check that user_img is exist
    while(1) {

    /*
        1. get alarm signal by bluetooth
        2. call move_car
        3. take picture
        4. write server (alarm exit signal)
        */


    }
/*
    forward(300000);
    move_right(350000);
    forward(300000);
    move_right(350000);
    forward(300000);
    move_right(350000);
    forward(300000);
    move_right(350000);
    stop();
*/
    gpioTerminate();
    return 0;
}
