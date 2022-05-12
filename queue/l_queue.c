
#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <malloc.h>
typedef struct QUEUE_NODE{
    QUEUE_DATA_TYPE value;
    struct QUEUE_NODE* next;
}QueueNode;
static QueueNode* front;
static QueueNode** rear;
void enque(QUEUE_DATA_TYPE value)
{
    QueueNode* new = malloc(sizeof(QueueNode));
    assert(new!=NULL);
    if(front==NULL)
    {
        front = new;
        rear = &front; 
    }
    new->value = value;
    new->next = NULL;
    *rear = new;
    rear = &new->next;
}

QUEUE_DATA_TYPE deque(void)
{
    assert(!is_empty());
    QueueNode* first=front;
    QUEUE_DATA_TYPE value = first->value;
    front = front->next;
    free(first);
    first=NULL;
    return value;
}

QUEUE_DATA_TYPE first(void)
{
    assert(!is_empty());
    return front->value;
}

int is_empty(void)
{
    return front==NULL;
}

int is_full(void)
{
    return 0;
}