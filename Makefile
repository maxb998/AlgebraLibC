# compiler name
CC = clang

SRC_DIR := src/
HEADERS_DIR := src/headers/

# build debug as default
OBJ_DIR = obj/debug/
BIN_DIR = bin/debug/
CFLAGS = -Wall -g -c -mavx2 -I$(HEADERS_DIR)
LDFLAGS1 = 
LDFLAGS2 = -lm

# condition to check value passed
ifeq ($(MODE),exec)
OBJ_DIR = obj/exec/
BIN_DIR = bin/exec/
CFLAGS = -O3 -c -mavx2 -march=native -I$(HEADERS_DIR)
LDFLAGS1 = 
LDFLAGS2 = -lm
endif

# files list
HEADERS := $(wildcard $(HEADERS_DIR)*.h)
SOURCES := $(wildcard $(SRC_DIR)*.c)
OBJ_FILES := $(SOURCES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# command used to check variables value and "debug" the makefile
print:
	@echo HEADERS = $(HEADERS)
	@echo SOURCES = $(SOURCES)
	@echo OBJ_FILES = $(OBJ_FILES)

# build options when debugging
build: $(BIN_DIR)main

$(BIN_DIR)main: $(OBJ_FILES)
	$(CC) $(LDFLAGS1) $(OBJ_FILES) -o $(BIN_DIR)main $(LDFLAGS2)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	$(CC) $(CFLAGS) $(SRC_DIR)$(*F).c -o $@

# delete all gcc output files
clean:
	rm -f bin/debug/main bin/exec/main
	rm -f obj/debug/*.o obj/exec/*.o



