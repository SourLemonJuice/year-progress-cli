CC := clang

version := $(shell git describe --tags --exact-match)
ifneq ($(.SHELLSTATUS), 0)
version := unstable
endif
version_long := $(shell git describe --tags --dirty --long)

# use "=" for dynamic changes
package_name = year-progress-$(version)-linux-x86_64

CFLAGS += -std=c17
CFLAGS += -Wall -Wextra -Wvla -Wno-unused-parameter
CFLAGS += -O2
CFLAGS += -Iexternal/ArgParseX/include/

CFLAGS += -DAPP_VERSION_STRING="\"$(version)\""
CFLAGS += -DAPP_VERSION_DESCRIBE="\"$(version_long)\""

sources_file := $(wildcard source/*.c)

all: year-progress

dist: year-progress-deb year-progress-rpm year-progress-pacman

libargparsex.a:
	cd external/ArgParseX/ && \
		./configure.sh --enable-batch-alloc && \
		mkdir -p build && \
		make && \
		cp build/libargparsex.a ../../

year-progress: $(sources_file) libargparsex.a
	$(CC) $^ $(CFLAGS) \
		-o year-progress

year-progress-deb: year-progress
	fpm --output-type deb \
		--version $(version) \
		--package $(package_name).deb

year-progress-rpm: year-progress
	fpm --output-type rpm \
		--version $(version) \
		--package $(package_name).rpm

year-progress-pacman: year-progress
	fpm --output-type pacman \
		--version $(version) \
		--package $(package_name).pkg.tar.zst

clean:
	-rm year-progress
	-rm lib*.a
	-rm *.deb *.rpm *.pkg.tar.zst
