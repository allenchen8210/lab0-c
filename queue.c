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
    if (!q)
        return false;
    q->head = NULL;
    q->tail = NULL;
    q->qsize = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q) {
        if (!q->qsize)
            free(q);
        else {
            for (list_ele_t *curr = q->head; q->qsize > 0; q->qsize--) {
                list_ele_t *temp = curr;
                curr = curr->next;
                free(temp->value);
                free(temp);
            }
            free(q);
        }
    }
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
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
    if (!q || !s)
        return false;

    list_ele_t *newh = malloc(sizeof(list_ele_t));

    if (!newh)
        return false;

    char *content = malloc(sizeof(strlen(s) + 1));

    if (!content) {
        free(newh);
        return false;
    }
    strcpy(content, s);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!q->qsize) {
        q->head = newh;
        q->tail = newh;
        newh->next = NULL;
        newh->value = content;
    } else {
        newh->next = q->head;
        newh->value = content;
        q->head = newh;
    }

    q->qsize++;
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
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !s)
        return false;

    list_ele_t *newt = malloc(sizeof(list_ele_t));

    if (!newt)
        return false;

    char *content = malloc(sizeof(strlen(s) + 1));

    if (!content) {
        free(newt);
        return false;
    }

    content = strcpy(content, s);

    if (!q->head)
        q->head = newt;
    else
        q->tail->next = newt;

    q->tail = newt;
    newt->value = content;
    newt->next = NULL;
    q->qsize++;
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
    if (!q || !q->qsize)
        return false;
    /* You need to fix up this code. */

    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    list_ele_t *temp = q->head;
    if (q->qsize != 1)
        q->head = q->head->next;
    else {
        q->head = NULL;
        q->tail = NULL;
    }

    free(temp->value);
    free(temp);
    q->qsize--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (!q || !q->qsize)
        return 0;
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->qsize;
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
    if (!q || !q->qsize)
        return;

    q->tail = q->head;
    while (q->tail->next) {
        list_ele_t *temp = q->tail->next;
        q->tail->next = temp->next;
        temp->next = q->head;
        q->head = temp;
    }
    /* You need to write the code for this function */
}
