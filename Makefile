SRC=src/*.c
BIN=openuo

all:
	mkdir -p bin
	gcc $(SRC) -g -L ../raylib/release/osx -I ../raylib/src -lglfw3 -lraylib -framework OpenGL -o bin/${BIN}

run: all
	./bin/${BIN}
