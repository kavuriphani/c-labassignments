# Makefile for BusReservation

CC = gcc
CFLAGS = -g -Wall -Wextra
SRCS = BusReservation.c bus_reservation_impl.c
TARGET = BusReservation.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
