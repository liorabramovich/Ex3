all: stringProg

stringProg: main.o
	gcc -Wall -Werror -o stringProg main.o

main.o: main.c
	gcc -Wall -Werror -c main.c

clean:
	rm -f *.a *.o stringProg