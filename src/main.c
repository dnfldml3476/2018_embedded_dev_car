#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <pigpio.h>
#include <car.h>
#include <camera.h>
#include <server.h>
#include <data.h>
#include <signal.h>

//#include <face.h>
#define FACE_VAL 0.5 // face tolerance

/*   test define *  */
//****************

//#define CAR_TEST
#define SERVER_TEST
//#define CONNECT_CAR
//#define CONNECT_CAMERA

/*  *   *  *  *  *  */

int client;
extern int danger;

void init() {
   if(gpioInitialise() < 0){
         fprintf(stderr, "pigpio initialisation failed.\n");
         exit(-1);
    }
    car_init();
    sensor_init();
    camera_init();
   // face_init();
    client = init_server();
}


int main() {
/***    init(); ***/

    client = init_server();

#ifndef CAR_TEST
    while(1) { // 5. repeat  waiting  alarm signal
    // 1. get alarm signal or register signal by bluetooth
        memset(input, 0, sizeof(input));
        recv_message = read_server(client);
        printf("** recv_message **\n");
        printf("%s\n\n", recv_message);

    // 2. check message 
        int id = identify_msg();
        int ret = 0; // auth is OK

#ifdef SERVER_TEST
        ret = 1;
#endif
        parse_msg(id);  // if id == 1 then, start move_car

    // 3. call move car and take picture
        if (id == 1) {     // if ret = 1 then success and break loop
            while(!ret) 
            { 
#ifdef CONNECT_CAR
                move_car();
#endif
#ifdef CONNECT_CAMERA
                while(!PICTURE_ON); // wait taking picture
                
                ret = face_compare(FACE_VAL);
#endif
                PICTURE_ON = 0; // picture not same
                FLAG_SENSOR = 1; // sensor on!
            }
        }

    // 4. if catch the car then signal success 
        if (ret == 1) { // send alamr exit signal
            //memset(input, 0, sizeof(input));
            if (make_userauth(1) == -1) {
                fprintf(stderr, "make userauth error\n");
                exit(1);
            }
            //memcpy(recv_message, UserAuth, sizeof(UserAuth));
            write_server(client, cJSON_Print(UserAuth));
        }
        ret = 0;
    }
#endif
#ifdef CAR_TEST
    move_car();
#endif
    gpioTerminate();

    return 0;
}
