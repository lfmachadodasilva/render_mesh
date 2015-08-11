/**
* Modulo de definicao de teste de colisao entre retas no espaco 2D
* @author Fabio Nakamura
*/


#ifndef __SEGMENT2D_INTERSECTION_H__
#define __SEGMENT2D_INTERSECTION_H__

#include "../../tads/vector2.h"
#include "../../tads/segment2d.h"

/**
* Dado dois segmentos retorna se eles se cruzam e retorna o ponto de intersecao se houver
*/
template <class Real> bool Segment2D_Intersection(const SEGMENT2D<Real>& S1,const SEGMENT2D<Real>& S2,Real& t);

#endif
