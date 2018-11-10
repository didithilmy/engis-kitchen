engi: main.c
	gcc -lncurses -lform -lpanel -o main main.c display.c game.c adt/imp/mesin_kar.c adt/imp/mesin_kata.c -I.