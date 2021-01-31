CC = gcc
CFLAGS =
SRCS = main.c file_tools.c menu.c

all:	main.c file_tools.o menu.o
	@echo Programa para analizar comportamiento de las llamadas al sistema de archivos
	$(CC) -o main main.c file_tools.o menu.o
file_tools.o: file_tools.c file_tools.h
	$(CC) -c file_tools.c
menu.o:	menu.c menu.h
	$(CC) -c menu.c
clean:
	$(RM) -r *.o *~ *.o.dSYM
depend:	$(SRCS)
	makedepend $^
