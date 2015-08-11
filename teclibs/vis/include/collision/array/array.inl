/**
* Modulo de implementacao dos metodos inline da classe ARRAY
* @author: Fabio Nakamura
*/





/**
* Operadores !
*/

template <class T> inline  ARRAY<T>& ARRAY<T>::operator = (const ARRAY<T>& Array)
{
	
	this->Max_Elements = Array.Max_Elements;
	this->Total_Elements = Array.Total_Elements;
	this->Growth_Rate = Array.Growth_Rate;

	if(this->Data)
	{
		delete[] this->Data;
		this->Data = NULL;
	}
	
	if(this->Total_Elements > 0)
	{
		this->Data = new T[this->Max_Elements];
		//memset(this->Data,0,sizeof(T)*Max_Elements);

		unsigned int i;
		for(i = 0; i < this->Total_Elements; i+= 1)
		{
			this->Data[i] = Array.Data[i];
		}
		//memcpy(this->Data,Array.Data,sizeof(T)*Array.Total_Elements);
	}
	else
		this->Data = new T[DEFAULT_MAX_ELEMENTS];

	return(*this);
}


/**
* Metodos de insercao
*/
template <class T> inline void ARRAY<T>::Insert_Element(unsigned int index,const T& New_Element)
{
	if(index < this->Max_Elements)
		this->Data[index] = New_Element;
	else
	{
		// Cresce Vetor por Growth e copia todos os elementos
		// de modo que caiba no indice index.

		index = this->Max_Elements;
		unsigned int New_Size;
		
		New_Size = (unsigned int)(index*this->Growth_Rate+1);

		T* Temp_Buffer = new T[New_Size];

		//memset(Temp_Buffer,0,sizeof(T)*New_Size);

		/**
		* Copia todas as entradas do vetor Data para Temp_Buffer
		*/
		//memcpy(Temp_Buffer,this->Data,sizeof(T)*this->Max_Elements);
		
		unsigned int i;
		for(i = 0; i < this->Total_Elements; i+= 1)
		{
			Temp_Buffer[i] = this->Data[i];
		}
	
		/**
		* Agora coloca o elemento que se deseja inserir.
		*/
		Temp_Buffer[this->Total_Elements] = New_Element;
		this->Max_Elements = New_Size;
		delete[] this->Data;
		this->Data = Temp_Buffer;
	}
	++this->Total_Elements;
	return;
}


template <class T> inline void ARRAY<T>::Insert_Element(const T& New_Element)
{
	if(this->Total_Elements < this->Max_Elements)
		this->Data[this->Total_Elements] = New_Element;
	else
	{
		// Cresce Vetor por Growth e copia todos os elementos
		// de modo que caiba no indice index.
		unsigned int New_Size;
		
		New_Size = (unsigned int)(this->Max_Elements*this->Growth_Rate + 1);

		T* Temp_Buffer = new T[New_Size];

		//memset(Temp_Buffer,0,sizeof(T)*New_Size);

		/**
		* Copia todas as entradas do vetor Data para Temp_Buffer
		*/
		unsigned int i;
		for(i = 0; i < this->Total_Elements; i+= 1)
		{
			Temp_Buffer[i] = this->Data[i];
		}
	

		/**
		* Agora coloca o elemento que se deseja inserir.
		*/
		Temp_Buffer[this->Total_Elements] = New_Element;

		this->Max_Elements = New_Size;
		delete[] this->Data;
		this->Data = Temp_Buffer;
	}

	++this->Total_Elements;
	return;
}

template <class T> inline void ARRAY<T>::Fast_Remove(unsigned int index)
{
	// A remocao do vetor e' trocar a posicao do ultimo elemento
	// com o elemento index;

	if(index < this->Total_Elements)
	{
		this->Data[index] = this->Data[this->Total_Elements - 1];
		--this->Total_Elements;
	}
	//if(this->Total_Elements == 0)
	//	memset(this->Data,0,sizeof(T)*this->Max_Elements);

	return;
}

template <class T> inline void ARRAY<T>::Remove_Element(unsigned int index)
{
	// Remove e coloca o vetor em ordem
	if(index < this->Total_Elements)
	{
		--this->Total_Elements;
		//memmove(Data + index, Data + index + 1, (this->Total_Elements - index) * sizeof(T));
		//memset(Data + this->Total_Elements,0, sizeof(T));
		unsigned int i;
		for( i = index ; i < this->Total_Elements ; i+=1)
		{
			this->Data[i] = this->Data[i+1];
		}
		
				
	}
	//if(this->Total_Elements == 0)
	//	memset(this->Data,0,sizeof(T)*this->Max_Elements);

	return;
}

