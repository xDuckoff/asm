all: program clean
program: a.o b.o
	gcc -m32 -o program a.o b.o
a.o: main.c
	gcc -m32 -std=c99 -o a.o -c main.c
b.o: prak.asm
	nasm -f elf32 -o b.o prak.asm
clean:
	rm a.o
	rm b.o
