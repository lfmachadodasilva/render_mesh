/**
* Modulo de definicao de um template array. Este array cresce dinamicamente
* no caso de inserir um elemento novo num array cheio.
* @author: Fabio Nakamura
*/

#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#define DEFAULT_GROWTH_RATE 1.5f
#define DEFAULT_MAX_ELEMENTS 10

template <class T> class ARRAY
{
	private:


		/**
		* Atributos privados da classe
		*/

		/**
		* O dado do Array
		*/
		T* Data;

		/**
		* Numero maximo de elementos
		*/
		unsigned int Max_Elements;

		/**
		* O numero total de elementos
		*/
		unsigned int Total_Elements;

		/**
		* A taxa de crescimento deste array 
		*/
		float Growth_Rate;

		
	public:

		/**
		* Atributos publicos da classe
		*/

		/**
		* Construtores
		*/

		/**
		* Constroi dado um numero maximo e o numero e a taxa de crescimento
		*/
		ARRAY(unsigned int Max_Elements,float Growth_Rate)
		{
			this->Max_Elements = Max_Elements;
			this->Total_Elements = 0;
			this->Growth_Rate = Growth_Rate;

			this->Data = new T[Max_Elements];
			//memset(this->Data,0,sizeof(T)*Max_Elements);
		}

		/**
		* Dado um outro Array
		*/
		ARRAY(const ARRAY& Array)
		{
			this->Data = NULL;
			*this = Array;
		}
		
		/**
		* Construtor Vazio
		*/
		ARRAY(void)
		{
			this->Max_Elements = DEFAULT_MAX_ELEMENTS;
			this->Total_Elements = 0;
			this->Growth_Rate = DEFAULT_GROWTH_RATE;

			//this->Data = NULL;
			this->Data = new T[DEFAULT_MAX_ELEMENTS];
			//memset(this->Data,0,sizeof(T)*DEFAULT_MAX_ELEMENTS);
		}


		/**
		* destrutor
		*/
        ~ARRAY(void)
		{
			this->Destroy();
		}

		/**
		* Metodos Get
		*/

		/**
		* Retorna o numero maximo de elementos
		*/
		unsigned int Get_Max_Quantity(void)const
		{
			return(this->Max_Elements);
		}

		/**
		* Retorna o numero de elementos
		*/
		unsigned int Get_Total_Elements(void)const
		{
			return(this->Total_Elements);
		}

		/**
		* Retorna a taxa de crescimento
		*/
		float Get_Growth_Rate(void)const
		{
			return(this->Growth_Rate);
		}

		/**
		* Retorna o vetor de T
		*/
		T* Get_Data(void)const
		{
			return(this->Data);
		}
		
		/**
		* Metodos Set
		*/

		/**
		* Nova quantidade maxima
		*/
		void Set_Max_Quantity(unsigned int New_Max_Quantity,bool Copy_Array);

		/**
		* Nova taxa de crescimento
		*/
		void Set_New_Growth_Rate(unsigned int New_Growth_Rate);

		
		/**
		* Operador =
		*/
		ARRAY& operator = (const ARRAY& Array);

				
		/**
		* Operacao de insercao
		*/

		/** 
		* Insere elemento no final do vetor
		*/
		void Insert_Element(const T& New_Element);

		/**
		* Insere elemento no vetor na posicao index
		*/
		void Insert_Element(unsigned int index,const T& New_Element);

		/**
		* Remove elemento na posicao index
		*/
		void Fast_Remove(unsigned int index);
		void Remove_Element(unsigned int index);



		/**
		* Remove todos os elementos;
		*/
		void Remove_All(void)
		{
			// Remove todos os elementos
			this->Total_Elements = 0;
			//memset(this->Data,0,sizeof(T)*this->Max_Elements);
			return;
		}

		/**
		* Retorna elemento uma referencia para o elemento i
		*/
		T Get_Element(unsigned int index)
		{
			return(this->Data[index]);
		}

		T* Get_Element_Address(unsigned int index)
		{
			return(&this->Data[index]);
		}

		
		/**
		* Destroi o vetor
		*/
		void Destroy(void)
		{
			if(this->Data)
			{
				delete[] this->Data;
				this->Data = NULL;
				this->Total_Elements = 0;
				this->Max_Elements = 0;
			}
			return;
		}

};
#include "array.inl"
#endif
