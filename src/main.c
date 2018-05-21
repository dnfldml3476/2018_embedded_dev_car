#include <stdio.h>
#include "init.h"
#include "server.h"



int main(int argc, char *argv[]) {
    printf("main \n");

    init();

    connect();

    return 0;
}
