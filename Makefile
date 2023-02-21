LOGGER_IP ?= # put log server IP in string
FTP_IP ?= # put console IP here

.PHONY: all build clean configure log post-build

all: build post-build

build:
	$(MAKE) -C build subsdk9_meta

post-build:
	rm build/mod.tar.gz || true
	mkdir atmosphere/ || true
	mkdir atmosphere/contents/ || true
	mkdir atmosphere/contents/0100000000010000/ || true
	mkdir atmosphere/contents/0100000000010000/exefs/ || true
	cp -f build/main.npdm atmosphere/contents/0100000000010000/exefs/
	cp -f build/subsdk9 atmosphere/contents/0100000000010000/exefs/
	tar -zcvf build/mod.tar.gz atmosphere/ LunaKit/

configure: clean
	cmake --toolchain=cmake/toolchain.cmake -DFTP_IP=$(FTP_IP) -DLOGGER_IP=$(LOGGER_IP) -S . -B build

clean:
	rm -r build || true

log: all
	python3 scripts/tcpServer.py 0.0.0.0
