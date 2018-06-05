#include <car.h>

void car_init()
{
    gpioSetMode(GPIN23,PI_OUTPUT); gpioSetMode(GPIN24,PI_OUTPUT);
    gpioSetMode(GPIN25,PI_OUTPUT); 
    gpioSetMode(GPIN6,PI_OUTPUT);  gpioSetMode(GPIN13,PI_OUTPUT);
    gpioSetMode(GPIN19,PI_OUTPUT);

    gpioWrite(GPIN25,1); // Left Enable
    gpioWrite(GPIN19,1); // Right Enable
}
void forward(int time)
{
    gpioWrite(GPIN23, 1); gpioWrite(GPIN24, 0); // Left
    gpioWrite(GPIN6, 1); gpioWrite(GPIN13, 0);  // Right
    gpioDelay(time);    // forwarding time
    stop();              
    gpioDelay(300000);  
}
void backward(int time)
{
    gpioWrite(GPIN23, 0); gpioWrite(GPIN24, 1);
    gpioWrite(GPIN6, 0); gpioWrite(GPIN13, 1);
    gpioDelay(time);    // backwarding time
    stop();
    gpioDelay(300000);
}
void move_right(int time)
{
    gpioWrite(GPIN23, 1); gpioWrite(GPIN24, 0);
    gpioWrite(GPIN6, 0); gpioWrite(GPIN13, 1);
    gpioDelay(time);    
    stop();
    gpioDelay(300000);
}
void move_left(int time)
{
    gpioWrite(GPIN23, 0); gpioWrite(GPIN24, 1);
    gpioWrite(GPIN6, 1); gpioWrite(GPIN13, 0);
    gpioDelay(time);
    stop();
    gpioDelay(300000);
}
void stop()
{
    gpioWrite(GPIN23, 0); gpioWrite(GPIN24, 0);
    gpioWrite(GPIN6, 0); gpioWrite(GPIN13, 0);
}




