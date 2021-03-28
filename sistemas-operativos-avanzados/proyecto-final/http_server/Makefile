CC = gcc
CFLAGS = -g
SRCS = server.c server_utils.c

all:	server.c server_utils.o
	@echo Sistema Operativo Servidor
	$(CC) $(CFLAGS) -o server server.c server_utils.o
server_utils.o: server_utils.c server_utils.h
	$(CC) $(CFLAGS) -c server_utils.c
clean:
	$(RM) -r *.o *~ *.o.dSYM server os_image os
depend:	$(SRCS)
	makedepend $^
