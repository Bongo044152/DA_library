#include"graph.h"

int G[MAX_PRIORITY];//record the number status
int prev_nonempty[MAX_PRIORITY];

void initQ(grp_t *gptr){
    if(!gptr) return;
    gptr->size = MAX_PRIORITY;

    for(int i = 0;i < MAX_PRIORITY;i++) {
        prev_nonempty[i] = -1;
        gptr->mats[i].next = &(gptr->mats[i]);
        gptr->mats[i].prev = &(gptr->mats[i]);
        gptr->mats[i].prior = i;
        G[i] = 0;
    }
    gptr->current_max = -1;
}

void insertQ(grp_t *gptr,int pri,grp_alloc_func alloc) {
    if(pri < 0 || pri >= gptr->size) return;

    struct gnode* newnode = (struct gnode*)alloc(sizeof(struct gnode));
    if(!newnode) return;
    newnode->prior = pri;
    struct gnode *head = &gptr->mats[pri];

    if(G[pri] == 1) {
        newnode->next = head->next;
        head->next->prev = newnode;
        newnode->prev = head;
        head->next = newnode;
    }else {
        G[pri] = 1;

        head->next = newnode;
        head->prev = newnode;
        newnode->next = head;
        newnode->prev = head;

        gptr->current_max = -1;
        for(int i = 0; i < gptr->size; ++i) {
            if(G[i] == 1) {
                gptr->current_max = i;
                break;               
            }
        }
        for(int i = 0; i < gptr->size; ++i) {
            prev_nonempty[i] = -1;
            for(int j = i + 1; j < gptr->size; ++j) {
                if(G[j] == 1) {
                    prev_nonempty[i] = j;
                    break;
                }
            }
        }
    }
}



struct gnode deleteQ(grp_t *gptr,grp_delete_func delloc) {
    if(!gptr || gptr->current_max < 0) {
        struct gnode e = { .prior = -1, .next = 0, .prev = 0};
        return e;
    }
    int index = gptr->current_max;
    struct gnode *head = &gptr->mats[index];
    struct gnode *del  = head->prev;
    struct gnode ret = *del;

    del->prev->next = del->next;
    del->next->prev = del->prev;

    delloc(del);

    if(head->next == head){
        G[index] = 0;
        gptr->current_max = prev_nonempty[index];
    }

    return ret;
}
