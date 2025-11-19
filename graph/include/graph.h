#ifndef GRAPH_H
#define GRAPH_H

#define MAX_PRIORITY 4

struct gnode{
    int prior;
    struct gnode *next;
    struct gnode *prev;
};

struct grp{
    struct gnode mats[MAX_PRIORITY];
    int size;
    int current_max;
};

typedef struct grp grp_t;

typedef void *(*grp_alloc_func)(int);
typedef void  (*grp_delete_func)(struct gnode*);

void initQ(grp_t *);
void insertQ(grp_t*,int,grp_alloc_func alloc);
struct gnode deleteQ(grp_t*,grp_delete_func delloc);









#endif