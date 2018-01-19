/**
 * @file list.h
 * A doubly linked list implementation.
 *
 * A linked list is a linear data structure where each element is a separate
 * object.
 *
 * Each element (we will call it a node) of a list is comprising of two items -
 * the data and a reference to the next node. The last node has a reference to
 * null. The entry point into a linked list is called the head of the list. It
 * should be noted that head is not a separate node, but the reference to the
 * first node. If the list is empty then the head is a null reference. A linked
 * list is a dynamic data structure. The number of nodes in a list is not fixed
 * and can grow and shrink on demand. Any application which has to deal with an
 * unknown number of objects will need to use a linked list.
 *
 * A Doubly Linked List is a variation of Linked list in which navigation is
 * possible in both ways, either forward and backward easily as compared to
 * Single Linked List.
 *
 * @author Chris Jerrett
 * @date 1/3/18
 */

#include "list.h"
#include <API.h>

/**
 * @brief Allocated a new list
 * @return the new list
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_t *list_new() {
  list_t *self;
  if (!(self = (list_t *)malloc(sizeof(list_t))))
    return NULL;
  self->head = NULL;
  self->tail = NULL;
  self->free = NULL;
  self->match = NULL;
  self->len = 0;
  return self;
}

/*
 * Free the list.
 */

void list_destroy(list_t *self) {
  unsigned int len = self->len;
  list_node_t *next;
  list_node_t *curr = self->head;

  while (len--) {
    next = curr->next;
    if (self->free)
      self->free(curr->val);
    free(curr);
    curr = next;
  }

  free(self);
}

/**
 * @brief Pushed a node to the end of a list
 * @param self the list
 * @param node the node
 * @return the node added
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_rpush(list_t *self, list_node_t *node) {
  if (!node)
    return NULL;

  if (self->len) {
    node->prev = self->tail;
    node->next = NULL;
    self->tail->next = node;
    self->tail = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

/**
 * @brief removes and returns the end node
 * @param self the list
 * @return the node removed
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_rpop(list_t *self) {
  if (!self->len)
    return NULL;

  list_node_t *node = self->tail;

  if (--self->len) {
    (self->tail = node->prev)->next = NULL;
  } else {
    self->tail = self->head = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/**
 * @brief removes and returns the start node
 * @param self the list
 * @return the node removed
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_lpop(list_t *self) {
  if (!self->len)
    return NULL;

  list_node_t *node = self->head;

  if (--self->len) {
    (self->head = node->next)->prev = NULL;
  } else {
    self->head = self->tail = NULL;
  }

  node->next = node->prev = NULL;
  return node;
}

/**
 * @brief Pushed a node to the start of a list
 * @param self the list
 * @param node the node
 * @return the node added
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_lpush(list_t *self, list_node_t *node) {
  if (!node)
    return NULL;

  if (self->len) {
    node->next = self->head;
    node->prev = NULL;
    self->head->prev = node;
    self->head = node;
  } else {
    self->head = self->tail = node;
    node->prev = node->next = NULL;
  }

  ++self->len;
  return node;
}

/**
 * @brief Finds a node in a list with a given value
 * @param self the list
 * @param val the value
 * @return the node
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_find(list_t *self, void *val) {
  list_iterator_t *it = list_iterator_new(self, LIST_HEAD);
  list_node_t *node;

  while ((node = list_iterator_next(it))) {
    if (self->match) {
      if (self->match(val, node->val)) {
        list_iterator_destroy(it);
        return node;
      }
    } else {
      if (val == node->val) {
        list_iterator_destroy(it);
        return node;
      }
    }
  }

  list_iterator_destroy(it);
  return NULL;
}

/**
 * @brief Finds a node a given index
 * @param self the list
 * @param index the index
 * @return the node
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_at(list_t *self, int index) {
  list_direction_t direction = LIST_HEAD;

  if (index < 0) {
    direction = LIST_TAIL;
    index = ~index;
  }

  if ((unsigned)index < self->len) {
    list_iterator_t *it = list_iterator_new(self, direction);
    list_node_t *node = list_iterator_next(it);
    while (index--)
      node = list_iterator_next(it);
    list_iterator_destroy(it);
    return node;
  }

  return NULL;
}

/**
 * @brief removes and returns the a given node from the list
 * @param self the list
 * @return the node removed
 * @author Chris Jerrett
 * @date 1/3/18
 **/
void list_remove(list_t *self, list_node_t *node) {
  node->prev ? (node->prev->next = node->next) : (self->head = node->next);

  node->next ? (node->next->prev = node->prev) : (self->tail = node->prev);

  if (self->free)
    self->free(node->val);

  free(node);
  --self->len;
}
