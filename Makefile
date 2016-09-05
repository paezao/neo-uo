SRC=src/*.c \
	src/resources/*.c
BIN=uo

all:
	mkdir -p bin
	gcc $(SRC) -g -L ../raylib/release/osx -I ../raylib/src -lglfw3 -lraylib -framework OpenGL -o bin/${BIN}

run: all
	./bin/${BIN}
