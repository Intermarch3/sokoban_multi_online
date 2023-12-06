##
## EPITECH PROJECT, 2023
## setting_up
## File description:
## Makefile
##

CC                := gcc
CFLAGS            := -c -Wall -g3
LDFLAGS           := -g3 -lncurses
EXECUTABLE        := my_sokoban

SOURCES_FILES     := $(wildcard src/*.c)
SOURCES_FILES += $(wildcard src/multiplayer/*.c)

OBJECTS_FILES     := $(SOURCES_FILES:.c=.o)

all: $(SOURCES_FILES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS_FILES)
	rm -f $(OBJECTS_LIB_FILES)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all
