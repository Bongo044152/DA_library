#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"

#define insert_front 1
#define insert_tail  2

void printList(d_link *head) {
    if (!head) { puts("(empty)"); return; }
    d_link *p = head;
    do {
        printf("%d ", p->data);
        p = p->next;
    } while (p != head);
    puts("");
}

int main(void) {
    d_link *head = NULL;

    puts("=== Insert ===");
    insert(NULL, &head, insert_tail, 10);   // 建第一顆（你的 insert 要能處理空表）
    insert(head, &head, insert_tail, 20);
    insert(head, &head, insert_tail, 30);
    printList(head);  // 10 20 30

    puts("=== Insert Front ===");
    insert(head, &head, insert_front, 5);
    printList(head);  // 5 10 20 30

    puts("=== Remove Node (10) ===");
    d_link *target = head->next;            // 指向 10
    d_link *ret = removenode(&head, target);
    if (ret == target) free(ret);           // 只在回傳值就是被刪節點時 free
    printList(head);  // 5 20 30

    puts("=== Remove Head (5) ===");
    target = head;                          // 指向 5（head）
    ret = removenode(&head, target);
    free(ret);
    printList(head);  // 20 30

    puts("=== Done ===");
    return 0;
}
