CC=gcc
EXE=Assignment2
EXE_ARGS=1 2
CC_OPTS=-o $(EXE) -std=gnu99 -g
SOURCES=*.c

all: build

build:
	$(CC) $(CC_OPTS) $(SOURCES)

clean:
	rm -f $(EXE) $(EXE).exe;

run: build
	./$(EXE) $(EXE_ARGS)
