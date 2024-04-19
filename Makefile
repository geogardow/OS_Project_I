.PHONY: all clean
.PHONY: all create
.PHONY: all client
.PHONY: all rebuild
BUILD_CLIENTE = cliente
BUILD_CREADOR = creador
BUILD_RECONSTRUCTOR = reconstructor

# Library paths
INPUTS_PATH = ./inputs
OUTPUTS_PATH = ./outputs
BIN_PATH = ./bin
INPUT_FILE = $(INPUTS_PATH)/input.txt
OUTPUT_FILE = $(OUTPUTS_PATH)/output.txt

all:
	@echo "Building bins..."
	@$(MAKE) -C src
	
create:
	@$(MAKE) -C src create
	
client:
	@$(MAKE) -C src client
	
rebuild:
	@$(MAKE) -C src rebuild
	
clean:
	@$(MAKE) -C src clean
	
