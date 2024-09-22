#!/bin/bash

name=yoavklein3/log-generator
tag=0.1

build() {
    docker build -t $name:$tag .
}

run() {
    docker run -d --name log-generator $name:$tag
}

push() {
    docker push $name:$tag
}
