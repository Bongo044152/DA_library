#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int init(queue_t *queueptr,int capacity) {
    if(capacity > 0) {
        queueptr -> elements = (void**) malloc(capacity*sizeof(void*));
        if(queueptr -> elements == NULL) return QUEUE_FAIL;

        queueptr -> front = 0;
        queueptr -> size = 0;
        queueptr -> capacity = capacity;
        return QUEUE_OK;
    }
    return QUEUE_FAIL;
}

int isfull(queue_t* queueptr) {
    return(queueptr -> size >= queueptr -> capacity);
}

int enqueue(queue_t* queueptr,void* val){
    if(queueptr == NULL) return QUEUE_FAIL;
    if(!isfull(queueptr)) {
        int rear = (queueptr -> front + queueptr -> size) % queueptr -> capacity;
        queueptr -> elements[rear] = val;
        (queueptr -> size)++;
        return QUEUE_OK;
    }
    return QUEUE_FULL;
}

int isempty(queue_t* queueptr) {
    return (queueptr -> size == 0);
}

int dequeue(queue_t* queueptr,void** retval) {
    if(queueptr == NULL) return QUEUE_FULL;
    if(!isempty(queueptr)) {
        *retval = queueptr -> elements[queueptr -> front];
        queueptr -> front = (queueptr -> front +1) %(queueptr -> capacity);//注意這一定要加 要環回
        queueptr -> size --;
        return QUEUE_OK;
    }
    return QUEUE_EMPTY;
}

int isexist(queue_t* queueptr,void *val,int(*compare)(void*,void*)) {
    for(int i = 0;i < queueptr ->size;i++) {
        int index = (queueptr -> front + i) % queueptr -> capacity;//注意這一定要加 要環回
        if(compare(val,queueptr -> elements[index]) == 0) 
            return 0;
    }
    return -1;
}