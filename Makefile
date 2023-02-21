LOGGER_IP ?= # put log server IP in string
FTP_IP ?= # put console IP here

.PHONY: all clean configure log

all:
	$(MAKE) -C build subsdk9_meta

configure: clean
	cmake --toolchain=cmake/toolchain.cmake -DFTP_IP=$(FTP_IP) -DLOGGER_IP=$(LOGGER_IP) -S . -B build

clean:
	rm -r build || true

log: all
	python3.8 scripts/tcpServer.py 0.0.0.0
