/**
* Modulo de declaracao da classe COLLISION_NODE_INTERNAL.COLLISION_NODE_INTERNAL e um 
* no interno da hierarquia.Os nos internos da geometria podem ou nao possuir geometria
* Os nos internos sao responsaveis por criar a hierarquia de colisao, ja que podemos
* adicionar outros volumes envolventes para fazer a concatenacao.
* @author Fabio Nakamura
* @version 1.0b
*/
#ifndef __COL_LIB_COLLISION_NODE_INTERNAL_H__
#define __COL_LIB_COLLISION_NODE_INTERNAL_H__

#include "collision_node.h"
#include "../array/array.h"

class COLLISION_NODE_INTERNAL :public COLLISION_NODE
{
		
	protected:

		/**
		* Re calcula o volume envolvente deste no, baseado nos
		* volumes envolventes dos nos filho.
		* O resultado e guardado no proprio no.
		*/
		virtual void Re_Compute_BV(void);

		/**
		* Faz a concatenacao do volume envolvente do no que chamou 
		* o metodo, com o no Node.
		* O novo volume envolvente do no que chamou o metodo e o resultado
		* do "merging"
		*/
		void Merge_BV(COLLISION_NODE* Node);

			

	public:

		/**
		* Faz o Update deste no e de todos os seus filhos.
		*/
		int Update(void);

		/**
		* Construtor
		* @param Type Qual o tipo de volume envolvente sera usado na hierarquia
		*
		*/
		COLLISION_NODE_INTERNAL(COLLISION_NODE::BV_TYPES Type);

		/**
		* Destrutor
		*/
		~COLLISION_NODE_INTERNAL(void);
		
		
		/**
		* Adiciona novo volume envolvente.
		* Usado pelos nos internos para a criacao da hierarquia
		* de volumes envolventes
		* @param node O no que se deseja adicionar.
		*/
		void Add(COLLISION_NODE* Node);	

		/**
		* Dado um no, se este existir na lista de filhos deste no interno
		* entao remova-o. Se for possivel remover retorna true, false caso contrario.
		*/
		bool Remove(COLLISION_NODE* Node);

		/** 
		* Destroi tudo alocado pelo no'
		*/
		void Destroy(void);

		/**
		* Desenha Volume Envolvente correspondente ao no.
		* Funcao de teste visual por enquanto
		*/
		void Render_BV(void);


		/**
		* Internal Use only
		*/
		/**
		* Os filhos deste no
		*/
		ARRAY<COLLISION_NODE*>Children;
		
	
};
#endif
