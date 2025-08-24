

enum Method {
    GET,
    POST,
    PUT,
    HEAD
};

struct http_header {
    char* key;
    char* value;
};

struct http_headers {
    struct http_header **header_list;
};


struct http_request {
    enum Method method;
    char* path;
    char* protocol;
    struct http_headers headers;
    char* body;
};
