CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c99
LDFLAGS = -pthread
TARGET = echo_server
SOURCES = echo_server.c client_handler.c utils.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = echo_server.h client_handler.h utils.h

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECTS)