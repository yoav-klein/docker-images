#!/bin/bash

env

java -javaagent:/app/jmx_prometheus_javaagent_1.0.1.jar=9404:/app/config.yaml App

