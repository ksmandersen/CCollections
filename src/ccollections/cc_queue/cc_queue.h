#ifndef CC_QUEUE_H
#define CC_QUEUE_H

#include "../shared/cc.h"

struct cc_queue_struct;
typedef struct cc_queue_struct cc_queue;

/*! \brief Create a queue data structure
 * \return A new empty queue */
cc_queue *cc_queue_new();

/*! \brief Add an object to the queue
 * \param queue the queue
 * \param obj the object to add */
void cc_queue_enqueue(cc_queue *queue, cc_object *obj);

/*! \brief Remove the first object of the queue
 * \param queue the queue
 * \return the removed object */
cc_object *cc_queue_dequeue(cc_queue *queue);

/*! \brief Get the first item in the queue
 * \param queue the queue
 * \return the first object in the queue */
cc_object *cc_queue_peek(cc_queue *queue);

/*! \brief Count the number of objects in the queue
 * \param queue the queue
 * \return the number of objects in the queue */
int cc_queue_count(cc_queue *queue);

/*! \brief Remove all objects from the queue
 * \param queue the queue */
void cc_queue_clear(cc_queue *queue);

/*! \brief Returns wether or not an object is in the queue
 * \param queue the queue
 * \param obj the object to search for
 * \return true if the object exists in the queue, false otherwise */
bool cc_queue_contains(cc_queue *queue, cc_object *obj);

/*! \brief Gets an enumerator for the elements in the queue
 * \param queue the queue
 * \return an enumerator, going from the beginning to the end */
cc_enumerator *cc_queue_get_enumerator(cc_queue *queue);

/*! \brief Get the queue wrapped in a cc_object
 * \param queue the queue
 * \return the cc_object */
cc_object *cc_queue_to_object(cc_queue *queue);

/*! \brief Get the queue from a cc_object
 * \param object the object
 * \return the queue */
cc_queue *cc_queue_from_object(cc_object *object);

#endif