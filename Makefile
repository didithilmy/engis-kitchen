engi: main.c
	gcc -lncurses -lform -lpanel -o main main.c ui/imp/game_ui.c manager/imp/game.c adt/imp/mesin_kar.c adt/imp/mesin_kata.c manager/imp/intro.c ui/imp/intro_ui.c ui/imp/ui_commons.c eventbus/eventbus.c manager/imp/map.c -I.