#include "list.h"
#include <API.h>
/**
 * Creates a new iterator
 * @param list the list
 * @param direction direction the iterator should progress in
 * @return the iterator created
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_iterator_t *list_iterator_new(list_t *list, list_direction_t direction) {
  list_node_t *node = direction == LIST_HEAD ? list->head : list->tail;
  return list_iterator_new_from_node(node, direction);
}

/**
 * Creates a new iterator by using the node to start at
 * @param node the start node
 * @param direction direction the iterator should progress in
 * @return the iterator created
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_iterator_t *list_iterator_new_from_node(list_node_t *node,
                                             list_direction_t direction) {
  list_iterator_t *self;
  if (!(self = (list_iterator_t *)malloc(sizeof(list_iterator_t))))
    return NULL;
  self->next = node;
  self->direction = direction;
  return self;
}

/**
 * @brief The next node in the iterator and advances the iterator. Returns NULL
 *when done.
 * @param self the iterator
 * @return the next node.
 * @author Chris Jerrett
 * @date 1/3/17
 **/
list_node_t *list_iterator_next(list_iterator_t *self) {
  list_node_t *curr = self->next;
  if (curr) {
    self->next = self->direction == LIST_HEAD ? curr->next : curr->prev;
  }
  return curr;
}

/**
 * @brief Destroys the iterator
 * @param self the iterator
 * @author Chris Jerrett
 * @date 1/3/17
 **/
void list_iterator_destroy(list_iterator_t *self) {
  free(self);
  self = NULL;
}
