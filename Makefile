CC=gcc
BUILD_DIR := bin
SOURCE_DIR := src
TEST_DIR := tests
CFLAGS += -std=gnu99 -g -DDEBUG -Wall -pthread
ALL_SOURCES := $(wildcard ${SOURCE_DIR}/*.c)
EXCLUDE := src/main2.c src/main3.c src/main4.c
ALL_SOURCES := $(filter-out ${EXCLUDE},${ALL_SOURCES})
ALL_OBJ := ${ALL_SOURCES:%.c=%.o}

Q1_NAME := q1
Q1_OBJ := $(filter-out src/question2.o src/question3.o src/question4.o, ${ALL_OBJ}) 
Q2_NAME := q2
Q2_OBJ := $(filter-out src/question1.o src/question3.o src/question4.o, ${ALL_OBJ}) 
Q3_NAME := q3
Q3_OBJ := $(filter-out src/question2.o src/question1.o src/question4.o, ${ALL_OBJ}) 
Q4_NAME := q4
Q4_OBJ := $(filter-out src/question2.o src/question3.o src/question1.o, ${ALL_OBJ}) 

ALL_EXE := $(Q1_NAME) $(Q2_NAME) $(Q3_NAME) $(Q4_NAME)
ALL_EXE += $(ALL_EXE) ${ALL_EXE:%=%.exe} ${ALL_EXE:%=%.dSYM}

TEST_SRC := $(wildcard ${TEST_DIR}/*.c)
TEST_OBJ := ${TEST_SRC:%.c=%.o} 
TEST_LIB := $(filter-out src/question% src/main%, ${ALL_SOURCES})
TEST_INC := $(SOURCE_DIR)
TEST_EXE := ${TEST_SRC:%.c=%} ${TEST_SRC:%.c=%.exe} ${TEST_SRC:%.c=%.dSYM}

.PHONY: all clean distclean test

all: $(Q1_NAME) $(Q2_NAME) $(Q3_NAME) $(Q4_NAME)

$(Q1_NAME): CFLAGS += -DQ1
$(Q1_NAME): $(Q1_OBJ)
	$(LINK.c) $(Q1_OBJ) -o $(Q1_NAME)

$(Q2_NAME): CFLAGS += -DQ2
$(Q2_NAME): $(Q2_OBJ)
	$(LINK.c) $(Q2_OBJ) -o $(Q2_NAME)

$(Q3_NAME): CFLAGS += -DQ3
$(Q3_NAME): $(Q3_OBJ)
	$(LINK.c) $(Q3_OBJ) -o $(Q3_NAME)

$(Q4_NAME): CFLAGS += -DQ4
$(Q4_NAME): $(Q4_OBJ)
	$(LINK.c) $(Q4_OBJ) -o $(Q4_NAME)

clean:
	@- $(RM) -rf $(ALL_EXE) $(TEST_EXE)
	@- $(RM) $(ALL_OBJ) $(TEST_OBJ)

distclean: clean

test: CFLAGS += $(foreach includedir,$(TEST_INC),-I$(includedir))
test: $(ALL_OBJ) 
	$(foreach test, $(TEST_SRC), $(LINK.c) $(test) $(TEST_LIB) -o $(patsubst %.c, %, $(test)); echo Running $(patsubst %.c, %, $(test)); $(patsubst %.c, %, $(test)); echo;)
