
FROM ubuntu:22.04


RUN apt-get update
RUN apt-get install -y stress

COPY stress.sh /

CMD ["/stress.sh"]
