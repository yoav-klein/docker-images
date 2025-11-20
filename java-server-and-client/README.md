# Observability - Tracing integration
---

In this demo we use Spring Boot to simulate a client and server. As in the basic example, 
we create a OpenTelemetry instance, this time having it write spans to Jaeger.
We hook our configure OpenTelemetry to the ObservabilityRegistry of Spring Boot, and
we have traces and spans created for us by Spring automatically.

## Usage
---

```
$ docker compose up [--build] -d
$ curl localhost:8080/delay
```

Then go the jaeger UI in port 8090 and see the traces, vatechi nafshecha!
