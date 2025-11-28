# Makefile for ShowReservation

CC = gcc
CFLAGS = -g -Wall -Wextra
SRCS = ShowReservation.c show_reservation_impl.c
TARGET = ShowReservation.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
