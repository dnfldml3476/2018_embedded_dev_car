#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <pigpio.h>
#include <car.h>
#include <camera.h>
#include <server.h>
#include <data.h>

//#include <face.h>

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
    /*
        need pairing
    */

    init();

    test_read();
    
    int client = init_server();

    while(1) { // 5. repeat  waiting  alarm signal
    // 1. get alarm signal or register signal by bluetooth
        memset(input, 0, sizeof(input));
        recv_message = read_server(client);

    // 2. check message 
        int id = identify_msg();
        int ret = 0; // auth is OK

        parse_msg(id);
        if (id == 0) {
            /* save_image */
            /*
            load_image(USER_FILENAME, 0);
            face_encoding(PyUser, 0);*/
        }
    // 3. call move car and take picture
        if (id == 1) { // if id == 1 then, start move_car
            /*
            call move_car

            and wait picture success
            */
            /*
            load_image(PIC_FILENAME, 1);
            face_encoding(PyPicture, 1);
            ret = face_compare(0.5);*/
        }

    // 4. if catch the car then signal success 
        if (ret == 1) { // send alamr exit signal
            memset(recv_message, 0, sizeof(recv_message));
            if (make_userauth(1) == -1) {
                fprintf(stderr, "make userauth error\n");
                exit(1);
            }
            //memcpy(recv_message, UserAuth, sizeof(UserAuth));
            write_server(client, cJSON_Print(UserAuth));
        }
    
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
