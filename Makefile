CXX = g++
CFLAGS = -W -Wall -Werror -ggdb3
BUILD_DIR = build
OBJ = main.o

main: ${BUILD_DIR}/${OBJ}
	${CXX} ${CFLAGS} $< -o ${BUILD_DIR}/main

${BUILD_DIR}/%.o: %.cpp
	@mkdir -p ${BUILD_DIR}
	${CXX} ${CFLAGS} $< -c -o $@

clean:
	rm -rf ${BUILD_DIR}

run: main
	./${BUILD_DIR}/main

debug: main
	valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=valgrind-out.txt \
			./main
