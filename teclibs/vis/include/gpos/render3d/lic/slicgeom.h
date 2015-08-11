#ifndef SLICGEOM_H
#define SLICGEOM_H

/***************************************************************************
*  $MCI Módulo de definição: SLicGeom  Descritor de Geometria de Superfície
*
*  Arquivo gerado:      slicgeom.h
*  Classe:				      SLicGeom
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   07/fev/2011 início desenvolvimento
*     2       tmt   02/jun/2011 mrt
*
*  $ED Descrição do módulo
*     Descritor de geometria para renderização de um campo vetorial em 
*     superfície e valores associados para uso no algoritmo de LIC.
*
***************************************************************************/

#include <gpos/render2d/lic/licgeom.h>

#include <lic/modelprocessor.h>
#include <lic/image.h>

#include <shader/glslshader.h>

class SLicGeom : public LicGeom {

private:

  // Lista de separação entre layers
  float * layerSep;

  // Lista de Layers Visíveis
  bool * layerVis;

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

  // Camada I Corrente
  int currI;

  // Camada J Corrente
  int currJ;

  // Imagem de Iluminação
  Image * colorImage;

  // Shader de Processamento de Modelo
  GLSLShader slicShader;

  // Desenha uma camada do modelo (-1 para desenhar todas)
  void DrawModel();

public:

	// Construtor. Recebe dimensões da geometria:
	// Número de células (IJK), quantidade de passos
	// no tempo e quantidade de vértices
	SLicGeom(int ni, int nj, int nk, int nt, int nv);

	// Destrutor
	virtual ~SLicGeom();

  // Retorna Array de Id de Vértices na Camada I
  unsigned int * GetVertexIdArrayI();
  
  // Retorna Array de Id de Vértices na Camada J
  unsigned int * GetVertexIdArrayJ();

  // Retorna Array de Vértices de Centro da Camada K
  float * GetVertexCoordK();

  // Retorna Array de Vértices de Centro da Camada I
  float * GetVertexCoordI();

  // Retorna Array de Vértices de Centro da Camada J
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

  // Ajusta Separação entre Camadas
  void SetLayerSeparation(const float * separation);

  // Ajusta Visibilidade de Camadas
  void SetLayerVisibility(const bool * visibility);

  // Ajusta Layer a ser renderizado (-1 para renderizar todos)
  void SetSector(int i, int j, int k);

  // Processa Modelo e Gera Imagens de entrada do LIC
  virtual bool ProcessModel();

  // Retorna Imagem de Iluminação
  virtual Image * GetColorImage();

};

#endif
