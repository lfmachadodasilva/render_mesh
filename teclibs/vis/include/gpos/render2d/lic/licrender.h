#ifndef LICRENDER_H
#define LICRENDER_H

/***************************************************************************
*  $MCI M�dulo de defini��o: LicRender  Renderizador de LIC
*
*  Arquivo gerado:      licrender.h
*  Classe:				LicRender
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   29/set/2010 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Renderizador para a biblioteca de LIC
*
***************************************************************************/

#include <lic/image.h>
#include <lic/evaluator.h>

#include "licgeom.h"

using namespace Lic;

class LicRender {

private:

	// Profundidade corrente do modelo
	int currK;

	// Vetor com Janela de desenho de LIC. XYWH.
	// XY indica canto superior esquerdo e WH dimens�es da janela
	int drawRect[4];

	// Geometria associada ao Render
	LicGeom * licGeom;

	// Avaliador de LIC corrente
	Evaluator * evaluator;

	// Imagem de Campo Vetorial
	Image * vectorImage;

	// Imagem de Magnitude
	Image * magnitudeImage;

	// Imagem de White Noise
	Image * noiseImage;

  // Indica se deve haver um offset na imagem de textura
  // de acordo com a matriz de proje��o corrente
  bool shouldOffsetNoise;

	// Imagem de Textura 1D para colora��o
	Image * colorTexture;

	// Indica se campo deve ser colorido
	bool shouldPaint;

	// Indica se anima��o est� sendo feita
	bool isAnimating;

	// Valor da constante C para anima��o
	float hanningC;

	// Valor da constante D para anima��o
	float hanningD;

	// Valor do step B para anima��o por segundo.
	float animB;

	// B corrente da anima��o
	float animCurrB;

	// Valor de L da anima��o
	float animL;

  // Acumulador de Tempo para C�lculo de Step de Anima��o
  double accTime;

	// Reconstr�i Evaluator
	void BuildEvaluator();

  // Prepara Desenho em Tela
	void PrepareDraw();

  // Obt�m offset do ponto (0,0) de acordo com a matriz ModelView corrente no OpenGL
  void GetCenterOffset(float * offX, float * offY);

public:

	// Construtor. Recebe um descritor de geometria.
	// Opcionalmente, � poss�vel informar a profundidade
	// e o timestep iniciais.
	LicRender(LicGeom * geometry, int k = 0);

	// Destrutor
	virtual ~LicRender();

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

	// Habilita pintura de magnitude usando uma textura 1D fornecida.
	// Caso textura seja NULL, � usada uma escala simples Azul-Vermelho
	// Channel indica o canal da imagem de magnitude a ser considerado (012 = RGB)
	void EnableMagnitudePainting(bool shouldPaint, Image * texture = NULL, int channel = 0);

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
