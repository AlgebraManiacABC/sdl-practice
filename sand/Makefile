CC=gcc
CFLAGS=-Wall -Werror -lm -std=c11 -lSDL2main -lSDL2 -llibSDL2_image -lmingw32 -Wl,--subsystem,windows
LDIR=../lib/
ODIR=./build/
LIBS=${wildcard ${LDIR}*.h}
LIBS+=${wildcard ./*.h}
SDIR=${LDIR}
SDIR+=./
SRC=${wildcard ${LDIR}*.c}
SRC+=${wildcard ./*.c}
OBJS=${patsubst ./%, ${ODIR}%, ${SRC:%.c=%.o}}

sand: ${OBJS}
	${CC} $^ -o $@ ${CFLAGS} icon.res

${ODIR}%.o: ${SDIR}%.c ${LIBS}
	${CC} -c ${filter-out ../lib/,${filter-out %.h,$^}} -o $@ ${CFLAGS}

clean:
	rm ${ODIR}*.o
	rm ${LDIR}*.o
	rm ./*.exe
