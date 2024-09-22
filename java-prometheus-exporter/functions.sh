#!/bin/bash

name=yoavklein3/java-prom-exp
tag=0.1

build() {
    docker build -t $name:$tag .
}

run() {
    docker run -d -e SIZE=200 --network=host --name java-prom-exp $name:$tag
}

push() {
    docker push $name:$tag
}
