

memory-consumer: http-server/utils.c http-server/http-server.c sll.c memory-consumer.c
	gcc -o $@ $^ -lpthread -Ihttp-server

.PHONY: run
run: memory-consumer
	./memory-consumer 8081

.PHONY: clean
clean:
	rm memory-consumer
