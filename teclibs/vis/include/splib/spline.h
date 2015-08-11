#ifndef SPLIB_SPLINE_H
#define SPLIB_SPLINE_H

#include "defines.h"
#include <ds/array.h>
#include <alg/vector.h>
#include <utl/writers/lua3filewriter.h>

#define SPLINE_LINEAR 0
#define SPLINE_CUBIC 1

/** Classe que representa um n� de controle da spline */
class SPLIB_API Knot
{
public:
   Knot();
   Knot(float x, float y, float z);
   ~Knot();

   /** Copia todo o n� para um n� k */
   void clone(Knot *k);

   void save(UtlWriter *writer);
   bool save(FILE *fp);
   bool load(FILE *fp);

   AlgVector m_pos;        ///< posi��o 3d
   AlgVector m_ds;         ///< Vetor tangente de origem
   AlgVector m_dd;         ///< Vetor tangente de destino
   float m_tension[2];     ///< Tens�o
   float m_continuity[2];  ///< Continuidade
   float m_bias[2];        ///< Polariza��o
   float m_length;         ///< Comprimento do in�cio da spline at� o n�
   bool m_symmetry;        ///< Simetria entre DS e DD
};

typedef DsArray<Knot*> KnotArray;

/** Classe representando uma spline */
class SPLIB_API Spline
{
private:
   static int m_nextid;
   int m_id;
   int m_nKnot;         ///< N�mero de n�s na spline
   KnotArray m_kArray;  ///< Array com os n�s da spline
   bool m_close;        ///< Indica se a spline � fechada (falso por default)
   float m_lengthTol;   ///< Toler�ncia para o c�lculo do comprimento
   float m_loop;        ///< Coeficiente para elimina��o de loops
   int m_interpolation; ///< Interpola��o da spline

   /** Retorna o n� na posi��o kPos.
   * @param kPos [in] posi��o do n� retornado, onde n�meros negativos correspondem a ordem inversa
   * @return ponteiro para o n�, ou NULL se kPos for inv�lido, por exemplo uma spline com 3 n�s (0,1,2) e kPos > 2 ou kPos < -3
   */
   Knot *getKnot(int kPos);

   /** Acha a base hermite para uma posi��o parametrizada s 
   * @param s [in] posi��o s
   * @param h1 [out] base hermite h1
   * @param h2 [out] base hermite h2
   * @param h3 [out] base hermite h3
   * @param h4 [out] base hermite h4
   */
   void getHermite(float s, float *h1, float *h2, float *h3, float *h4);
   
   /** Acha a derivada da base hermite para um posi��o parametrizada s
   * @param s [in] posi��o s
   * @param h1 [out] derivada da base hermite h1
   * @param h2 [out] derivada da base hermite h2
   * @param h3 [out] derivada da base hermite h3
   * @param h4 [out] derivada da base hermite h4
   */
   void getHermiteDer(float s, float *h1, float *h2, float *h3, float *h4);

   /** Calcula os valores de ds e dd de k, baseado nos valores de ks (antecessor) e kd (sucessor).
   * @param k [in|out] n� que ter� seus valores ds e dd alterados
   * @param ks [in] n� anterior a k
   * @param kd [in] n� posterior a k
   */
   void setKnotTangent(Knot *k, Knot *ks, Knot *kd);

   /** Calcula os valor de ds de k, baseado nos valores de ks (antecessor) e kd (sucessor).
   * @param k [in|out] n� que ter� seu valor ds alterado
   * @param ks [in] n� anterior a k
   * @param kd [in] n� posterior a k
   */
   void setKnotTangentDS(Knot *k, Knot *ks, Knot *kd);

   /** Calcula os valor de ds de k, baseado nos valores de ks (antecessor) e kd (sucessor).
   * @param k [in|out] n� que ter� seu valor dd alterado
   * @param ks [in] n� anterior a k
   * @param kd [in] n� posterior a k
   */
   void setKnotTangentDD(Knot *k, Knot *ks, Knot *kd);

   /** Calcula o comprimento do in�cio da spline at� o n� k, baseado no comprimento de ks (antecessor)
   * @param k [in|out] n� que ter� seu comprimento alterado
   * @param ks [in] n� anterior a k que serve como refer�ncia para o calculo do comprimento de k
   */
   void setKnotLength(Knot *k, Knot *ks);

   /** Calcula o comprimento de uma bezier
   * @param p1 [in] n� inicial da bezier
   * @param p2 [in] ponto de controle de p1
   * @param p3 [in] ponto de controle de p4
   * @param p4 [in] n� final da bezier
   * @param tol [in] tolerancia para o teste de parada da subdivis�o da bezier
   * @param [in] sinoidal bezier pode ter um formato senoidal
   * @return comprimento da curva
   */
   float getBezierLength(AlgVector &p1, AlgVector &p2, AlgVector &p3, AlgVector &p4, float tol, bool sinoidal = true);

   /** Retorna o comprimento da curva entre dois pontos parametrizados por s0 e s2 no segmento seg
   * @param [in] seg segmento dos pontos
   * @param [in] s0 primeiro ponto parametrizado
   * @param [in] s2 segundo ponto parametrizado
   * @param [in] sinoidal indica se a curva pode ter um formato senoidal
   * @return comprimento da curva entre os dois pontos
   */
   float getLength(int seg, float s0, float s2, bool sinoidal = false);

   /** Retorna a posi��o param�trica e o segmento que est� � um comprimento length do in�cio da spline
   * @param [in] length comprimento que se deseja achar a parametriza��o
   * @param [out] seg segmento da spline em que a posi��o parametrica se encontra
   * @param [out] s posi��o param�trica encontrada
   * @return false se length for maior que o comprimento da spline
   */
   bool getParametric(float length, int *seg, float *s);

   /** Retorna a posi��o param�trica s que cont�m um comprimento length do in�cio da spline
   * @param [in] seg segmento dos pontos
   * @param [in] s0 posi��o param�trica inicial
   * @param [in] s2 posi��o param�trica final
   * @param [in] s0len comprimento na posi��o s0
   * @param [in] length comprimento desejado
   * @param [out] s posi��o param�trica resultante
   * @param [out] slen comprimento de s encontrado
   * @param [in] sinoidal indica se a curva pode ter um formato senoidal
   * @return true se ja encontrou a posi��o
   */
   bool getParametric(int seg, float s0, float s2, float s0len, float length, float *s, float *slen, bool sinoidal = false);

   /** Acha o par�metro de bias e tension para um respectivo ds.
   * Continuity � considerado como tendo valor 0
   * @param P0 [in] posi��o do n� anterior
   * @param P1 [in] posi��o do n�
   * @param P2 [in] posi��o do n� posterior
   * @param DS [in] tangente para se encontrar os par�metros
   * @param bias [out] par�metro encontrado
   * @param tension [out] par�metro encontrado
   */
   static void getBiasTensionDS(AlgVector &P0, AlgVector &P1, AlgVector &P2, AlgVector &DS, float *bias, float *tension);

   /** Acha o par�metro de bias e tension para um respectivo dd.
   * Continuity � considerado como tendo valor 0
   * @param P0 [in] posi��o do n� anterior
   * @param P1 [in] posi��o do n�
   * @param P2 [in] posi��o do n� posterior
   * @param DS [in] tangente para se encontrar os par�metros
   * @param bias [out] par�metro encontrado
   * @param tension [out] par�metro encontrado
   */
   static void getBiasTensionDD(AlgVector &P0, AlgVector &P1, AlgVector &P2, AlgVector &DD, float *bias, float *tension);

public:

   /** Construtor */
   Spline();

   /** Destrutor */
   ~Spline();

   int getId(){return m_id;};

   /** Adiciona um n� na posi��o x,y,z na posi��o kPos da lista de pontos da spline (�ltimo por default).
   * O n� adicionado na posi��o p (independente da ordem), move todos os n�s a partir de p para o final da spline.
   * @param x [in] coordenada x
   * @param y [in] coordenada y
   * @param z [in] coordenada z
   * @kPos [in] posi��o na spline, onde n�meros negativos correspondem a ordem inversa
   * @return false se kPos for inv�lido, por exemplo uma spline com 3 n�s (0,1,2) e kPos > 3 ou kPos < -4
   */
   bool addKnot(float x, float y, float z, int kPos = -1);

   /** Adiciona um n� no ponto parametrizado por s no segmento seg
   * O n� adicionado no comprimento x (independente da ordem), move todos os n�s a partir de x para o final da spline.
   * @param s [in] posi��o parametrizada da curva. N�meros negativos correspondem a ordem inversa
   * @return false se o segmento de reta n�o existir ou se s n�o ertencer ao intervalo [0,1].
   */
   bool addKnot(float s);

   /** Adiciona um n� de acordo com o comprimento da spline
   * O n� adicionado no comprimento x (independente da ordem), move todos os n�s a partir de x para o final da spline.
   * @param length [in] comprimento da origem da spline at� o n�, valores negativos correspondem a comprimentos a partir do final da spline
   * @return false se length for maior que o comprimento da spline
   */
   bool addKnotLen(float length);

   /** Remove o n� kPos da spline
   * @param kPos [in] posi��o do n� a ser removido, onde n�meros negativos correspondem a ordem inversa
   * @return retorna false se kPos for inv�lido, por exemplo uma spline com 3 n�s (0,1,2) e kPos > 2 ou kPos < -3
   */
   bool removeKnot(int kPos);

   /** Remove todos os n�s da spline */
   void removeAllKnot();

   /** Retorna o n�mero de n�s na spline
   * @return n�mero de n�s na spline
   */
   int getKnotSize();
   
   /** Retorna a posi��o (x,y,z) do n� na posi��o kPos
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param x [out] coordenada x
   * @param y [out] coordenada y
   * @param z [out] coordenada z
   * return false se kPos for inv�lido
   */
   bool getKnotPosition(int kPos, float *x, float *y, float *z);

   /** Define uma nova posi��o (x,y,z) para o n� na posi��o kPos
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param x [in] coordenada x
   * @param y [in] coordenada y
   * @param z [in] coordenada z
   * return false se kPos for inv�lido
   */
   bool setKnotPosition(int kPos, float x, float y, float z);

   /** Atualiza as tangentes do n� na posi��o kPos
   * @param kPos [in] posi��o do n� atualizado, o uso de n�meros negativos N�O corresponde a ordem inversa e resulta em resultados inesperados
   * @param side o que atualizar: -1 para ds; 0 para ds e dd; 1 para dd
   */
   void updateKnotTangent(int kPos, int side = 0);

   /** Atualiza o comprimento de toda a spline */
   void updateKnotLen();

   /** Atualiza o comprimento da spline considerando que houve uma mudan�a no n� de posi��o kPos
   * @param kPos [in] n� que houve mudan�a de par�metros e portanto ocorreu varia��es na spline em suas redondezas, n�meros negativos correspondem a ordem inversa.
   */
   void updateKnotLen(int kPos);

   /** Retorna a posi��o xyz do ponto parametrizado por s
   * @param s [in] posi��o parametrizada da curva.  N�meros negativos correspondem a ordem inversa
   * @param x [out] coordenada x
   * @param y [out] coordenada y
   * @param z [out] coordenada z
   * @return false se o segmento de reta n�o existir.
   */
   bool getPosition(float s, float *x, float *y, float *z);

   /** Retorna a posi��o xyz do ponto no comprimento length 
   * @param length [in] comprimento desejado para a localiza��o do ponto.  Valores negativos correspondem a ordem inversa da spline
   * @param x [out] coordenada x
   * @param y [out] coordenada y
   * @param z [out] coordenada z
   * @return false se length for maior que o comprimento da spline
   */
   bool getPositionLen(float length, float *x, float *y, float *z);

   /** Retorna a tangente no ponto xyz do ponto parametrizado por s
   * @param s posi��o [in] parametrizada da curva.  N�meros negativos correspondem a ordem inversa
   * @param x [out] coordenada x do vetor tangente
   * @param y [out] coordenada y do vetor tangente
   * @param z [out] coordenada z do vetor tangente
   * @return false se o segmento de reta n�o existir.
   */
   bool getTangent(float s, float *x, float *y, float *z);

   /** Retorna a tangente no ponto xyz no comprimento length 
   * @param length [in] comprimento desejado para a localiza��o do ponto.  Valores negativos correspondem a ordem inversa da spline
   * @param x [out] coordenada x do vetor tangente
   * @param y [out] coordenada y do vetor tangente
   * @param z [out] coordenada z do vetor tangente
   * @return false se length for maior que o comprimento da spline
   */
   bool getTangentLen(float length, float *x, float *y, float *z);

   /** Retorna o comprimento de um segmento da spline partindo do n� kStart at� o n� kEnd.
   * Valores negativos correspondem a ordem inversa.
   * Se a spline for aberta e kStart > kEnd, o resultado � o caminho inverso (kEnd � kStart)
   * @param kStart [in] n� �nicial (0 por default)
   * @param kEnd [out] n� final (-1 por default)
   * @return comprimento do segmento da spline, ou -1 caso kStart ou kEnd sejam inv�lidos
   */
   float getLen(int kStart = 0, int kEnd = -1);

   /** retorna o comprimento desde o in�cio da spline do ponto parametrizado por s no segmento seg
   * @param s [in] posi��o parametrizada da curva.  N�meros negativos correspondem a ordem inversa
   * @return comprimento do in�cio da spline ao ponto s
   */
   float getLen(float s);

   /** Retorna a simetria de uma n� na posi��o kPos
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param sym [out] se o n� � sim�trio
   * @return false se kPos for inv�lido
   */
   bool getKnotSymmetry(int kPos, bool *sym);

   /** Define a simetria de um n�
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param sym [in] se o n� deve ser sim�trico
   * @return false se kPos for inv�lido
   */
   bool setKnotSymmetry(int kPos, bool sym);

   /** Retorna se a spline � fechada
   * @return se a spline � fechada
   */
   bool getClose(){return m_close;};

   /** Define se a spline deve ser fechada
   * @param close se a spline deve ser fechada
   */
   void setClose(bool close);

   /** Define a toler�ncia para o c�lculo do comprimento.
   * A altera��o desse valor implica numa atualiza��o do comprimento de toda a spline
   * @param tol [in] toler�ncia para o c�lculo do comprimento da spline
   */
   void setLenTol(float tol);

   /** Retorna a toler�ncia para o c�lculo do comprimento
   * @return toler�ncia para o c�lculo do comprimento da spline
   */
   float getLenTol(){return m_lengthTol;};


   void setLoop(float loop){m_loop = loop;};
   float getLoop(){return m_loop;};

   /** Retorna a tens�o do n� kPos no lado side.
   * Se side=0 ser� retornado dois floats em tension[0] e tension[1]
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param tension [out] tens�o na posi��o kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inv�lido
   */
   bool getKnotTension(int kPos, float *tension, int side=0);

   /** define a tens�o do n� kPos no lado side.
   * Se side=0 ser� o mesmo valor de tension � definido para os dois lados
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param tension [in] tens�o para a posi��o kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inv�lido
   */
   bool setKnotTension(int kPos, float tension, int side=0);

   /** Retorna a continuidade do n� kPos no lado side.
   * Se side=0 ser� retornado dois floats em continuity[0] e continuity[1]
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param continuity [out] continuidade na posi��o kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inv�lido
   */
   bool getKnotContinuity(int kPos, float *continuity, int side=0);

   /** define a continuidade do n� kPos no lado side.
   * Se side=0 ser� o mesmo valor de continuity � definido para os dois lados
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param continuity [in] continuidade para a posi��o kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inv�lido
   */
   bool setKnotContinuity(int kPos, float continuity, int side=0);

   /** Retorna o bias do n� kPos no lado side.
   * Se side=0 ser� retornado dois floats em bias[0] e bias[1]
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param bias [out] bias na posi��o kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inv�lido
   */
   bool getKnotBias(int kPos, float *bias, int side=0);

   /** define o bias do n� kPos no lado side.
   * Se side=0 ser� o mesmo valor de bias � definido para os dois lados
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param bias [in] bias para a posi��o kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inv�lido
   */
   bool setKnotBias(int kPos, float bias, int side=0);

   /** Retorna o valor de DS do n� na posi��o kPos
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param x [out] coordenada x de DS
   * @param y [out] coordenada y de DS
   * @param z [out] coordenada z de DS
   * @return false se kPos for inv�lido
   */
   bool getKnotDS(int kPos, float *x, float *y, float *z);

   /** Define um novo valor para DS do n� na posi��o kPos.
   * Se estiver sendo utilizado algum m�todo que tenha rela��o com o comprimento da spline, 
   * ser� necess�rio fazer uma chamada ao m�todo updateKnotLen(kPos) para atualizar o comprimento da spline
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param x [in] coordenada x de DS
   * @param y [in] coordenada y de DS
   * @param z [in] coordenada z de DS
   * @return false se kPos for inv�lido
   */
   bool setKnotDS(int kPos, float x, float y, float z);

   /** Retorna o valor de DD do n� na posi��o kPos
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param x [out] coordenada x de DD
   * @param y [out] coordenada y de DD
   * @param z [out] coordenada z de DD
   * @return false se kPos for inv�lido
   */
   bool getKnotDD(int kPos, float *x, float *y, float *z);

   /** Define um novo valor para DD do n� na posi��o kPos.
   * Se estiver sendo utilizado algum m�todo que tenha rela��o com o comprimento da spline, 
   * ser� necess�rio fazer uma chamada ao m�todo updateKnotLen(kPos) para atualizar o comprimento da spline
   * @param kPos [in] posi��o do n�, onde n�meros negativos correspondem a ordem inversa
   * @param x [in] coordenada x de DD
   * @param y [in] coordenada y de DD
   * @param z [in] coordenada z de DD
   * @return false se kPos for inv�lido
   */
   bool setKnotDD(int kPos, float x, float y, float z);

   /** Elimina curvas muito acentuadas alterando o valor de tens�o dos n�s da spline */
   void eliminateLoops();

   /** Elimina curva acentuada no segmento seg
   * @param seg [in] segmento da spline, onde n�meros negativos correspondem a ordem inversa
   */
   void eliminateLoops(int seg);

   int getInterpolation(){return m_interpolation;};
   void setInterpolation(int interpolation);
   void save(UtlWriter *writer);
   bool save(FILE *fp);
   bool load(FILE *fp);
};

#endif
