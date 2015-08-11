#ifndef LIC3RENDER_H
#define LIC3RENDER_H

/***************************************************************************
*  $MCI Módulo de definição: Lic3Render  Renderizador de LIC Trifásico
*
*  Arquivo gerado:      lic3render.h
*  Classe:				      Lic3Render
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   17/jan/2011 início desenvolvimento
*
*  $ED Descrição do módulo
*     Renderizador para LIC Triplo (Gás (R) + Óleo (G) + Água (B) em única
*     imagem, utilizando saturação como peso).
*
***************************************************************************/

#include <lic/image.h>
#include <lic/evaluator.h>
#include <lic/licrender.h>

#include <shader/glslshader.h>

#include <gpos/render2d/lic/licgeom.h>
#include <gpos/render3d/lic/slicgeom.h>

using namespace Lic;

class Lic3Render {

private:

	// Seção corrente do modelo
	int currK;

  // Renderizador de Lic de Gás
  LicRender * gasRender;

  // Renderizador de Lic de Óleo
  LicRender * oilRender;

  // Renderizador de Lic de Água
  LicRender * watRender;

	// Geometria de Saturação
	LicGeom * satGeom;

  // Geometria de Gás
  LicGeom * gasGeom;

  // Geometria de Óleo
  LicGeom * oilGeom;

  // Geometria de Água
  LicGeom * watGeom;

  // Imagem de Lic de Gás
  Image * gasImage;

  // Imagem de Lic de Óleo
  Image * oilImage;

  // Imagem de Lic de Água
  Image * watImage;

	// Imagem de Saturação
	Image * satImage;

  // Shader de Processamento de Lic3
  GLSLShader lic3Shader;

  // Carrega uma Textura em um Shader
  void LoadTexture(const char * varName, GLuint texId, int texUnit, int edgeMode = GL_REPEAT, bool is2D = true);

  // Desenha Lic Triplo
  void DrawTripleLic();

  // Realiza preparação para renderização em uma Textura usando um determinado Framebuffer Object
  void PrepareTextureDraw(GLuint fb, GLuint tex);

  // Encerra renderização em Textura
  void EndTextureDraw(GLuint fb, GLuint tex);

public:

	// Construtor. Recebe um descritor de geometria de gás, óleo, água e saturação.
	Lic3Render(LicGeom * gas, LicGeom * oil, LicGeom * water, LicGeom * sat, bool isSurface = false);

	// Destrutor
	virtual ~Lic3Render();

	// Desenha LIC Estático
	void DrawStaticLic(float L);

  // Desenha LIC Estático em Textura
  Image * GenerateStaticLic(float L, Image * target = NULL);

	// Prepara Desenho de Animação
	// L é o tamanho da linha no Lic
	// B é o avanço da onda de animação por segundo. (Período = 2PI)
	void StartAnimation(float L, float B);

	// Interrompe Animação
	void StopAnimation();

	// Indica se está sendo feita animação
	bool IsAnimating();

	// Desenha um quadro da animação.
	// drawNewFrame indica se B deve ser incrementado.
  // Time é o tempo de referência corrente em segundos
	// Caso Time seja negativo, tempo é desconsiderado.
	void DrawAnimatedLic(double time = -1, bool drawNewFrame = true);

  // Desenha um quadro de animação em textura.
  Image * GenerateAnimatedLic(double time = -1, bool drawNewFrame = true, Image * target = NULL);

	// Ajusta constantes de Hanning para animação.
	void SetHanningConstants(float c, float d);

	// Ajusta retângulo do vetor que será renderizado. 
	// XY indicam o canto inferior da imagem e WH a largura e altura.
	// O canto inferior esquerdo da imagem é (0,0).
	// Caso W ou H sejam 0, renderiza toda a imagem.
	void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

	// Ajusta dimesões de cada campo gerado
	bool SetImageResolution(int w, int h);

  // Habilita ou Desabilita uso de acesso indireto a textura de noise
  // Caso esteja habilitado, utiliza os valores de RG na TexImage como
  // coordenadas para acesso.
  void EnableNoiseIndirection(bool enable = true);

  // Indica se deve haver um offset da textura em função da projeção
  // para preservar imagem final em caso de zoom ou pan.
  void EnableNoiseOffset(bool enable = true);
};

#endif
