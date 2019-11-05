/******************************************************************************
 * pqueue.h
 *
 * Assorted routines for creating and managing priority queues useful for event
 * driven simulation. 
 *
 * John C. Gallagher
 * Department of Computer Science and Engineering
 * Wright State University
 * john.gallagher@wright.edu (Primary maintainer)
 *
*
 * Last Revised on 09/03/2017
 *
 * SPECIAL NOTES
 * -------------
 * This code is NOT written to be especially efficient.  It is rather designed
 * to be easy to understand.  You can undoubtedly implement many of the core
 * internal data structure better.  You are welcome to do so once you 
 * come to understand what's going on and how you'd even use priority 
 * queues to support event driven simulation.
 *****************************************************************************/

#ifndef PQUEUE_H
#define PQUEUE_H

/******************************************************************************
 * Forward declaration of the PQUEUE structs. The member variables of the
 * structs are private and should never be accessed directly.
 *****************************************************************************/

typedef struct pqueue_item_s pqueue_item_t;
typedef struct pqueue_s pqueue_t;


void   pqueue_init(pqueue_t *queue, char *queue_name);
void   pqueue_destroy(pqueue_t *queue);

void   pqueue_push(pqueue_t *queue, double enter_time, double exit_time, int identity_code, int state_code);
int    pqueue_pop(pqueue_t *queue, double *enter_time, double	*exit_time, int	*identity_code, int *state_code);

int    pqueue_empty(pqueue_t *queue);
int    pqueue_size(pqueue_t *queue);
int    pqueue_size_of_group(pqueue_t *queue, int group_code);
double pqueue_next_enter_time(pqueue_t *queue);
double pqueue_next_exit_time(pqueue_t *queue);
double pqueue_next_wait_time(pqueue_t *queue);
int    pqueue_next_item_id(pqueue_t *queue);
int    pqueue_next_item_group(pqueue_t *queue);

double pqueue_next_enter_time_of_group(pqueue_t *queue, int group_code);
double pqueue_next_exit_time_of_group(pqueue_t *queue, int group_code);
double pqueue_next_wait_time_of_group(pqueue_t *queue, int group_code);
double pqueue_next_item_id_of_group(pqueue_t *queue, int group_code);

double pqueue_average_wait_time(pqueue_t *queue);

void   pqueue_print(pqueue_t *queue, int full_flag);

#endif
