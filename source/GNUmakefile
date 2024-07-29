clang_flag += -std=c17
clang_flag += -Wall
clang_flag += -Os

sources_file=$(wildcard *.c)

default: year-progress

year-progress: main.c GNUmakefile
	gcc ${sources_file} \
		--output year-progress \
		${clang_flag}
