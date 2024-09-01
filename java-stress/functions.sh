#!/bin/bash

tag=yoavklein3/java-stress
version=0.1

build() {
    docker build -t $tag:$version .
}

push() {
    docker push $tag:$version
}

run() {
    docker run -m 200MB -d -e SIZE=200 --name java-stress $tag:$version
}

