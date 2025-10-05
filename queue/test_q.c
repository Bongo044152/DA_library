#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "my_queue.h"

static void print_help(void) {
    printf(
        "可用指令：\n"
        "  help                       顯示本幫助\n"
        "  init <cap>                 以容量 cap 初始化 queue\n"
        "  enq|enqueue <int>          將整數值入隊\n"
        "  deq|dequeue                出隊一個元素並印出\n"
        "  isFull                     檢查是否已滿\n"
        "  isEmpty                    檢查是否為空\n"
        "  exist <int>                檢查是否存在該整數\n"
        "  reserve <new_cap>          重新配置容量（new_cap 必須 >= size）\n"
        "  free                       釋放 queue 內部緩衝區\n"
        "  quit                       結束程式\n"
    );
}

static bool int_equal(void *a, void *b) {
    if (!a || !b) return false;
    return *(int *)a == *(int *)b;
}

int main(void) {
    queue_t q = {0};
    char command[100];

    print_help();
    while (true) {
        if (scanf("%99s", command) != 1) {
            fprintf(stderr, "讀取指令失敗，結束。\n");
            break;
        }

        if (strcmp(command, "quit") == 0) {
            my_queue_free(&q);
            return 0;
        }
        else if (strcmp(command, "help") == 0) {
            print_help();
        }
        else if (strcmp(command, "init") == 0) {
            int cap;
            if (scanf("%d", &cap) != 1 || cap <= 0) {
                fprintf(stderr, "init 需要正整數容量。\n");
            } else {
                if (!init(&q, (unsigned int)cap)) {
                    fprintf(stderr, "init 失敗。\n");
                } else {
                    printf("初始化成功，容量 = %u\n", q.capacity);
                }
            }
        }
        else if (strcmp(command, "enq") == 0 || strcmp(command, "enqueue") == 0) {
            int *data = (int *)malloc(sizeof(int));
            if (!data) {
                fprintf(stderr, "記憶體配置失敗。\n");
            } else if (scanf("%d", data) != 1) {
                fprintf(stderr, "讀取整數失敗。\n");
                free(data);
            } else {
                if (!enqueue(&q, data)) {
                    fprintf(stdout, "enqueue failed!\n");
                    free(data);
                } else {
                    printf("enqueue 成功\n");
                }
            }
        }
        else if (strcmp(command, "deq") == 0 || strcmp(command, "dequeue") == 0) {
            int *data = NULL;
            if (!dequeue(&q, (void **)&data)) {
                fprintf(stdout, "dequeue failed!\n");
            } else {
                printf("取得的資料： %d\n", *data);
                free(data);
            }
        }
        else if (strcmp(command, "isFull") == 0) {
            printf(isFULL(&q) ? "True\n" : "False\n");
        }
        else if (strcmp(command, "isEmpty") == 0) {
            printf(isEmpty(&q) ? "True\n" : "False\n");
        }
        else if (strcmp(command, "exist") == 0) {
            int val;
            if (scanf("%d", &val) != 1) {
                fprintf(stderr, "讀取整數失敗。\n");
            } else {
                bool ok = isExist(&q, &val, int_equal);
                printf(ok ? "存在\n" : "不存在\n");
            }
        }
        else if (strcmp(command, "reserve") == 0) {
            unsigned int new_cap;
            if (scanf("%u", &new_cap) != 1) {
                fprintf(stderr, "reserve 需要正整數容量。\n");
            } else {
                if (!reserve(&q, new_cap)) {
                    printf("Fail!\n");
                } else {
                    printf("Succeeded!\n");
                }
            }
        }
        else if (strcmp(command, "free") == 0) {
            my_queue_free(&q);
            printf("free ~\n");
        }
        else {
            fprintf(stderr, "未知指令：%s（輸入 help 查看說明）\n", command);
        }

        memset(command, 0, sizeof(command));
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    my_queue_free(&q);
    return 0;
}

