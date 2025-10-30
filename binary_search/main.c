#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bsearch.h"

int compareint(void* a,void* b) {
    return(*(int*)a - *(int*)b);
}

int comparechar(void* a,void *b){
    return(strcmp((char*) a,(char*)b));
}

int main(void) {
    int a = 10, b = 20, c = 30, d = 40;
    void *arr[] = { &a, &b, &c, &d };  // 已排序

    int key = 30;
    void *res = binarySearch(arr, 0, 3, &key, compareint);
    if (res) {
        printf("found: %d\n", *(int *)res);
    } else {
        printf("not found\n");
    }
}