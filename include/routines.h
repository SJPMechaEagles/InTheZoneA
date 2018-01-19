/**
 * @brief Routine system that allows mapping buttons to actions.
 * @author Chris Jerrett
 * @date 1/8/17
 */
#include "controller.h"

/**
 * @brief Struct representing a routine
 */
typedef struct routine_t {
	// the button it triggers on
	button_t on_button;
	// buttons it disables @todo
	button_t *blocked_buttons;

	// the routine to start the function on
	void (*routine)(void *);
} routine_t;

/**
 * @brief Starts the routine system
 */
void init_routine();

/**
 * @brief Tasks the manages tourines
 */
void routine_task();

/**
 * @brief Stops the routine systsem
 */
void deinit_routines();

/**
 * @brief Registers a routine for the system to use
 * @param routine The routine to register
 * @param on_buttons the trigger button
 * @param prohibited_buttons the buttons it blocks @todo
 */
void register_routine(void (*routine)(void *), button_t on_buttons,
                      button_t *prohibited_buttons);
