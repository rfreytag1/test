/*
 * quickswap.cpp
 *
 *  Created on: 22.10.2013
 *      Author: pfannkuchen
 */
#include "quickswap.hpp"

void qckswap(int *a, int *b)
{
  if(*a == *b) return;
  asm("xor %1, %0;"
      "xor %0, %1;"
      "xor %1, %0;" : "=a" (*a), "=b" (*b) : "a" (*a), "b" (*b));
}

/*
void qckswap(int *a, int *b)
{
  if(*a == *b) return;
  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}*/


