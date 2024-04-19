# Define variables
CC := gcc

creador: creador/creador.c
	$(CC) -o creador/creador -lrt -lpthread $<
	./creador/creador $(PARAM)

cliente: cliente/cliente.c
	$(CC) -o cliente/cliente -lrt -lpthread $<
	./cliente/cliente

reconstructor: reconstructor/reconstructor.c
	$(CC) -o reconstructor/reconstructor -lrt -lpthread $<
	./reconstructor/reconstructor
