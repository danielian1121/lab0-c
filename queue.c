/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->count = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return;
    list_ele_t *temp = q->head;
    list_ele_t *readyFree;
    while (temp) {
        readyFree = temp;
        temp = temp->next;
        free(readyFree->value);
        free(readyFree);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /** If q is NULL, return false. */
    if (q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    /** If malloc failed, return false.  */
    if (newh == NULL)
        return false;

    char *s_copy = malloc(strlen(s) + 1);

    /** If malloc failed, return false. */
    if (s_copy == NULL) {
        free(newh);
        return false;
    }
    strcpy(s_copy, s);

    /** Set the new element. */
    newh->value = s_copy;
    newh->next = q->head;
    newh->prev = NULL;
    q->head = newh;

    /** If the new element is the first, set q->tail as q->head. */
    if (q->head->next == NULL)
        q->tail = q->head;
    else
        q->head->next->prev = q->head;

    /** Add count. */
    q->count++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /** If q is NULL, return false. */
    if (q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    /** If malloc failed, return false.  */
    if (newh == NULL)
        return false;

    char *s_copy = malloc(strlen(s) + 1);

    /** If malloc failed, return false. */
    if (s_copy == NULL) {
        free(newh);
        return false;
    }
    strcpy(s_copy, s);

    /** Set the new element. */
    newh->value = s_copy;
    newh->prev = q->tail;
    newh->next = NULL;
    q->tail = newh;


    /** If the new element is the first, set q->head as q->tail. */
    if (q->tail->prev == NULL)
        q->head = q->tail;
    else
        q->tail->prev->next = q->tail;

    /** Add count. */
    q->count++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /** If q is NULL or q->head is NULL, return false. */
    if (q == NULL || q->head == NULL)
        return false;

    /** If len > bufsize, use strncpy to copy.
     * Otherwise, use strcpy.
     */
    if (sp != NULL) {
        size_t len = strlen(q->head->value);
        if (len > bufsize - 1) {
            strncpy(sp, q->head->value, bufsize - 1);
            sp[bufsize - 1] = '\0';
        } else {
            strcpy(sp, q->head->value);
        }
    }

    /** Check the element is the last or not. */
    if (q->head == q->tail)
        q->tail = NULL;

    /** Delete the head element. */
    list_ele_t *temp;
    temp = q->head;
    q->head = q->head->next;
    if (q->head != NULL)
        q->head->prev = NULL;

    /** Free the head element. */
    free(temp->value);
    free(temp);

    /** Subtract count. */
    q->count--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->count : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->head == NULL)
        return;
    list_ele_t *temp = q->head;
    list_ele_t *swap;
    /** Swap next and prev in every element from head to tail. */
    while (temp) {
        swap = temp->next;
        temp->next = temp->prev;
        temp->prev = swap;
        temp = swap;
    }
    /* swap head and tail */
    swap = q->head;
    q->head = q->tail;
    q->tail = swap;
}
