/*
 * binsearch.cpp
 *
 *  Created on: 22.10.2013
 *      Author: pfannkuchen
 */
#include "binsearch.hpp"

int binsearch(int* array, int s, int e, int needle)
{
  int h = (e - s) / 2 + s;

  if((e-s) == 0)
  {
    if(array[e] == needle) return e;
    else return -1;
  }

  int hval = array[h];

  if(hval == needle) return h;

  if(hval < needle) return binsearch(array, h+1, e, needle);
  if(hval > needle) return binsearch(array, s, h-1, needle);

  return -1;
}
