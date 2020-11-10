CC = gcc
CCFLAGS = -O2 -Werror -Wall -Wextra -Wshadow

LIB_TARGET = perceptron.a
TST_TARGET = perceptron_test

SRC = $(shell find ./src -name "*.c")
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

.phony: all
all: lib test

.phony: dirs
dirs:
	@mkdir -p obj lib
	
.phony: lib
lib: dirs $(OBJ)
	@mkdir -p ./lib
	@echo [AR] ./lib/$(LIB_TARGET)
	@ar -crs ./lib/$(LIB_TARGET) $(OBJ)



obj/%.o: src/%.c
	@echo [CC] $@
	@$(CC) -c $< -o $@ $(CCFLAGS) -Iinclude

.phony: test
test:
	@mkdir -p bin
	@echo [*] Compiling the test ..
	@$(CC) ./test.c ./lib/$(LIB_TARGET) -o bin/$(TST_TARGET) $(CCFLAGS) -Iinclude
	@$(CC) ./test_noise.c ./lib/$(LIB_TARGET) -o bin/$(TST_TARGET)_noise $(CCFLAGS) -Iinclude
	
	

	
.phony: clean
clean:
	@rm -r obj
	
.phony: clean_all
clean_all:
	@rm -r obj lib bin
