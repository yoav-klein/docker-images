#!/bin/bash

name=stress

docker build -t yoavklein3/$name:0.1 .
docker push yoavklein3/$name:0.1
