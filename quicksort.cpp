/*
 * quicksort.cpp
 *
 *  Created on: 21.10.2013
 *      Author: pfannkuchen
 */

#include <pthread.h>
#include "quicksort.h"
#include "quickswap.h"


/*
int qckpart(int* array, int s, int e)
{
  int p = (e - s) / 2 + s;
  qckswap(&array[p], &array[e]);
  int *pval = &array[e];

  int si = s;
  for(int i = s; i <= e-1; i++)
  {
    if(array[i] <= *pval)
    {
      qckswap(&array[si], &array[i]);
      si++;
    }
  }
  qckswap(&array[si], &array[e]);
  return si;
}
*/
void qcksrt(int* array, int s, int e)
{

  if((e - s) <= 0) return;

  int p = (e - s) / 2 + s;
  qckswap(&array[p], &array[e]);
  int *pval = &array[e];

  int si = s;
  for(int i = s; i <= e-1; i++)
  {
    if(array[i] <= *pval)
    {
      qckswap(&array[si], &array[i]);
      si++;
    }
  }
  qckswap(&array[si], &array[e]);
  p = si;

  //int p = qckpart(array, s, e);

  qcksrt(array, s, p-1);
  qcksrt(array, p+1, e);
}

extern int threads;
extern int bucketsize;
static int thrc = 0;
void* qcksrt_th(void* info)
{
  qcksrt_info* qi = static_cast<qcksrt_info*>(info);
  int e = qi->e, s = qi->s;
  int* array = qi->array;
  if((e - s) <= 0) return 0;

  int p = (e - s) / 2 + s;
  qckswap(&array[p], &array[e]);
  int *pval = &array[e];

  int si = s;
  for(int i = s; i <= e-1; i++)
  {
    if(array[i] <= *pval)
    {
      qckswap(&array[si], &array[i]);
      si++;
    }
  }
  qckswap(&array[si], &array[e]);
  p = si;

  //int p = qckpart(array, s, e);

  qcksrt_info qit1, qit2;
  qit1.array = array;
  qit1.s = s;
  qit1.e = p-1;

  qit2.array = array;
  qit2.s = p+1;
  qit2.e = e;

  pthread_attr_t th1_attr, th2_attr;
  pthread_attr_init(&th1_attr);
  pthread_attr_init(&th2_attr);
  pthread_t th1, th2;
  int threaded = 0;
  if(thrc < threads && (qit1.e - qit1.s) >= bucketsize)
  {
    pthread_create(&th1, &th1_attr, qcksrt_th, &qit1);
    thrc++;
    threaded |= 1<<0;
  }
  else
  {
    qcksrt_th(&qit1);
  }

  if(thrc < threads && (qit2.e - qit2.s) >= bucketsize)
  {
    pthread_create(&th2, &th2_attr, qcksrt_th, &qit2);
    thrc++;
    threaded |= 1<<1;
  }
  else
  {
    qcksrt_th(&qit2);
  }

  void* grbg;
  if(threaded & (1<<0))
  {
    pthread_join(th1, &grbg);
    thrc--;
  }

  if(threaded & (1<<1))
  {
    pthread_join(th2, &grbg);
    thrc--;
  }
  pthread_attr_destroy(&th1_attr);
  pthread_attr_destroy(&th2_attr);
  return 0;
}
