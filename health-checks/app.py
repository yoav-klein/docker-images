
import os
from flask import Flask, Response

app = Flask(__name__)


@app.get("/")
def version():
    return os.environ.get("VERSION", "")


@app.get("/health")
def health():
    if os.path.exists("/tmp/health"):
        return Response("OK\n", status=200)

    return Response("UNHEALTHY\n", status=500)


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)

