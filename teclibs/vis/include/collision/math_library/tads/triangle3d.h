/**
* Modulo de definicao de uma classe que representa a primitiva triangulo em 3D.
* @author : Fabio Nakamura
*/

#ifndef __TRIANGLE3D_H__
#define __TRIANGLE3D_H__

#include "vector3.h"

template <class Real> class TRIANGLE3D
{
	public:

		/**
		* Os tres vertices do triangulo
		*/

		/**
		* Vertice 1
		*/
		VECTOR3<Real> V1;

		/**
		* Vertice 2
		*/
		VECTOR3<Real> V2;

		/**
		* Vertice 3
		*/
		VECTOR3<Real> V3;

		/**
		* Construtores
		*/

		/**
		* Vazio
		*/
		TRIANGLE3D(void);

		/**
		* Dado tres vertices
		*/
		TRIANGLE3D(const VECTOR3<Real>& v1,const VECTOR3<Real>& v2,const VECTOR3<Real>& v3);

		/**
		* Dado um vetor de vertices, onde Vertex e um vetor de tamanho 3
		*/
		TRIANGLE3D(const VECTOR3<Real>* Vertex);

		/**
		* Dado um vetor de Real* , tal que Tamnaho de Real*  = 9
		*/
		TRIANGLE3D(const Real* Vertex);

		/**
		* retorna a normal deste triangulo
		* A normal e dada por V2-V1 x V3-V1
		*/
		VECTOR3<Real> Get_Unit_Normal(void)const;
		VECTOR3<Real> Get_Normal(void)const;

		/**
		* Faz um Set de vertices
		*/
		void Set_Triangle(const VECTOR3<Real>& v1,const VECTOR3<Real>& v2,const VECTOR3<Real>& v3);
		void Set_Triangle(const TRIANGLE3D<Real>& Triangle);


		/**
		* Determina se dado triangulo e formado por tres pontos colineares
		*/
		bool Is_Colinear(void);

		/**
		* Retorna a Area do Triangulo
		*/
		Real Area(void);
		
};
#include "triangle3d.inl"

#endif
