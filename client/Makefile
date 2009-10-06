CFLAGS=-Wall -pedantic -ggdb --std=c99 `pkg-config --cflags --libs sdl` -lSDL_image -lSDL_ttf -lSDL_mixer

poker: main.c
	$(CC) $(CFLAGS) -o $@ $^

