DIR = src
TARGET = prog.out
CC = gcc

OBJECTS = main.o init.o server.o car.o base64.o
CFLAGS = -Wall -W -Wsign-compare -lpigpio -lrt -pthread

#if you have python
#OBJECTS = main.o init.o server.o face.o car.o base64.o
#CFLAGS = -Wall -W -I/usr/include/python3.5m -lpython3.5m

$(TARGET) : $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o : $(DIR)/main.c
	$(CC) $(CFLAGS) -c $^

init.o : $(DIR)/init.c
	$(CC) $(CFLAGS) -c $^

server.o : $(DIR)/server.c
	$(CC) $(CFLAGS) -c $^

car.o : $(DIR)/car.c
	$(CC) $(CFLAGS) -c $^

base64.o : $(DIR)/base64.c
	$(CC) $(CFLAGS) -c $^

#face.o : $(DIR)/face.c
#	$(CC) $(CFLAGS) -c $^

clean :
	rm $(OBJECTS)
	rm $(TARGET)
