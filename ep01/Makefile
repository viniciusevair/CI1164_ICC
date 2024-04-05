# PROGRAMA
PROG = perfSL
OBJS = main.o gaussSeidel.o elimGauss.o linSys.o utils.o

# Compilador
CC     = gcc

# Acrescentar onde apropriado as opções para incluir uso da biblioteca LIKWID
CFLAGS = -O0 -g -DLIKWID_PERFMON
LFLAGS = -lm -llikwid

LIKWID = /home/soft/likwid/
LIKWID_FLAGS = -I$(LIKWID)/include
LIKWID_LIB = -L$(LIKWID)/lib

# Lista de arquivos para distribuição
DISTFILES = *.c *.h LEIAME* Makefile
DISTDIR = `basename ${PWD}`

.PHONY: all clean purge dist

%.o: %.c %.h
	$(CC) $(LIKWID_FLAGS) $(LIKWID_LIB) -c $(CFLAGS) -o $@ $<

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LIKWID_FLAGS) $(LIKWID_LIB) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	@echo "Limpando sujeira ..."
	@rm -f *~ *.bak

purge:  clean
	@echo "Limpando tudo ..."
	@rm -f $(PROG) $(OBJS) core a.out $(DISTDIR) $(DISTDIR).tar

dist: purge
	@echo "Gerando arquivo de distribuição ($(DISTDIR).tar) ..."
	@ln -s . $(DISTDIR)
	@tar -cvf $(DISTDIR).tar $(addprefix ./$(DISTDIR)/, $(DISTFILES))
	@rm -f $(DISTDIR)
