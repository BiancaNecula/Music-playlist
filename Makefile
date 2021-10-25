# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99


build: main.c DoublyLinkedList.c DoublyLinkedList.h
	$(CC) $(CFLAGS) -o tema1 main.c DoublyLinkedList.c 

pack:
	zip -FSr 315CA_BiancaNecula_Tema1.zip README Makefile *.c *.h

clean:
	rm -f tema1

