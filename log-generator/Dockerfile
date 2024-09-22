
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y jq

COPY logs.sh .

CMD ["./logs.sh"]
