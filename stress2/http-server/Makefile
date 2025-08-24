

http-server: utils.c http-server.c http-server.h
	gcc -o $@ $^

.PHONY: run
run: http-server
	./http-server 8081
