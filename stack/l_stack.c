#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>

typedef struct STACK_NODE{
    STACK_DATA_TYPE value;
    struct STACK_NODE* next;
}StackNode;

static StackNode* top_element;

void push(STACK_DATA_TYPE value)
{
    StackNode* new = malloc(sizeof(StackNode));
    assert(new!=NULL);
    new->value = value;
    new->next = top_element;
    top_element = new;
}

STACK_DATA_TYPE pop(void)
{
    assert(!is_empty());
    StackNode* first = top_element;
    STACK_DATA_TYPE value = first->value;
    top_element = first->next;
    free(first);
    first = NULL;
    return value;
}

STACK_DATA_TYPE top(void)
{
    assert(!is_empty());
    return top_element->value;
}

int is_empty(void)
{
    return top_element==NULL;
}

int is_full()
{
    return 0;
}