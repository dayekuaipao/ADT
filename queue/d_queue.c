#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <malloc.h>

static QUEUE_DATA_TYPE *queue;
static size_t queue_size;
#define ARRAY_SIZE (queue_size+1)
static size_t rear;
static size_t front;


void enque(QUEUE_DATA_TYPE value)
{
    if(is_empty())
    {
        queue_size = 1;
        queue = malloc(sizeof(QUEUE_DATA_TYPE)*ARRAY_SIZE);
    }
    else if(is_full())
    {
        queue_size *= 2;
        queue = realloc(queue,sizeof(QUEUE_DATA_TYPE)*ARRAY_SIZE);
    }
    assert(queue!=NULL);
    queue[rear]=value;
    rear = (rear+1)%ARRAY_SIZE;
}

QUEUE_DATA_TYPE deque(void)
{
    assert(!is_empty());
    QUEUE_DATA_TYPE value = queue[front];
    front = (front+1)%ARRAY_SIZE;
    if(is_empty())
    {
        assert(queue_size!=0);
        queue_size=0;
        front=0;
        rear=0;
        free(queue);
        queue=NULL;
    }
    return value;
}

QUEUE_DATA_TYPE first(void)
{
    assert(!is_empty());
    return queue[front];
}

int is_empty(void)
{
    return rear == front;
}

int is_full(void)
{
    return (rear+1)%ARRAY_SIZE == front;
}