/**
 * @file Wrapper around button toggle functionality.
 * @brief provides function for easier interaction with the VEX joystick
 * controllers
 *
 * @author Chris Jerrett
 **/

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "controller.h"
#include <API.h>

/**
 * @brief Initializes the buttons
 */
void buttonInit();

/**
 * @brief Detects if button is a new press from most recent check by comparing
 * previous value to current value.
 *
 * @param button
 *        The button to detect from the Buttons enumeration (see
 * include/buttons.h).
 *
 * @return true or false depending on if there was a change in button state.
 */
bool buttonIsNewPress(button_t);

/**
 * @brief Returns the current status of a button (pressed or not pressed)
 *
 * @param button
 *        The button to detect from the Buttons enumeration.
 *
 * @return true (pressed) or false (not pressed)
 */
bool buttonGetState(button_t);

#endif
