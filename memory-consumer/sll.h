
#ifndef __SLL_H__
#define __SLL_H__

// Define sll_node structure
struct sll_node {
    void *data;
    struct sll_node* next;
};


struct sll_node* sll_create_node(void *data);
void sll_insert(struct sll_node** head, void *data);
void sll_free_list(struct sll_node* head, void (*delete_handler)(void*));
void *sll_find(struct sll_node *head, int (*compare)(void*, void*), void *key);
struct sll_node *sll_delete(struct sll_node *head, int (*compare)(void*,void*), void *key, void (*delete_handler)(void*));


#endif
