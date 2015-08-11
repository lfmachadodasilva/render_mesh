#ifndef LICEXTRACTOR_H
#define LICEXTRACTOR_H

/***************************************************************************
*  $MCI M�dulo de defini��o: LicExtractor  Extrator de Informa��es para LIC
*
*  Arquivo gerado:      licextractor.h
*  Classe:				LicExtractor
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   29/set/2010 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Classe que constr�i objetos LicGeom a partir de modelos de reservat�rio
*
***************************************************************************/

#include <gpos/model/modelnew.h>
#include <alg/matrix.h>
#include <alg/vector.h>

#include "licgeom.h"

class LicExtractor {
protected:
	// �ltimo Objeto de Geometria Constru�do
	LicGeom * lastGeom;

  // Valor de PI
  double const m_pi;

	// Quantidade de c�lulas em i (Width de cada campo vetorial)
	int ni;

	// Quantidade de c�lulas em j (Height de cada campo vetorial)
	int nj;

	// Quantidade de c�lulas em k (Profundidade)
	int nk;

	// Quantidade de c�lulas no tempo
	int nt;

	// Quantidade de v�rtices
	int nv;

  // Escala a ser aplicada nos vetores do modelo
  float modelScale[3];

  // Indica qual das 3 componentes (IJK) representa o Z da imagem
  int depthId;

  // Indica se o LicGeom corrente constr�i Gradientes
  bool isGradient;

  // Indica se LicGeom corrente constr�i Mapa de Satura��o
  bool isSaturation;

	// Ponteiro para Posi��o dos V�rtices em um LicGeom
	float * vertexCoord;

  // Ponteiro para Normal dos V�rtices em um LicGeom
	float * vertexNormal;

  // Indica se Eixo Y est� orientado para cima (false) ou para baixo (true)
  bool yInverted;

  // Indica se Eixo Z est� invertido
  bool zInverted;

	// Ponteiro para Campo Vetorial em um LicGeom
	float * vertexVec;

	// Ponteiro para Magnitude em um LicGeom
	float * vertexTexCoord;

  // Ponteiro para Magnitude Original em um LicGeom
	float * vertexMag;

	// Magnitude m�nima em cada timestep
	float * minMag;

	// Magnitude m�xima em cada timestep
	float * maxMag;

	// Valor m�nimo da componente Z em cada timestep
	float * minZVal;

	// Valor m�ximo da componente Z em cada timestep
	float * maxZVal;

	// Indica valor m�nimo e m�ximo de uma escala ad hoc de magnitude
	float magScale[2];

  // Indica valor m�nimo e m�ximo de uma escala ad hoc de valor de Z
	float zScale[2];

	// Ponteiro para Limites de Tela em um LicGeom
	float * screenLimits;

	// Ponteiro para lista de �ndices de v�rtice em LicGeom
	unsigned int * vertexIdList;

  // Faz liga��o com um objeto de geometria. Caso seja NULL, desliga liga��o.
  virtual void LinkGeometry(LicGeom * geom);

	// L� informa��es gerais de modelo
	virtual void ReadHeader(ResModelNew * model);

	// L� conte�do das c�lulas de um c�lulas. Timestep indica qual step deve ser
  // processado. -1 indica que todos os timesteps ser�o processados.
	virtual void ReadCells(ResModelNew * model, int propX, int propY, int propZ, int timestep);

  // Processa Vetores de um Timestep
  virtual void ProcessTimestep(int t);

  // Processa um Timestep de um mapa de satura��o
  virtual void ProcessSaturation (int t);

  // Atribui um valor correspondente a val numa escala linear em [Min,Max].
  float Interpolate(const float & val, const float & min, const float & max);

public:

	// Construtor Padr�o
	LicExtractor();

	// Destrutor
	virtual ~LicExtractor();

	// Constr�i um LicGeom a partir de um modelo e 3 propriedades, correspondente a XYZ
	// Caso alguma propriedade seja inv�lida ou NULL, considera que os valores da componente s�o sempre 0
  // Caso timestep seja inv�lido, n�o constr�i timestep algum.
	LicGeom * BuildGeometry(ResModelNew * model, const char * propX, const char * propY, const char * propZ, int timestep = 0);

  // Constr�i um LicGeom a partir de propriedades de satura��o de g�s, �leo e �gua (nesta ordem).
  // Caso timestep seja inv�lido, n�o constr�i timestep algum.
  LicGeom * BuildSatGeometry(ResModelNew * model, const char * propG, const char * propO, const char * propW, int timestep = 0);

  // Constr�i um timestep em uma determinada geometria a partir de um modelo
  void BuildTimestep(LicGeom * geom, ResModelNew * model, int t);

	// Retorna ponteiro para �ltimo objeto LicGeom gerado
	LicGeom * GetLastGeometry();

  // Indica qual das componentes (IJK = 012) representa a profundidade da imagem (Z)
  void SetDepthId(int id);

  // Indica se eixo Y aponta para baixo (true) ou para cima (false)
  void SetYInverted(bool inverted);

  // Ajusta escala a ser aplicada globalmente aos vetores
  void SetModelScale(float x, float y, float z) { modelScale[0] = x; modelScale[1] = y; modelScale[2] = z; }
};

#endif