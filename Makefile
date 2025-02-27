# Copyright Peiu Andreea Grupa 324CA

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
SRC = image_editor.c rotate.c image_utils.c functions.c apply.c
OBJ = $(SRC:.c=.o)
TARGET = image_editor

# Compiler setup
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Build executable
build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

pack:
	zip -FSr 324CA_PeiuAndreea_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: build pack clean