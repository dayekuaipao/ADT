#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
static STACK_DATA_TYPE *stack;
static size_t stack_size;
static int top_element=-1;

void push(STACK_DATA_TYPE value)
{
    if(is_empty())
    {
        stack_size = 1;
        stack = malloc(sizeof(STACK_DATA_TYPE)*stack_size);
    }
    else if(is_full())
    {
            stack_size *= 2;
            stack = realloc(stack, sizeof(STACK_DATA_TYPE)*stack_size);
    }
    assert(stack!=NULL);
    stack[++top_element] = value;
}

STACK_DATA_TYPE pop(void)
{
    assert(!is_empty());
    STACK_DATA_TYPE value = stack[top_element--];
    if(is_empty())
    {
        assert(stack_size!=0);
        stack_size = 0;
        free(stack);
        stack=NULL;
    }
    return value;
}

STACK_DATA_TYPE top(void)
{
    assert(!is_empty());
    return stack[top_element];
}

int is_empty(void)
{
    return top_element==-1;
}

int is_full(void)
{
    return top_element==stack_size-1;
}