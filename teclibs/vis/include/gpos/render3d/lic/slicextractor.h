#ifndef SLICEXTRACTOR_H
#define SLICEXTRACTOR_H

/***************************************************************************
*  $MCI Módulo de definição: SLicExtractor  Extrator de Superfície para Lic
*
*  Arquivo gerado:      slicextractor.h
*  Classe:				      SLicExtractor
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   07/fev/2011 início desenvolvimento
*
*  $ED Descrição do módulo
*     Classe que constrói objetos LicGeom a partir de superfícies de um
*     modelo de reservatório
*
***************************************************************************/

#include <gpos/model/modelnew.h>
#include <alg/matrix.h>
#include <alg/vector.h>

#include <gpos/render2d/lic/licextractor.h>
#include "slicgeom.h"

class SLicExtractor : public LicExtractor {
private:

  // Último modelo processado
  ResModelNew * lastModel;

  // Id de Vértices para desenho da Camada I
  unsigned int * vertexIdListI;

  // Id de Vértices para desenho da Camada J
  unsigned int * vertexIdListJ;

  // Coordenadas de vértice do centro da camada K
  float * vertexCoordK;
  
  // Coordenadas de vértice do centro da camada I
  float * vertexCoordI;

  // Coordenadas de vértice do centro da camada J
  float * vertexCoordJ;

  // Normais do centro da camada K
  float * vertexNormalMidK;

  // Campo vetorial no centro da camada K
  float * vertexVecK;

  // Campo vetorial no centro da camada I
  float * vertexVecI;

  // Campo vetorial no centro da camada J
  float * vertexVecJ;

  // Normais da Camada I
  float * vertexNormalI;

  // Normais da Camada J
  float * vertexNormalJ;

  // Lê informações gerais de modelo
  virtual void ReadHeader(ResModelNew * model);

  // Lê conteúdo das células de um células. Timestep indica qual step deve ser
  // processado. -1 indica que todos os timesteps serão processados.
  virtual void ReadCells(ResModelNew * model, int propX, int propY, int propZ, int timestep);

  // Processa Vetores de um Timestep
  virtual void ProcessTimestep(int t);

  // Processa um Timestep de um mapa de saturação
  virtual void ProcessSaturation (int t);

  // Faz ligação com um objeto de geometria. Caso seja NULL, desliga ligação.
  virtual void LinkGeometry(LicGeom * geom);

  // Constrói dados de campo vetorial no centro da geometria
  void BuildCenterTimestep(ResModelNew * model);

  // Constrói geometria no centro das células
  void BuildCenterGeometry(ResModelNew * model);

  // Constrói Normais a partir de vértices em vert e armazena em list
  void BuildNormals(float * list, int * vert);

public:

	// Construtor Padrão
  SLicExtractor();

	// Destrutor
  virtual ~SLicExtractor();

};

#endif

