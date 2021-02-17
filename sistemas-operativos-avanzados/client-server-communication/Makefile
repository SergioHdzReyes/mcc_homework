CC = gcc
CFLAGS = -g
SRCS = client.c server.c
OBJS = $(SRCS:.c=.o)

all:	$(OBJS)
	@echo Programa basico de comunicacion entre procesos
.c.o:
	$(CC) -o $@ $(CFLAGS) $<
clean:
	$(RM) -r *.o *~ *.o.dSYM
