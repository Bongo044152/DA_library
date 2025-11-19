#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// 使用者提供的 alloc/free
void* user_alloc(int size) {
    return malloc(size);
}

void user_free(struct gnode* p) {
    free(p);
}

int main() {
    grp_t g;
    initQ(&g);

    insertQ(&g,2,user_alloc);
    insertQ(&g,3,user_alloc);
    insertQ(&g,1,user_alloc);
    insertQ(&g,3,user_alloc);

    while (1) {
        struct gnode ret = deleteQ(&g, user_free);
        printf("delete: %d, current_max: %d\n", ret.prior, g.current_max);

        if (ret.prior == -1) break;   
    }

    return 0;
}






    
