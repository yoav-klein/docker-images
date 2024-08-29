#!/bin/bash

docker run --name stress -d --env SIZE=128MB yoavklein3/stress:0.1
