CC=gcc
SRC_DIR=src
BIN_DIR=bin
LIB_DIR=lib
INCLUDE_DIR=include
CFLAG=-Wall -m64
SRC_FILES= \
	${SRC_DIR}/Lab02.c


.PHONY: clean rebuild

Lab02: ${SRC_FILES}
	${CC} ${CFLAG} ${SRC_FILES} -lpthread -o ${BIN_DIR}/Lab02

clean:
	rm ${BIN_DIR}/Lab02

rebuild: clean Lab02
