import os
from flask import Flask, Response

app = Flask(__name__)

@app.route("/<var_name>", methods=["GET"])
def read_env(var_name):
    value = os.getenv(var_name)

    if value is None:
        return Response(
            f"Environment variable '{var_name}' not set\n",
            status=404,
            mimetype="text/plain"
        )

    return Response(f"{value}\n", mimetype="text/plain")


@app.route("/", methods=["GET"])
def root():
    return Response(
        "Usage: GET /<ENV_VAR_NAME>\nExample: /MY_ENV_VAR\n",
        mimetype="text/plain"
    )


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8080)

