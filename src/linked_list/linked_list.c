#include "linked_list.h"
#include <stdlib.h>

struct LinkedList*
ll_new(void)
{
    struct LinkedList* ll = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    if (ll == NULL) {
        return NULL;
    }

    ll->head = NULL;
    ll->tail = NULL;

    return ll;
}

int ll_add(struct LinkedList* ll, void *dataptr)
{
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->dataptr = dataptr;
    node->next = NULL;
    if (ll->head == NULL) {
        ll->head = node;
        ll->tail = node;
    } else {
        struct Node* prev_tail = ll->tail;
        ll->tail = node;
        prev_tail->next = node;
    }
}

int ll_remove(struct LinkedList* ll, void *dataptr)
{
    struct Node* node = ll->head;
    struct Node* prev_node = ll->head;
    while(node != NULL) {
        if (node->dataptr == dataptr) {
            struct Node* this_node = node;
            prev_node->next = this_node->next;
            if (this_node == ll->tail) {
                ll->tail = prev_node;
            }
            return 0;
        }
        prev_node = node;
        node = node->next;
    }
    return -1;
}

void* ll_get(struct LinkedList* ll, size_t index)
{
    struct Node* node = ll->head;
    size_t curr = 0;
    while(node != NULL) {
        if (curr == index) {
            return node->dataptr;
        }
        node = node->next;
        curr++;
    }
    return NULL;
}

void ll_destroy(struct LinkedList* ll)
{
    struct Node* node = ll->head;
    while(node != NULL) {
        struct Node* curr = node;
        node = node->next;
        free(curr);
    }
    free(ll);
}
