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

//當我看歐趴熊程式碼的時候 我的想法是insert有分三種 after front和 insert在中間
//我就有個想法 當我把使用者想要insert的狀態(link_status)用參數傳入
//然後我的insert函式 把狀態拿去判斷插入front after還是在中間
void insert(d_link *prevnode,d_link **head,int link_status,int val) { 
    d_link *node = newnode(val);
    if(!node) return;

    if(!*head) {
        *head = node;
        (*head)->next = node;
        (*head)->prev = node;
        return;
    }
    
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
        if((*head)->next == *head){
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
        //這裡的null的意思是 全部都找一圈 結果還是沒找到 回傳null
    }
    delete_(cur);
    cur->next = cur->prev = cur;//防誤用
    return cur;//因為要在主程式free 回傳給主程式是free就好了
}