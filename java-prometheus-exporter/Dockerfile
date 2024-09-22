FROM openjdk:11-jdk

RUN mkdir /app
WORKDIR /app

RUN curl https://repo1.maven.org/maven2/io/prometheus/jmx/jmx_prometheus_javaagent/1.0.1/jmx_prometheus_javaagent-1.0.1.jar -o jmx_prometheus_javaagent_1.0.1.jar

COPY start.sh .
RUN chmod +x start.sh
COPY config.yaml .
COPY App.java .

RUN javac App.java

CMD ["./start.sh"]

