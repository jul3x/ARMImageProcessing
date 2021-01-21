CC = gcc
AR = ar
CFLAGS = -std=c99 -O3 -Wall -Wextra -pedantic

all: img_process

img_process: main.c libpnmio/src/pnmio.c libpnmio/src/pnmio.h
	${CC} -o img_process main.c libpnmio/src/pnmio.c libpnmio/src/pnmio.h -lm ${CFLAGS}

clean: all
	rm img_process
