#ifndef QUEUE_H
#define QUEUE_H

#define QUEUE_OK 0
#define QUEUE_FAIL -1
#define QUEUE_FULL -2
#define QUEUE_EMPTY -3

struct queue {
    int size;//等於stack的Sp
    int capacity;//等於stack的size
    int front;//要刪的數字 Rear等於下一個可以插入的點 = (front + size) % capacity 
    void **elements;
};

typedef struct queue queue_t;

int init(queue_t*,int);
int isfull(queue_t* queueptr);
int enqueue(queue_t* queueptr,void* val);
int isempty(queue_t* queueptr);
int dequeue(queue_t* queueptr,void** retval);
int isexist(queue_t* queueptr,void *val,int(*compare)(void*,void*));
void queue_free(queue_t* queueptr);


#endif