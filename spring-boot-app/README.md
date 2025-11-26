# Spring Boot application
---

### Background
For testing a Datadog dashboard, specifically the HTTP-related metrics exposed by Spring Boot, I needed an Spring Boot application
that exposes the prometheus metrics, and also have few endpoints that I can control their latency.

So this app has the `/delay`, `/foo` and `/bar` endpoints which are all the same, taking the `ms` parameter for milliseconds to delay.

