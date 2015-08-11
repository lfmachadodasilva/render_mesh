/**
* Alguns testes uteis de geometria para auxiliar no calculo de volumes envolventes, teste 
* de colisoes e etc...
* @author: Fabio Nakamura
*/
#ifndef __MISCELANEOUS_H__
#define __MISCELANEOUS_H__

#include "../math_includes.h"

/**
* Dado uma direcao, retorna os indices do vetor de pontos dos pontos nos extremos.
*/
template <class Real> void Extreme_Points_Along_Direction(const VECTOR3<Real>& Direction,
													 const VECTOR3<Real>* Points,unsigned int Num_of_Points,
													 unsigned int& Min,unsigned int &Max);

/**
* Dado uma direcao, retorna os indices do vetor de pontos dos pontos nos extremos.
*/
template <class Real> void Extreme_Points_Along_Direction(const VECTOR3<Real>& Direction,
													 const Real* Points,unsigned int Num_of_Points,
													 unsigned int& Min,unsigned int &Max);



/**
* Igual a funcao acima, porem Direction = V[3] e Points = V[Num_of_Points*3];
*/
template <class Real> void Extreme_Points_Along_Direction(const Real* Direction,
														  const Real* Points,unsigned int Num_of_Points,
														  unsigned int& Min,unsigned int &Max);

/**
* Projeta um triangulo dado uma direcao , e retorna o minimo e maximo na direcao
*/
template <class Real> void Project_Triangle(const VECTOR3<Real>& Direction,const TRIANGLE3D<Real>& Triangle,
											Real& Min_Point,Real& Max_Point);

#endif

