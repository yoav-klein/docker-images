#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Get the SIZE environment variable
    char *size_str = getenv("SIZE");
    if (size_str == NULL) {
        printf("Environment variable SIZE is not set.\n");
        return 1;
    }

    // Convert the SIZE variable to an integer (MB)
    int size_mb = atoi(size_str);
    if (size_mb <= 0) {
        printf("Invalid SIZE value: %s\n", size_str);
        return 1;
    }

    // Calculate the size in bytes
    size_t size = size_mb * 1024 * 1024;  // Convert MB to bytes

    // Allocate the specified amount of memory
    char *buffer = (char *)malloc(size);
    if (buffer == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Touch the memory to ensure it's actually allocated
    for (size_t i = 0; i < size; i++) {
        buffer[i] = 0;
    }

    printf("%d MB of memory allocated.\n", size_mb);

    // Sleep indefinitely
    while (1) {
        sleep(1);
    }

    // Free the memory (this line won't be reached due to the infinite loop)
    free(buffer);

    return 0;
}

