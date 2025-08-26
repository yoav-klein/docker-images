#!/bin/bash

tag=yoavklein3/java-stress
version=0.5

build() {
    docker build -t $tag:$version .
}

push() {
    docker push $tag:$version
}

run() {
    docker run -p 8090:8090 -p 9404:9404 -d -e SIZE=200 --name java-stress $tag:$version
}

stop() {
    docker container stop java-stress
    docker container prune
}
