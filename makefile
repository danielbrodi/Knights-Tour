#PATH
IDIR = ./api/
SDIR = ./src/
TDIR = ./test_files/

#COMPILER
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -lm -I$(IDIR)
RM = rm -rf

TARGETS := knight_tour

.PHONY = all clean

all: $(TARGETS)

knight_tour: $(SDIR)knight_tour.c $(TDIR)knight_tour_test.c $(SDIR)bit_array.c
	$(CC) $(CFLAGS) -o $@ $^

bit_array: $(TDIR)bit_array_test.c $(SDIR)bit_array.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	$(RM) *.o $(TARGETS)
