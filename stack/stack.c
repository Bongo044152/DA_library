#include <stdio.h>  //for NULL
#include <stdlib.h> // for malloc
#include <string.h> //for memset
#include "stack.h"

int init(stack_t *stackptr,int size) {
    if(stackptr == NULL) return STACK_FAIL;
    if(size > 0) {
        stackptr -> elements =(void**) malloc(size*sizeof(void*));//記得malloc的型態是void 不是int

        if(stackptr -> elements == NULL) return -1;//remember
        memset(stackptr -> elements,0,size*sizeof(void*));
        stackptr -> sp = -1;
        stackptr -> size = size;

        return STACK_OK;
    }
    return  STACK_FAIL;
}

int isfull(stack_t *stackptr) {
    if(stackptr == NULL) return STACK_FAIL;
    return (stackptr -> sp >= stackptr -> size - 1);
}

int push(stack_t *stackptr,void *val) {
    if(stackptr == NULL) return STACK_FULL;
    if(!isfull(stackptr)) {
        stackptr -> elements[++(stackptr -> sp)] = val;
        return STACK_OK;
    }
    return STACK_FAIL;
}

int isempty(stack_t* stackptr) {
    if(stackptr == NULL) return STACK_FAIL;
    return(stackptr -> sp < 0);
}

int pop1(stack_t* stackptr,void** retvalue) {
    if(stackptr == NULL) return STACK_EMPTY;
    if(!isempty(stackptr)) {
        *retvalue = stackptr -> elements[(stackptr -> sp)--];
        return STACK_OK;
    }
    return STACK_EMPTY;
}

void *pop2(stack_t* stackptr,int* status) {
    if(stackptr == NULL) return NULL;
    if(!isempty(stackptr)) {
        *status = 0;
        return stackptr -> elements[(stackptr -> sp)--];
    }
    return NULL;
}

int isexist(stack_t* stackptr,void* key,int (*compare)(void* key,void* node)){
    if(stackptr == NULL) return -1;
    for(int i=0;i<=stackptr ->sp;i++) {
        if(compare(key,stackptr -> elements[i])==0) return 0;
    }
    return -1;
}

void free_stack(stack_t *stackptr) {
    if(!stackptr) return STACK_FAIL;
    if(stackptr->elements != NULL) {
        free(stackptr -> elements);
        stackptr -> elements = NULL;
    }
    stackptr->size = 0;
    stackptr->sp = -1;
}