#include <stdio.h>  //for NULL
#include <stdlib.h> // for malloc
#include <string.h> //for memset
#include "stack.h"

int init(stack *stackptr,int size) {
    if(stackptr == NULL) return STACK_FAIL;
    if(size > 0) {
        stackptr -> element = (int*)malloc(size*sizeof(int));
        
        if(stackptr -> element == NULL) return STACK_FAIL;

        memset(stackptr -> element,-1,size*sizeof(int));
        stackptr -> sp =-1;
        stackptr -> size = size;
        return STACK_OK;
    }
    return STACK_FAIL;
}

int isfull(stack *stackptr) {
    return((stackptr -> sp) >= (stackptr -> size -1));
}

int push(stack *stackptr,int value) {
    if(stackptr == NULL || stackptr -> element == NULL) return STACK_FAIL;
    if(!isfull(stackptr)) {
        stackptr -> element[++stackptr -> sp] = value;
        return STACK_OK;
    }
    return STACK_FULL;
}

int isempty(stack* stackptr) {
    return(stackptr -> sp < 0);
}

int pop(stack *stackptr,int *retvalue) {
    if(stackptr == NULL || stackptr -> element == NULL) return STACK_FAIL;
    if(!isempty(stackptr)) {
        *retvalue = stackptr -> element[stackptr -> sp--];
        return STACK_OK;
    }
    return STACK_EMPTY;
}

int isexist(stack *stackptr, int value) {
    for(int i=0; i<=stackptr -> sp ; i++) {
        if(stackptr -> element[i] == value) return STACK_OK;
    }
    return STACK_FAIL;
}