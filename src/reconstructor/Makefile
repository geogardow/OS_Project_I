# Application names and source files
SRC = reconstructor.c
BUILD_RECONSTRUCTOR = reconstructor

# Library paths
BIN_PATH = ../../bin

# Compiler and flags
CC = gcc
THREADFLAGS = -lrt -lpthread
MODE := 0

all: $(BUILD_RECONSTRUCTOR)

$(BUILD_RECONSTRUCTOR): $(SRC)
	$(CC) -o $(BIN_PATH)/$@ $< $(THREADFLAGS)
	
rebuild:
	$(BIN_PATH)/$(BUILD_RECONSTRUCTOR) $(MODE)

clean:
	rm -f $(BIN_PATH)/$(BUILD_RECONSTRUCTOR)
	rm -f ./output.txt

