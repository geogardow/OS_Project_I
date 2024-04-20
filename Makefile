.PHONY: all clean
.PHONY: all create
.PHONY: all client
.PHONY: all rebuild
.PHONY: all stats

BUILD_CLIENTE = cliente
BUILD_CREADOR = creador
BUILD_RECONSTRUCTOR = reconstructor

# Library paths
BIN_PATH = ./bin


all:
	@echo "Building bins..."
	@$(MAKE) -B -C src
	
create:
	@$(MAKE) -C src create
	
client:
	@$(MAKE) -C src client
	
rebuild:
	@$(MAKE) -C src rebuild
	
stats:
	@$(MAKE) -C src stats
	
clean:
	@$(MAKE) -C src clean
	
