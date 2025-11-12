#ifndef stack_h
#define stack_h

#define STACK_OK        0
#define STACK_FULL      -1
#define STACK_EMPTY     -2
#define STACK_FAIL      -3

struct stack {
    void** elements;
    int sp;
    int size;
};

typedef struct stack stack_t;

int init(stack_t* ,int size);
int push(stack_t*,void*);
int isfull(stack_t*);
int isempty(stack_t*);
int isexist(stack_t*,void*,int compare(void*,void*));
int pop1(stack_t*,void**ret);
void* pop2(stack_t*,int*);
void free_stack(stack_t *);





#endif