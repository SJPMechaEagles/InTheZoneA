/**
* @file encoders.h
* @author Chris Jerrett
* @date 9/9/2017
* @brief wrapper around encer functions
**/

#ifndef _ENCODERS_H_
#define  _ENCODERS_H_

#include <API.h>

/**
* @brief The number of IMEs.
* This number is compared against the number detect in init_encoders
* @see init_encoders()
* @author Chris Jerrett
* @date 9/9/2017
* @see IME_NUMBER
**/
#define IME_NUMBER 0

/**
* @brief Initializes all motor encoders
* @author Chris Jerrett
* @date 9/9/2017
* @see IME_NUMBER
**/
bool init_encoders() {
  return imeInitializeAll() == IME_NUMBER;
}

#endif
