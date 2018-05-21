DIR = src
OBJECTS = main.o init.o server.o
TARGET = prog.out
CC = gcc
CFLAGS = -Wall -W

$(TARGET) : $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o : $(DIR)/main.c
	$(CC) $(CFLAGS) -c $^

init.o : $(DIR)/init.c
	$(CC) $(CFLAGS) -c $^

server.o : $(DIR)/server.c
	$(CC) $(CFLAGS) -c $^

clean :
	rm $(OBJECTS)
	rm $(TARGET)
