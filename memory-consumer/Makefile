
SRC=src
IMAGE=yoavklein/memory-consumer
VERSION=0.1

memory-consumer: http-server/utils.c http-server/http-server.c ${SRC}/sll.c ${SRC}/memory-consumer.c
	gcc -o $@ $^ -lpthread -Ihttp-server

.PHONY: run
run: memory-consumer
	./memory-consumer 8081

.PHONY: clean
clean:
	rm memory-consumer

.PHONY: build-image
build-image: memory-consumer
	docker build -t ${IMAGE}:${VERSION} .

.PHONY: push
push: build-image
	docker push ${IMAGE}:${VERSION}
