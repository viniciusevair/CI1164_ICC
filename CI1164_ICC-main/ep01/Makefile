CFLAGS = -Wall -g -O0
LDFLAGS = -llikwid -lm
PROGRAM_NAME = perfSL

CC = gcc
LKWDFLAGS = -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -L${LIKWID_LIB}

# arquivos-objeto
OBJECTS = main.o elimGauss.o gaussSeidel.o linSys.o utils.o

all: $(PROGRAM_NAME)

run:
	./script.sh

$(PROGRAM_NAME): $(OBJECTS)
	$(CC) $(LKWDFLAGS) -o $(PROGRAM_NAME) $(OBJECTS) $(LDFLAGS)

%.o: %.c
	$(CC) $(LKWDFLAGS) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

purge: clean
	rm -f $(PROGRAM_NAME)

