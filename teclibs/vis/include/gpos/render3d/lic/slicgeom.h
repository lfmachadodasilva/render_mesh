#ifndef SLICGEOM_H
#define SLICGEOM_H

/***************************************************************************
*  $MCI M�dulo de defini��o: SLicGeom  Descritor de Geometria de Superf�cie
*
*  Arquivo gerado:      slicgeom.h
*  Classe:				      SLicGeom
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   07/fev/2011 in�cio desenvolvimento
*     2       tmt   02/jun/2011 mrt
*
*  $ED Descri��o do m�dulo
*     Descritor de geometria para renderiza��o de um campo vetorial em 
*     superf�cie e valores associados para uso no algoritmo de LIC.
*
***************************************************************************/

#include <gpos/render2d/lic/licgeom.h>

#include <lic/modelprocessor.h>
#include <lic/image.h>

#include <shader/glslshader.h>

class SLicGeom : public LicGeom {

private:

  // Lista de separa��o entre layers
  float * layerSep;

  // Lista de Layers Vis�veis
  bool * layerVis;

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

  // Camada I Corrente
  int currI;

  // Camada J Corrente
  int currJ;

  // Imagem de Ilumina��o
  Image * colorImage;

  // Shader de Processamento de Modelo
  GLSLShader slicShader;

  // Desenha uma camada do modelo (-1 para desenhar todas)
  void DrawModel();

public:

	// Construtor. Recebe dimens�es da geometria:
	// N�mero de c�lulas (IJK), quantidade de passos
	// no tempo e quantidade de v�rtices
	SLicGeom(int ni, int nj, int nk, int nt, int nv);

	// Destrutor
	virtual ~SLicGeom();

  // Retorna Array de Id de V�rtices na Camada I
  unsigned int * GetVertexIdArrayI();
  
  // Retorna Array de Id de V�rtices na Camada J
  unsigned int * GetVertexIdArrayJ();

  // Retorna Array de V�rtices de Centro da Camada K
  float * GetVertexCoordK();

  // Retorna Array de V�rtices de Centro da Camada I
  float * GetVertexCoordI();

  // Retorna Array de V�rtices de Centro da Camada J
  float * GetVertexCoordJ();

  // Retorna Array de Normais de Centro da Camada K
  float * GetNormalArrayMidK();

  // Retorna Array de Campo Vetorial de Centro da Camada K
  float * GetVectorArrayK();

  // Retorna Array de Campo Vetorial de Centro da Camada I
  float * GetVectorArrayI();

  // Retorna Array de Campo Vetorial de Centro da Camada J
  float * GetVectorArrayJ();
  
  // Retorna Array de Normais na Camada I
  float * GetNormalArrayI();
  
  // Retorna Array de Normais na Camada I
  float * GetNormalArrayJ();

  // Ajusta Separa��o entre Camadas
  void SetLayerSeparation(const float * separation);

  // Ajusta Visibilidade de Camadas
  void SetLayerVisibility(const bool * visibility);

  // Ajusta Layer a ser renderizado (-1 para renderizar todos)
  void SetSector(int i, int j, int k);

  // Processa Modelo e Gera Imagens de entrada do LIC
  virtual bool ProcessModel();

  // Retorna Imagem de Ilumina��o
  virtual Image * GetColorImage();

};

#endif
