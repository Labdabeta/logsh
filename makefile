CC=gcc
CFLAGS=
HEADERS=proposition.h
OBJECTS=proposition.o

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

logsh: $(OBJECTS)
	$(CC) main.c -o $@ $^ $(CFLAGS)
