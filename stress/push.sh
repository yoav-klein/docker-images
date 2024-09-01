#!/bin/bash

name=stress
version=0.2

docker build -t yoavklein3/$name:$version .
docker push yoavklein3/$name:$version
