# Application names and source files
SRC = cliente.c
BUILD_CLIENTE = cliente

# Library paths
BIN_PATH = ../../bin

# Compiler and flags
CC = gcc
THREADFLAGS = -lrt -lpthread

all: $(BUILD_CLIENTE)

$(BUILD_CLIENTE): $(SRC)
	$(CC) -o $(BIN_PATH)/$@ $< $(THREADFLAGS)
	
client:
	$(BIN_PATH)/$(BUILD_CLIENTE)
	
clean:
	rm -f $(BIN_PATH)/$(BUILD_CLIENTE)

