CC = gcc
CFLAGS = -g

all:	client server
	@echo Programa basico de comunicacion entre procesos
client:
	$(CC) $(CFLAGS) -o client client.c client_utils.c
server:
	$(CC) $(CFLAGS) -o server server.c server_utils.c
clean:
	$(RM) -r *.o *~ *.o.dSYM server client fifo_*
