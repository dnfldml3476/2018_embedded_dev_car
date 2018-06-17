#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/wait.h>
#include <pigpio.h>
#include <car.h>
#include <camera.h>
#include <server.h>
#include <face.h>
#include <data.h>
#include <signal.h>

//#include <face.h>
#define FACE_VAL 0.5 // face tolerance

/*   test define *  */
//****************

//#define CAR_TEST
//#define SERVER_TEST
#define CONNECT_CAR
#define CONNECT_CAMERA

/*  *   *  *  *  *  */

int client;
extern int danger;

void init() {
   if(gpioInitialise() < 0){
         fprintf(stderr, "pigpio initialisation failed.\n");
         exit(-1);
    }
    car_init();
    stop_car();
    sensor_init();
    camera_init();
    face_init();
    printf("init complete\n");
}

char message[200000];
int main() {
/***    init(); ***/
    init();
 //   client = init_server();
    client = init_server();
    bool check = false;
#ifndef CAR_TEST
    while(1) { // 5. repeat  waiting  alarm signal
    // 1. get alarm signal or register signal by bluetooth
        memset(input, 0, sizeof(input));
        printf("waiting server\n");
        recv_message = read_server(client);
        printf("** recv_message **\n");
        printf("message size: %u\n", strlen(recv_message));
        printf("accumulate message %u\n", strlen(message));
        
    // 2. check message 
        int id = 0;
        if(check == false) { // check both side
            id = identify_msg(recv_message);
            if (id == -1)
                check  = true;
        }
        printf("after first identify %d\n", id);;
        if (check == true) 
        {
            strcat(message, input);
            
           printf("%s\n\n", message);

            if ((id = identify_msg(message)) == -1) 
                continue;
            else {
                memcpy(input, message, sizeof(message));
                memset(message, 0, sizeof(message));
                printf("\n%s\n\n", input);
                printf("now call parse_msg\n");
                check = false;
            }
        }
 //       int id = 0;
        int ret = 0; // auth is OK

#ifdef SERVER_TEST
        ret = 1;
#endif
        parse_msg(id);
        printf("after parse_msg\n");    
    
    // 3. call move car and take picture
        if (id == 1) {     // if ret = 1 then success and break loop
            while(!ret) 
            { 
                printf("call move_car\n");
                move_car();
#ifdef CONNECT_CAMERA
                printf("waiting camera\n");
                while(!PICTURE_ON) ;
                     // wait taking picture
                printf("before face_compare\n");
                ret = face_compare(FACE_VAL);
                printf("face_compare complete\n");
                
#endif
                PICTURE_ON = 0; // picture not same
                FLAG_SENSOR = 1; // sensor on!
                //sleep(1);
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
    gpioTerminate();

    return 0;
}
