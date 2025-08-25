
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <string.h> /* strtok */
#include "utils.h"
#include "http-server.h"


void free_http_request_params(struct query_params params) {
    struct query_param **param_list_runner = params.param_list;
    
    printf("FREE\n");
    if(params.param_list == NULL) return;

    while(*param_list_runner) {
        struct query_param *current = *param_list_runner;
        free(current->key);
        free(current->value);
        free(current);
        ++param_list_runner;
    }

    free(params.param_list);
}



void parse_uri(struct http_request *request, char *uri) {
    char **param_str_list;
    char **params_runner;
    int num_params = 0, index = 0;
    char *uri_runner = uri;
    int length = 0;
    
    /* parse path*/
    while(*uri_runner && *uri_runner != '?') ++uri_runner;
    length = uri_runner - uri;
    request->path = malloc(length + 1);
    memcpy(request->path, uri, length);
    request->path[length] = '\0';

    /* if no query params, return */
    if(!*uri_runner) {
        printf("NO PARAMS\n"); fflush(stdout);
        return;
    }


    uri = ++uri_runner;
    param_str_list = split(uri, "&");
    params_runner = param_str_list;


    while(*params_runner) {
        ++num_params;
        ++params_runner;
    }

    params_runner = param_str_list;

    request->query_params.param_list = malloc(sizeof(struct query_param*) * (num_params + 1)); 
    
    /* handle each query param string */
    while(*params_runner) {
        char *curr = *params_runner;
        char **parts = split(curr, "=");

        request->query_params.param_list[index] = malloc(sizeof(struct query_param));
        request->query_params.param_list[index]->key = parts[0];
        request->query_params.param_list[index]->value = parts[1];
        ++params_runner;
        ++index;

        free_string_array_leave_strings(parts);
    }
    request->query_params.param_list[index] = NULL;

    free_string_array(param_str_list);
}

void test3() {
    struct http_request request = { 0 };

    parse_uri(&request, "/?name=yoav&tenant=abc");
//  parse_uri(&request, "/my/resource?name=yoav&age=38&profession=software");
    
    printf("Path: %s\n",request.path);
    struct query_param** param_list = request.query_params.param_list;
    if(param_list != NULL) {
        while(*param_list) {
            printf("%s\n", (*param_list)->key);
            printf("%s\n", (*param_list)->value);

            ++param_list;
        }
    }
    

    free_http_request_params(request.query_params);
}   



void parse_uri2(struct http_request *request, char *uri) {
    char **param_str_list = split(uri, "&");
    char **runner = param_str_list;
    int num_params = 0, index = 0;

    while(*runner) {
        ++num_params;
        ++runner;
    }

    runner = param_str_list;


    request->query_params.param_list = malloc(sizeof(struct query_param*) * (num_params + 1)); 
    
    /* handle each query param string */
    while(*runner) {
        char *curr = *runner;
        char **parts = split(curr, "=");

        request->query_params.param_list[index] = malloc(sizeof(struct query_param));
        request->query_params.param_list[index]->key = parts[0];
        request->query_params.param_list[index]->value = parts[1];
        ++runner;
        ++index;

        free_string_array_leave_strings(parts);
    }
    request->query_params.param_list[index] = NULL;

    free_string_array(param_str_list);
}

void using_split() {
    char *str = "name=yoav&age=38&profession=software";

    char **arr = split(str, "&");
    char **runner = arr;

    while(*runner) {
        char *curr = *runner;
        char **parts = split(curr, "=");
        printf("Key: %s\n", parts[0]);
        printf("Value: %s\n", parts[1]);
        ++runner;

        free_string_array(parts);
    }

    free_string_array(arr);
}


int main() {
    test3();
    return 0;
}

