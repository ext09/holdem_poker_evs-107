CFLAGS=-Wall -pedantic --std=c99 `pkg-config --cflags --libs sdl`

poker: main.c menu.c
	$(CC) -o $@ $^

