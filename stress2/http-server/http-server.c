
#include <stdio.h> /* printf */
#include <sys/types.h>   /* socket */
#include <sys/socket.h> /* socket */
#include <stdlib.h> /* exit */
#include <arpa/inet.h>  /* INADDR_ANY */
#include <string.h> /* memset */
#include <sys/epoll.h> /* epoll_create1 */
#include <unistd.h> /* close */

#include "http-server.h"
#include "utils.h"

#define LISTEN_BACKLOG (50)
#define BUFF_SIZE (500)


int create_socket() {
	int opt = 1; 
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("socket creation");
		exit(1);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, 
												&opt, sizeof(opt)))
	{
		perror("setsockopt"); 
		exit(EXIT_FAILURE);
	}
	
	return sockfd;
}

void bind_socket(int sockfd, int is_specified_addr, char* addr, int port)  {
	struct sockaddr_in servaddr;
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	if(is_specified_addr) {
		servaddr.sin_addr.s_addr = inet_addr(addr);
	}
	else {
		servaddr.sin_addr.s_addr = INADDR_ANY;
	}
	servaddr.sin_port = htons(port);
	
	if(-1 == bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
		perror("bind");
		exit(1);
	}
	printf("Bound to %s\n", inet_ntoa(servaddr.sin_addr));

}

void read_from_client(int cfd, char* buffer, size_t size) {
	size_t bytes_read = 0;

    while(bytes_read < size) {
        bytes_read = read(cfd, buffer, size);
    }

	bytes_read = read(cfd, buffer, BUFF_SIZE);
	if(-1 == bytes_read)
	{
		perror("read");
	}
	buffer[bytes_read] = 0;

    printf("===== RAW\n");
    printf("%s", buffer);
    printf("==== RAW\n");
}


char *read_head(int sock) {
    char *head = read_until(sock, "\r\n\r\n", 0);
    return head;
}

struct http_request parse_head(const char *head) {
    struct http_request ret = { 0 };
    char **head_lines = split(head, "\r\n");
    char *request_line = head_lines[0];
    struct http_header *headers[100];
    struct http_header *current_header;
    char **current_parts;
    char **header_lines = head_lines + 1;
    int index = 0, i = 0;

    /* parse request line */
    char** request_line_parts = split(request_line, " ");
    if(strcmp("GET", request_line_parts[0]) == 0) {
        ret.method = GET;
    }
    else if(strcmp("POST", request_line_parts[0]) == 0) {
        ret.method = POST;
    }
    else if(strcmp("PUT", request_line_parts[0]) == 0) {
        ret.method = PUT;
    } else {
        printf("UNKNOWN METHOD");
    }
    free(request_line_parts[0]);
    ret.path = request_line_parts[1];
    ret.protocol = request_line_parts[2];
    free_string_array_leave_strings(request_line_parts);
    
    /* parse headers */ 
    while(*header_lines) {
        current_header = (struct http_header*) malloc(sizeof(*current_header));
        current_parts = split(*header_lines, ": ");
        current_header->key = current_parts[0];
        current_header->value = current_parts[1];
        headers[index++] = current_header;
        
        free_string_array_leave_strings(current_parts);
        header_lines++;
    }
    
    free_string_array(head_lines);
    
    ret.headers.header_list = malloc(sizeof(struct http_header*) * index + 1 );
    for(i = 0; i < index; ++i) {
        ret.headers.header_list[i] = headers[i];
    }
    ret.headers.header_list[index] = NULL;

    return ret;
}

char *get_header_value(struct http_headers headers, const char *key) {
    struct http_header **runner = headers.header_list;
    
    while(*runner) {
        struct http_header *current = *runner;
        if(strcmp(current->key, key) == 0) {
            return current->value;
        }
    }

    return NULL;
}

void free_http_request(struct http_request request) {
    struct http_header *current = NULL;
    free(request.path);
    free(request.protocol);

    struct http_header **runner = request.headers.header_list;
    while(*runner) {
        current = *runner;
        free(current->key);
        free(current->value);
        free(current);
        ++runner;
    }
    free(request.headers.header_list);
}

void serve(int sockfd) {
    struct sockaddr_in cliaddr;
	socklen_t client_addr_size;	
	int cfd;
    char buffer[BUFF_SIZE] = { 0 };
    int i = 0;
    struct http_request request = { 0 };

	memset(&cliaddr, 0, sizeof(cliaddr));
	
	client_addr_size = sizeof(cliaddr);

    
	cfd = accept(sockfd, (struct sockaddr*)&cliaddr, &client_addr_size);
	if(-1 == cfd)
	{
		perror("accept");
		exit(1);
	}

    char *head = read_head(cfd);
    request = parse_head(head);

    printf("Value of Host: %s", get_header_value(request.headers, "Host"));

    free_http_request(request);
    free(head);

    fflush(stdout);
    close(cfd);
}


int main(int argc, char** argv) {
    printf("Hello\n");
    
    int sockfd = create_socket();
    
    if(argc > 2) {
        bind_socket(sockfd, 1, argv[1], atoi(argv[2] ));
    } else if(argc > 1) {
        bind_socket(sockfd, 0, NULL, atoi(argv[1]));
    } else {
        printf("Usage: ./program [addr] <port>\n");
        exit(1);
    }


    
    if(-1 == listen(sockfd, LISTEN_BACKLOG)) {
		perror("listen");
		exit(1);
	} 
    //while(1) {
        serve(sockfd);
    //}

    return 0;
}


