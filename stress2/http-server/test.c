
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <string.h> /* strtok */
#include "utils.h"



int main() {
    char header[80] = "Length: 23\r\nType: bag\r\n\r\nBBodyyyyy";
    
    char** arr = split(header, "\r\n\r\n");
    char** tmp = arr;
    while(*tmp) {
        printf("=====\n");
        printf("%s\n", *tmp);
        ++tmp;
    }

    free_string_array(arr);

    return 0;
}

