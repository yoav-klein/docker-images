#!/bin/bash

name=stress2
version=0.1

docker build -t yoavklein3/$name:$version .
docker push yoavklein3/$name:$version
