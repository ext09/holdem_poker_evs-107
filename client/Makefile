CFLAGS=-Wall -pedantic --std=c99 `pkg-config --cflags --libs sdl` -lSDL_image -lSDL_ttf

poker: main.c
	$(CC) $(CFLAGS) -o $@ $^

