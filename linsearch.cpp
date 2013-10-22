/*
 * linsearch.cpp
 *
 *  Created on: 22.10.2013
 *      Author: pfannkuchen
 */

#include "linsearch.hpp"

int linsearch(int* array, int s, int needle)
{
  for(int i = 0; i <= s; i++)
  {
    if(array[i] == needle)
      return i;
  }
  return -1;
}
