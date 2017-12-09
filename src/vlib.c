#include "vlib.h"

void reverse(char *str, int len) {
    int i=0, j=len-1, temp;
    while (i<j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}

int itoaa(int a, char *buffer, int digits) {
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

void ftoaa(float a, char *buffer, int precision) {
  // Extract integer part
  int ipart = (int)a;

  // Extract floating part
  float fpart = a - (float)ipart;

  // convert integer part to string
  int i = itoa(ipart, buffer, 0);

  // check for display option after point
  if(precision != 0) {
    buffer[i] = '.';  // add dot

    // Get the value of fraction part up to given num.
    // of points after dot. The third parameter is needed
    // to handle cases like 233.007
    fpart = fpart * pow(10, precision);

    itoa((int)fpart, buffer + i + 1, precision);
  }
}

inline void *calloc_real(size_t elements, size_t size){
  void *mem = malloc(elements * size);
  memset(mem, 0, elements * size);
  return mem;
}
