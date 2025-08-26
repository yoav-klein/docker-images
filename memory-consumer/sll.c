#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "sll.h"

// Function to create a new node
struct node* create_node(void *data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) {
        printf("Memory allocation error\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Insert a node at the beginning
void insert(struct node** head, void *data) {
    struct node* new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Free the list
void free_list(struct node* head, void (*delete_handler)(void*)) {
    struct node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        if(delete_handler) delete_handler(temp->data);
        free(temp);
    }
}

void *find(struct node *head, int (*compare)(void*, void*), void *key) {
    while(head != NULL) {
        if(0 == compare(head->data, key)) return head->data;
        head = head->next;
    }

    return NULL;
}

struct node *delete(struct node *head, int (*compare)(void*,void*), void *key, void (*delete_handler)(void*)) {
    struct node *origin = head;
    struct node *last = NULL;
    while(head) {
        if(0 == compare(head->data, key)) {
            struct node *tmp = head;
            head = head->next;
            if(last == NULL) { // first node 
                origin = head;
            } else { // middle node
                last->next = head;
            }
            // free node
            if(delete_handler) delete_handler(tmp->data);
            free(tmp);
        } else {
            last = head;
            head = head->next;
        }
    }

    return origin;
}




