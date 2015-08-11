/**
* Modulo de definicao de uma classe que representa a primitiva triangulo em 2D.
* @author : Fabio Nakamura
*/

#ifndef __TRIANGLE2D_H__
#define __TRIANGLE2D_H__

#include "vector2.h"

template <class Real> class TRIANGLE2D
{
	public:

		/**
		* Os tres vertices do triangulo
		*/

		/**
		* Vertice 1
		*/
		VECTOR2<Real> V1;

		/**
		* Vertice 2
		*/
		VECTOR2<Real> V2;

		/**
		* Vertice 3
		*/
		VECTOR2<Real> V3;

		/**
		* Construtores
		*/

		/**
		* Vazio
		*/
		TRIANGLE2D(void);

		/**
		* Dado tres vertices
		*/
		TRIANGLE2D(const VECTOR2<Real>& v1,const VECTOR2<Real>& v2,const VECTOR2<Real>& v3);

		/**
		* Dado um vetor de vertices, onde Vertex e um vetor de tamanho 3
		*/
		TRIANGLE2D(const VECTOR2<Real>* Vertex);

		/**
		* Dado um vetor de Real* , tal que Tamnaho de Real*  = 6
		*/
		TRIANGLE2D(const Real* Vertex);


		/*
		* Faz um Set de vertices
		*/
		void Set_Triangle(const VECTOR2<Real>& v1,const VECTOR2<Real>& v2,const VECTOR2<Real>& v3);
		void Set_Triangle(const TRIANGLE2D<Real>& Triangle);

		/**
		* Determina se dado triangulo e formado por tres pontos colineares
		*/
		bool Is_Colinear(void);

		/**
		* Retorna a Area do Triangulo
		*/
		Real Area(void);


		
};
#include "triangle2d.inl"

#endif
