CFLAGS=-std=c99 -Wall -g -fPIC -pedantic -O2
LDLIBS=-lglfw3 -ldl -framework OpenGL
SRC_MAIN=src/main.c
SRC_GAME=src/game/*.c \
		 src/game/core/*.c

all: game libgame.so

game:
	$(CC) $(SRC_MAIN) $(CFLAGS) $(LDFLAGS) -o bin/$@ $(LDLIBS)

libgame.so: $(SRC_GAME)
	$(CC) $(CFLAGS) -shared $(LDFLAGS) -o bin/$@ $(SRC_GAME) $(LDLIBS)

clean:
	$(RM) bin/*

run: game libgame.so
	./bin/$<
