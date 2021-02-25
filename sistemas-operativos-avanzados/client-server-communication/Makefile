CC = gcc
CFLAGS = -g
#SRCS = client.c server.c
#OBJS = $(SRCS:.c=.o)

all:	client
	@echo Programa basico de comunicacion entre procesos
#	$(CC) $(CFLAGS) -o client
client:
	$(CC) $(CFLAGS) -o client -c client.c
clean:
	$(RM) -r *.o *~ *.o.dSYM
