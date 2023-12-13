CC	= cc
CFLAGS	= -std=c18 -pedantic -Wall -Werror -g -O3 -funsigned-char -fsanitize=address
OUT	= a.out
FILE	= main

example: compile
	./a.out < inputE.txt > output.txt
	difft output.txt correct.txt

execute: compile
	./a.out < input.txt > output.txt
	bat output.txt

compile: clean $(FILE).o malloc.o
	$(CC) $(CFLAGS) -o $(OUT) $(FILE).o malloc.o

$(FILE).o: $(FILE).c
	$(CC) -include wecc.h -c $(FILE).c $(CFLAGS)

malloc.o: malloc.c
	$(CC) -c malloc.c $(CFLAGS) 

clean:
	rm -f *.s *.o $(OUT) output.txt
