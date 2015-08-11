#ifndef UTL_TEMPLATE_SORT_H
#define UTL_TEMPLATE_SORT_H

// Generic functions implemented through a template
// Purpose: Sorting algorithms

// Notes:
// - The type TYPE must be concrete
// - The type TYPE must have the operator = defined

// Compare Function:
// - Receives two elements to be compared
// - Returns:
//   * -1 if the first element is lower
//   *  0 if the elements are equal
//   * +1 if the first element if higher

#define SORTTEMPLATE template <class TYPE>
#define COMPARE_FUNCTION int(*CompareFunction)(TYPE, TYPE)
#define PIVOT_FUNCTION   int(*PivotFunction)(TYPE[], int, int, int(*)(TYPE, TYPE))

//-------------------------------------//
// Troca de lugar entre dois elementos //
//-------------------------------------//
// Tempo: O(1)

SORTTEMPLATE void utlExchangeValues (TYPE* Element1, TYPE* Element2);

//------------------//
// RemoveDuplicates //
//------------------//
// Entrada: vetor ORDENADO de objetos
//          (ou qualquer vetor em que possíveis duplicatas sejam todas consecutivas)
// Tempo: O(n)

SORTTEMPLATE int utlRemoveDuplicates (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);

//---------//
// Minimum //
//---------//
// Melhor caso: O(n)
// Pior caso: O(n)
// Caso médio: O(n)

SORTTEMPLATE int utlMin (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE TYPE utlMin (TYPE Sequence[], int Size, COMPARE_FUNCTION);

//---------//
// Maximum //
//---------//
// Melhor caso: O(n)
// Pior caso: O(n)
// Caso médio: O(n)

SORTTEMPLATE int utlMax (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE TYPE utlMax (TYPE Sequence[], int Size, COMPARE_FUNCTION);

//---------------------//
// Minimum and Maximum //
//---------------------//
// Melhor caso: O(3*n/2), a constante é 1.5, e não 2
// Pior caso: O(3*n/2), a constante é 1.5, e não 2
// Caso médio: O(3*n/2), a constante é 1.5, e não 2

SORTTEMPLATE void utlMinMax (TYPE Sequence[], int FirstIndex, int LastIndex, int &MinIndex, int &MaxIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlMinMax (TYPE Sequence[], int Size, TYPE* Minimum, TYPE* Maximum, COMPARE_FUNCTION);

//---------------//
// Binary search //
//---------------//
// Melhor caso: O(1)
// Pior caso: O(lg(n))
// Caso médio: O(lg(n))

SORTTEMPLATE int utlBinarySearch (TYPE Sequence[], int FirstIndex, int LastIndex, TYPE Element, COMPARE_FUNCTION);
SORTTEMPLATE int utlBinarySearch (TYPE Sequence[], int Size, TYPE Element, COMPARE_FUNCTION);

//-------------//
// Select Sort //
//-------------//
// Algoritmo:
// - Acha o minimo do vetor e coloca na posicao inicial
// - O primeiro elemento esta certo, repete recursivamente comecando do proximo
// Melhor caso: O(n^2)
// Pior caso: O(n^2)
// Caso médio: O(n^2)
// 100.000 floats randomicos em 13,5s

SORTTEMPLATE void utlSelectSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlSelectSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

//-------------//
// Insert Sort //
//-------------//
// Algoritmo:
// - Considere um subvetor do primeiro elemento até o segundo
// - Desloca o último elemento para trás até a posição correta no subvetor
// - Repete recursivamente para um subvetor do primeiro elemento ate um elemento a mais
// Melhor caso: O(n) (lista já ordenada)
// Pior caso: O(n^2) (lista anti-ordenada)
// Caso médio: O(n^2)
// 100.000 floats randomicos em 7,5s

SORTTEMPLATE void utlInsert (TYPE Sequence[], int FirstIndex, int ElementIndex, COMPARE_FUNCTION);

SORTTEMPLATE void utlInsertSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlInsertSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

//-------------//
// Bubble Sort //
//-------------//
// Algoritmo (reverso):
// - Considere um subvetor de tamanho maximo, do primeiro ao ultimo elemento
// - Comecando do ultimo elemento e retornando, desloca cada elemento ate encostar num igual ou menor
// - O menor elemento esta no comeco, repete recursivamente para um subvetor comecando um elemento a frente
// Melhor caso: O(n) (lista já ordenada)
// Pior caso: O(n^2) (lista cujo primeiro elemento é o maior)
// Caso médio: O(n^2)
// 100.000 floats randomicos em 53,0s

SORTTEMPLATE void utlBubbleSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlBubbleSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

//------------//
// Merge Sort //
//------------//
// Algoritmo:
// - Divide o vetor em duas partes iguais
// - Realiza o Merge Sort recursivamente em cada parte
// - Faz o Merge das duas partes (junta as duas, assumidas ordenadas, num novo vetor ainda ordenado)
// Melhor caso: O(n*lg(n))
// Pior caso: O(n*lg(n))
// Caso médio: O(n*lg(n))
// 100.000 floats randomicos em 1,2s

SORTTEMPLATE void utlMerge (TYPE SortArray[], TYPE SubArray1[], TYPE SubArray2[], int SubStart1, int SubLast1, int SubLast2, COMPARE_FUNCTION);

SORTTEMPLATE void utlDoMergeSort (TYPE Sequence[], TYPE SubArray1[], TYPE SubArray2[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);

SORTTEMPLATE void utlMergeSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlMergeSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

//--------------------------------//
// Pivoteamento e particionamento //
//--------------------------------//

SORTTEMPLATE int utlLastPivot   (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE int utlRandomPivot (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE int utlMedianPivot (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);

SORTTEMPLATE int utlPartition   (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION, PIVOT_FUNCTION);

SORTTEMPLATE int utlSimplePartition (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE int utlRandomPartition (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE int utlMedianPartition (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);

//--------//
// Select //
//--------//

SORTTEMPLATE int utlSelect (TYPE Sequence[], int FirstIndex, int LastIndex, int ElementOrder, COMPARE_FUNCTION, PIVOT_FUNCTION);

// Simples
// Melhor caso: O(1)
// Pior caso: O(n^2)
// Caso médio: O(n)

SORTTEMPLATE int utlSimpleSelect (TYPE Sequence[], int Size, int ElementOrder, COMPARE_FUNCTION);

// Randomico
// Melhor caso: O(1)
// Pior caso: O(n^2)
// Caso médio: O(n)

SORTTEMPLATE int utlRandomSelect (TYPE Sequence[], int Size, int ElementOrder, COMPARE_FUNCTION);

// Balanceado
// Melhor caso: O(1)
// Pior caso: O(n)
// Caso médio: O(n)

SORTTEMPLATE int utlMedianSelect (TYPE Sequence[], int Size, int ElementOrder, PIVOT_FUNCTION);

//------------//
// Quick Sort //
//------------//

SORTTEMPLATE void utlQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION, PIVOT_FUNCTION);
SORTTEMPLATE void utlQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION, PIVOT_FUNCTION);

// Simples
// Melhor caso: O(n*lg(n))
// Pior caso: O(n^2) (pivôs escolhidos como menores ou maiores elementos)
// Caso médio: O(n*lg(n))
// 250.000 floats randomicos em menos de 0,2s

SORTTEMPLATE void utlSimpleQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlSimpleQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

// Randomico
// Melhor caso: O(n*lg(n))
// Pior caso: O(n^2)
// Caso médio: O(n*lg(n))
// 250.000 floats randomicos em menos de 0,1s

SORTTEMPLATE void utlRandomQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlRandomQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

// Balanceado
// Melhor caso: O(n*lg(n))
// Pior caso: O(n*lg(n))
// Caso médio: O(n*lg(n))
// 250.000 floats randomicos em menos de 0,5s

SORTTEMPLATE void utlMedianQuickSort (TYPE Sequence[], int FirstIndex, int LastIndex, COMPARE_FUNCTION);
SORTTEMPLATE void utlMedianQuickSort (TYPE Sequence[], int Size, COMPARE_FUNCTION);

#include "sort.inl"
#include "sortfunctors.inl"

#undef PIVOT_FUNCTION
#undef COMPARE_FUNCTION
#undef SORTTEMPLATE

#endif // UTL_TEMPLATE_SORT_H
