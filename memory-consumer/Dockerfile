
FROM ubuntu:24.04

RUN apt-get update

RUN mkdir /app
WORKDIR /app

COPY stress.c .
RUN gcc stress.c -o stress

CMD ["./stress"]
