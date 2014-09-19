BUILD_DIR := bin
SOURCE_DIR := src
TEST_DIR := tests
CFLAGS += -std=gnu99 -g -DDEBUG -Wall
ALL_SOURCES := $(wildcard ${SOURCE_DIR}/*.c)
LIB_SRC := $(filter-out src/main%.c, $(ALL_SOURCES))

Q1_NAME := q1
Q1_ARGS := 6 6
Q1_ENTRY := $(SOURCE_DIR)/main.c
Q1_SRC := $(LIB_SRC) $(Q1_ENTRY)
Q1_OBJ := ${Q1_SRC:%.c=%.o}

Q2_NAME := q2
Q2_ARGS := $(Q1_ARGS)
Q2_ENTRY := $(SOURCE_DIR)/main2.c
Q2_SRC := $(LIB_SRC) $(Q2_ENTRY)
Q2_OBJ := ${Q2_SRC:%.c=%.o}

Q3_NAME := q3
Q3_ARGS := $(Q1_ARGS)
Q3_ENTRY := $(SOURCE_DIR)/main3.c
Q3_SRC := $(LIB_SRC) $(Q3_ENTRY)
Q3_OBJ := ${Q3_SRC:%.c=%.o}

Q4_NAME := q4
Q4_ARGS := $(Q1_ARGS)
Q4_ENTRY := $(SOURCE_DIR)/main4.c
Q4_SRC := $(LIB_SRC) $(Q4_ENTRY)
Q4_OBJ := ${Q4_SRC:%.c=%.o}

ALL_EXE := $(Q1_NAME) $(Q2_NAME) $(Q3_NAME) $(Q4_NAME)
ALL_EXE += $(ALL_EXE) ${ALL_EXE:%=%.exe} ${ALL_EXE:%=%.dSYM}
ALL_OBJ := ${ALL_SOURCES:%.c=%.o}

TEST_SRC := $(wildcard ${TEST_DIR}/*.c)
TEST_OBJ := ${TEST_SRC:%.c=%.o} 
TEST_INC := $(SOURCE_DIR)
TEST_EXE := ${TEST_SRC:%.c=%} ${TEST_SRC:%.c=%.exe} ${TEST_SRC:%.c=%.dSYM}

ifneq ($(OS),Windows_NT)
	CFLAGS += -pthread
endif

.PHONY: all clean distclean test

all: $(Q1_NAME) $(Q2_NAME) $(Q3_NAME) $(Q4_NAME)

$(Q1_NAME): $(Q1_OBJ)
	$(LINK.c) $(Q1_OBJ) -o $(Q1_NAME)

$(Q2_NAME): $(Q2_OBJ)
	$(LINK.c) $(Q2_OBJ) -o $(Q2_NAME)

$(Q3_NAME): $(Q3_OBJ)
	$(LINK.c) $(Q3_OBJ) -o $(Q3_NAME)

$(Q4_NAME): $(Q4_OBJ)
	$(LINK.c) $(Q4_OBJ) -o $(Q4_NAME)

clean:
	@- $(RM) -rf $(ALL_EXE) $(TEST_EXE)
	@- $(RM) $(ALL_OBJ) $(TEST_OBJ)

distclean: clean

run: all
	./$(Q1_NAME) $(Q1_ARGS)

test: CFLAGS += $(foreach includedir,$(TEST_INC),-I$(includedir))
test: $(ALL_OBJ) 
	@- $(foreach test, $(TEST_SRC), $(LINK.c) $(test) $(LIB_SRC) -o $(patsubst %.c, %, $(test)); echo Running $(patsubst %.c, %, $(test)); $(patsubst %.c, %, $(test)); echo;)
