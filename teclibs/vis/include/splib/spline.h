#ifndef SPLIB_SPLINE_H
#define SPLIB_SPLINE_H

#include "defines.h"
#include <ds/array.h>
#include <alg/vector.h>
#include <utl/writers/lua3filewriter.h>

#define SPLINE_LINEAR 0
#define SPLINE_CUBIC 1

/** Classe que representa um nó de controle da spline */
class SPLIB_API Knot
{
public:
   Knot();
   Knot(float x, float y, float z);
   ~Knot();

   /** Copia todo o nó para um nó k */
   void clone(Knot *k);

   void save(UtlWriter *writer);
   bool save(FILE *fp);
   bool load(FILE *fp);

   AlgVector m_pos;        ///< posição 3d
   AlgVector m_ds;         ///< Vetor tangente de origem
   AlgVector m_dd;         ///< Vetor tangente de destino
   float m_tension[2];     ///< Tensão
   float m_continuity[2];  ///< Continuidade
   float m_bias[2];        ///< Polarização
   float m_length;         ///< Comprimento do início da spline até o nó
   bool m_symmetry;        ///< Simetria entre DS e DD
};

typedef DsArray<Knot*> KnotArray;

/** Classe representando uma spline */
class SPLIB_API Spline
{
private:
   static int m_nextid;
   int m_id;
   int m_nKnot;         ///< Número de nós na spline
   KnotArray m_kArray;  ///< Array com os nós da spline
   bool m_close;        ///< Indica se a spline é fechada (falso por default)
   float m_lengthTol;   ///< Tolerância para o cálculo do comprimento
   float m_loop;        ///< Coeficiente para eliminação de loops
   int m_interpolation; ///< Interpolação da spline

   /** Retorna o nó na posição kPos.
   * @param kPos [in] posição do nó retornado, onde números negativos correspondem a ordem inversa
   * @return ponteiro para o nó, ou NULL se kPos for inválido, por exemplo uma spline com 3 nós (0,1,2) e kPos > 2 ou kPos < -3
   */
   Knot *getKnot(int kPos);

   /** Acha a base hermite para uma posição parametrizada s 
   * @param s [in] posição s
   * @param h1 [out] base hermite h1
   * @param h2 [out] base hermite h2
   * @param h3 [out] base hermite h3
   * @param h4 [out] base hermite h4
   */
   void getHermite(float s, float *h1, float *h2, float *h3, float *h4);
   
   /** Acha a derivada da base hermite para um posição parametrizada s
   * @param s [in] posição s
   * @param h1 [out] derivada da base hermite h1
   * @param h2 [out] derivada da base hermite h2
   * @param h3 [out] derivada da base hermite h3
   * @param h4 [out] derivada da base hermite h4
   */
   void getHermiteDer(float s, float *h1, float *h2, float *h3, float *h4);

   /** Calcula os valores de ds e dd de k, baseado nos valores de ks (antecessor) e kd (sucessor).
   * @param k [in|out] nó que terá seus valores ds e dd alterados
   * @param ks [in] nó anterior a k
   * @param kd [in] nó posterior a k
   */
   void setKnotTangent(Knot *k, Knot *ks, Knot *kd);

   /** Calcula os valor de ds de k, baseado nos valores de ks (antecessor) e kd (sucessor).
   * @param k [in|out] nó que terá seu valor ds alterado
   * @param ks [in] nó anterior a k
   * @param kd [in] nó posterior a k
   */
   void setKnotTangentDS(Knot *k, Knot *ks, Knot *kd);

   /** Calcula os valor de ds de k, baseado nos valores de ks (antecessor) e kd (sucessor).
   * @param k [in|out] nó que terá seu valor dd alterado
   * @param ks [in] nó anterior a k
   * @param kd [in] nó posterior a k
   */
   void setKnotTangentDD(Knot *k, Knot *ks, Knot *kd);

   /** Calcula o comprimento do início da spline até o nó k, baseado no comprimento de ks (antecessor)
   * @param k [in|out] nó que terá seu comprimento alterado
   * @param ks [in] nó anterior a k que serve como referência para o calculo do comprimento de k
   */
   void setKnotLength(Knot *k, Knot *ks);

   /** Calcula o comprimento de uma bezier
   * @param p1 [in] nó inicial da bezier
   * @param p2 [in] ponto de controle de p1
   * @param p3 [in] ponto de controle de p4
   * @param p4 [in] nó final da bezier
   * @param tol [in] tolerancia para o teste de parada da subdivisão da bezier
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

   /** Retorna a posição paramétrica e o segmento que está à um comprimento length do início da spline
   * @param [in] length comprimento que se deseja achar a parametrização
   * @param [out] seg segmento da spline em que a posição parametrica se encontra
   * @param [out] s posição paramétrica encontrada
   * @return false se length for maior que o comprimento da spline
   */
   bool getParametric(float length, int *seg, float *s);

   /** Retorna a posição paramétrica s que contém um comprimento length do início da spline
   * @param [in] seg segmento dos pontos
   * @param [in] s0 posição paramétrica inicial
   * @param [in] s2 posição paramétrica final
   * @param [in] s0len comprimento na posição s0
   * @param [in] length comprimento desejado
   * @param [out] s posição paramétrica resultante
   * @param [out] slen comprimento de s encontrado
   * @param [in] sinoidal indica se a curva pode ter um formato senoidal
   * @return true se ja encontrou a posição
   */
   bool getParametric(int seg, float s0, float s2, float s0len, float length, float *s, float *slen, bool sinoidal = false);

   /** Acha o parâmetro de bias e tension para um respectivo ds.
   * Continuity é considerado como tendo valor 0
   * @param P0 [in] posição do nó anterior
   * @param P1 [in] posição do nó
   * @param P2 [in] posição do nó posterior
   * @param DS [in] tangente para se encontrar os parâmetros
   * @param bias [out] parâmetro encontrado
   * @param tension [out] parâmetro encontrado
   */
   static void getBiasTensionDS(AlgVector &P0, AlgVector &P1, AlgVector &P2, AlgVector &DS, float *bias, float *tension);

   /** Acha o parâmetro de bias e tension para um respectivo dd.
   * Continuity é considerado como tendo valor 0
   * @param P0 [in] posição do nó anterior
   * @param P1 [in] posição do nó
   * @param P2 [in] posição do nó posterior
   * @param DS [in] tangente para se encontrar os parâmetros
   * @param bias [out] parâmetro encontrado
   * @param tension [out] parâmetro encontrado
   */
   static void getBiasTensionDD(AlgVector &P0, AlgVector &P1, AlgVector &P2, AlgVector &DD, float *bias, float *tension);

public:

   /** Construtor */
   Spline();

   /** Destrutor */
   ~Spline();

   int getId(){return m_id;};

   /** Adiciona um nó na posição x,y,z na posição kPos da lista de pontos da spline (último por default).
   * O nó adicionado na posição p (independente da ordem), move todos os nós a partir de p para o final da spline.
   * @param x [in] coordenada x
   * @param y [in] coordenada y
   * @param z [in] coordenada z
   * @kPos [in] posição na spline, onde números negativos correspondem a ordem inversa
   * @return false se kPos for inválido, por exemplo uma spline com 3 nós (0,1,2) e kPos > 3 ou kPos < -4
   */
   bool addKnot(float x, float y, float z, int kPos = -1);

   /** Adiciona um nó no ponto parametrizado por s no segmento seg
   * O nó adicionado no comprimento x (independente da ordem), move todos os nós a partir de x para o final da spline.
   * @param s [in] posição parametrizada da curva. Números negativos correspondem a ordem inversa
   * @return false se o segmento de reta não existir ou se s não ertencer ao intervalo [0,1].
   */
   bool addKnot(float s);

   /** Adiciona um nó de acordo com o comprimento da spline
   * O nó adicionado no comprimento x (independente da ordem), move todos os nós a partir de x para o final da spline.
   * @param length [in] comprimento da origem da spline até o nó, valores negativos correspondem a comprimentos a partir do final da spline
   * @return false se length for maior que o comprimento da spline
   */
   bool addKnotLen(float length);

   /** Remove o nó kPos da spline
   * @param kPos [in] posição do nó a ser removido, onde números negativos correspondem a ordem inversa
   * @return retorna false se kPos for inválido, por exemplo uma spline com 3 nós (0,1,2) e kPos > 2 ou kPos < -3
   */
   bool removeKnot(int kPos);

   /** Remove todos os nós da spline */
   void removeAllKnot();

   /** Retorna o número de nós na spline
   * @return número de nós na spline
   */
   int getKnotSize();
   
   /** Retorna a posição (x,y,z) do nó na posição kPos
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param x [out] coordenada x
   * @param y [out] coordenada y
   * @param z [out] coordenada z
   * return false se kPos for inválido
   */
   bool getKnotPosition(int kPos, float *x, float *y, float *z);

   /** Define uma nova posição (x,y,z) para o nó na posição kPos
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param x [in] coordenada x
   * @param y [in] coordenada y
   * @param z [in] coordenada z
   * return false se kPos for inválido
   */
   bool setKnotPosition(int kPos, float x, float y, float z);

   /** Atualiza as tangentes do nó na posição kPos
   * @param kPos [in] posição do nó atualizado, o uso de números negativos NÃO corresponde a ordem inversa e resulta em resultados inesperados
   * @param side o que atualizar: -1 para ds; 0 para ds e dd; 1 para dd
   */
   void updateKnotTangent(int kPos, int side = 0);

   /** Atualiza o comprimento de toda a spline */
   void updateKnotLen();

   /** Atualiza o comprimento da spline considerando que houve uma mudança no nó de posição kPos
   * @param kPos [in] nó que houve mudança de parâmetros e portanto ocorreu variações na spline em suas redondezas, números negativos correspondem a ordem inversa.
   */
   void updateKnotLen(int kPos);

   /** Retorna a posição xyz do ponto parametrizado por s
   * @param s [in] posição parametrizada da curva.  Números negativos correspondem a ordem inversa
   * @param x [out] coordenada x
   * @param y [out] coordenada y
   * @param z [out] coordenada z
   * @return false se o segmento de reta não existir.
   */
   bool getPosition(float s, float *x, float *y, float *z);

   /** Retorna a posição xyz do ponto no comprimento length 
   * @param length [in] comprimento desejado para a localização do ponto.  Valores negativos correspondem a ordem inversa da spline
   * @param x [out] coordenada x
   * @param y [out] coordenada y
   * @param z [out] coordenada z
   * @return false se length for maior que o comprimento da spline
   */
   bool getPositionLen(float length, float *x, float *y, float *z);

   /** Retorna a tangente no ponto xyz do ponto parametrizado por s
   * @param s posição [in] parametrizada da curva.  Números negativos correspondem a ordem inversa
   * @param x [out] coordenada x do vetor tangente
   * @param y [out] coordenada y do vetor tangente
   * @param z [out] coordenada z do vetor tangente
   * @return false se o segmento de reta não existir.
   */
   bool getTangent(float s, float *x, float *y, float *z);

   /** Retorna a tangente no ponto xyz no comprimento length 
   * @param length [in] comprimento desejado para a localização do ponto.  Valores negativos correspondem a ordem inversa da spline
   * @param x [out] coordenada x do vetor tangente
   * @param y [out] coordenada y do vetor tangente
   * @param z [out] coordenada z do vetor tangente
   * @return false se length for maior que o comprimento da spline
   */
   bool getTangentLen(float length, float *x, float *y, float *z);

   /** Retorna o comprimento de um segmento da spline partindo do nó kStart até o nó kEnd.
   * Valores negativos correspondem a ordem inversa.
   * Se a spline for aberta e kStart > kEnd, o resultado é o caminho inverso (kEnd à kStart)
   * @param kStart [in] nó ínicial (0 por default)
   * @param kEnd [out] nó final (-1 por default)
   * @return comprimento do segmento da spline, ou -1 caso kStart ou kEnd sejam inválidos
   */
   float getLen(int kStart = 0, int kEnd = -1);

   /** retorna o comprimento desde o início da spline do ponto parametrizado por s no segmento seg
   * @param s [in] posição parametrizada da curva.  Números negativos correspondem a ordem inversa
   * @return comprimento do início da spline ao ponto s
   */
   float getLen(float s);

   /** Retorna a simetria de uma nó na posição kPos
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param sym [out] se o nó é simétrio
   * @return false se kPos for inválido
   */
   bool getKnotSymmetry(int kPos, bool *sym);

   /** Define a simetria de um nó
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param sym [in] se o nó deve ser simétrico
   * @return false se kPos for inválido
   */
   bool setKnotSymmetry(int kPos, bool sym);

   /** Retorna se a spline é fechada
   * @return se a spline é fechada
   */
   bool getClose(){return m_close;};

   /** Define se a spline deve ser fechada
   * @param close se a spline deve ser fechada
   */
   void setClose(bool close);

   /** Define a tolerância para o cálculo do comprimento.
   * A alteração desse valor implica numa atualização do comprimento de toda a spline
   * @param tol [in] tolerância para o cálculo do comprimento da spline
   */
   void setLenTol(float tol);

   /** Retorna a tolerância para o cálculo do comprimento
   * @return tolerância para o cálculo do comprimento da spline
   */
   float getLenTol(){return m_lengthTol;};


   void setLoop(float loop){m_loop = loop;};
   float getLoop(){return m_loop;};

   /** Retorna a tensão do nó kPos no lado side.
   * Se side=0 será retornado dois floats em tension[0] e tension[1]
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param tension [out] tensão na posição kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inválido
   */
   bool getKnotTension(int kPos, float *tension, int side=0);

   /** define a tensão do nó kPos no lado side.
   * Se side=0 será o mesmo valor de tension é definido para os dois lados
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param tension [in] tensão para a posição kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inválido
   */
   bool setKnotTension(int kPos, float tension, int side=0);

   /** Retorna a continuidade do nó kPos no lado side.
   * Se side=0 será retornado dois floats em continuity[0] e continuity[1]
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param continuity [out] continuidade na posição kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inválido
   */
   bool getKnotContinuity(int kPos, float *continuity, int side=0);

   /** define a continuidade do nó kPos no lado side.
   * Se side=0 será o mesmo valor de continuity é definido para os dois lados
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param continuity [in] continuidade para a posição kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inválido
   */
   bool setKnotContinuity(int kPos, float continuity, int side=0);

   /** Retorna o bias do nó kPos no lado side.
   * Se side=0 será retornado dois floats em bias[0] e bias[1]
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param bias [out] bias na posição kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inválido
   */
   bool getKnotBias(int kPos, float *bias, int side=0);

   /** define o bias do nó kPos no lado side.
   * Se side=0 será o mesmo valor de bias é definido para os dois lados
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param bias [in] bias para a posição kPos
   * @param side lado desejado, onde -1(ds), 0(ds e dd), 1(dd)
   * @return false se kPos for inválido
   */
   bool setKnotBias(int kPos, float bias, int side=0);

   /** Retorna o valor de DS do nó na posição kPos
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param x [out] coordenada x de DS
   * @param y [out] coordenada y de DS
   * @param z [out] coordenada z de DS
   * @return false se kPos for inválido
   */
   bool getKnotDS(int kPos, float *x, float *y, float *z);

   /** Define um novo valor para DS do nó na posição kPos.
   * Se estiver sendo utilizado algum método que tenha relação com o comprimento da spline, 
   * será necessário fazer uma chamada ao método updateKnotLen(kPos) para atualizar o comprimento da spline
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param x [in] coordenada x de DS
   * @param y [in] coordenada y de DS
   * @param z [in] coordenada z de DS
   * @return false se kPos for inválido
   */
   bool setKnotDS(int kPos, float x, float y, float z);

   /** Retorna o valor de DD do nó na posição kPos
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param x [out] coordenada x de DD
   * @param y [out] coordenada y de DD
   * @param z [out] coordenada z de DD
   * @return false se kPos for inválido
   */
   bool getKnotDD(int kPos, float *x, float *y, float *z);

   /** Define um novo valor para DD do nó na posição kPos.
   * Se estiver sendo utilizado algum método que tenha relação com o comprimento da spline, 
   * será necessário fazer uma chamada ao método updateKnotLen(kPos) para atualizar o comprimento da spline
   * @param kPos [in] posição do nó, onde números negativos correspondem a ordem inversa
   * @param x [in] coordenada x de DD
   * @param y [in] coordenada y de DD
   * @param z [in] coordenada z de DD
   * @return false se kPos for inválido
   */
   bool setKnotDD(int kPos, float x, float y, float z);

   /** Elimina curvas muito acentuadas alterando o valor de tensão dos nós da spline */
   void eliminateLoops();

   /** Elimina curva acentuada no segmento seg
   * @param seg [in] segmento da spline, onde números negativos correspondem a ordem inversa
   */
   void eliminateLoops(int seg);

   int getInterpolation(){return m_interpolation;};
   void setInterpolation(int interpolation);
   void save(UtlWriter *writer);
   bool save(FILE *fp);
   bool load(FILE *fp);
};

#endif
