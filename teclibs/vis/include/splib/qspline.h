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

   /** Tipo de interpola��o */
   enum Interpolation
   {
      LERP,    ///< interpola��o linear
      SLERP,   ///< interpola��o esf�rica
      SQUAD    ///< interpola��o c�bica
   };

   /** Construtor */
   QSpline();

   /** Destrutor */
   ~QSpline();
   
   int getId(){return m_id;};

   /** Adiciona o quaternio q na posi��o qPos
   * @param q [in] quat�rnio a ser adicionado
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return n�mero de quat�rnios na lista
   */
   int addQuatern(const AlgQuatern q, int qPos=-1);

   /** Adiciona um quat�rnio na posi��o qPos
   * @param angle [in] �ngulo de rota��o
   * @param axisx [in] coordenada x do eixo de rota��o 
   * @param axisy [in] coordenada y do eixo de rota��o 
   * @param axisz [in] coordenada z do eixo de rota��o 
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return n�mero de quat�rnios na lista
   */
   int addQuatern(float angle, float axisx, float axisy, float axisz, int qPos=-1);

   /** Adiciona um quat�rnio na posi��o qPos
   * @param angle [in] �ngulo de rota��o
   * @param axis [in] eixo de rota��o 
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return n�mero de quat�rnios na lista
   */
   int addQuatern(float angle, const AlgVector &axis, int qPos=-1);

   /** Adiciona um quat�rnio na posi��o qPos de acordo com a matrix de rota��o formado pelas linhas u,v,w
   * @param u [in] primeira linha da matriz de rota��o
   * @param v [in] segunda linha da matriz de rota��o
   * @param w [in] terceira linha da matriz de rota��o
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return n�mero de quat�rnios na lista
   */
   int addQuatern(const AlgVector &u, const AlgVector &v, const AlgVector &w, int qPos=-1);

   /** Adiciona um quat�rnio na posi��o qPos a partir de seus valores puros [w,x,y,z]
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return n�mero de quat�rnios na lista
   */
   int addQuaternRaw(float w, float x, float y, float z, int qPos=-1);

   /** Remove o quat�rnio na posi��o qPos da lista
   * @param qPos [in] posi��o a ser removida, onde n�meros negativos correspondem a ordem inversa
   * @return retorna false se kPos for inv�lido, por exemplo uma lista com 3 n�s (0,1,2) e qPos > 2 ou qPos < -3
   */
   bool removeQuatern(int qPos);

   /** Remove todos os quat�rnios da lista */
   void removeAllQuatern();

   /** Retorna o quat�rnio do n� na posi��o qPos
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param q [out] quat�rnio retornado
   * @return false se qPos for inv�lido
   */
   bool getQuatern(int qPos, AlgQuatern *q);

   /** Retorna o quat�rnio (angle,axis) do n� na posi��o qPos
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param angle [out] �ngulo de rota��o
   * @param axisx [out] coordenada x do eixo de rota��o 
   * @param axisy [out] coordenada y do eixo de rota��o 
   * @param axisz [out] coordenada z do eixo de rota��o 
   * @return false se qPos for inv�lido
   */
   bool getQuatern(int qPos, float *angle, float *axisx, float *axisy, float *axisz);

   /** Retorna o quat�rnio (angle,axis) do n� na posi��o qPos
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param angle [out] �ngulo de rota��o
   * @param axis  [out] eixo de rota��o
   * @return false se qPos for inv�lido
   */
   bool getQuatern(int qPos, float *angle, AlgVector *axis);

   /** Retorna o quat�rnio do n� na posi��o qPos como uma matriz de rota��o formada pelas linhas u,v,w
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param u [in] primeira linha da matriz de rota��o
   * @param v [in] segunda linha da matriz de rota��o
   * @param w [in] terceira linha da matriz de rota��o
   * @return false se qPos for inv�lido
   */
   bool getQuatern(int qPos, AlgVector *u, AlgVector *v, AlgVector *w);

   /** Retorna o quat�rnio do n� na posi��o qPos em seu formato puro [w,x,y,z]
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return false se qPos for inv�lido
   */
   bool getQuaternRaw(int qPos, float *w, float *x, float *y, float *z);


   /** Retorna o quat�rnio q do ponto parametrizado por s
   * @param s [in] posi��o parametrizada.  N�meros negativos correspondem a ordem inversa
   * @param q [out] quat�rnio retornado
   * @return false se o segmento n�o existir.
   */
   bool getQuatern(float s, AlgQuatern *q);

   /** Retorna o quat�rnio (angle,axis) do ponto parametrizado por s
   * @param s [in] posi��o parametrizada.  N�meros negativos correspondem a ordem inversa
   * @param angle [out] �ngulo de rota��o
   * @param axisx [out] coordenada x
   * @param axisy [out] coordenada y
   * @param axisz [out] coordenada z
   * @return false se o segmento n�o existir.
   */
   bool getQuatern(float s, float *angle, float *axisx, float *axisy, float *axisz);

   /** Retorna o quat�rnio (angle,axis) do ponto parametrizado por s
   * @param s [in] posi��o parametrizada.  N�meros negativos correspondem a ordem inversa
   * @param angle [out] �ngulo de rota��o
   * @param axis [out] eixo de rota��o
   * @return false se o segmento n�o existir.
   */
   bool getQuatern(float s, float *angle, AlgVector *axis);

   /** Retorna o quat�rnio do ponto parametrizado por s, na forma de uma matriz de rota��o formada pelas linhas u,v,w
   * @param s [in] posi��o parametrizada.  N�meros negativos correspondem a ordem inversa
   * @param u [in] primeira linha da matriz de rota��o
   * @param v [in] segunda linha da matriz de rota��o
   * @param w [in] terceira linha da matriz de rota��o
   * @return false se o segmento n�o existir.
   */
   bool getQuatern(float s, AlgVector *u, AlgVector *v, AlgVector *w);

   /** Retorna o quat�rnio do ponto parametrizado por s no seu formato puro [w,x,y,z]
   * @param s [in] posi��o parametrizada.  N�meros negativos correspondem a ordem inversa
   * @return false se o segmento n�o existir.
   */
   bool getQuaternRaw(float s, float *w, float *x, float *y, float *z);
   
   /** Define uma novo quat�rnio q para a posi��o qPos
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param q [in] quat�rnio
   * @return false se qPos for inv�lido
   */
   bool setQuatern(int qPos, const AlgQuatern &q);

   /** Define uma novo quat�rnio (angle,axis) para a posi��o qPos
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param angle [in] �ngulo de rota��o
   * @param axisx [in] coordenada x do eixo de rota��o 
   * @param axisy [in] coordenada y do eixo de rota��o 
   * @param axisz [in] coordenada z do eixo de rota��o 
   * @return false se qPos for inv�lido
   */
   bool setQuatern(int qPos, float v, float x, float y, float z);

   /** Define uma novo quat�rnio (angle,axis) para a posi��o qPos
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param angle [in] �ngulo de rota��o
   * @param axis [in] eixo de rota��o 
   * return false se qPos for inv�lido
   */
   bool setQuatern(int qPos, float v, const AlgVector &axis);
   
   /** Define uma novo quat�rnio para a posi��o qPos a partir de uma matriz de rota��o formada pelas linhas u,v,w
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @param u [in] primeira linha da matriz de rota��o
   * @param v [in] segunda linha da matriz de rota��o
   * @param w [in] terceira linha da matriz de rota��o
   * return false se qPos for inv�lido
   */
   bool setQuatern(int qPos, const AlgVector &u, const AlgVector &v, const AlgVector &w);

   /** Define uma novo quat�rnio para a posi��o qPos no seu estado puro [w,x,y,z]
   * @param qPos [in] posi��o na lista, onde n�meros negativos correspondem a ordem inversa
   * @return false se qPos for inv�lido
   */
   bool setQuaternRaw(int qPos, float w, float x, float y, float z);

   /** N�mero de quat�rios na lista
   * @return n�mero de quat�rnios na lista
   */
   int getSize();

   /** Retorna se a lista � fechada
   * @return se a lista � fechada
   */
   bool getClose();

   /** Define se a lsita deve ser fechada
   * @param close se a lista deve ser fechada
   */
   void setClose(bool close);

   /** Retorna o tipo de interpola��o utilizada
   * @return interpola��o atual
   */
   Interpolation getInterpolation();

   /** Define qual interpola��o utilizar
   * @param interp [in] interpola��o a ser utilizada
   */
   void setInterpolation(Interpolation interp);

   bool load(FILE *fp);
   bool save(FILE *fp);
   void save(UtlWriter *writer);

private:
   static int m_nextid;
   int m_id;

   AlgQuaternPArray m_qArray; ///< lista de quat�rnios
   int m_nQuat;            ///< n�mero de quat�rnios
   bool m_close;           ///< lista fechada ou n�o
   Interpolation m_interp; ///< interpola��o utilizada
};

#endif
