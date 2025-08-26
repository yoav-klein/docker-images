

http-server: utils.c http-server.c main.c
	gcc -o $@ $^

.PHONY: run
run: http-server
	./http-server 8081
