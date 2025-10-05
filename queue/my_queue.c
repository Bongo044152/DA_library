#include "my_queue.h"
#include <stdbool.h>
#include <stdlib.h>

bool init(queue_t *q, unsigned int capacity)
{
    if (!q)
        return false;

    q->size = 0;
    q->front = 0;
    q->capacity = 0;
    q->element = NULL;

    if (capacity == 0)
        return true;

    void **element = (void **) malloc(sizeof(void *) * capacity);
    if (!element) {
        return false;
    }
    q->element = element;
    q->capacity = capacity;
    return true;
}

bool enqueue(queue_t *q, void *data)
{
    if (!q || isFULL(q))
        return false;

    void **array = q->element;
    unsigned int idx = (q->front + q->size) % q->capacity;
    array[idx] = data;
    ++q->size;

    return true;
}

bool dequeue(queue_t *q, void **retValue)
{
    if (!q || isEmpty(q) || !retValue)
        return false;

    *retValue = q->element[q->front];
    q->front = (q->front + 1) % q->capacity;
    --q->size;
    return true;
}

bool isFULL(const queue_t *q)
{
    return q->size == q->capacity;
}
bool isEmpty(const queue_t *q)
{
    return q->size == 0;
}
bool isExist(queue_t *q, void *target, bool (*cmp)(void *, void *))
{
    for (unsigned int i = 0; i < q->size; ++i) {
        int idx = (q->front + i) % q->capacity;
        if (cmp(q->element[idx], target)) {
            return true;
        }
    }
    return false;
}

bool reserve(queue_t *q, unsigned int new_reserve_size)
{
    if (!q)
        return false;
    else if (new_reserve_size <= q->capacity)
        return true;

    void **element = (void **) malloc(sizeof(void *) * new_reserve_size);
    if (!element)
        return false;

    // move data
    for (unsigned int i = 0; i < q->size; ++i) {
        int idx = (q->front + i) % q->capacity;
        element[i] = q->element[idx];
    }

    free(q->element);
    q->element = element;
    q->capacity = new_reserve_size;
    q->front = 0;

    return true;
}
void my_queue_free(queue_t *q)
{
    free(q->element);
    q->size = 0;
    q->capacity = 0;
    q->front = 0;
    q->element = NULL;
}
