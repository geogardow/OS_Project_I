.PHONY: all clean
.PHONY: all create
.PHONY: all client
.PHONY: all rebuild
BUILD_CLIENTE = cliente
BUILD_CREADOR = creador
BUILD_RECONSTRUCTOR = reconstructor

# Library paths
INPUTS_PATH = ../inputs
OUTPUTS_PATH = ../outputs
BIN_PATH = ../bin
INPUT_FILE = $(INPUTS_PATH)/input.txt
OUTPUT_FILE = $(OUTPUTS_PATH)/output.txt

all:
	@echo "Building bins..."
	@$(MAKE) -C cliente
	@$(MAKE) -C creador
	@$(MAKE) -C reconstructor
	
create:
	@$(MAKE) -C creador create
	
client:
	@$(MAKE) -C cliente client
	
rebuild:
	@$(MAKE) -C reconstructor rebuild
	
clean:
	@$(MAKE) -C cliente clean
	@$(MAKE) -C creador clean
	@$(MAKE) -C reconstructor clean
	
