CFLAGS = -g

life: life.o game.o board.o file.o
	gcc $(CFLAGS) -Wall game.o board.o file.o life.o -lm -o life
game.o:game.c
	gcc $(CFLAGS) -Wall -c game.c
board.o:board.c
	gcc $(CFLAGS) -Wall -c board.c
fileprocess.o:fileprocess.c
	gcc $(CFLAGS) -Wall -c file.c
life.o:life.c
	gcc $(CFLAGS) -Wall -c life.c
clean:
	rm -f life.o game.o board.o file.o
