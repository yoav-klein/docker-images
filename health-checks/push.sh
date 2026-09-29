#!/bin/bash

VERSION=0.2

docker build -t yoavklein3/health:${VERSION} --build-arg VERSION=${VERSION} .
docker push yoavklein3/health:0.1
