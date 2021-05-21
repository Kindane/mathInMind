MAIN_FILE = main.cpp
CC = g++
BUILD_DIR = build
OUTPUT_FILE = main

.PHONY: build

all: build run

build:
	@mkdir -p ${BUILD_DIR}
	${CC} ${MAIN_FILE} -o ${BUILD_DIR}/${OUTPUT_FILE}

run: build
	${BUILD_DIR}/${OUTPUT_FILE}

clean:
	@echo Removing \"${BUILD_DIR}\" directory...
	@rm -rf ${BUILD_DIR}
	@echo Done.