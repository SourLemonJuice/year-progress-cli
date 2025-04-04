CC = clang

version = v2.0.1

CFLAGS += -std=c17
CFLAGS += -Wall -Wextra -Wvla -Wno-unused-parameter
CFLAGS += -O3
CFLAGS += -Iexternal/ArgParseX/include/

CFLAGS += -DAPP_VERSION_STRING="\"${version}\""
CFLAGS += -DAPP_VERSION_DESCRIBE="\"$(shell git describe --long --dirty)\""

sources_file=$(wildcard source/*.c)

default: year-progress

libargparsex.a:
	cd external/ArgParseX/ && \
		./configure.sh --enable-batch-alloc && \
		mkdir -p build && \
		make && \
		cp build/libargparsex.a ../../

year-progress: ${sources_file} libargparsex.a
	${CC} $^ ${CFLAGS} \
		-o year-progress

# TODO to be deleted
year-progress.js: ${sources_file}
	/usr/lib/emscripten/emcc $^ ${CFLAGS} \
		-o year-progress.js

.PHONY: clean
clean:
	-rm year-progress
	-rm lib*.a
