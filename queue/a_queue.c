#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#define QUEUE_SIZE 100 
#define ARRAY_SIZE (QUEUE_SIZE+1)

static QUEUE_DATA_TYPE queue[QUEUE_SIZE+1];
static size_t front;
static size_t rear;

void enque(QUEUE_DATA_TYPE value)
{
    assert(!is_full());
    queue[rear]=value;
    rear = (rear+1)%ARRAY_SIZE;
}

QUEUE_DATA_TYPE deque(void)
{
    assert(!is_empty());
    QUEUE_DATA_TYPE value = queue[front];
    front = (front+1)%ARRAY_SIZE;
    return value;
}

QUEUE_DATA_TYPE first(void)
{
    assert(!is_empty());
    return queue[front];
}

int is_empty(void)
{
    return front==rear;
}

int is_full(void)
{
    return (rear+1)%ARRAY_SIZE==front;
}