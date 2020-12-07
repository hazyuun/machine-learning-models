CC = gcc
CCFLAGS = -g -O2 -Werror -Wall -Wextra -Wshadow
INCLUDE = -Iinclude -Iinclude/utils -Irainy-csv/src

LIB_TARGET = perceptron.a
TST_TARGET = perceptron_test

SRC = $(shell find ./src -name "*.c")
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

.phony: all
all: lib tests

.phony: dirs
dirs:
	@mkdir -p $(dir $(OBJ)) bin
	
.phony: lib
lib: dirs $(OBJ)
	@mkdir -p ./lib
	@echo [AR] ./lib/$(LIB_TARGET)
	@ar -crs ./lib/$(LIB_TARGET) $(OBJ)



obj/%.o: src/%.c
	@echo [CC] $@
	@$(CC) -c $< -o $@ $(CCFLAGS) $(INCLUDE) -D USE_RAINY_CSV


TESTSRC = $(shell find ./tests -name "*.c")
TESTEXE = $(patsubst ./tests/%.c, ./bin/%, $(TESTSRC))
CSVSRC = rainy-csv/src/csv.c
TESTINC = -Iinclude -Irainy-csv/src -Iinclude/utils

.phony: tests
tests: dirs $(TESTEXE)
	
bin/%: tests/%.c
	@echo [CC] $@
	@$(CC) $< ./lib/$(LIB_TARGET) $(CSVSRC) -o $@ $(CCFLAGS) $(TESTINC) -lm
	
.phony: clean
clean:
	@rm -r obj
	
.phony: clean_all
clean_all:
	@rm -r obj lib bin
