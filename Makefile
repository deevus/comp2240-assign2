CC=gcc
EXE=Assignment2
EXE_ARGS=6 6
CC_FLAGS= -o $(EXE) -std=gnu99 -g
SOURCES=*.c

ifneq ($(OS),Windows_NT)
	CC_FLAGS += -pthread
endif

all: build

build:
	$(CC) $(CC_FLAGS) $(SOURCES)

clean:
	rm -f $(EXE) $(EXE).exe;

run: build
	./$(EXE) $(EXE_ARGS)
