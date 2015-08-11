#ifndef LICGEOM_H
#define LICGEOM_H

/***************************************************************************
*  $MCI Módulo de definição: LicGeom  Descritor de Geometria para LIC
*
*  Arquivo gerado:      licgeom.h
*  Classe:				      LicGeom
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   29/set/2010 início desenvolvimento
*
*  $ED Descrição do módulo
*     Descritor de geometria para renderização de um campo vetorial
*	    e valores associados para uso no algoritmo de LIC.
*
***************************************************************************/

#include <gpos/model/modelnew.h>

#include <string>
#include <lic/image.h>
#include <lic/modelprocessor.h>

#include <shader/glslshader.h>

using std::string;
using Lic::Image;
using Lic::ModelProcessor;

class LicGeom : public ModelProcessor {

private:
  // Shader de Processamento de Modelo
  GLSLShader geomShader;

  // Shader de Processamento de Gradiente
  GLSLShader gradShader;

protected:
	// Quantidade de células em i (Width de cada campo vetorial)
	int ni;

	// Quantidade de células em j (Height de cada campo vetorial)
	int nj;

	// Quantidade de células em k (Profundidade)
	int nk;

	// Quantidade de timesteps
	int nt;

	// Quantidade de vértices
	int nv;

  // Profundidade Corrente
  int currK;

  // Propriedades a que geometria corresponde
  int properties[3];

  // Indica se Y está invertido no modelo
  bool isYInverted;

  // Indica se Z está invertido no modelo
  bool isZInverted;

  // Indica se geometria representa um gradiente
  bool isGradient;

  // Indica se Geometria representa uma saturação (3 Componentes somam 1 e possuem valores em [0,1])
  bool isSaturation;

  // Indica quantidade de pixels em cada direção que são
  // avaliados para a aproximação de gradiente.
  float gradPixels;

  // Imagem de Campo Vetorial
  Image * vectorImage;

  // Imagem de Coordenada de Textura
  Image * texImage;

  // Imagem de Gradiente
  Image * gradImage;

	// Posição dos Vértices
	float * vertexCoord;

  // Normal suavizada dos vértices
  float * vertexNormal;

	// Valor do campo vetorial médio de cada vértice em um determinado tempo
	float * vertexVec;

	// Armazena Coordenadas de Textura (RG = ST) e escala arbitrária em Z (B = Z Scale)
	float * vertexTexCoord;

  // Vetor de Magnitude para Cálculo do Gradiente
  float * vertexMag;

  // Magnitude mínima em cada timestep
	float * minMag;

	// Magnitude máxima em cada timestep
	float * maxMag;

  // Indica se escala de magnitude deve ser global
  bool useGlobalScale;

  // Magnitude Global Mínima
  float globalMinMag;
  
  // Magnitude Global Máxima
  float globalMaxMag;

	// Valor mínimo da componente Z em cada timestep
	float * minZVal;

	// Valor máximo da componente Z em cada timestep
	float * maxZVal;

	// Largura de cada campo vetorial montado
	int width;

	// Altura de cada campo vetorial montado
	int height;

  // Indica qual a componente está representada em K (012 = XYZ)
  int depth;

	// Lista para renderização de Quads por profundidade
	// [v1v2v3v4v1'v2'v3'v4' K0][v1v2v3v4v1'v2'v3'v4' K1][...]
	// v corresponde a um índice de vértice válido
	unsigned int * vertexIdList;

  // Ângulo de rotação do modelo
  float modelAngle;

  // Imagem auxiliar para geração de texturas intermediárias
  Image * auxImage;

	// Processa Imagem de Magnitude (para Gradiente)
	virtual void ProcessMagImage ();

  // Processa imagem de gradiente
  virtual void ProcessGradientImage ();

  // Prepara Textura para ser usada como Target de Renderização
  void PrepareTexture(unsigned int tex);

  // Testa estado do framebuffer
  static bool TestFramebufferStatus();

public:

	// Construtor. Recebe dimensões da geometria:
	// Número de células (IJK), quantidade de passos
	// no tempo e quantidade de vértices
	LicGeom(int ni, int nj, int nk, int nt, int nv);

	// Destrutor
	virtual ~LicGeom();

  // Processa Modelo
  virtual bool ProcessModel();

  // Retorna Imagem de Campo Vetorial
  virtual Image * GetVectorImage();

  // Retorna Imagem de Textura
  virtual Image * GetTexCoordImage();

  // Ajusta Layer Corrente
  virtual void SetSector(int k);

	// Ajusta dimesões de cada campo gerado.
	// Retorna true caso o tamanho tenha sido alterado e false e false caso contrário.
	// Retorna false quando a resolução pedida é igual à corrente.
	bool SetImageResolution(int w, int h);

	// Retorna nas variáveis w e h o tamanho do campo utilizado
	void GetImageResolution(int * w, int * h);

  // Ajusta propriedades a que geometria corresponde (Id de Propriedades)
  void SetProperties(int idX, int idY, int idZ);

  // Ajusta propriedades a que geometria corresponde (Nome de Propriedades)
  void SetProperties(ResModelNew * mdl, const char * propX, const char * propY, const char * propZ);

  // Retorna propriedades a que geometria corresponde
  void GetProperties(int * idX, int * idY, int * idZ);
	
  // Indica qual componente está representada em K (XYZ = 012)
  void SetDepth(int depth);

  // Retorna Array de Coordenadas de Textura
  float * GetTexCoordArray();

  // Retorna Ponteiro para Array de Magnitude
	float * GetMagnitudeArray();

	// Retorna Ponteiro para Array Vetor
	float * GetVectorArray();

	// Retorna Ponteiro para Array de Índices de Vértice
	unsigned int * GetVertexIdArray(); 

	// Retorna Ponteiro para Array de Vértices
	float * GetVertexArray();

  // Retorna Ponteiro de Normais Suavizadas
  float * GetNormalArray();

  // Retorna ponteiro para lista de menores e maiores magnitudes por timestep
  void GetMagLimitsArrays(float ** min, float ** max);

  // Retorna ponteiro para lista de menores e maiores valores de Z por timestep
  void GetZLimitsArrays(float ** min, float ** max);

  // Ajusta Escala de Magnitude Global
  void SetGlobalMagnitude(float min, float max);

  // Retorna Escala de Magnitude Global
  void GetGlobalMagnitude(float * min, float * max);

  // Habilita Uso de Escala de Magnitude Global
  void EnableGlobalScale(bool enable = true);

	// Retorna quantidade de células em i (Width de cada campo vetorial)
	int GetNI();

	// Retorna quantidade de células em j (Height de cada campo vetorial)
	int GetNJ();

	// Retorna quantidade de células em k (Profundidade)
	int GetNK();

  // Retorna quantidade de vértices
  int GetNV();

	// Retorna quantidade de timesteps
	int GetNT();

  // Ajusta se Geometria representa ou não um Gradiente
  void SetGradient(bool isGrad);

  // Indica se Geometria representa um Gradiente (apenas valor de X)
  bool IsGradient();

  // Ajusta se Geometria representa um mapa de saturação
  void SetSaturation(bool isSat);

  // Indica se Geometria representa um mapa de saturação
  bool IsSaturation();

  // Retorna o valor máximo e mínimo de magnitude em um determinado timestep
  void GetMagnitudeLimits(int t, float * minVal, float * maxVal);

  // Retorna o valor máximo e mínimo de Z em um determinado timestep
  void GetZLimits(int t, float * minVal, float * maxVal);

  // Ajusta se Y do eixo do modelo está invertido
  void SetYInverted(bool inverted);

  // Ajusta se Z do eixo do modelo está invertido
  void SetZInverted(bool inverted);

  // Indica se Modelo possui eixo Y invertido
  bool IsYInverted();

  // Indica se Modelo possui eixo Z invertido
  bool IsZInverted();

  // Ajusta Ângulo de Rotação do Modelo (Grau)
  void SetModelAngle(float angle);

  // Retorna Ângulo de Rotação do Modelo (Grau)
  float GetModelAngle();

};

#endif
