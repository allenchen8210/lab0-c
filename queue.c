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
    queue_t *q = malloc(sizeof(*q));
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

    list_ele_t *newh = malloc(sizeof(*newh));

    if (!newh)
        return false;

    int s_len = strlen(s) + 1;
    // printf("string length excluding the terminating null byte = %d bits\n",
    // s_len-1);
    char *content = (char *) malloc(s_len * sizeof(char));

    if (!content) {
        free(newh);
        return false;
    }

    // printf("obtain %lu bits from malloc\n", strlen(content));
    strcpy(content, s);
    // printf("actually obtain %lu bits after use strcpy\n", strlen(content));

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

    list_ele_t *newt = malloc(sizeof(*newt));

    if (!newt)
        return false;
    int s_len = strlen(s) + 1;
    char *content = (char *) malloc((s_len * sizeof(char)));

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
    } else
        return false;

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

    list_ele_t *prev = NULL;
    list_ele_t *curr = q->head;
    list_ele_t *next;
    q->tail = q->head;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    q->head = prev;
    /* You need to write the code for this function */
}
