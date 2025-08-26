
#ifndef __SLL_H__
#define __SLL_H__

// Define node structure
struct node {
    void *data;
    struct node* next;
};


struct node* create_node(void *data);
void insert(struct node** head, void *data);
void free_list(struct node* head, void (*delete_handler)(void*));
void *find(struct node *head, int (*compare)(void*, void*), void *key);
struct node *delete(struct node *head, int (*compare)(void*,void*), void *key, void (*delete_handler)(void*));


#endif
