MAIN_FILE = main.cpp
OTHER_FILES =
CC = gcc
BUILD_DIR = build
OUTPUT_FILE = main

.PHONY: build

all: build run

build:
	@mkdir -p ${BUILD_DIR}
	${CC} ${MAIN_FILE} ${OTHER_FILES} -o ${BUILD_DIR}/${OUTPUT_FILE} -lstdc++

run: build
	${BUILD_DIR}/${OUTPUT_FILE}

clean:
	@echo Removing \"${BUILD_DIR}\" directory...
	@rm -rf ${BUILD_DIR}
	@echo Done.