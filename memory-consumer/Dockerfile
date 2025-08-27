
FROM ubuntu:24.04

RUN apt-get update

RUN mkdir /app
WORKDIR /app

COPY memory-consumer .

CMD ["./memory-consumer", "80"]
