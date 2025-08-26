#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy */
#include "http-server.h"

#define MAX_ALLOCATIONS

/* structs */
struct thread_data {
    int *data;
    pthread_mutex_t *mutex;
    pthread_cond_t *cond;
    struct http_server* server;
};

struct allocation {
    void *location;
    int id;
}

/* globals */
struct http_request *g_request;
static int gid = 0;
struct allocation allocations[MAX_ALLOCATIONS] = { 0 };

/* functions */
void protect(int code, const char *msg) {
    if(code != 0) {
        perror(msg);
    }
}


void *http_server(void *args) {
    struct thread_data package = *((struct thread_data*)args);

    pthread_mutex_t *mutex = package.mutex;
    pthread_cond_t *cond = package.cond;
    int *data = package.data;
    struct http_server server = *(package.server);
    
    while(1) {
        pthread_mutex_lock(mutex);
        while(*data != 0) {
            printf("HTTTP_SERVER: Waiting for data to be consumed\n"); fflush(stdout);
            pthread_cond_wait(cond, mutex);
        }

        printf("HTTP_SERVER: Waiting for a request\n");
        struct http_request request = get_request(server);
        // put request in buffer
        g_request = &request;

        printf("HTTP_SERVER: Got request\n");
        
        *data = 1;
        pthread_cond_signal(cond);
        pthread_mutex_unlock(mutex);

    } 
}

void handle_allocate(struct http_request *request, struct http_response *response) {
    response->status_code = OK;
    response->body = "{\"status\": \"OK\"}";
}

void handle_release(struct http_request *request, struct http_response *response) {
    response->status_code = OK;
    response->body = "{\"status\": \"OK\"}";
}

void handle_status(struct http_request *request, struct http_response *response) {
    response->status_code = OK;
    response->body = "{\"status\": \"OK\"}";
}

void handle_request() {
    struct http_request request = *g_request;
    struct http_response response;
    char content_length_string[20] = { 0 };
    
    /* protocol is always the same */
    response.protocol = malloc(sizeof(char*) + 1);
    strcpy(response.protocol, "HTTP/1.1");
    
    /* handler depends on path */
    if(0 == strcmp(request.path, "/allocate")) {
        handle_allocate(g_request ,&response);
    } else if(0 == strcmp(request.path, "/release")) {
        handle_release(g_request, &response);
    } else if(0 == strcmp(request.path, "/status")) {
        handle_status(g_request, &response);
    } else {
        response.status_code = NOT_FOUND;
        response.body = "Unknown path";
    }
    
    sprintf(content_length_string, "%lu", strlen(response.body));

    struct http_header **headers = malloc(sizeof(*headers) * 3);
    headers[0] = create_header("Content-Length", content_length_string);
    headers[1] = create_header("Content-Type", "text/plain");
    headers[2] = NULL;

    response.headers.header_list = headers;

    send_response(request.clientfd, response);

    free_http_response(response);
}

void handle_requests(struct thread_data package) {
    pthread_mutex_t *mutex = package.mutex;
    pthread_cond_t *cond = package.cond;
    int *data = package.data;
    
    while(1) {
        pthread_mutex_lock(mutex);
        while(*data != 1) {
            printf("HANDLER: Waiting for data to be written\n");
            pthread_cond_wait(cond, mutex);
        }

        printf("HANDLER: Ohh request, handling\n");
        
        handle_request(); 

        free_http_request(*g_request);

        *data = 0;
        pthread_cond_signal(cond);
        pthread_mutex_unlock(mutex);

    }
}

int main(int argc, char **argv) {
    struct http_server server; 
    if(argc > 2) {
        server = init_server(argv[1], atoi(argv[2]));
    } else if(argc > 1) {
        server = init_server(NULL, atoi(argv[1]));
    } else {
        printf("Usage: ./program [addr] <port>\n");
        exit(1);
    }

    srand(time(NULL));
    int data = 0;

    pthread_t thread_id;;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    struct thread_data package;

    package.data = &data;
    package.mutex = &mutex;
    package.cond = &cond;
    package.server = &server;

    protect(pthread_cond_init(&cond, NULL), "cond_init");
    protect(pthread_mutex_init(&mutex, NULL), "mutex_init");
    
    protect(pthread_create(&thread_id, NULL, http_server, &package), "pthread_create");
    
    
    handle_requests(package);

    pthread_join(thread_id, NULL);

    close_server(server);

    return 0;   
}
