#!/bin/bash

docker run --rm --name stress -d --env SIZE=400 yoavklein3/stress:0.1
