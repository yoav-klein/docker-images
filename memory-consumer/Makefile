
SRC=src
IMAGE=yoavklein3/memory-consumer
VERSION=0.2

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

.PHONY: run-container
run-container: build-image
	docker run --name memory-consumer -p 8081:80 -d --rm ${IMAGE}:${VERSION}

.PHONY: stop-container
stop-container:
	docker container stop memory-consumer
