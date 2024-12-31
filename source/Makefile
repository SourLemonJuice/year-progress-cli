version = v1.2

clang_flag += -std=c17
clang_flag += -Wall
clang_flag += -O3

clang_flag += -DAPP_VERSION_STRING="\"${version}\""
clang_flag += -DAPP_VERSION_DESCRIBE="\"$(shell git describe --long --dirty)\""

sources_file=$(wildcard *.c)

default: year-progress

year-progress: main.c Makefile
	gcc ${sources_file} \
		--output year-progress \
		${clang_flag}

year-progress.js: main.c Makefile
	/usr/lib/emscripten/emcc ${sources_file} \
		-o year-progress.js \
		${clang_flag}
