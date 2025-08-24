

enum Method {
    GET,
    POST,
    PUT,
    HEAD
};

enum StatusCode {
    OK = 200,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    SERVER_ERROR = 500
};

char *status_code_to_string(enum StatusCode code) {
    switch(code) {
        case 200: return "OK"; break;
        case 401: return "Unauthorized"; break;
        case 403: return "Fobidden"; break;
        case 500: return "Internal server error"; break;
    }
}

struct http_header {
    char* key;
    char* value;
};

struct http_headers {
    struct http_header **header_list;
};


struct http_request {
    enum Method method;
    char *path;
    char *protocol;
    struct http_headers headers;
    char *body;
};

struct http_response {
    enum StatusCode status_code;
    char *protocol;
    struct http_headers headers;
    char *body;
};
