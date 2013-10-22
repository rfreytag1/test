/*
 * quicksort.h
 *
 *  Created on: 21.10.2013
 *      Author: pfannkuchen
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

void qcksrt(int *array, int s, int e);

struct qcksrt_info
{
  int* array;
  int s;
  int e;
};
void* qcksrt_th(void* info);


#endif /* QUICKSORT_H_ */
