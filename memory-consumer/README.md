# Memory Consumer
---

A memory-consuming application. This app consumes as much memory as you tell it to.


## Usage
---

Use the Makefile to build the app, build image, push image, run container, etc.


Allocate memory:
```
$ curl <url>/consume?amount=<amount-in-Mi>

# response
{
    "status": "OK",
    "allocationId": "1"
}
```

Release memory:
```
$ curl <url>/release?allocationId=1
{
    "status": "OK"
}
```

Status:
```
$ curl <url>/status
{
    "allocations": [
    {
        "allocationId": "3",
        "amountMi": 1000
    },
    {
        "allocationId": "4",
        "amountMi": 500
    }
    ]
}
```

Read from file:
```
$ curl <url>/readFile?path=<path>&amount=<amount-in-Mi>
{
    "status": "OK"
}

```
