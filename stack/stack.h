#ifndef STACK_H_
#define STACK_H_
#define STACK_DATA_TYPE int
void push(STACK_DATA_TYPE value);
STACK_DATA_TYPE pop(void);
STACK_DATA_TYPE top(void);
int is_empty(void);
int is_full(void);
#endif