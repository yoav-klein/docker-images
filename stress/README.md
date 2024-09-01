# Stress
---

A container that takes up a specific amount of memory.



Usage:

Environment variables:
* `SIZE` - mandatory - how much size in MB will the process allocate.
* `PERCENT` - optional - how much percent of the allocated space will be actaully used.

```
$ gcc -o stress stress.c
$ SIZE=10 PERCENT=10 ./stress 
```
