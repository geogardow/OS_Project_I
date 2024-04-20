# Application names and source files
SRC = estadistica.c
BUILD_ESTADISTICA = estadistica

# Library paths
BIN_PATH = ../../bin

# Compiler and flags
CC = gcc
THREADFLAGS = -lrt -lpthread

stats: $(BUILD_ESTADISTICA)

$(BUILD_ESTADISTICA): $(SRC)
	$(CC) -o $(BIN_PATH)/$@ $< $(THREADFLAGS)
	$(BIN_PATH)/$(BUILD_ESTADISTICA)
	
clean:
	rm -f $(BIN_PATH)/$(BUILD_ESTADISTICA)
