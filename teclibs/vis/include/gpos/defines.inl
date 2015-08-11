#include <assert.h>

void ResReverseIndex (int index, int ni, int nj, int nk, int* i, int* j, int* k)
{
  int ninj = ni*nj;
  ResReverseIndex(index, ni, nj, nk, ninj, i, j, k);
}

void ResReverseIndex (int index, int ni, int nj, int nk, int ninj, int* i, int* j, int* k)
{
  assert(0 <= index && index < ninj*nk);
  *k = index / ninj;
  *j = (index - (ninj * (*k))) / ni;
  *i = index % ni;
}

int ResReverseIndexI (int index, int ni)
{
  return index % ni;
}

int ResReverseIndexJ (int index, int ni, int nj)
{
  int ninj = ni*nj;
  int k = index / ninj;
  return (index - (ninj*k)) / ni;
}

int ResReverseIndexJ (int index, int ni, int nj, int ninj)
{
  int k = index / ninj;
  return (index - (ninj*k)) / ni;
}

int ResReverseIndexK (int index, int ni, int nj)
{
  return ResReverseIndexK(index, ni*nj);
}

int ResReverseIndexK (int index, int ninj)
{
  return index / ninj;
}
