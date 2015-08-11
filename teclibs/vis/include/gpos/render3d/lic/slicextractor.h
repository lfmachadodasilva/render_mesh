#ifndef SLICEXTRACTOR_H
#define SLICEXTRACTOR_H

/***************************************************************************
*  $MCI M�dulo de defini��o: SLicExtractor  Extrator de Superf�cie para Lic
*
*  Arquivo gerado:      slicextractor.h
*  Classe:				      SLicExtractor
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   07/fev/2011 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Classe que constr�i objetos LicGeom a partir de superf�cies de um
*     modelo de reservat�rio
*
***************************************************************************/

#include <gpos/model/modelnew.h>
#include <alg/matrix.h>
#include <alg/vector.h>

#include <gpos/render2d/lic/licextractor.h>
#include "slicgeom.h"

class SLicExtractor : public LicExtractor {
private:

  // �ltimo modelo processado
  ResModelNew * lastModel;

  // Id de V�rtices para desenho da Camada I
  unsigned int * vertexIdListI;

  // Id de V�rtices para desenho da Camada J
  unsigned int * vertexIdListJ;

  // Coordenadas de v�rtice do centro da camada K
  float * vertexCoordK;
  
  // Coordenadas de v�rtice do centro da camada I
  float * vertexCoordI;

  // Coordenadas de v�rtice do centro da camada J
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

  // L� informa��es gerais de modelo
  virtual void ReadHeader(ResModelNew * model);

  // L� conte�do das c�lulas de um c�lulas. Timestep indica qual step deve ser
  // processado. -1 indica que todos os timesteps ser�o processados.
  virtual void ReadCells(ResModelNew * model, int propX, int propY, int propZ, int timestep);

  // Processa Vetores de um Timestep
  virtual void ProcessTimestep(int t);

  // Processa um Timestep de um mapa de satura��o
  virtual void ProcessSaturation (int t);

  // Faz liga��o com um objeto de geometria. Caso seja NULL, desliga liga��o.
  virtual void LinkGeometry(LicGeom * geom);

  // Constr�i dados de campo vetorial no centro da geometria
  void BuildCenterTimestep(ResModelNew * model);

  // Constr�i geometria no centro das c�lulas
  void BuildCenterGeometry(ResModelNew * model);

  // Constr�i Normais a partir de v�rtices em vert e armazena em list
  void BuildNormals(float * list, int * vert);

public:

	// Construtor Padr�o
  SLicExtractor();

	// Destrutor
  virtual ~SLicExtractor();

};

#endif

