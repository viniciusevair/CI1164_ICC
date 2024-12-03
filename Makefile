CC = gcc
LIKWID_HOME = /home/soft/likwid
PROGRAM_NAME = matmult
CFLAGS = -Wall -g -O3 -mavx2 -march=native -I${LIKWID_HOME}/include -DLIKWID_PERFMON
LDFLAGS = -L${LIKWID_HOME}/lib -llikwid -lm

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(PROGRAM_NAME)

run: all
	./main_script.sh

$(PROGRAM_NAME): $(OBJECTS)
	$(CC) ${CFLAGS} -o $(PROGRAM_NAME) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

purge: clean
	rm -f $(PROGRAM_NAME) *.dat *.png results
