# Application names and source files
SRC = views.c
BUILD_VIEWS = views

# Library paths
BIN_PATH = ../../bin

# Compiler and flags
CC = gcc

all: $(BUILD_VIEWS)

$(BUILD_VIEWS): $(SRC)
	$(CC) -o $(BIN_PATH)/$@ $< 
	
view_out:
	gnome-terminal -- /bin/bash -c "../../bin/views ../reconstructor/output.txt; exec bash"

view_in:
	gnome-terminal -- /bin/bash -c "../../bin/views ../cliente/live_read.txt; exec bash"	

clean:
	rm -f $(BIN_PATH)/$(BUILD_VIEWS)
