#ifndef LICEXTRACTOR_H
#define LICEXTRACTOR_H

/***************************************************************************
*  $MCI Módulo de definição: LicExtractor  Extrator de Informações para LIC
*
*  Arquivo gerado:      licextractor.h
*  Classe:				LicExtractor
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   29/set/2010 início desenvolvimento
*
*  $ED Descrição do módulo
*     Classe que constrói objetos LicGeom a partir de modelos de reservatório
*
***************************************************************************/

#include <gpos/model/modelnew.h>
#include <alg/matrix.h>
#include <alg/vector.h>

#include "licgeom.h"

class LicExtractor {
protected:
	// Último Objeto de Geometria Construído
	LicGeom * lastGeom;

  // Valor de PI
  double const m_pi;

	// Quantidade de células em i (Width de cada campo vetorial)
	int ni;

	// Quantidade de células em j (Height de cada campo vetorial)
	int nj;

	// Quantidade de células em k (Profundidade)
	int nk;

	// Quantidade de células no tempo
	int nt;

	// Quantidade de vértices
	int nv;

  // Escala a ser aplicada nos vetores do modelo
  float modelScale[3];

  // Indica qual das 3 componentes (IJK) representa o Z da imagem
  int depthId;

  // Indica se o LicGeom corrente constrói Gradientes
  bool isGradient;

  // Indica se LicGeom corrente constrói Mapa de Saturação
  bool isSaturation;

	// Ponteiro para Posição dos Vértices em um LicGeom
	float * vertexCoord;

  // Ponteiro para Normal dos Vértices em um LicGeom
	float * vertexNormal;

  // Indica se Eixo Y está orientado para cima (false) ou para baixo (true)
  bool yInverted;

  // Indica se Eixo Z está invertido
  bool zInverted;

	// Ponteiro para Campo Vetorial em um LicGeom
	float * vertexVec;

	// Ponteiro para Magnitude em um LicGeom
	float * vertexTexCoord;

  // Ponteiro para Magnitude Original em um LicGeom
	float * vertexMag;

	// Magnitude mínima em cada timestep
	float * minMag;

	// Magnitude máxima em cada timestep
	float * maxMag;

	// Valor mínimo da componente Z em cada timestep
	float * minZVal;

	// Valor máximo da componente Z em cada timestep
	float * maxZVal;

	// Indica valor mínimo e máximo de uma escala ad hoc de magnitude
	float magScale[2];

  // Indica valor mínimo e máximo de uma escala ad hoc de valor de Z
	float zScale[2];

	// Ponteiro para Limites de Tela em um LicGeom
	float * screenLimits;

	// Ponteiro para lista de índices de vértice em LicGeom
	unsigned int * vertexIdList;

  // Faz ligação com um objeto de geometria. Caso seja NULL, desliga ligação.
  virtual void LinkGeometry(LicGeom * geom);

	// Lê informações gerais de modelo
	virtual void ReadHeader(ResModelNew * model);

	// Lê conteúdo das células de um células. Timestep indica qual step deve ser
  // processado. -1 indica que todos os timesteps serão processados.
	virtual void ReadCells(ResModelNew * model, int propX, int propY, int propZ, int timestep);

  // Processa Vetores de um Timestep
  virtual void ProcessTimestep(int t);

  // Processa um Timestep de um mapa de saturação
  virtual void ProcessSaturation (int t);

  // Atribui um valor correspondente a val numa escala linear em [Min,Max].
  float Interpolate(const float & val, const float & min, const float & max);

public:

	// Construtor Padrão
	LicExtractor();

	// Destrutor
	virtual ~LicExtractor();

	// Constrói um LicGeom a partir de um modelo e 3 propriedades, correspondente a XYZ
	// Caso alguma propriedade seja inválida ou NULL, considera que os valores da componente são sempre 0
  // Caso timestep seja inválido, não constrói timestep algum.
	LicGeom * BuildGeometry(ResModelNew * model, const char * propX, const char * propY, const char * propZ, int timestep = 0);

  // Constrói um LicGeom a partir de propriedades de saturação de gás, óleo e água (nesta ordem).
  // Caso timestep seja inválido, não constrói timestep algum.
  LicGeom * BuildSatGeometry(ResModelNew * model, const char * propG, const char * propO, const char * propW, int timestep = 0);

  // Constrói um timestep em uma determinada geometria a partir de um modelo
  void BuildTimestep(LicGeom * geom, ResModelNew * model, int t);

	// Retorna ponteiro para último objeto LicGeom gerado
	LicGeom * GetLastGeometry();

  // Indica qual das componentes (IJK = 012) representa a profundidade da imagem (Z)
  void SetDepthId(int id);

  // Indica se eixo Y aponta para baixo (true) ou para cima (false)
  void SetYInverted(bool inverted);

  // Ajusta escala a ser aplicada globalmente aos vetores
  void SetModelScale(float x, float y, float z) { modelScale[0] = x; modelScale[1] = y; modelScale[2] = z; }
};

#endif