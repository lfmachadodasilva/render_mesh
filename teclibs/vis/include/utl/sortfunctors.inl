#include <stdlib.h>

template <typename Type, typename Compare, typename PivotMode> class UtlSort;

//---------------------------//
// Template para comparação  //
//---------------------------//

template<typename Type> class UtlSortCompare
{
public:
  UTL_FORCE_INLINE int operator() (const Type & elem1, const Type & elem2) const
  {
    if (elem1 > elem2)
      return 1;
    else if (elem2 > elem1)
      return -1;
    else
      return 0;
  }
};

//------------------------------//
// Templates para pivoteamento  //
//------------------------------//

template<typename Type> class UtlSortPivotLast
{
public:
  UTL_FORCE_INLINE int operator() (const Type Sequence[], int FirstIndex, int LastIndex) const
  {
    return LastIndex;
  }
};

template<typename Type> class UtlSortPivotMiddle
{
public:
  UTL_FORCE_INLINE int operator() (const Type Sequence[], int FirstIndex, int LastIndex) const
  {
    return (FirstIndex+LastIndex) / 2;
  }
};

template<typename Type> class UtlSortPivotRandom
{
public:
  UTL_FORCE_INLINE int operator() (const Type Sequence[], int FirstIndex, int LastIndex) const
  {
    return utlRandomInt(FirstIndex, LastIndex);
  }
};

template<typename Type, typename Compare = UtlSortCompare<Type> > class UtlSortPivotMedian
{
public:
  UTL_FORCE_INLINE int operator() (const Type Sequence[], int FirstIndex, int LastIndex) const
  {
    int Group, GroupStart, GroupEnd, MedianIndex;
    UtlSort<Type, Compare, UtlSortPivotMedian> sort;

    if (FirstIndex >= LastIndex) return FirstIndex;

    // Pega a mediana de cada conjunto de 5 elementos e coloca no começo do array

    for (Group = 0, GroupStart = FirstIndex; GroupStart < LastIndex; ++Group, GroupStart += 5)
    {
      GroupEnd = GroupStart+4;
      if (GroupEnd > LastIndex) GroupEnd = LastIndex;
      MedianIndex = (GroupStart + GroupEnd) / 2;

      sort.InsertSort(Sequence, GroupStart, GroupEnd);

      utlExchangeValues(&Sequence[FirstIndex+Group], &Sequence[MedianIndex]);
    }

    // Acha a mediana das medianas

    MedianIndex = sort.Select(Sequence, FirstIndex, FirstIndex+Group-1, Group/2);

    return MedianIndex;
  }
};


template <typename Type, typename Compare = UtlSortCompare<Type>, typename PivotMode = UtlSortPivotLast<Type> > class UtlSort
{
public:

  UtlSort () {};
  UtlSort (const Compare & compare, const PivotMode & pivot)
  {
    SetCompareFunctor(compare);
    SetPivotFunctor(pivot);
  }
  ~UtlSort () {};

  //------------------//
  // RemoveDuplicates //
  //------------------//

  int RemoveDuplicates (Type Sequence[], int FirstIndex, int LastIndex)
  {
    int LastValidIndex = FirstIndex;
    for (int i = FirstIndex+1; i <= LastIndex; ++i)
    {
      if (m_Compare(Sequence[i],Sequence[LastValidIndex])) // Diferentes
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

  int Min (Type Sequence[], int FirstIndex, int LastIndex)
  {
    int MinIndex = FirstIndex;
    for (int i = FirstIndex+1; i <= LastIndex; ++i)
    {
      if (m_Compare(Sequence[i],Sequence[MinIndex]) < 0) MinIndex = i;
    }
    return MinIndex;
  }

  Type Min (Type Sequence[], int Size)
  {
    return Sequence[Min(Sequence, 0, Size-1)];
  }

  //---------//
  // Maximum //
  //---------//

  int Max (Type Sequence[], int FirstIndex, int LastIndex)
  {
    int MaxIndex = FirstIndex;
    for (int i = FirstIndex+1; i <= LastIndex; ++i)
    {
      if (m_Compare(Sequence[i],Sequence[MaxIndex]) > 0) MaxIndex = i;
    }
    return MaxIndex;
  }

  Type Max (Type Sequence[], int Size)
  {
    return Sequence[Max(Sequence, 0, Size-1)];
  }

  //---------------------//
  // Minimum and Maximum //
  //---------------------//

  void MinMax (Type Sequence[], int FirstIndex, int LastIndex, int &MinIndex, int &MaxIndex)
  {
    if (FirstIndex > LastIndex) return;

    if ((LastIndex - FirstIndex + 1) % 2) // Número ímpar de elementos
    {
      MinIndex = MaxIndex = FirstIndex;
      ++FirstIndex;
    }
    else // Número par de elementos
    {
      if (m_Compare(Sequence[FirstIndex],Sequence[FirstIndex+1]) < 0) {MinIndex = FirstIndex; MaxIndex = FirstIndex+1;}
      else {MaxIndex = FirstIndex; MinIndex = FirstIndex+1;}
      FirstIndex += 2;
    }

    for (int i = FirstIndex; i < LastIndex; i+=2)
    {
      if (m_Compare(Sequence[i],Sequence[i+1]) < 0)
      {
        if (m_Compare(Sequence[i  ],Sequence[MinIndex]) < 0) MinIndex = i;
        if (m_Compare(Sequence[i+1],Sequence[MaxIndex]) > 0) MaxIndex = i+1;
      }
      else
      {
        if (m_Compare(Sequence[i  ],Sequence[MaxIndex]) > 0) MaxIndex = i;
        if (m_Compare(Sequence[i+1],Sequence[MinIndex]) < 0) MinIndex = i+1;
      }
    }
  }

  void MinMax (Type Sequence[], int Size, Type* Minimum, Type* Maximum)
  {
    int MinIndex, MaxIndex;
    MinMax(Sequence, 0, Size-1, MinIndex, MaxIndex);
    (*Minimum) = Sequence[MinIndex];
    (*Maximum) = Sequence[MaxIndex];
  }

  //---------------//
  // Binary search //
  //---------------//

  int BinarySearch (Type Sequence[], int FirstIndex, int LastIndex, Type Element)
  {
    if (FirstIndex > LastIndex) return -1;

    int MiddleIndex = (FirstIndex + LastIndex) / 2;

    int Comparison = m_Compare(Sequence[MiddleIndex],Element);

    if (Comparison ==  1) return BinarySearch(Sequence, FirstIndex, MiddleIndex-1, Element);
    if (Comparison == -1) return BinarySearch(Sequence, MiddleIndex+1, LastIndex,  Element);
    return MiddleIndex;
  }

  int BinarySearch (Type Sequence[], int Size, Type Element)
  {
    return BinarySearch(Sequence, 0, Size-1, Element);
  }

  //-------------//
  // Select Sort //
  //-------------//

  void SelectSort (Type Sequence[], int FirstIndex, int LastIndex)
  {
    if (FirstIndex >= LastIndex) return;

    for (int i = FirstIndex; i < LastIndex; ++i)
    {
      int MinIndex = Min(Sequence, i, LastIndex);
      utlExchangeValues(&Sequence[i], &Sequence[MinIndex]);
    }
  }

  void SelectSort (Type Sequence[], int Size)
  {
    SelectSort(Sequence, 0, Size-1);
  }

  //-------------//
  // Insert Sort //
  //-------------//

  void Insert (Type Sequence[], int FirstIndex, int ElementIndex)
  {
    Type Temp = Sequence[ElementIndex];
    int j = ElementIndex - 1;
    while (j >= FirstIndex && m_Compare(Sequence[j],Temp) > 0)
    {
      Sequence[j+1] = Sequence[j];
      --j;
    }
    Sequence[j+1] = Temp;
  }

  void InsertSort (Type Sequence[], int FirstIndex, int LastIndex)
  {
    if (FirstIndex >= LastIndex) return;

    for (int i = FirstIndex+1; i <= LastIndex; ++i)
    {
      Insert(Sequence,FirstIndex,i);
    }
  }

  void InsertSort (Type Sequence[], int Size)
  {
    InsertSort(Sequence, 0, Size-1);
  }

  //-------------//
  // Bubble Sort //
  //-------------//

  void BubbleSort (Type Sequence[], int FirstIndex, int LastIndex)
  {
    if (FirstIndex >= LastIndex) return;

    for (int i = FirstIndex; i < LastIndex; ++i)
    {
      bool flag = false;
      for (int j = LastIndex; j > i; --j)
      {
        if (m_Compare(Sequence[j],Sequence[j-1]) < 0)
        {
          flag = true;
          utlExchangeValues(&Sequence[j], &Sequence[j-1]);
        }
      }
      if (!flag) return;
    }
  }

  void BubbleSort (Type Sequence[], int Size)
  {
    BubbleSort(Sequence, 0, Size-1);
  }

  //------------//
  // Merge Sort //
  //------------//

  void Merge (Type SortArray[], Type SubArray1[], Type SubArray2[], int SubStart1, int SubLast1, int SubLast2)
  {
    int i,j;

    int Size1 = SubLast1 - SubStart1 + 1;
    int Size2 = SubLast2 - SubLast1;

    Type* SortArray1 = SortArray + SubStart1;
    Type* SortArray2 = SortArray + SubLast1 + 1;

    for (i = 0; i < Size1; ++i) SubArray1[i] = SortArray1[i];
    for (j = 0; j < Size2; ++j) SubArray2[j] = SortArray2[j];

    i=0;
    j=0;
    for (int index = SubStart1; index <= SubLast2; ++index)
    {
      if (j == Size2) SortArray[index] = SubArray1[i++];
      else if (i == Size1) SortArray[index] = SubArray2[j++];
      else if (m_Compare(SubArray1[i],SubArray2[j]) <= 0) SortArray[index] = SubArray1[i++];
      else SortArray[index] = SubArray2[j++];
    }
  }

  void DoMergeSort (Type Sequence[], Type SubArray1[], Type SubArray2[], int FirstIndex, int LastIndex)
  {
    if (FirstIndex >= LastIndex) return;

    int MiddleIndex = (FirstIndex + LastIndex) / 2;

    DoMergeSort(Sequence, SubArray1, SubArray2, FirstIndex, MiddleIndex);
    DoMergeSort(Sequence, SubArray1, SubArray2, MiddleIndex+1, LastIndex);
    Merge(Sequence, SubArray1, SubArray2, FirstIndex, MiddleIndex, LastIndex);
  }

  void MergeSort (Type Sequence[], int FirstIndex, int LastIndex)
  {
    if (FirstIndex >= LastIndex) return;

    int SubSize = ((LastIndex - FirstIndex) / 2) + 1;
    Type *SubArray1 = new Type[SubSize];
    Type *SubArray2 = new Type[SubSize];

    DoMergeSort(Sequence, SubArray1, SubArray2, FirstIndex, LastIndex);

    delete[] SubArray2;
    delete[] SubArray1;
  }

  void MergeSort (Type Sequence[], int Size)
  {
    MergeSort(Sequence, 0, Size-1);
  }

  //--------------------------------//
  // Pivoteamento e particionamento //
  //--------------------------------//

  int Partition (Type Sequence[], int FirstIndex, int LastIndex)
  {
    int PivotIndex = m_Pivot(Sequence, FirstIndex, LastIndex);

    Type Pivot = Sequence[PivotIndex];
    Sequence[PivotIndex] = Sequence[LastIndex];
    Sequence[LastIndex] = Pivot;

    int i = FirstIndex - 1;
    for (int j = FirstIndex; j < LastIndex; ++j)
    {
      if (m_Compare(Sequence[j],Pivot) <= 0)
      {
        utlExchangeValues(&Sequence[++i], &Sequence[j]);
      }
    }
    Sequence[LastIndex] = Sequence[++i];
    Sequence[i] = Pivot;
    return i;
  }

  //--------//
  // Select //
  //--------//

  int Select (Type Sequence[], int FirstIndex, int LastIndex, int ElementOrder)
  {
    if (FirstIndex >= LastIndex) return FirstIndex;

    if (LastIndex - FirstIndex + 1 <= 5)
    {
      InsertSort(Sequence, FirstIndex, LastIndex);
      return FirstIndex + ElementOrder - 1;
    }

    int PivotIndex = Partition(Sequence, FirstIndex, LastIndex);
    int PivotOrder = PivotIndex - FirstIndex + 1;

    if (ElementOrder == PivotOrder) return PivotIndex;
    if (ElementOrder < PivotOrder) return Select(Sequence, FirstIndex, PivotIndex-1, ElementOrder);
    return Select(Sequence, PivotIndex+1, LastIndex, ElementOrder-PivotOrder);
  }

  //------------//
  // Quick Sort //
  //------------//

  void QuickSort (Type Sequence[], int FirstIndex, int LastIndex)
  {
    if (FirstIndex >= LastIndex) return;

    if (LastIndex - FirstIndex + 1 <= 5)
    {
      InsertSort(Sequence, FirstIndex, LastIndex);
      return;
    }

    int MiddleIndex = Partition(Sequence, FirstIndex, LastIndex);
    QuickSort(Sequence, FirstIndex, MiddleIndex-1);
    QuickSort(Sequence, MiddleIndex+1, LastIndex);
  }

  void QuickSort (Type Sequence[], int Size)
  {
    QuickSort(Sequence, 0, Size-1);
  }


  Compare& GetCompareFunctor ()
  {
    return m_Compare;
  }
  void SetCompareFunctor (const Compare & compare)
  {
    m_Compare = compare;
  }
  void SetPivotFunctor (const PivotMode & pivot)
  {
    m_Pivot = pivot;
  }

private:

  Compare m_Compare;
  PivotMode m_Pivot;

};
