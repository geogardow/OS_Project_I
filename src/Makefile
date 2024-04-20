.PHONY: all clean
.PHONY: all create
.PHONY: all client
.PHONY: all rebuild
.PHONY: all stats

BUILD_CLIENTE = cliente
BUILD_CREADOR = creador
BUILD_RECONSTRUCTOR = reconstructor
BUILD_ESTADISTICA = estadistica

# Library paths
BIN_PATH = ../bin

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
	
stats:
	@$(MAKE) -C estadistica stats
	
clean:
	@$(MAKE) -C cliente clean
	@$(MAKE) -C creador clean
	@$(MAKE) -C reconstructor clean
	
