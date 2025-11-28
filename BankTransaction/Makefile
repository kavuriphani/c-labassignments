CC = gcc
CFLAGS = -g -Wall -Wextra
SRCS = BankTransaction.c bank_transaction_impl.c
TARGET = BankTransaction.exe

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
