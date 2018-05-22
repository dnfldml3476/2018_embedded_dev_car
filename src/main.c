#include <stdio.h>
#include "init.h"
#include "server.h"
#include "car.h"



int main(int argc, char *argv[]) {
    printf("main \n");

    init();

    connect();

    move_left();

    return 0;
}
