CC = gcc
CFLAGS = -g
SRCS = main.c file_tools.c menu.c

all:	main.c file_tools.o menu.o
	@echo Programa para analizar comportamiento de las llamadas al sistema de archivos
	$(CC) $(CFLAGS) -o main main.c file_tools.o menu.o
file_tools.o: file_tools.c file_tools.h
	$(CC) $(CFLAGS) -c file_tools.c
menu.o:	menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c
clean:
	$(RM) -r *.o *~ *.o.dSYM main system_calls.txt
depend:	$(SRCS)
	makedepend $^
