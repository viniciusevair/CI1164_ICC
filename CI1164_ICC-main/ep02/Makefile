CFLAGS = -Wall -g -O3 -mavx2 -march=native
LDFLAGS = -llikwid -lm
PROGRAM_NAME = matmult

CC = gcc
LKWDFLAGS = -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -L${LIKWID_LIB}

# arquivos-objeto
OBJECTS = matriz.o matmult.o

all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(OBJECTS)
	$(CC) -o $(PROGRAM_NAME) $(OBJECTS) -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

purge: clean
	rm -f $(PROGRAM_NAME)

