#ifndef d_list
#define d_list

#define insert_front 1
#define insert_tail 2

struct dnode {
    int data;
    struct dnode *next;
    struct dnode *prev;
};

typedef struct dnode d_link;


void insert(d_link *prevnode, d_link **head, int link_status, int x);
d_link *removenode(d_link **head, d_link *target);

#endif