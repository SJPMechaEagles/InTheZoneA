#include "list.h"
#include <API.h>

/**
 * Allocates a new node
 * @param val The value the node contains.
 * @return The newly allocated node.
 * @author Chris Jerrett
 * @date 1/3/18
 * Node must be freed
 */
list_node_t *list_node_new(void *val) {
  list_node_t *self;
  if (!(self = (list_node_t *)malloc(sizeof(list_node_t))))
    return NULL;
  self->prev = NULL;
  self->next = NULL;
  self->val = val;
  return self;
}
