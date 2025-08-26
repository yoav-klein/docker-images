#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include "sll.h"

// Function to create a new sll_node
struct sll_node* sll_create_node(void *data) {
    struct sll_node* new_node = (struct sll_node*)malloc(sizeof(struct sll_node));
    if (!new_node) {
        printf("Memory allocation error\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Insert a sll_node at the beginning
void sll_insert(struct sll_node** head, void *data) {
    struct sll_node* new_node = sll_create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// Free the list
void sll_free_list(struct sll_node* head, void (*delete_handler)(void*)) {
    struct sll_node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        if(delete_handler) delete_handler(temp->data);
        free(temp);
    }
}

void *sll_find(struct sll_node *head, int (*compare)(void*, void*), void *key) {
    while(head != NULL) {
        if(0 == compare(head->data, key)) return head->data;
        head = head->next;
    }

    return NULL;
}

struct sll_node *sll_delete(struct sll_node *head, int (*compare)(void*,void*), void *key, void (*delete_handler)(void*)) {
    struct sll_node *origin = head;
    struct sll_node *last = NULL;
    while(head) {
        if(0 == compare(head->data, key)) {
            struct sll_node *tmp = head;
            head = head->next;
            if(last == NULL) { // first sll_node 
                origin = head;
            } else { // middle sll_node
                last->next = head;
            }
            // free sll_node
            if(delete_handler) delete_handler(tmp->data);
            free(tmp);
        } else {
            last = head;
            head = head->next;
        }
    }

    return origin;
}




