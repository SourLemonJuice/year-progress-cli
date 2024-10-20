clang_flag += -std=c17
clang_flag += -Wall
clang_flag += -O3

clang_flag += -DAPP_VERSION_STRING="\"Build 1\""
clang_flag += -DAPP_VERSION_DESCRIBE="\"$(shell git describe --long --dirty)\""

sources_file=$(wildcard *.c)

default: year-progress

year-progress: main.c GNUmakefile
	gcc ${sources_file} \
		--output year-progress \
		${clang_flag}
