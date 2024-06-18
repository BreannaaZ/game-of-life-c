all : life.c board.c board.h
	gcc -o life.out life.c board.c board.h

clean:
	rm life.out
