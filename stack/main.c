#include <stdio.h>   // for printf
#include <stdlib.h>  // for exit, malloc
#include <string.h>  // for name string compare
#include "stack.h"

struct myDataNode {
    char name[10];
    int age;
};
typedef struct myDataNode myNode_t;

int compareName(void *node, void *key) {
    myNode_t *myNode = (myNode_t *)node;
    return strcmp(myNode->name, key);
}

int compareAge(void *node, void *key) {
    myNode_t *myNode = (myNode_t *)node;
    int *age = (int *)key;
    if (myNode->age == *age) return 0;
    return 1;
}

int main() {
    stack_t stackA;

    if (init(&stackA, 100) == STACK_FAIL) {
        printf("initial stack error\n");
        exit(1);
    }

    // --- push (第一次) ---
    for (int i = 1; i < 5; i++) {
        myNode_t *node = (myNode_t *)malloc(sizeof(myNode_t));
        sprintf(node->name, "robert_%d", i);
        node->age = 15 + i;

        if (push(&stackA, (void *)node) != STACK_OK) {
            printf("push error %d\n", i);
        }
        printf("push %d into stack\n", i);
    }

    // --- pop (使用 pop 介面) ---
    while (!isEmpty(&stackA)) {
        myNode_t *x;
        if (pop(&stackA, (void **)&x) != STACK_OK) {
            printf("pop error\n");
        } else {
            printf("pop %s from stack\n", x->name);
            free(x);
        }
    }

    // --- push (第二次，為了示範 pop2) ---
    for (int i = 1; i < 5; i++) {
        myNode_t *node = (myNode_t *)malloc(sizeof(myNode_t));
        sprintf(node->name, "robert_%d", i);
        node->age = 15 + i;

        if (push(&stackA, (void *)node) != STACK_OK) {
            printf("push error %d\n", i);
        }
        printf("push %d into stack\n", i);
    }

    // --- pop2 ---
    while (!isEmpty(&stackA)) {
        int errorCode;
        myNode_t *x = pop2(&stackA, &errorCode);

        if (errorCode != STACK_OK) {
            printf("pop error\n");
        } else {
            printf("pop %s from stack\n", x->name);
            free(x);
        }
    }

    // --- push (第三次，為了示範 isExist) ---
    for (int i = 1; i < 5; i++) {
        myNode_t *node = (myNode_t *)malloc(sizeof(myNode_t));
        sprintf(node->name, "robert_%d", i);
        node->age = 15 + i;

        if (push(&stackA, (void *)node) != STACK_OK) {
            printf("push error %d\n", i);
        }
        printf("push %d into stack\n", i);
    }

    // --- isExist 測試 ---
    printf("robert_1 in stack = %d, robert_100 in stack=%d \n",
           isExist(&stackA, (void *)"robert_1", compareName),
           isExist(&stackA, (void *)"robert_100", compareName));

    int age1 = 16, age2 = 100;
    printf("age 16 in stack = %d, age 100 in stack=%d \n",
           isExist(&stackA, (void *)&age1, compareAge),
           isExist(&stackA, (void *)&age2, compareAge));

    return 0;
}
