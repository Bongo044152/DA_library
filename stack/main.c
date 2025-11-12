#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// 比較函式（以字串為例）
int compareString(void *key, void *node) {
    return strcmp((char *)key, (char *)node);
}

int main() {
    stack_t stackA;
    int status;
    void *ret = NULL;

    if (init(&stackA, 5) == STACK_FAIL) {
        printf("Stack init failed\n");
        return -1;
    }
    printf("Stack initialized.\n");

    // push 測試
    char *data[] = {"apple", "banana", "cherry", "date", "elderberry", "overflow"};
    for (int i = 0; i < 6; i++) {
        int result = push(&stackA, data[i]);
        if (result == STACK_OK)
            printf("Pushed: %s\n", data[i]);
        else
            printf("Push failed (stack full): %s\n", data[i]);
    }

    // isexist 測試
    char key1[] = "banana";
    char key2[] = "grape";
    printf("Is '%s' exist? %s\n", key1,
           isexist(&stackA, key1, compareString) == 0 ? "Yes" : "No");
    printf("Is '%s' exist? %s\n", key2,
           isexist(&stackA, key2, compareString) == 0 ? "Yes" : "No");

    // pop1 測試
    while (!isempty(&stackA)) {
        if (pop1(&stackA, &ret) == STACK_OK)
            printf("Pop1 -> %s\n", (char *)ret);
        else
            printf("Pop1 failed (empty stack)\n");
    }

    // push 測試（填回一點）
    push(&stackA, "new_item_1");
    push(&stackA, "new_item_2");

    // pop2 測試
    void *popped = pop2(&stackA, &status);
    if (popped && status == 0)
        printf("Pop2 -> %s\n", (char *)popped);
    else
        printf("Pop2 failed.\n");

    // 最後檢查是否為空
    printf("Stack empty? %s\n", isempty(&stackA) ? "Yes" : "No");


    if (stackA.elements != NULL) {
        free(stackA.elements);
        stackA.elements = NULL;
    }

    printf("Stack memory freed.\n");
    return 0;
}
