CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC_DIR = src
BIN_DIR = bin
SOURCES = $(SRC_DIR)/*.c
TARGET = $(BIN_DIR)/memory_simulator

all:
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean