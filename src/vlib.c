#include "vlib.h"

/**
* @brief reverses a string 'str' of length 'len'
* @author Chris Jerrett
* @date 9/9/2017
* @param str the string to reverse
* @param len the length
**/
void reverse(char *str, int len) {
    int i=0, j=len-1, temp;
    while (i<j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

<<<<<<< HEAD
int itoaa(int a, char *buffer, int digits) {
=======
/**
* @brief converts a int to string.
* @param a the integer
* @param buffer the string the int will be written to.
* @param digits the number of digits to be written
* @return the digits
* @author Chris Jerrett, Christian DeSimone
* @date 9/9/2017
**/
int itoa_bad(int a, char *buffer, int digits) {
>>>>>>> ded3f5b4ae2b95c32256269a5d5319f4c4e5d2e2
  int i = 0;
   while (a) {
       buffer[i++] = (a%10) + '0';
       a = a/10;
   }

   // If number of digits required is more, then
   // add 0s at the beginning
   while (i < digits)
       buffer[i++] = '0';

   reverse(buffer, i);
   buffer[i] = '\0';
   return i;
}

<<<<<<< HEAD
void ftoaa(float a, char *buffer, int precision) {
=======
/**
* @brief converts a float to string.
* @param a the float
* @param buffer the string the float will be written to.
* @param precision digits after the decimal to write
* @author Christian DeSimone
* @date 9/26/2017
**/
<<<<<<< HEAD
void ftoa(float a, char *buffer, int precision) {
=======
void ftoa_bad(float a, char *buffer, int precision) {
>>>>>>> ded3f5b4ae2b95c32256269a5d5319f4c4e5d2e2
>>>>>>> refs/remotes/origin/master
  // Extract integer part
  int ipart = (int)a;

  // Extract floating part
  float fpart = a - (float)ipart;

  // convert integer part to string
  int i = itoa_bad(ipart, buffer, 0);

  // check for display option after point
  if(precision != 0) {
    buffer[i] = '.';  // add dot

    // Get the value of fraction part up to given num.
    // of points after dot. The third parameter is needed
    // to handle cases like 233.007
    fpart = fpart * pow(10, precision);

    itoa_bad((int)fpart, buffer + i + 1, precision);
  }
}
