DIR = src
TARGET = prog.out
CC = gcc

#OBJECTS = main.o server.o car.o base64.o camera.o data.o
#CFLAGS = -Wall -W -Wsign-compare -I$(DIR)/include -lpigpio -lrt -pthread -lbluetooth -lcjson

#if you install python and face_recognition
OBJECTS = main.o server.o face.o car.o base64.o camera.o data.o
CFLAGS = -Wall -W -Wsign-compare -I$(DIR)/include -I/usr/include/python3.5m -lpython3.5m -lpigpio -lrt -pthread -lbluetooth -lcjson
#CFLAGS = -Wall -W -I/usr/include/python3.5m -lpython3.5m

$(TARGET) : $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

main.o : $(DIR)/main.c
	$(CC) $(CFLAGS) -c $^

server.o : $(DIR)/server.c
	$(CC) $(CFLAGS) -c $^

car.o : $(DIR)/car.c
	$(CC) $(CFLAGS) -c $^

base64.o : $(DIR)/base64.c
	$(CC) $(CFLAGS) -c $^

camera.o : $(DIR)/camera.c
	$(CC) $(CFLAGS) -c $^

data.o : $(DIR)/data.c
	$(CC) $(CFLAGS) -c $^

face.o : $(DIR)/face.c
	$(CC) $(CFLAGS) -c $^

clean :
	rm $(OBJECTS)
	rm $(TARGET)
