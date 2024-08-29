
FROM ubuntu:22.04


RUN apt-get update
RUN apt-get install -y stress
RUN apt-get install -y gcc

RUN mkdir /app
WORKDIR /app

COPY stress.c .
RUN gcc stress.c -o stress

CMD ["./stress"]
