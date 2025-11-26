# ---- Build stage ----
FROM eclipse-temurin:21-jdk-alpine AS builder
WORKDIR /app

COPY . ./
RUN chmod +x gradlew
RUN ./gradlew bootJar


# ---- Run stage ----
FROM eclipse-temurin:21-jre-alpine
WORKDIR /app

# Copy the built jar from the previous stage
COPY --from=builder /app/app/build/libs/*.jar app.jar

# Expose port 8080 (Spring Boot default)
EXPOSE 8080

# Set default JVM options (optional)
ENV JAVA_OPTS="-XX:+UseContainerSupport"

# Run the Spring Boot app
ENTRYPOINT ["sh", "-c", "java $JAVA_OPTS -jar app.jar"]

