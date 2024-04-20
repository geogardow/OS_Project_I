.PHONY: all clean
.PHONY: all create
.PHONY: all client
.PHONY: all rebuild
.PHONY: all stats
.PHONY: all views

BUILD_CLIENTE = cliente
BUILD_CREADOR = creador
BUILD_RECONSTRUCTOR = reconstructor
BUILD_ESTADISTICA = estadistica
BUILD_VIEW = views

# Library paths
BIN_PATH = ../bin

all:
	@echo "Building bins..."
	@$(MAKE) -C cliente
	@$(MAKE) -C creador
	@$(MAKE) -C reconstructor
	@$(MAKE) -C views
	
create:
	@$(MAKE) -C creador create
	
clientv:
	@$(MAKE) -C views view_in
	@$(MAKE) -C cliente client
	
	
client:
	@$(MAKE) -C cliente client
	
rebuildv:
	echo > ./reconstructor/output.txt
	@$(MAKE) -C views view_out
	@$(MAKE) -C reconstructor rebuild
	
rebuild:
	@$(MAKE) -C reconstructor rebuild
	
stats:
	@$(MAKE) -C estadistica stats
		
clean:
	@$(MAKE) -C cliente clean
	@$(MAKE) -C creador clean
	@$(MAKE) -C reconstructor clean
	
