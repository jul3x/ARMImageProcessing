CC = gcc
ASM = as
CFLAGS = -std=c99 -O3 -Wall -Wextra -pedantic

all: img_process

img_process: main.c libpnmio/src/pnmio.c libpnmio/src/pnmio.h img.o
	${CC} -o img_process main.c libpnmio/src/pnmio.c libpnmio/src/pnmio.h img.o -lm ${CFLAGS}

img.o : img.s
	${ASM} -o img.o img.s

clean: all
	rm img_process img.o
