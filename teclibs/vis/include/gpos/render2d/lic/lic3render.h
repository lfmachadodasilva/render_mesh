#ifndef LIC3RENDER_H
#define LIC3RENDER_H

/***************************************************************************
*  $MCI M�dulo de defini��o: Lic3Render  Renderizador de LIC Triplo
*
*  Arquivo gerado:      lic3render.h
*  Classe:				      Lic3Render
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   17/jan/2011 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Renderizador para LIC Triplo (G�s (R) + �leo (G) + �gua (B) em �nica
*     imagem, utilizando satura��o como peso).
*
***************************************************************************/

#include <lic/image.h>
#include <lic/evaluator.h>

#include "licgeom.h"
#include "licrender.h"

using namespace Lic;

class Lic3Render {

private:

	// Se��o corrente do modelo
	int currK;

  // Renderizador de Lic de G�s
  LicRender * gasRender;

  // Renderizador de Lic de �leo
  LicRender * oilRender;

  // Renderizador de Lic de �gua
  LicRender * watRender;

	// Geometria de Satura��o
	LicGeom * satGeom;

  // Imagem de Lic de G�s
  Image * gasImage;

  // Imagem de Lic de �leo
  Image * oilImage;

  // Imagem de Lic de �gua
  Image * watImage;

	// Imagem de Satura��o
	Image * satImage;

  // Carrega Programa de Shader
  int LoadShaderProgram();

  // Carrega Fragment Shader
  int LoadShader();

  // Carrega uma Textura em um Shader
  void LoadTexture(const char * varName, int pid, GLuint texId, int texUnit, int edgeMode = GL_REPEAT, bool is2D = true);

  // Desenha Lic Triplo
  void DrawTripleLic();

  // Realiza prepara��o para renderiza��o em uma Textura usando um determinado Framebuffer Object
  void PrepareTextureDraw(GLuint fb, GLuint tex);

  // Encerra renderiza��o em Textura
  void EndTextureDraw(GLuint fb, GLuint tex);

public:

	// Construtor. Recebe um descritor de geometria de g�s, �leo, �gua e satura��o.
	Lic3Render(LicGeom * gas, LicGeom * oil, LicGeom * water, LicGeom * sat, int k = 0);

	// Destrutor
	virtual ~Lic3Render();

	// Desenha LIC Est�tico
	void DrawStaticLic(float L);

  // Desenha LIC Est�tico em Textura
  Image * GenerateStaticLic(float L, Image * target = NULL);

	// Prepara Desenho de Anima��o
	// L � o tamanho da linha no Lic
	// B � o avan�o da onda de anima��o por segundo. (Per�odo = 2PI)
	void StartAnimation(float L, float B);

	// Interrompe Anima��o
	void StopAnimation();

	// Indica se est� sendo feita anima��o
	bool IsAnimating();

	// Desenha um quadro da anima��o.
	// drawNewFrame indica se B deve ser incrementado.
  // Time � o tempo de refer�ncia corrente em segundos
	// Caso Time seja negativo, tempo � desconsiderado.
	void DrawAnimatedLic(double time = -1, bool drawNewFrame = true);

  // Desenha um quadro de anima��o em textura.
  Image * GenerateAnimatedLic(double time = -1, bool drawNewFrame = true, Image * target = NULL);

	// Ajusta constantes de Hanning para anima��o.
	void SetHanningConstants(float c, float d);

	// Ajusta ret�ngulo do vetor que ser� renderizado. 
	// XY indicam o canto inferior da imagem e WH a largura e altura.
	// O canto inferior esquerdo da imagem � (0,0).
	// Caso W ou H sejam 0, renderiza toda a imagem.
	void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

	// Ajusta dimes�es de cada campo gerado
	bool SetImageResolution(int w, int h);

	// Ajusta profundidade e timestep da renderiza��o corrente
	bool SetSector (int k);

  // Indica se deve haver um offset da textura em fun��o da proje��o
  // para preservar imagem final em caso de zoom ou pan.
  void EnableNoiseOffset(bool enable = true);
};

#endif
