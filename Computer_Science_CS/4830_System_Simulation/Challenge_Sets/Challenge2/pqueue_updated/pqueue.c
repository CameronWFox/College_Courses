/******************************************************************************
 * pqueue.c
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
 *
 * The basic idea of the code is to give tools to allow the creation and use
 * of multiple priority queues.  The queues are intended to allow you to 
 * keep track of events in an event driven simulation.  Events can be entered
 * into a queue with ID information and entry and exit times.  When items
 * are removed, they are removed in chronological order of EXIT time.  The 
 * use of such structures was discussed in class.
 *
 * An individual queue will contain the following
 * information:
 *
 * Name of the Queue (Optional): A string up to 80 characters in length
 *
 * Number of Items in the Queue: An integer that records how many elements are
 *                               currently in the queue.
 *
 * List Head                   : Pointer to the first in a list of elements/
 *                               items currently in the queue.
 *
 *
 * Each list item that could be in a queue contain the following items:
 *
 * entry time:    A double that records the time that the event "started" in 
 *                the simulated world.
 *
 * exit time:     A double that records the that the the event "end" in the 
 *                simulated world.
 *
 * identity code: An integer that can serve as a unique identifier for the 
 *                specific event.  This would let you track a specific event
 *                as it enters and exits various status queues.  You could 
 *                treat the ID code as an index into a user maintained data
 *                structure that warehouses additional info about the identity
 *                of the agent in an event queue.
 *
 * state code:    An integer that can server as a unique identifier for the 
 *                "type" of event.  You an think of the identity code as an
 *                identifier for a specific thing (the code should be unique 
 *                in the simulation) and the state code as a "group" 
 *                identifier that can be used to bundle events into groups.
 *
 * Specific API routines are defined below and in the file pqueue.h.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>    
#include <float.h>
#include "pqueue.h"

/******************************************************************************
 * The following structs define the internal data storage templates for 
 * whole queues (pqueue_t) and individual even items (pqueue_item_t) 
 * which the queues store.  You should NEVER have to access any of the struct
 * fields directly.  Rather, use the API routines that are defined later.
 * If you need other kinds of access to the internals of these structs, it
 * is highly recommended that you update the library to give access through 
 * an API routine.  That way, if someone else rewrites this thing for efficiency,
 * you need not hunt through your user level code for references to struct 
 * fields that may no longer exist in the new implementation.
 *****************************************************************************/

#define PQUEUE_NUM_GROUPS	256


// This is the type definition for a single priority queue item
// Each queue will be implemented as a linked list of these
// items.  

typedef struct pqueue_item_s
   { double                enter_time;
     double                exit_time;
     int                   identity_code;
     int                   group_code;
     struct pqueue_item_s  *next_item;
   } pqueue_item_t;
typedef pqueue_item_t *pqueue_item_ptr;

// This is the queue type.  It contains a pointer to
// the first in the linked list of priority queue items along with
// a count of items currently in the queue and a string
// that contains the name of the queue.

typedef struct pqueue_s
  { pqueue_item_t  *head;
    int            item_count;
    int			   group_count[PQUEUE_NUM_GROUPS];
    char           queue_name[80];
  } pqueue_t;
typedef pqueue_t *pqueue_t_ptr;

/******************************************************************************
 *                        PUBLIC AND PRIVATE FUNCTIONS
 *
 * Following are is all the code for public (user callable) and private 
 * (called only internally to this source code segment).  The commenting here
 * gets a little sparse.  Private functions begin with '_'.  Public functions
 * begin with 'pqueue_'.  
 *****************************************************************************/


/******************************************************************************
 * NAME:  void pqueue_init(pqueue_t *queue, char *queue_name)
 *
 * DESCRIPTION: This routine is used to initialize a priority queue variable
 *              of <pqueue_t> to an empty and usable state.  You should use
 *              this routine THE FIRST time you intent to use a pqueue variable.
 *              You should NEVER call this twice on the same queue.  If you 
 *              want to flush an existing queue and return it to an empty state,
 *              use pqueue_destroy(), which returns all dynamically allocated
 *              memory to the system AND sets all internal queue fields to 
 *              what is needed to represent an empty queue with the default
 *              name.  The input parameters are as follows:
 *
 *              queue      : Pointer to a pqueue_t struct type
 *              queue_name : String pointer of up to 80 characters that 
 *                           contains a name to be associated with the queue.
 *                           If this value is NULL, the queue is assigned 
 *                           the default name of "NO NAME (Default)"
 *
 *              NOTE: When no longer needed, all pqueue_t structs should be
 *                    destroyed with a call to pqueue_destroy().  We 
 *                    wouldn't want to create memory leaks, would we?
 *
 * RETURN VALUE: The function returns no value.  Changes are made to the 
 *               pqueue_t struct via a pointer.
 *
 *****************************************************************************/

void pqueue_init(pqueue_t *queue, char *queue_name)
 { int i;
 
   queue->head       = NULL;
   queue->item_count = 0;
   for (i=0; i < PQUEUE_NUM_GROUPS; i++)
       queue->group_count[i] = 0;
   if (queue_name == NULL) 
      strncpy(queue->queue_name, "NO NAME (Default)", 80);
   else 
      strncpy(queue->queue_name, queue_name, 80);
 } // end pqueue_init()


/******************************************************************************
 * NAME:  pqueue_destroy(pqueue_t *queue)
 *
 * DESCRIPTION: This routine is used to flush out and deallocate all dynamically
 *              allocated memory associated with a pqueue_t struct.  This has
 *              the effect of completely flushing all records out of queue and
 *              setting the internal fields of the struct to represent an
 *              empty queue with no elements and the queue name
 *              "NO NAME (Default)". YOU SHOULD NEVER CALL THIS ON
 *              A pqueue_t struct THAT HAS NOT BEEN INITIALIZED BY 
 *              pqueue_init().  
 * 
 *              The input parameters are as follows:
 *
 *              queue      : Pointer to a pqueue_t struct type
 *
 *              NOTE: When no longer needed, all pqueue_t structs should be
 *                    destroyed with a call to pqueue_destroy().  We 
 *                    wouldn't want to create memory leaks, would we?
 *
 * RETURN VALUE: The function returns no value.  Changes are made to the 
 *               pqueue_t struct via a pointer.
 *
 *****************************************************************************/

void pqueue_destroy(pqueue_t *queue)
 { pqueue_item_t *head;
   pqueue_item_t *temp;
   head = queue->head;
   while (head != NULL)
      { temp = head;
        head = head->next_item;
        free(temp);
      }
   queue->head = NULL;
   pqueue_init(queue, NULL);
 } // end pqueue_destroy()
 

/******************************************************************************
 * NAME:  pqueue_push(pqueue_t *queue, double enter_time, double exit_time,
 *                    int identity_code, int group_code)
 *
 * DESCRIPTION: This routine is used add items to a priority queue.  IT SHOULD
 *              NOT BE USED ON A pqueue_t struct that had not been initialized
 *              by pqueue_init().  The input parameters are as follows:
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 *       
 *              enter_time   : A floating point value that represents the 
 *                             moment, measured by the simulation world clock,
 *                             that the event/item enters the queue.
 *
 *              exit_time    : A floating point value that represents the moment,
 *                             measured by the simulation world clock, that the
 *                             event item will/should EXIT the queue.  exit_time
 *                             MUST be greater than or equal to enter_time.  If
 *                             this condition is violated, the routine will end
 *                             the whole program with an error message.
 *             
 *             identity_code : An integer intended to be a unique tracking code
 *                             for a specific individual as it moves among queues.
 *                             See class notes and the header of this file for 
 *                             more information.
 *
 *             group_code    : An integer intended to be a code designating the
 *                             pushed event's membership in a "class or group".
 *                             See class notes and/or the header for this file
 *                             for more information.
 *
 *
 * RETURN VALUE: The function returns no value.  Changes are made to the 
 *               pqueue_t struct AND relevant internally curated dynamic 
 *               memory via a pointer to the pqueue_t struct.
 *
 * IMPLEMENTATION NOTE: In this implementation, the queue is maintained as 
 *                      a singly linked list.  New elements are insertion 
 *                      sorted into an existing list so that the list is 
 *                      maintained in order of ASCENDING EXIT TIMES.  We
 *                      do this so that items can be easily "popped" in 
 *                      priority order (events that finish earlier come out
 *                      earlier) by getting info from the list head and then
 *                      deleting it.  The code here is a little baroque 
 *                      because of special cases related to linking and 
 *                      unlinking to the pqueue_t struct head field rather than
 *                      to the next field of a generic content node.
 *                      Yes, this could have been MUCH more elegant.  Fix it
 *                      if you like.
 *
 *                      Also, in this implementation, an event push takes 
 *                      time proportional to the current number of items in 
 *                      the priority queue.  Pops occur in constant time, as 
 *                      the element needed for a pop is always at the head of 
 *                      the list.
 *
 *****************************************************************************/

void pqueue_push(pqueue_t 	*queue,
                 double 	enter_time,
                 double		exit_time,
                 int		identity_code,
                 int		group_code)

{ pqueue_item_t *previous;
  pqueue_item_t *current;
  pqueue_item_t *new;

  current = queue->head;
  
  if ((new = (pqueue_item_t *)malloc(sizeof(pqueue_item_t))) == NULL)
     { fprintf(stderr, "Malloc Failed in pqueue_push() -- Program Terminated\n");
       exit(1);
     }

  queue->item_count++;
  queue->group_count[group_code]++;
  new->enter_time    = enter_time;
  new->exit_time     = exit_time;
  new->identity_code = identity_code;
  new->group_code    = group_code;
    
  // Queue is empty, just add the item as the new first element
  // and return from the function

  if (current == NULL)
     { new->next_item     = NULL;
       queue->head        = new;
       return;
      } 

  // Queue has ONE item.  Handle this special case
  if ((current->next_item == NULL) || (current->exit_time >= exit_time))
     { if (current->exit_time < exit_time)
        { new->next_item     = NULL;
          current->next_item = new;
        }
       else
        { new->next_item = current;
          queue->head = new;
        };
       return;
     }

  // Queue has two or more items.  Handle general case

  while ((current != NULL) && (current->exit_time < exit_time))
     { previous = current;
       current  = current->next_item;
     }
  if (current == NULL)
     { if (previous->exit_time < exit_time)
        { new->next_item     = NULL;
          previous->next_item = new;
        }
       else
        { new->next_item       = current;
          previous->next_item  = new;
        };
       return;
     }
  previous->next_item = new;
  new->next_item      = current;
  return;
  
} // end pqueue_push()


/******************************************************************************
 * NAME:  pqueue_pop(pqueue_t *queue, double *enter_time, *double exit_time,
 *                    int *identity_code, int *group_code)
 *
 * DESCRIPTION: This routine is used to remove items from a priority queue.  
 *              IT SHOULD NOT BE USED ON A pqueue_t struct that had not been 
 *              initialized by pqueue_init().  The input parameters are as 
 *              follows:
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 *       
 *              enter_time   : Pointer to a floating point value.  The entry
 *                             time of the element that is popped will be placed
 *                             in the memory referenced by the pointer.
 *
 *              exit_time    : Pointer to a floating point value.  The exit
 *                             time of the element that is popped will be placed
 *                             in the memory referenced by the pointer.
 *             
 *             identity_code : Pointer to an integer value.  The identity code
 *                             of the element that is popped will be placed
 *                             in the memory referenced by the pointer.
 *
 *             group_code    : Pointer to an integer value.  The group code
 *                             of the element that is popped will be placed
 *                             in the memory referenced by the pointer.
 *
 *
 * RETURN VALUE: The function returns no value.  Changes are made to the 
 *               pqueue_t struct AND relevant internally curated dynamic 
 *               memory via a pointer to the pqueue_t struct.
 *
 * IMPLEMENTATION NOTE: In this implementation, the queue is maintained as 
 *                      a singly linked list.  New elements are insertion 
 *                      sorted into an existing list so that the list is 
 *                      maintained in order of ASCENDING EXIT TIMES.  We
 *                      do this so that items can be easily "popped" in 
 *                      priority order (events that finish earlier come out
 *                      earlier) by getting info from the list head and then
 *                      deleting it.  The code here is a little baroque 
 *                      because of special cases related to linking and 
 *                      unlinking to the pqueue_t struct head field rather than
 *                      to the next field of a generic content node.
 *                      Yes, this could have been MUCH more elegant.  Fix it
 *                      if you like.
 *
 *                      Also, in this implementation, an event push takes 
 *                      time proportional to the current number of items in 
 *                      the priority queue.  Pops occur in constant time, as 
 *                      the element needed for a pop is always at the head of 
 *                      the list.
 *
 *****************************************************************************/

int  pqueue_pop(pqueue_t 	*queue,
                double 	    *enter_time,
                double	    *exit_time,
                int		    *identity_code,
                int		    *group_code)

{ int pqueue_empty();
  pqueue_item_t *temp;

  if (pqueue_empty(queue)) return(0);  // If the queue is empty, return with failure code
                                       // otherwise retrieve info from the exiting record
                                       // and then remove it.
  
  *enter_time    = queue->head->enter_time;
  *exit_time     = queue->head->exit_time;
  *identity_code = queue->head->identity_code;
  *group_code    = queue->head->group_code;
  temp = queue->head;
  queue->head = queue->head->next_item;
  free(temp);
  queue->item_count--;
  queue->group_count[*group_code]--;
  return(1); // return with success code.
}

/******************************************************************************
 * NAME:  int pqueue_empty(pqueue_t *queue)
 *
 * DESCRIPTION: This routine returns the empty / not empty status of a pqueue 
 *              If empty, this routine returns 1.  If not empty, it returns 0.
 *              Input parameters are as follows:
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 *
 *****************************************************************************/
 
int pqueue_empty(pqueue_t *queue)
{ if ((queue->head == NULL) ||(queue->item_count == 0))
     return(1);
  else
     return(0);
} // end pqueue_empty()


/******************************************************************************
 * NAME:  int pqueue_size(pqueue_t *queue)
 *		  int pqueue_size_of_group(pqueue_t  *queue, int group_code)
 *
 * DESCRIPTION: This first routine returns an integer that is the number of 
 *              events items currently in the priority queue.  The second routine
 *              returns an integer that is the number of items currently in the
 *              pqueue_t that match the given group_code.  An out of range
 *              group code will trigger a program ending error.
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 *
 *              group_code   : Integer group code to be matched if the group
 *                             variant is called.
 *
 *****************************************************************************/

int pqueue_size(pqueue_t *queue)
{ if (queue == NULL) return(0); else return(queue->item_count);
}

int pqueue_size_group(pqueue_t *queue, int group_code)
{ if (queue == NULL) 
     return(0); 
  if (group_code < PQUEUE_NUM_GROUPS)
     return(queue->group_count[group_code]);
  fprintf(stderr, "Error in pqueue_size_group() - Invalid Group Code\n");
  exit(1);
}

/******************************************************************************
 * NAME:  double pqueue_next_enter_time(pqueue_t *queue)
 *        double pqueue_next_exit_time(pqueue_t *queue)
 *        double pqueue_next_wait_time(pqueue_t *queue)
 *		  double pqueue_next_item_id(pqueue_t *queue)
 *        double pqueue_next_item_group(pqueue_t *queue)
 *
 *        double pqueue_next_enter_time_of_group(pqueue_t *queue, int group_code)
 *        double pqueue_next_exit_time_of_group(pqueue_t *queue, int group_code)
 *        double pqueue_next_wait_time_of_group(pqueue_t *queue, int group_code)
 *		  double pqueue_next_item_id_of_group(pqueue_t *queue, int group_code)
 *        double pqueue_next_item_of_group_(pqueue_t *queue, int group_code)
 *
 * DESCRIPTION: These routines return the indicated value associated with the
 *              item in the pqueue with the with the SMALLEST exit time.  In 
 *              other words, the simulation clock time at which the "earliest 
 *              finishing" event in the queue will finish.
 *
 *              If the queue is empty, this routine will return the IEEE 
 *              floating point representation for INFINITY, as if there is
 *              no events to happen, one will wait infinity time for SOMETHING
 *              to happen.  Well, that and floating point infinity actually
 *              does the right thing for comparisons and such ;)
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 *
 *****************************************************************************/

double pqueue_next_enter_time(pqueue_t *queue)
{ if ((queue == NULL) || (queue->item_count == 0))
     return(INFINITY);
  else
     return queue->head->enter_time;
} // end pqueue_next_enter_time();

double pqueue_next_exit_time(pqueue_t *queue)
{ if ((queue == NULL) || (queue->item_count == 0))
     return(INFINITY);
  else
     return queue->head->exit_time;
} // end pqueue_next_exit_time();

double pqueue_next_wait_time(pqueue_t *queue)
{ if (pqueue_empty(queue)) 
     return(INFINITY);
  else 
     return (pqueue_next_exit_time(queue) - pqueue_next_enter_time(queue));
} // end pqueue_next_wait_time()

int pqueue_next_item_id(pqueue_t *queue)
{ if (pqueue_empty(queue))
     return(0);
  else 
     return(queue->head->identity_code);
} // end pqueue_next_item_id()

int pqueue_next_item_group(pqueue_t *queue)
{ if (pqueue_empty(queue))
     return(0);
  else 
     return(queue->head->group_code);
} // end pqueue_next_item_state()


pqueue_item_ptr _pqueue_find(pqueue_t *queue, int group_code)
{ pqueue_item_ptr current;
  pqueue_item_ptr previous;
  
  current = queue->head;
  
  while ((current != NULL) && (current->group_code != group_code))
     { previous = current;
       current  = previous->next_item;
     }

  return (current);
}

double pqueue_next_enter_time_of_group(pqueue_t *queue, int group_code)
{ pqueue_item_ptr item;
  if ((queue == NULL) || (queue->item_count == 0))
     return(INFINITY);
  item = _pqueue_find(queue, group_code);
  if (item == NULL) return INFINITY;
  return (item->enter_time);
}
  
double pqueue_next_exit_time_of_group(pqueue_t *queue, int group_code)
{ pqueue_item_ptr item;
  if ((queue == NULL) || (queue->item_count == 0))
     return(INFINITY);
  item = _pqueue_find(queue, group_code);
  if (item == NULL) return INFINITY;
  return (item->exit_time);
}     

double pqueue_next_wait_time_of_group(pqueue_t *queue, int group_code)
{ pqueue_item_ptr item;
  if ((queue == NULL) || (queue->item_count == 0))
     return(INFINITY);
  item = _pqueue_find(queue, group_code);
  if (item == NULL) return INFINITY;
  return (pqueue_next_exit_time_of_group(queue,group_code) - 
          pqueue_next_enter_time_of_group(queue, group_code));
}   

double pqueue_next_item_id_of_group(pqueue_t *queue, int group_code)
{ pqueue_item_ptr item;
  if ((queue == NULL) || (queue->item_count == 0))
     return(INFINITY);
  item = _pqueue_find(queue, group_code);
  if (item == NULL) return INFINITY;
  return (item->identity_code);
}   
 


/******************************************************************************
 * NAME:  double pqueue_average_wait_time(pqueue_t *queue)
 *
 * DESCRIPTION: This routine returns the AVERAGE WAIT TIME for all items in
 *              the referenced priority queue.  WAIT TIME is defined as an
 *              items exit time minus its entry time and defines "how long"
 *              the item will linger in the queue as measured against the
 *              simulation's world clock. 
 *
 *              If the queue is empty, this routine will return the IEEE 
 *              floating point representation for INFINITY, as if there is
 *              no events to happen, one will wait infinity time for SOMETHING
 *              to happen.  Well, that and floating point infinity actually
 *              does the right thing for comparisons and such ;)
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 *
 *****************************************************************************/

double pqueue_average_wait_time(pqueue_t *queue)
{ pqueue_item_t *head;
  double time_sum = 0.0;
  double count = 0.0;
  
  if (((head = queue->head)==NULL) || (queue->item_count == 0))
     return(INFINITY);
     
  while (head != NULL)
     { count += 1.0;
       time_sum += head->exit_time - head->enter_time;
       head = head->next_item;
     }
  return(time_sum/count);
} // end pqueue_average_wait_time();




/******************************************************************************
 * NAME:  void pqueue_print(pqueue_t *queue, int full) 
 *
 * DESCRIPTION: This routine prints out information about the referenced queue
 *              and, optionally, all the elements in the priority queue listed
 *              in order of ascending exit times (highest priority item on top).
 *              The input parameters are as follows:
 *
 *              queue        : Pointer to a pqueue_t struct to which the item
 *                             is to be added.
 * 
 *              full_flag    : If this integer is zero, the routine will print
 *                             only summary statistics about the queue.  If it
 *                             is non-zero, it will print summary statistics
 *                             and the whole queue (this could be lengthy).
 *
 *****************************************************************************/

void pqueue_print(pqueue_t *queue, int full_flag)
{ pqueue_item_t *head;
 
  head = queue->head;
  
  printf("\n---------------------------------------------------\n");
  printf("Queue Name               = %s\n",  queue->queue_name);
  printf("Queue Length             = %d\n",  queue->item_count);
  printf("Queue Average Wait Time  = %lf\n", pqueue_average_wait_time(queue));
  printf("\n");
  printf("Next Event Enter Time    = %lf\n", pqueue_next_enter_time(queue));
  printf("Next Event Exit Time     = %lf\n", pqueue_next_exit_time(queue));
  printf("Next Event Wait Time     = %lf\n", pqueue_next_wait_time(queue));

  printf("Next Event Item ID       = %d ",    pqueue_next_item_id(queue));
  if (pqueue_empty(queue))
     printf("(Empty Queue Default)\n");
  else  
     printf("\n");
  printf("Next Event State ID      = %d ",  pqueue_next_item_group(queue));
  if (pqueue_empty(queue))
     printf("(Empty Queue Default)\n");
  else  
     printf("\n");

  printf("---------------------------------------------------\n");
  if (queue->item_count == 0) return;

  if (full_flag)
     { printf("Exit      Enter     Expected    Item ID   Item\n");
       printf("Time      Time      Queue       Code      State\n");
       printf("                    Time                  Code\n");
       printf("---------------------------------------------------\n");
       while (head != NULL)
         { printf("%08.5lf  %08.5lf  %08.5lf    %06d    %03d\n",
                   head->exit_time, head->enter_time,
                   head->exit_time - head->enter_time,
                   head->identity_code,
                   head->group_code);
           head=head->next_item;
	     }
       printf("---------------------------------------------------\n");
     }   
} // end pqueue_print();

#define COMPILE_SAMPLE_CODE
#ifdef  COMPILE_SAMPLE_CODE
#define NUMBER_OF_LINES  25
#define PROCESS_TIME     (3.0 * 0.00027777777777)   // Three Seconds

int main()
{ int    input_identity_code = 0;
  double input_enter_time;
  double input_exit_time;
  int    input_group_code = 1;
  
  double queue_enter_time;
  double queue_exit_time;
  int    queue_identity_code;
  int    queue_group_code;
  
  int    full_debug = 0;
  int    i;
  
  double average_line_length;
  
  double time_mark = 0.0;
  
  
  pqueue_t master_queue;
  
  pqueue_init(&master_queue, "Master Queue");
  
    while (!feof(stdin))
       { fscanf(stdin,"%lf", &input_enter_time);
         
         while (pqueue_next_exit_time(&master_queue) < input_enter_time)
            pqueue_pop(&master_queue, &queue_enter_time, &queue_exit_time, &queue_identity_code, &queue_group_code);
            
         input_exit_time = input_enter_time + (PROCESS_TIME * (1.0 + (double)pqueue_size_group(&master_queue, input_group_code)));       
         pqueue_push(&master_queue, input_enter_time, input_exit_time, input_identity_code, input_group_code);
         input_identity_code++;
         input_group_code++;
         if (input_group_code > NUMBER_OF_LINES) 
            input_group_code = 1;
         
         average_line_length = 0.0;
         for (i=1; i <= NUMBER_OF_LINES; i++)
             average_line_length += (double)pqueue_size_group(&master_queue, i);
         average_line_length /= (double)NUMBER_OF_LINES; 
    
           if (input_enter_time > time_mark)
               { time_mark = input_enter_time;
                 printf("%lf %lf\n", input_enter_time, 60.0 * average_line_length * PROCESS_TIME);
               }
      }
       
    while (!pqueue_empty(&master_queue))
       { pqueue_pop(&master_queue, &queue_enter_time, &queue_exit_time, &queue_identity_code, &queue_group_code);
         average_line_length = 0.0;
         for (i=1; i <= NUMBER_OF_LINES; i++)
             average_line_length += (double)pqueue_size_group(&master_queue, i);
         average_line_length /= (double)NUMBER_OF_LINES; 
         if (queue_exit_time > time_mark)
             { time_mark = queue_exit_time;
               printf("%lf %lf\n", queue_exit_time, 60.0 * average_line_length * PROCESS_TIME);
             }
       }

}
#endif  
