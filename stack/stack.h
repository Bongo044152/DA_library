#ifndef STACK_H
#define STACK_H

#define STACK_OK 0
#define STACK_FAIL 0
#define STACK_EMPTY 0
#define STACK_FULL 0

#endif

struct stack {
    int *element;
    int size;
    int sp;
};
typedef struct stack stack;


int init(stack *,int size);
int push(stack *,int value);
int pop(stack *,int* retvalue);
int isexist(stack *,int value);
int isfull(stack *);
int isempty(stack *);