/**
* Modulo de declaracao da classe SPHERE.Esta classe representa uma esfera
* @author: Fabio Nakamura
*/

#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector3.h"

template <class Real> class SPHERE
{
	public:

		/**
		* O centro da esfera
		*/
		VECTOR3<Real> Center;

		/**
		* O raio da esfera
		*/
		Real Radius;

		/**
		* Construtor
		*/
		/**
		* Construtor Vazio
		*/
		SPHERE(void);

		/**
		* Copia
		*/
		SPHERE(const SPHERE<Real>& Sphere);

		/**
		* Dado um centro e um raio
		*/
		SPHERE(const VECTOR3<Real>& Center,const Real Radius);
		SPHERE(const Real* Center,const Real Radius);
		SPHERE(const Real Center_x,const Real Center_y,const Real Center_z,const Real Radius);


		/**
		* Metodos Get / Set
		*/
		void Set_New_Center(const VECTOR3<Real>& New_Center);
		void Set_New_Center(const Real* New_Center);
		void Set_New_Center(const Real New_Center_x,const Real New_Center_y,const Real New_Center_z);
		void Set_New_Radius(const Real New_Radius);

};
#include "sphere.inl"

#endif

