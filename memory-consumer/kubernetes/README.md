# Kubernetes
---

The Pod definition included here creates a pod with an init conainer which populates a 1Gi file in `/data/file.bin`.

The main container is our `memory-consumer` application.

Exampe usage

```
$ kubectl apply -f pod.yaml
$ kubectl exec -it memory-consumer -- bash
$ curl "localhost/readFile?path=/data/file.bin&amount=300"
$ curl "localhost/allocate?amount=200"
...
```

