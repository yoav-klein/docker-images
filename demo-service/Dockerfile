FROM python:3.12-slim

# Build-time argument
ARG VERSION

# Make it available at runtime
ENV VERSION=${VERSION}

WORKDIR /app

RUN pip install --no-cache-dir flask

COPY app.py /app/app.py

EXPOSE 8080

CMD ["python", "app.py"]

