CC=gcc
APP_BINARY=oefening2

ML=/home/lubuntu/minimod/Libs/

CFLAGS += -g -DLINUX -Wall -I$(ML) -I../lib/ -I.
LFLAGS += -lpthread -L$(ML) -lrt

OBJECTS=main.o

all: oefening2
Debug: oefening2
oefening2: $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJECTS) -o $(APP_BINARY)


-include $(OBJECTS:.o=.d)

%.o: %.c
	$(CC) -c $(CFLAGS) $*.c -o $*.o
	$(CC) -MM $(CFLAGS) $*.c > $*.d

cleanDebug: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS:.o=.d)
	rm -f $(APP_BINARY)





