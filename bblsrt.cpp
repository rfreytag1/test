/*
 * bblsrt.cpp
 *
 *  Created on: 22.10.2013
 *      Author: pfannkuchen
 */

#include "quickswap.h"
#include "bblsrt.h"

void bblsrt(int* array, int s)
{
  for(int i = 0; i < s-1; i++)
  {
    for(int j = i+1; j < s; j++)
    {
      if(array[i] > array[j]) qckswap(&array[i], &array[j]);
    }
  }
}
