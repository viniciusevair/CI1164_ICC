CC = gcc
PROGRAM_NAME = matmult
CFLAGS = -Wall -g -O3 -mavx2 -march=native
LDFLAGS = -lm
#LDFLAGS = -llikwid -lm
#LKWDFLAGS = -DLIKWID_PERFMON -I${LIKWID_INCLUDE} -L${LIKWID_LIB}

SOURCE_DIR = src
OBJECTS_DIR = build
SOURCES := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(OBJECTS_DIR)/%.o,$(SOURCES))

all: $(PROGRAM_NAME)

run: all
	./script.sh

$(PROGRAM_NAME): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $(PROGRAM_NAME) $(OBJECTS)

$(OBJECTS_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS_DIR)

purge: clean
	rm -f $(PROGRAM_NAME)
