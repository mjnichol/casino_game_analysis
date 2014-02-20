all: main.o game.o deck.o
	gcc main.o game.o deck.o -o cat_eric.exe -lm	

main.o: main.c
	gcc -c main.c
game.o: game.c
	gcc -c game.c
deck.o: deck.c
	gcc -c deck.c

clean:
	rm -rf *.o casino_game.exe
