/*
%M itransf.h - Transformacoes e matrizes para o interact
%a Marcelo Medeiros Carneiro
   Juli Huang
%d 03.08.94
%h Separado do tasksel em 13.05.96 por Newton Sanches
%p Interact
*/

#ifndef _ITR_TRANSF_
#define _ITR_TRANSF_

#include "interactapi.h"
/*
%C Matriz de Transformacao 
*/
struct INTERACT_API itrTMatrix {
 double m[2][3];
 itrTMatrix () { m[0][0]=m[1][1]=1.; m[0][1]=m[0][2]=m[1][0]=m[1][2]=0.; }
};

/*
%F Redefinicao do operador mais significando concatenacao de matrizes
*/
inline itrTMatrix operator*(const itrTMatrix &a, const itrTMatrix &b) {
 itrTMatrix r;
 r.m[0][0] = a.m[0][0]*b.m[0][0] + a.m[0][1]*b.m[1][0];
 r.m[0][1] = a.m[0][0]*b.m[0][1] + a.m[0][1]*b.m[1][1];
 r.m[0][2] = a.m[0][0]*b.m[0][2] + a.m[0][1]*b.m[1][2] + a.m[0][2];
 r.m[1][0] = a.m[1][0]*b.m[0][0] + a.m[1][1]*b.m[1][0];
 r.m[1][1] = a.m[1][0]*b.m[0][1] + a.m[1][1]*b.m[1][1];
 r.m[1][2] = a.m[1][0]*b.m[0][2] + a.m[1][1]*b.m[1][2] + a.m[1][2];
 return r;
}

/*
%C Transformacao - E' a matriz de transformacao com operacoes de mover, 
   aumentar/diminuir, cizalhar, tranformar pontos ...
*/
class INTERACT_API itrTransf {
 protected:
  itrTMatrix m;

 public:
  itrTransf                 () { Identity (); }
  virtual ~itrTransf        () {}

  void       Identity       ();
  void       Translate      (double tx,double ty);
  void       Rotate         (double angle);
  void       Scale          (double sx,double sy);
  void       Shear          (double sx,double sy);
  void       SetMatrix      (itrTMatrix *tm);
  void       AccMatrix      (itrTMatrix *tm);
  itrTMatrix GetMatrix      ();
  void TransformPoint       (double *x,double *y);
};

#endif

