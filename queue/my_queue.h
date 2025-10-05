#ifndef __MY_QUEUE_H__
#define __MY_QUEUE_H__

#include <stdbool.h>

struct queue {
    void **element;
    int front;
    unsigned int size;
    unsigned int capacity;
};
typedef struct queue queue_t;

// interface (operation of queue)


bool init(queue_t *, unsigned int);
bool enqueue(queue_t *, void *);
bool dequeue(queue_t *, void **);

bool isFULL(const queue_t *);
bool isEmpty(const queue_t *);
bool isExist(queue_t *, void *, bool (*)(void *, void *));

bool reserve(queue_t *, unsigned int);
void my_queue_free(queue_t *);

#endif
