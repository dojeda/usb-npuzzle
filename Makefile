SHELL = /bin/sh
CC = gcc
PYTHON = /usr/bin/python
CFLAGS = -O3 -funroll-loops -fomit-frame-pointer -pipe
BINS =   astar_cero.8puzzle      astar_manhattan.8puzzle \
       idastar_cero.8puzzle    idastar_manhattan.8puzzle \
	 astar_cero.15puzzle     astar_manhattan.15puzzle \
       idastar_cero.15puzzle   idastar_manhattan.15puzzle
OBJS =  astar_cero.8puzzle.o idastar_cero.8puzzle.o 8puzzle_cero.o \
	astar_cero.15puzzle.o idastar_cero.15puzzle.o 15puzzle_cero.o \
	astar_manhattan.8puzzle.o idastar_manhattan.8puzzle.o 8puzzle_manhattan.o \
	astar_manhattan.15puzzle.o idastar_manhattan.15puzzle.o 15puzzle_manhattan.o \
	cola_8puzzle.o cola_15puzzle.o
8PUZZLE       = -DN=N8 -DNxN=N8xN8 -DNxNxchar=N8xN8xchar -DN_1=N8_1\
		-DMANHATTAN=manhattan8 -DFILAS=filas8  -DCOLUMNAS=colus8 
15PUZZLE      = -DN=N15 -DNxN=N15xN15 -DNxNxchar=N15xN15xchar -DN_1=N15_1\
		-DMANHATTAN=manhattan15 -DFILAS=filas15 -DCOLUMNAS=colus15
CEROFLAGS      = -DCERO
MANHATTANFLAGS = -UCERO
HASHFLAGS      = -DHASH_SIZE=1201559

# Variables para la documentacion
DOXYGEN  = doxygen
DOX_FILE = dox-config
DOCS     = docs

all: preprocess $(BINS)

preprocess:
	rm -rf preprocess.h defines.h
	@echo Generacion de valores preprocesados
	@make preprocess.h
	@make defines.h
	@echo Fin generacion de valores preprocesados

astar: astar_cero.8puzzle  astar_manhattan.8puzzle \
       astar_cero.15puzzle astar_manhattan.15puzzle

idastar: idastar_cero.8puzzle  idastar_manhattan.8puzzle \
	 idastar_cero.15puzzle idastar_manhattan.15puzzle

# reglas para heuristica cero:
astar_cero.8puzzle: astar_cero.8puzzle.o 8puzzle_cero.o cola_8puzzle.o

idastar_cero.8puzzle: idastar_cero.8puzzle.o 8puzzle_cero.o

astar_cero.8puzzle.o: astar.c astar.h puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(CEROFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ astar.c

idastar_cero.8puzzle.o: idastar.c astar.h puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(CEROFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ idastar.c

8puzzle_cero.o: puzzle.c puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(CEROFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ puzzle.c

astar_cero.15puzzle: astar_cero.15puzzle.o 15puzzle_cero.o cola_15puzzle.o

idastar_cero.15puzzle: idastar_cero.15puzzle.o 15puzzle_cero.o

astar_cero.15puzzle.o: astar.c astar.h puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(CEROFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ astar.c

idastar_cero.15puzzle.o: idastar.c astar.h puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(CEROFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ idastar.c

15puzzle_cero.o: puzzle.c puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(CEROFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ puzzle.c


# reglas para heuristica manhattan:
astar_manhattan.8puzzle: astar_manhattan.8puzzle.o 8puzzle_manhattan.o cola_8puzzle.o

idastar_manhattan.8puzzle: idastar_manhattan.8puzzle.o 8puzzle_manhattan.o

astar_manhattan.8puzzle.o: astar.c astar.h puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(MANHATTANFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ astar.c

idastar_manhattan.8puzzle.o: idastar.c astar.h puzzle.h sglib.h 
	$(CC) $(CFLAGS) $(MANHATTANFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ idastar.c

8puzzle_manhattan.o: puzzle.c puzzle.h sglib.h preprocess.h
	$(CC) $(CFLAGS) $(MANHATTANFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ puzzle.c

astar_manhattan.15puzzle: astar_manhattan.15puzzle.o 15puzzle_manhattan.o cola_15puzzle.o

idastar_manhattan.15puzzle: idastar_manhattan.15puzzle.o 15puzzle_manhattan.o

astar_manhattan.15puzzle.o: astar.c astar.h puzzle.h sglib.h
	$(CC) $(CFLAGS) $(MANHATTANFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ astar.c

idastar_manhattan.15puzzle.o: idastar.c astar.h puzzle.h sglib.h
	$(CC) $(CFLAGS) $(MANHATTANFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ idastar.c

15puzzle_manhattan.o: puzzle.c puzzle.h sglib.h preprocess.h
	$(CC) $(CFLAGS) $(MANHATTANFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ puzzle.c

# reglas generales para cero y manhattan
cola_8puzzle.o: cola_puzzle.c cola_puzzle.h sglib.h cola_impl.h puzzle.h
	$(CC) $(CFLAGS) $(CEROFLAGS) $(8PUZZLE) $(HASHFLAGS) -c -o $@ cola_puzzle.c

cola_15puzzle.o: cola_puzzle.c cola_puzzle.h sglib.h cola_impl.h puzzle.h
	$(CC) $(CFLAGS) $(CEROFLAGS) $(15PUZZLE) $(HASHFLAGS) -c -o $@ cola_puzzle.c


# para generar calculos de heuristica manhattan
preprocess.h: var-generator.py
	$(PYTHON) var-generator.py --header  > $@
	$(PYTHON) var-generator.py -n 8  >> $@
	$(PYTHON) var-generator.py -n 15 >> $@
	$(PYTHON) var-generator.py --footer >> $@
	$(PYTHON) var-generator.py --header --filacol >> $@
	$(PYTHON) var-generator.py -n 8  --filacol    >> $@
	$(PYTHON) var-generator.py -n 15 --filacol    >> $@
	$(PYTHON) var-generator.py --footer --filacol >> $@

defines.h:
	$(PYTHON) var-generator.py --defines -n 8 >  $@
	$(PYTHON) var-generator.py --defines -n 15 >> $@


# para generar la documentacion
docs: puzzle.c puzzle.h astar.c astar.h idastar.c idastar.h cola_puzzle.c cola_puzzle.h
	$(DOXYGEN) $(DOX_FILE)

clean_objs:
	rm -rf $(OBJS)

clean_docs:
	rm -rf $(DOCS)

clean_bin:
	rm -rf $(BINS)

clean: clean_objs clean_docs clean_bin
