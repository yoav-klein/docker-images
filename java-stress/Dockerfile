
FROM openjdk:11-jdk

WORKDIR /app

COPY app/* .

RUN javac MemoryConsumer.java

CMD ["java", "MemoryConsumer"]
