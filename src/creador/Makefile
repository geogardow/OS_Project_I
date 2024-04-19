# Application names and source files
SRC = creador.c
BUILD_CREADOR = creador

# Library paths
BIN_PATH = ../../bin

# Compiler and flags
CC = gcc
THREADFLAGS = -lrt -lpthread
N := 100

all: $(BUILD_CREADOR)

$(BUILD_CREADOR): $(SRC)
	$(CC) -o $(BIN_PATH)/$@ $< $(THREADFLAGS)
	

create:
	$(BIN_PATH)/$(BUILD_CREADOR) $(N)

clean:
	rm -f $(BIN_PATH)/$(BUILD_CREADOR)
