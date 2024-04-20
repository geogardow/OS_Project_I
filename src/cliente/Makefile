# Application names and source files
SRC = cliente.c
BUILD_CLIENTE = cliente

# Library paths
BIN_PATH = ../../bin

# Compiler and flags
CC = gcc
THREADFLAGS = -lrt -lpthread
MODE := 0

all: $(BUILD_CLIENTE)

$(BUILD_CLIENTE): $(SRC)
	cp ./input.txt ./live_read.txt
	$(CC) -o $(BIN_PATH)/$@ $< $(THREADFLAGS)
	
client:
	$(BIN_PATH)/$(BUILD_CLIENTE) $(MODE)
	
clean:
	rm -f $(BIN_PATH)/$(BUILD_CLIENTE)
	rm -f ./live_read.txt
