CC=gcc
CFLAGS=-Wall -Werror -lm -std=c11 -lmingw32 -lSDL2main -lSDL2 -llibSDL2_image
LDIR=../lib/
LIBS=${wildcard ${LDIR}*.h}
LSRC=${wildcard ${LDIR}*.c}

sand: sand.c ${LIBS} ${LSRC}
	${CC} $^ -o $@ ${CFLAGS}

clean:
	rm ./*.o
	rm sand.exe