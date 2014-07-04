CC = g++
OBJECTS = main.o FileServer.o

all: iDownlode

main.o: main.cpp FileServer.h
	$(CC) -c -g  main.cpp

FileServer.o: FileServer.cpp FileServer.h
	$(CC) -c -g FileServer.cpp

iDownlode: $(OBJECTS)
	$(CC) -o iDownlode $(OBJECTS)

clean:
	rm -f iDownlode $(OBJECTS)
