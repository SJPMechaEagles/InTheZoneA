#include "routines.h"
#include "controller.h"
#include "list.h"
#include "log.h"
#include "toggle.h"

static list_t *routine_list;

static TaskHandle routine_task_var;

/**
 * @brief Task that manages routines
 * @author Chris Jerrett
 */
void routine_task() {
  list_node_t *node;
  list_iterator_t *it = list_iterator_new(routine_list, LIST_HEAD);
  if (it != NULL) {
    while (node = list_iterator_next(it)) {
      if (node->val != NULL) {
        routine_t *routine = (routine_t *)(node->val);
        if (buttonIsNewPress(routine->on_button)) {
          TaskHandle task;
          task = taskCreate(routine->routine, TASK_DEFAULT_STACK_SIZE, &task,
                            TASK_PRIORITY_DEFAULT);
        }
      }
    }
  } else {
    error("List iterator was null");
  }
  list_iterator_destroy(it);
}

/**
 * @brief Starts the routine system
 * @author Chris Jerrett
 */
void init_routine() {
  routine_list = list_new();
  routine_task_var = taskRunLoop(routine_task, 20);
}

/**
 * @brief Stops the routine system
 * @author Chris Jerrett
 */
void deinit_routines() { list_destroy(routine_list); }

/**
 * @brief Registers a routine for the system to use
 * @param routine The routine to register
 * @param on_buttons the trigger button
 * @param prohibited_buttons the buttons it blocks @todo
 * @author Chris Jerrett
 */
void register_routine(void (*routine)(void *), button_t on_buttons,
                      button_t *prohibited_buttons) {
  struct routine_t *r = (struct routine_t *)malloc(sizeof(routine_t));
  r->blocked_buttons = prohibited_buttons;
  r->routine = routine;
  r->on_button = on_buttons;
  list_node_t *node = list_node_new(r);
  node->val = r;
  list_rpush(routine_list, node);
}
