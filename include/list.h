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

#ifndef LIST_H
#define LIST_H

#include <API.h>

/**
 * @brief list_t iterator direction.
 * Tells a iterator what direction to traverse the linked list in.
 * @author Chris Jerrett
 * @date 1/3/18
 */
typedef enum {
  /**
   * @brief start at head
   */
  LIST_HEAD
  /**
   *@brief start at tail
   */
  ,
  LIST_TAIL
} list_direction_t;

/**
 * @brief A node in a list
 * @author Chris Jerrett
 * @date 1/3/18
 */
typedef struct list_node {
  struct list_node *prev;
  struct list_node *next;
  void *val;
} list_node_t;

/**
 * @brief A struct representing a linked list.
 * @author Chris Jerrett
 * @date 1/3/18
 **/
typedef struct {
  // start of list
  list_node_t *head;
  // end of list
  list_node_t *tail;
  // length of list
  unsigned int len;

  // the value
  void (*free)(void *val);

  // a compare function
  int (*match)(void *a, void *b);
} list_t;

/**
 * @brief A iterator representation
 * Allows automatic iteration through linked list
 * @author Chris Jerrett
 * @date 1/3/18
 */

typedef struct {
  list_node_t *next;
  list_direction_t direction;
} list_iterator_t;

/**
 * Allocates a new node
 * @param val The value the node contains.
 * @return The newly allocated node.
 * @author Chris Jerrett
 * @date 1/3/18
 * Node must be freed
 */
list_node_t *list_node_new(void *val);

/**
 * @brief Allocated a new list
 * @return the new list
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_t *list_new();

/**
 * @brief Pushed a node to the end of a list
 * @param self the list
 * @param node the node
 * @return the node added
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_rpush(list_t *self, list_node_t *node);

/**
 * @brief Pushed a node to the start of a list
 * @param self the list
 * @param node the node
 * @return the node added
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_lpush(list_t *self, list_node_t *node);

/**
 * @brief Finds a node in a list with a given value
 * @param self the list
 * @param val the value
 * @return the node
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_find(list_t *self, void *val);

/**
 * @brief Finds a node a given index
 * @param self the list
 * @param index the index
 * @return the node
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_at(list_t *self, int index);

/**
 * @brief removes and returns the end node
 * @param self the list
 * @return the node removed
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_rpop(list_t *self);

/**
 * @brief removes and returns the start node
 * @param self the list
 * @return the node removed
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_node_t *list_lpop(list_t *self);

/**
 * @brief removes and returns the a given node from the list
 * @param self the list
 * @return the node removed
 * @author Chris Jerrett
 * @date 1/3/18
 **/
void list_remove(list_t *self, list_node_t *node);

/**
 * @brief Deallocates a list
 * @param self the list
 * @author Chris Jerrett
 * @date 1/3/18
 **/
void list_destroy(list_t *self);

/**
 * Creates a new iterator
 * @param list the list
 * @param direction direction the iterator should progress in
 * @return the iterator created
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_iterator_t *list_iterator_new(list_t *list, list_direction_t direction);

/**
 * Creates a new iterator by using the node to start at
 * @param node the start node
 * @param direction direction the iterator should progress in
 * @return the iterator created
 * @author Chris Jerrett
 * @date 1/3/18
 **/
list_iterator_t *list_iterator_new_from_node(list_node_t *node,
                                             list_direction_t direction);

/**
 * @brief The next node in the iterator and advances the iterator. Returns NULL
 *when done.
 * @param self the iterator
 * @return the next node.
 * @author Chris Jerrett
 * @date 1/3/17
 **/
list_node_t *list_iterator_next(list_iterator_t *self);

/**
 * @brief Destroys the iterator
 * @param self the iterator
 * @author Chris Jerrett
 * @date 1/3/17
 **/
void list_iterator_destroy(list_iterator_t *self);

#endif
