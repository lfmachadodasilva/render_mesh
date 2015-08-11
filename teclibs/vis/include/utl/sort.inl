#include "random.h"

#include <stdlib.h>

//-------------------------------------//
// Troca de lugar entre dois elementos //
//-------------------------------------//

SORTTEMPLATE void utlExchangeValues (TYPE* element1, TYPE* element2)
{
  TYPE temp = *element1;
  *element1 = *element2;
  *element2 = temp;
}

//------------------//
// RemoveDuplicates //
//------------------//

SORTTEMPLATE int utlRemoveDuplicates (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  int LastValidIndex = FirstIndex;
  for (int i = FirstIndex+1; i <= LastIndex; ++i)
  {
    if (CompareFunction(Sequence[i],Sequence[LastValidIndex])) // Diferentes
    {
      ++LastValidIndex;
      utlExchangeValues(&Sequence[i], &Sequence[LastValidIndex]);
    }
  }
  return LastValidIndex;
}

//---------//
// Minimum //
//---------//

SORTTEMPLATE int utlMin (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  int MinIndex = FirstIndex;
  for (int i = FirstIndex+1; i <= LastIndex; ++i)
  {
    if (CompareFunction(Sequence[i],Sequence[MinIndex]) < 0) MinIndex = i;
  }
  return MinIndex;
}

SORTTEMPLATE TYPE utlMin (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  return Sequence[utlMin(Sequence, 0, Size-1, CompareFunction)];
}

//---------//
// Maximum //
//---------//

SORTTEMPLATE int utlMax (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  int MaxIndex = FirstIndex;
  for (int i = FirstIndex+1; i <= LastIndex; ++i)
  {
    if (CompareFunction(Sequence[i],Sequence[MaxIndex]) > 0) MaxIndex = i;
  }
  return MaxIndex;
}

SORTTEMPLATE TYPE utlMax (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  return Sequence[utlMax(Sequence, 0, Size-1, CompareFunction)];
}

//---------------------//
// Minimum and Maximum //
//---------------------//

SORTTEMPLATE void utlMinMax (TYPE Sequence[], int FirstIndex, int LastIndex, int &MinIndex, int &MaxIndex, COMPARE_FUNCTION)
{
  if (FirstIndex > LastIndex) return;

  if ((LastIndex - FirstIndex + 1) % 2) // Número ímpar de elementos
  {
    MinIndex = MaxIndex = FirstIndex;
    ++FirstIndex;
  }
  else // Número par de elementos
  {
    if (CompareFunction(Sequence[FirstIndex],Sequence[FirstIndex+1]) < 0) {MinIndex = FirstIndex; MaxIndex = FirstIndex+1;}
    else {MaxIndex = FirstIndex; MinIndex = FirstIndex+1;}
    FirstIndex += 2;
  }

  for (int i = FirstIndex; i < LastIndex; i+=2)
  {
    if (CompareFunction(Sequence[i],Sequence[i+1]) < 0)
    {
      if (CompareFunction(Sequence[i  ],Sequence[MinIndex]) < 0) MinIndex = i;
      if (CompareFunction(Sequence[i+1],Sequence[MaxIndex]) > 0) MaxIndex = i+1;
    }
    else
    {
      if (CompareFunction(Sequence[i  ],Sequence[MaxIndex]) > 0) MaxIndex = i;
      if (CompareFunction(Sequence[i+1],Sequence[MinIndex]) < 0) MinIndex = i+1;
    }
  }
}

SORTTEMPLATE void utlMinMax (TYPE Sequence[], int Size, TYPE* Minimum, TYPE* Maximum, COMPARE_FUNCTION)
{
  int MinIndex, MaxIndex;
  utlMinMax(Sequence, 0, Size-1, MinIndex, MaxIndex, CompareFunction);
  (*Minimum) = Sequence[MinIndex];
  (*Maximum) = Sequence[MaxIndex];
}

//---------------//
// Binary search //
//---------------//

SORTTEMPLATE int utlBinarySearch (TYPE Sequence[], int FirstIndex, int LastIndex, TYPE Element, COMPARE_FUNCTION)
{
  if (FirstIndex > LastIndex) return -1;

  int MiddleIndex = (FirstIndex + LastIndex) / 2;

  int Comparison = CompareFunction(Sequence[MiddleIndex],Element);

  if (Comparison ==  1) return utlBinarySearch(Sequence, FirstIndex, MiddleIndex-1, Element, CompareFunction);
  if (Comparison == -1) return utlBinarySearch(Sequence, MiddleIndex+1, LastIndex,  Element, CompareFunction);
  return MiddleIndex;
}

SORTTEMPLATE int utlBinarySearch (TYPE Sequence[], int Size, TYPE Element, COMPARE_FUNCTION)
{
  return utlBinarySearch(Sequence, 0, Size-1, Element, CompareFunction);
}

//-------------//
// Select Sort //
//-------------//

SORTTEMPLATE void utlSelectSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  if (FirstIndex >= LastIndex) return;

  for (int i = FirstIndex; i < LastIndex; ++i)
  {
    int MinIndex = utlMin(Sequence, i, LastIndex, CompareFunction);
    utlExchangeValues(&Sequence[i], &Sequence[MinIndex]);
  }
}

SORTTEMPLATE void utlSelectSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlSelectSort(Sequence, 0, Size-1, CompareFunction);
}

//-------------//
// Insert Sort //
//-------------//

SORTTEMPLATE void utlInsert (TYPE Sequence[], int FirstIndex, int ElementIndex, COMPARE_FUNCTION)
{
  TYPE Temp = Sequence[ElementIndex];
  int j = ElementIndex - 1;
  while (j >= FirstIndex && CompareFunction(Sequence[j],Temp) > 0)
  {
    Sequence[j+1] = Sequence[j];
    --j;
  }
  Sequence[j+1] = Temp;
}

SORTTEMPLATE void utlInsertSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  if (FirstIndex >= LastIndex) return;

  for (int i = FirstIndex+1; i <= LastIndex; ++i)
  {
    utlInsert(Sequence,FirstIndex,i,CompareFunction);
  }
}

SORTTEMPLATE void utlInsertSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlInsertSort(Sequence, 0, Size-1, CompareFunction);
}

//-------------//
// Bubble Sort //
//-------------//

SORTTEMPLATE void utlBubbleSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  if (FirstIndex >= LastIndex) return;

  for (int i = FirstIndex; i < LastIndex; ++i)
  {
    bool flag = false;
    for (int j = LastIndex; j > i; --j)
    {
      if (CompareFunction(Sequence[j],Sequence[j-1]) < 0)
      {
        flag = true;
        utlExchangeValues(&Sequence[j], &Sequence[j-1]);
      }
    }
    if (!flag) return;
  }
}

SORTTEMPLATE void utlBubbleSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlBubbleSort(Sequence, 0, Size-1, CompareFunction);
}

//------------//
// Merge Sort //
//------------//

SORTTEMPLATE void utlMerge (TYPE SortArray[], TYPE SubArray1[], TYPE SubArray2[], int SubStart1, int SubLast1, int SubLast2, COMPARE_FUNCTION)
{
  int i,j;

  int Size1 = SubLast1 - SubStart1 + 1;
  int Size2 = SubLast2 - SubLast1;

  TYPE* SortArray1 = SortArray + SubStart1;
  TYPE* SortArray2 = SortArray + SubLast1 + 1;

  for (i = 0; i < Size1; ++i) SubArray1[i] = SortArray1[i];
  for (j = 0; j < Size2; ++j) SubArray2[j] = SortArray2[j];

  i=0;
  j=0;
  for (int index = SubStart1; index <= SubLast2; ++index)
  {
    if (j == Size2) SortArray[index] = SubArray1[i++];
    else if (i == Size1) SortArray[index] = SubArray2[j++];
    else if (CompareFunction(SubArray1[i],SubArray2[j]) <= 0) SortArray[index] = SubArray1[i++];
    else SortArray[index] = SubArray2[j++];
  }
}

SORTTEMPLATE void utlDoMergeSort (TYPE Sequence[], TYPE SubArray1[], TYPE SubArray2[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  if (FirstIndex >= LastIndex) return;

  int MiddleIndex = (FirstIndex + LastIndex) / 2;

  utlDoMergeSort(Sequence, SubArray1, SubArray2, FirstIndex, MiddleIndex, CompareFunction);
  utlDoMergeSort(Sequence, SubArray1, SubArray2, MiddleIndex+1, LastIndex, CompareFunction);
  utlMerge(Sequence, SubArray1, SubArray2, FirstIndex, MiddleIndex, LastIndex, CompareFunction);
}

SORTTEMPLATE void utlMergeSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  if (FirstIndex >= LastIndex) return;

  int SubSize = ((LastIndex - FirstIndex) / 2) + 1;
  TYPE *SubArray1 = new TYPE[SubSize];
  TYPE *SubArray2 = new TYPE[SubSize];

  utlDoMergeSort(Sequence, SubArray1, SubArray2, FirstIndex, LastIndex, CompareFunction);

  delete[] SubArray2;
  delete[] SubArray1;
}

SORTTEMPLATE void utlMergeSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlMergeSort(Sequence, 0, Size-1, CompareFunction);
}

//--------------------------------//
// Pivoteamento e particionamento //
//--------------------------------//

SORTTEMPLATE int utlLastPivot (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  return LastIndex;
}

SORTTEMPLATE int utlRandomPivot (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  return utlRandomInt(FirstIndex, LastIndex);
}

SORTTEMPLATE int utlMedianPivot (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  int Group, GroupStart, GroupEnd, MedianIndex;

  if (FirstIndex >= LastIndex) return FirstIndex;

  // Pega a mediana de cada conjunto de 5 elementos e coloca no começo do array

  for (Group = 0, GroupStart = FirstIndex; GroupStart < LastIndex; ++Group, GroupStart += 5)
  {
    GroupEnd = GroupStart+4;
    if (GroupEnd > LastIndex) GroupEnd = LastIndex;
    MedianIndex = (GroupStart + GroupEnd) / 2;

    utlInsertSort(Sequence, GroupStart, GroupEnd, CompareFunction);

    utlExchangeValues(&Sequence[FirstIndex+Group], &Sequence[MedianIndex]);
  }

  // Acha a mediana das medianas

  MedianIndex = utlSelect(Sequence, FirstIndex, FirstIndex+Group-1, Group/2, CompareFunction, utlMedianPivot<TYPE>);

  return MedianIndex;
}

SORTTEMPLATE int utlPartition (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION, PIVOT_FUNCTION)
{
  int PivotIndex = PivotFunction(Sequence, FirstIndex, LastIndex, CompareFunction);

  TYPE Pivot = Sequence[PivotIndex];
  Sequence[PivotIndex] = Sequence[LastIndex];
  Sequence[LastIndex] = Pivot;

  int i = FirstIndex - 1;
  for (int j = FirstIndex; j < LastIndex; ++j)
  {
    if (CompareFunction(Sequence[j],Pivot) <= 0)
    {
      utlExchangeValues(&Sequence[++i], &Sequence[j]);
    }
  }
  Sequence[LastIndex] = Sequence[++i];
  Sequence[i] = Pivot;
  return i;
}

SORTTEMPLATE int utlSimplePartition(TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  return utlPartition(Sequence, FirstIndex, LastIndex, CompareFunction, utlLastPivot<TYPE>);
}

SORTTEMPLATE int utlRandomPartition(TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  return utlPartition(Sequence, FirstIndex, LastIndex, CompareFunction, utlRandomPivot<TYPE>);
}

SORTTEMPLATE int utlMedianPartition(TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  return utlPartition(Sequence, FirstIndex, LastIndex, CompareFunction, utlMedianPivot<TYPE>);
}

//--------//
// Select //
//--------//

SORTTEMPLATE int utlSelect (TYPE Sequence[], int FirstIndex, int LastIndex, int ElementOrder, COMPARE_FUNCTION, PIVOT_FUNCTION)
{
  if (FirstIndex >= LastIndex) return FirstIndex;

  if (LastIndex - FirstIndex + 1 <= 5)
  {
    utlInsertSort(Sequence, FirstIndex, LastIndex, CompareFunction);
    return FirstIndex + ElementOrder - 1;
  }

  int PivotIndex = utlPartition(Sequence, FirstIndex, LastIndex, CompareFunction, PivotFunction);
  int PivotOrder = PivotIndex - FirstIndex + 1;

  if (ElementOrder == PivotOrder) return PivotIndex;
  if (ElementOrder < PivotOrder) return utlSelect(Sequence, FirstIndex, PivotIndex-1, ElementOrder, CompareFunction, PivotFunction);
  return utlSelect(Sequence, PivotIndex+1, LastIndex, ElementOrder-PivotOrder, CompareFunction, PivotFunction);
}

SORTTEMPLATE int utlSimpleSelect (TYPE Sequence[], int Size, int ElementOrder, COMPARE_FUNCTION)
{
  return utlSelect(Sequence, 0, Size-1, ElementOrder, CompareFunction, utlLastPivot<TYPE>);
}

SORTTEMPLATE int utlRandomSelect (TYPE Sequence[], int Size, int ElementOrder, COMPARE_FUNCTION)
{
  return utlSelect(Sequence, 0, Size-1, ElementOrder, CompareFunction, utlRandomPivot<TYPE>);
}

SORTTEMPLATE int utlMedianSelect (TYPE Sequence[], int Size, int ElementOrder, COMPARE_FUNCTION)
{
  return utlSelect(Sequence, 0, Size-1, ElementOrder, CompareFunction, utlMedianPivot<TYPE>);
}

//------------//
// Quick Sort //
//------------//

SORTTEMPLATE void utlQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION, PIVOT_FUNCTION)
{
  utlQuickSort(Sequence, 0, Size-1, CompareFunction, PivotFunction);
}

SORTTEMPLATE void utlQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION, PIVOT_FUNCTION)
{
  if (FirstIndex >= LastIndex) return;

  if (LastIndex - FirstIndex + 1 <= 5)
  {
    utlInsertSort(Sequence, FirstIndex, LastIndex, CompareFunction);
    return;
  }

  int MiddleIndex = utlPartition(Sequence, FirstIndex, LastIndex, CompareFunction, PivotFunction);
  utlQuickSort(Sequence, FirstIndex, MiddleIndex-1, CompareFunction, PivotFunction);
  utlQuickSort(Sequence, MiddleIndex+1, LastIndex, CompareFunction, PivotFunction);
}

SORTTEMPLATE void utlSimpleQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  utlQuickSort(Sequence, FirstIndex, LastIndex, CompareFunction, utlLastPivot<TYPE>);
}

SORTTEMPLATE void utlRandomQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  utlQuickSort(Sequence, FirstIndex, LastIndex, CompareFunction, utlRandomPivot<TYPE>);
}

SORTTEMPLATE void utlMedianQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION)
{
  utlQuickSort(Sequence, FirstIndex, LastIndex, CompareFunction, utlMedianPivot<TYPE>);
}

SORTTEMPLATE void utlSimpleQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlQuickSort(Sequence, 0, Size-1, CompareFunction, utlLastPivot<TYPE>);
}

SORTTEMPLATE void utlRandomQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlQuickSort(Sequence, 0, Size-1, CompareFunction, utlRandomPivot<TYPE>);
}

SORTTEMPLATE void utlMedianQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION)
{
  utlQuickSort(Sequence, 0, Size-1, CompareFunction, utlMedianPivot<TYPE>);
}

#undef PIVOT_FUNCTION
#undef COMPARE_FUNCTION
#undef SORTTEMPLATE
