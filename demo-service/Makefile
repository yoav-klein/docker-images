
IMAGE=yoavklein3/demo-service


.PHONY: build-image
build-image:
	docker build --build-arg VERSION=${VERSION} -t ${IMAGE}:${VERSION} .
	docker tag ${IMAGE}:${VERSION} ${IMAGE}:latest

.PHONY: push-image
push-image: build-image
	docker push ${IMAGE}:${VERSION}


.PHONY: run
run-version:
	docker run --rm --name demo-service -p 8080:8080 -d ${IMAGE}:${VERSION}

.PHONY:
run-latest:
	docker run --rm --name demo-service -p 8080:8080 -d ${IMAGE}:latest

.PHONY: push
push: build-image
	docker push ${IMAGE}:${VERSION}

.PHONY: stop
stop:
	docker container stop demo-service

.PHONY: test
test:
	curl localhost:8080/VERSION
