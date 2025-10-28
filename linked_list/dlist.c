#include<stdio.h>
#include<stdlib.h>
#include"dlist.h"

static d_link* newnode(int x) {
    d_link *node = (d_link*) malloc(sizeof(d_link));
    if(!node) return NULL;
    else {
        node->next = NULL;
        node->prev = NULL;
        node->data = x;
    }
    return node;
}

static void insertnode(d_link *prevnode,d_link *node) {
    node->next = prevnode->next;
    prevnode->next->prev = node;
    node->prev = prevnode;
    prevnode->next = node;
}

void insert(d_link *prevnode,d_link **head,int link_status,int x) {
    d_link *node = newnode(x);
    if(!node) return;

    if(!*head) {
        *head = node;
        (*head)->next = node;
        (*head)->prev = node;
        return;
    }
    
    d_link *frontnode = *head;
    if(link_status == insert_front) {
        insertnode((*head)->prev,node);
        *head = node;
    } else if(link_status == insert_tail) {
        insertnode((*head)->prev,node);
        return;
    } else {
        if(!prevnode) prevnode = *head;
        insertnode(prevnode,node);
        return;
    }
}

static void delete_(d_link* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

d_link *removenode(d_link **head,d_link *target) {
    if(!*head||!target) return NULL;
    if(target == *head) {
        if(!(*head)->next){
            *head = NULL;
            delete_(target);
            target->next = target->prev = target;//自我閉環
            return NULL;
        } else {
            *head = target->next;
            delete_(target);
            target->next = target->prev = target;//自我閉環
            return NULL;
        }
    }

    d_link* cur = *head;

    while(cur != target) {
        cur = cur -> next;
        if(cur == (*head)) return NULL;
    }
    delete_(cur);
    cur->next = cur->prev = cur;//防誤用
    return cur;
}