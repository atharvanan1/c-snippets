#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stddef.h>

struct Node {
    void *dataptr;
    struct Node *next;
};

struct LinkedList {
    struct Node *head;
    struct Node *tail;
};

struct LinkedList* ll_new(void);
int ll_add(struct LinkedList* ll, void *dataptr);
int ll_remove(struct LinkedList* ll, void *dataptr);
void* ll_get(struct LinkedList* ll, size_t index);
void ll_destroy(struct LinkedList* ll);

#endif /* LINKED_LIST_H_ */