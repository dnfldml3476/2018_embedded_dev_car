DIR = src
TARGET = prog.out

OBJECTS = main.o init.o server.o car.o
CC = gcc
CFLAGS = -Wall -W 

#if you have python
#OBJECTS = main.o init.o server.o face.o car.o
#CFLAGS = -Wall -W -I/usr/include/python2.7 -lpython2.7

$(TARGET) : $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o : $(DIR)/main.c
	$(CC) $(CFLAGS) -c $^

init.o : $(DIR)/init.c
	$(CC) $(CFLAGS) -c $^

server.o : $(DIR)/server.c
	$(CC) $(CFLAGS) -c $^

server.o : $(DIR)/car.c
	$(CC) $(CFLAGS) -c $^

#face.o : $(DIR)/face.c
#	$(CC) $(CFLAGS) -c $^

clean :
	rm $(OBJECTS)
	rm $(TARGET)
