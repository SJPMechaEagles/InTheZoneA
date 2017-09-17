/**
* @file vlib.h
* @author Chris Jerrett
* @date 9/9/2017
* @brief Contains misc helpful functions.
**/

#ifndef _VLIB_H_
#define _VLIB_H_

#include <math.h>
#include <API.h>
#include <string.h>

/**
* @brief reverses a string 'str' of length 'len'
* @author Chris Jerrett
* @date 9/9/2017
* @param str the string to reverse
* @param len the length
**/
void reverse(char *str, int len);

/**
* @brief converts a int to string.
* @param a the integer
* @param buffer the string the int will be written to.
* @param digits the number of digits to be written
* @return the digits
* @author Chris Jerrett
* @date 9/9/2017
**/
int itoa(int a, char *buffer, int digits);

/**
* @brief converts a float to string.
* @param a the float
* @param buffer the string the float will be written to.
* @param precision digits after the decimal to write
**/
void ftoa(float a, char *buffer, int precision);

void *calloc_real(size_t elements, size_t size);

#endif
