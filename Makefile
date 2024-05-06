CC=gcc
CFLAGS = -Wno-implicit-function-declaration

compile: bitmap-art.c
	${CC} ${CFLAGS} -c bitmap-art.c

link: bitmap-art.o
	${CC} ${CFLAGS} bitmap-art.o -o bitmap-art

all: link

clean:
	rm bitmap-art.o bitmap-art
