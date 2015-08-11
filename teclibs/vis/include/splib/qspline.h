//* qspline.h
// Quaternion Spline
// hermann@tecgraf.puc-rio.br
// Nov 2004

#ifndef SPLIB_QSPLINE_H
#define SPLIB_QSPLINE_H

#include "defines.h"
#include <ds/array.h>
#include <alg/quatern.h>
#include <utl/writers/lua3filewriter.h>

typedef DsArray<AlgQuatern*> AlgQuaternPArray;

class SPLIB_API QSpline
{
public:

   /** Tipo de interpolação */
   enum Interpolation
   {
      LERP,    ///< interpolação linear
      SLERP,   ///< interpolação esférica
      SQUAD    ///< interpolação cúbica
   };

   /** Construtor */
   QSpline();

   /** Destrutor */
   ~QSpline();
   
   int getId(){return m_id;};

   /** Adiciona o quaternio q na posição qPos
   * @param q [in] quatérnio a ser adicionado
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return número de quatérnios na lista
   */
   int addQuatern(const AlgQuatern q, int qPos=-1);

   /** Adiciona um quatérnio na posição qPos
   * @param angle [in] ângulo de rotação
   * @param axisx [in] coordenada x do eixo de rotação 
   * @param axisy [in] coordenada y do eixo de rotação 
   * @param axisz [in] coordenada z do eixo de rotação 
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return número de quatérnios na lista
   */
   int addQuatern(float angle, float axisx, float axisy, float axisz, int qPos=-1);

   /** Adiciona um quatérnio na posição qPos
   * @param angle [in] ângulo de rotação
   * @param axis [in] eixo de rotação 
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return número de quatérnios na lista
   */
   int addQuatern(float angle, const AlgVector &axis, int qPos=-1);

   /** Adiciona um quatérnio na posição qPos de acordo com a matrix de rotação formado pelas linhas u,v,w
   * @param u [in] primeira linha da matriz de rotação
   * @param v [in] segunda linha da matriz de rotação
   * @param w [in] terceira linha da matriz de rotação
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return número de quatérnios na lista
   */
   int addQuatern(const AlgVector &u, const AlgVector &v, const AlgVector &w, int qPos=-1);

   /** Adiciona um quatérnio na posição qPos a partir de seus valores puros [w,x,y,z]
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return número de quatérnios na lista
   */
   int addQuaternRaw(float w, float x, float y, float z, int qPos=-1);

   /** Remove o quatérnio na posição qPos da lista
   * @param qPos [in] posição a ser removida, onde números negativos correspondem a ordem inversa
   * @return retorna false se kPos for inválido, por exemplo uma lista com 3 nós (0,1,2) e qPos > 2 ou qPos < -3
   */
   bool removeQuatern(int qPos);

   /** Remove todos os quatérnios da lista */
   void removeAllQuatern();

   /** Retorna o quatérnio do nó na posição qPos
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param q [out] quatérnio retornado
   * @return false se qPos for inválido
   */
   bool getQuatern(int qPos, AlgQuatern *q);

   /** Retorna o quatérnio (angle,axis) do nó na posição qPos
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param angle [out] ângulo de rotação
   * @param axisx [out] coordenada x do eixo de rotação 
   * @param axisy [out] coordenada y do eixo de rotação 
   * @param axisz [out] coordenada z do eixo de rotação 
   * @return false se qPos for inválido
   */
   bool getQuatern(int qPos, float *angle, float *axisx, float *axisy, float *axisz);

   /** Retorna o quatérnio (angle,axis) do nó na posição qPos
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param angle [out] ângulo de rotação
   * @param axis  [out] eixo de rotação
   * @return false se qPos for inválido
   */
   bool getQuatern(int qPos, float *angle, AlgVector *axis);

   /** Retorna o quatérnio do nó na posição qPos como uma matriz de rotação formada pelas linhas u,v,w
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param u [in] primeira linha da matriz de rotação
   * @param v [in] segunda linha da matriz de rotação
   * @param w [in] terceira linha da matriz de rotação
   * @return false se qPos for inválido
   */
   bool getQuatern(int qPos, AlgVector *u, AlgVector *v, AlgVector *w);

   /** Retorna o quatérnio do nó na posição qPos em seu formato puro [w,x,y,z]
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return false se qPos for inválido
   */
   bool getQuaternRaw(int qPos, float *w, float *x, float *y, float *z);


   /** Retorna o quatérnio q do ponto parametrizado por s
   * @param s [in] posição parametrizada.  Números negativos correspondem a ordem inversa
   * @param q [out] quatérnio retornado
   * @return false se o segmento não existir.
   */
   bool getQuatern(float s, AlgQuatern *q);

   /** Retorna o quatérnio (angle,axis) do ponto parametrizado por s
   * @param s [in] posição parametrizada.  Números negativos correspondem a ordem inversa
   * @param angle [out] ângulo de rotação
   * @param axisx [out] coordenada x
   * @param axisy [out] coordenada y
   * @param axisz [out] coordenada z
   * @return false se o segmento não existir.
   */
   bool getQuatern(float s, float *angle, float *axisx, float *axisy, float *axisz);

   /** Retorna o quatérnio (angle,axis) do ponto parametrizado por s
   * @param s [in] posição parametrizada.  Números negativos correspondem a ordem inversa
   * @param angle [out] ângulo de rotação
   * @param axis [out] eixo de rotação
   * @return false se o segmento não existir.
   */
   bool getQuatern(float s, float *angle, AlgVector *axis);

   /** Retorna o quatérnio do ponto parametrizado por s, na forma de uma matriz de rotação formada pelas linhas u,v,w
   * @param s [in] posição parametrizada.  Números negativos correspondem a ordem inversa
   * @param u [in] primeira linha da matriz de rotação
   * @param v [in] segunda linha da matriz de rotação
   * @param w [in] terceira linha da matriz de rotação
   * @return false se o segmento não existir.
   */
   bool getQuatern(float s, AlgVector *u, AlgVector *v, AlgVector *w);

   /** Retorna o quatérnio do ponto parametrizado por s no seu formato puro [w,x,y,z]
   * @param s [in] posição parametrizada.  Números negativos correspondem a ordem inversa
   * @return false se o segmento não existir.
   */
   bool getQuaternRaw(float s, float *w, float *x, float *y, float *z);
   
   /** Define uma novo quatérnio q para a posição qPos
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param q [in] quatérnio
   * @return false se qPos for inválido
   */
   bool setQuatern(int qPos, const AlgQuatern &q);

   /** Define uma novo quatérnio (angle,axis) para a posição qPos
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param angle [in] ângulo de rotação
   * @param axisx [in] coordenada x do eixo de rotação 
   * @param axisy [in] coordenada y do eixo de rotação 
   * @param axisz [in] coordenada z do eixo de rotação 
   * @return false se qPos for inválido
   */
   bool setQuatern(int qPos, float v, float x, float y, float z);

   /** Define uma novo quatérnio (angle,axis) para a posição qPos
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param angle [in] ângulo de rotação
   * @param axis [in] eixo de rotação 
   * return false se qPos for inválido
   */
   bool setQuatern(int qPos, float v, const AlgVector &axis);
   
   /** Define uma novo quatérnio para a posição qPos a partir de uma matriz de rotação formada pelas linhas u,v,w
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @param u [in] primeira linha da matriz de rotação
   * @param v [in] segunda linha da matriz de rotação
   * @param w [in] terceira linha da matriz de rotação
   * return false se qPos for inválido
   */
   bool setQuatern(int qPos, const AlgVector &u, const AlgVector &v, const AlgVector &w);

   /** Define uma novo quatérnio para a posição qPos no seu estado puro [w,x,y,z]
   * @param qPos [in] posição na lista, onde números negativos correspondem a ordem inversa
   * @return false se qPos for inválido
   */
   bool setQuaternRaw(int qPos, float w, float x, float y, float z);

   /** Número de quatérios na lista
   * @return número de quatérnios na lista
   */
   int getSize();

   /** Retorna se a lista é fechada
   * @return se a lista é fechada
   */
   bool getClose();

   /** Define se a lsita deve ser fechada
   * @param close se a lista deve ser fechada
   */
   void setClose(bool close);

   /** Retorna o tipo de interpolação utilizada
   * @return interpolação atual
   */
   Interpolation getInterpolation();

   /** Define qual interpolação utilizar
   * @param interp [in] interpolação a ser utilizada
   */
   void setInterpolation(Interpolation interp);

   bool load(FILE *fp);
   bool save(FILE *fp);
   void save(UtlWriter *writer);

private:
   static int m_nextid;
   int m_id;

   AlgQuaternPArray m_qArray; ///< lista de quatérnios
   int m_nQuat;            ///< número de quatérnios
   bool m_close;           ///< lista fechada ou não
   Interpolation m_interp; ///< interpolação utilizada
};

#endif
