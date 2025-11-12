#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int compareString(void *a, void *b) {
    return strcmp((char *)a, (char *)b);
}

int main() {
    queue_t q;
    void *ret = NULL;

    if (init(&q, 4) == QUEUE_FAIL) {
        printf("Queue init failed.\n");
        return -1;
    }
    printf("Queue initialized.\n");

    // enqueue 測試
    char *data[] = {"apple", "banana", "cherry", "date", "overflow"};
    for (int i = 0; i < 5; i++) {
        int result = enqueue(&q, data[i]);
        if (result == QUEUE_OK)
            printf("Enqueued: %s\n", data[i]);
        else
            printf("Enqueue failed (queue full): %s\n", data[i]);
    }

    // isexist 測試
    char key1[] = "banana";
    char key2[] = "grape";
    printf("Is '%s' exist? %s\n", key1, isexist(&q, key1, compareString) == 0 ? "Yes" : "No");
    printf("Is '%s' exist? %s\n", key2, isexist(&q, key2, compareString) == 0 ? "Yes" : "No");

    // dequeue 測試
    while (!isempty(&q)) {
        if (dequeue(&q, &ret) == QUEUE_OK)
            printf("Dequeued -> %s\n", (char *)ret);
        else
            printf("Dequeue failed (empty queue)\n");
    }

    // 再 enqueue 測試環回是否正常
    enqueue(&q, "x");
    enqueue(&q, "y");
    enqueue(&q, "z");
    printf("After wrap-around enqueue:\n");
    while (!isempty(&q)) {
        if (dequeue(&q, &ret) == QUEUE_OK)
            printf("Dequeued -> %s\n", (char *)ret);
    }

    // 🧹 使用 queue_free() 釋放記憶體
    queue_free(&q);
    printf("Queue memory freed.\n");

    return 0;
}
