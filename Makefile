CC=gcc
EXE_ARGS=6 6
CC_FLAGS= -std=gnu99 -g
ALL_SOURCES=$(wildcard src/*.c)
LIB_SRC=$(filter-out src/main%.c, $(ALL_SOURCES))
Q1_MAIN=src/main.c
Q1_EXE=q1
Q1_BUILD=$(CC) $(CC_FLAGS) -o $(Q1_EXE) $(LIB_SRC) $(Q1_MAIN)

ifneq ($(OS),Windows_NT)
	CC_FLAGS += -pthread
endif

all: build

build:
	$(Q1_BUILD)

clean:
	rm -f $(Q1_EXE) $(Q1_EXE).exe;

run: build
	./$(EXE) $(EXE_ARGS)
