#ifndef BSTREE_H_
#define BSTREE_H_
#define BSTREE_DATA_TYPE int
#include <stddef.h>
void insert(BSTREE_DATA_TYPE value);

int delete(BSTREE_DATA_TYPE value);

void* find(BSTREE_DATA_TYPE value);

void pre_order_traverse(void (*callback)(BSTREE_DATA_TYPE value));

void in_order_traverse(void (*callback)(BSTREE_DATA_TYPE value));

void post_order_traverse(void (*callback)(BSTREE_DATA_TYPE value));

void breath_first_traverse(void (*callback)(BSTREE_DATA_TYPE value));

#endif