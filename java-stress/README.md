# Java Stress
---

This is a Java memory consumer to diagnose and explore memory-related issues.

The application occupies a certain amount of memory. It runs a HTTP server that you can 
send requests to change the amount of memory occupied.

```
$ curl http://<host>:8090/update/size=<size-in-MB>
```

It also runs a Prometheus JMX exporter on port 9404.

```
$ curl http://<host>:9404/metrics
```
