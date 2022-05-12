#ifndef QUEUE_H_
#define QUEUE_H_
#define QUEUE_DATA_TYPE int

void enque(QUEUE_DATA_TYPE value);
QUEUE_DATA_TYPE deque(void);
QUEUE_DATA_TYPE first(void);
int is_empty(void);
int is_full(void);
#endif