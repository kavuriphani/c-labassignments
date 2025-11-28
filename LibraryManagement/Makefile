CC = gcc
CFLAGS = -g -Wall -Wextra
SRCS = LibraryManagement.c library_management_impl.c
TARGET = LibraryManagement.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
