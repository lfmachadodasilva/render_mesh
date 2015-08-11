#ifndef LICRENDER_H
#define LICRENDER_H

/***************************************************************************
*  $MCI Módulo de definição: LicRender  Renderizador de LIC
*
*  Arquivo gerado:      licrender.h
*  Classe:				LicRender
*
*  Projeto: ResRender
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   29/set/2010 início desenvolvimento
*
*  $ED Descrição do módulo
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
	// XY indica canto superior esquerdo e WH dimensões da janela
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
  // de acordo com a matriz de projeção corrente
  bool shouldOffsetNoise;

	// Imagem de Textura 1D para coloração
	Image * colorTexture;

	// Indica se campo deve ser colorido
	bool shouldPaint;

	// Indica se animação está sendo feita
	bool isAnimating;

	// Valor da constante C para animação
	float hanningC;

	// Valor da constante D para animação
	float hanningD;

	// Valor do step B para animação por segundo.
	float animB;

	// B corrente da animação
	float animCurrB;

	// Valor de L da animação
	float animL;

  // Acumulador de Tempo para Cálculo de Step de Animação
  double accTime;

	// Reconstrói Evaluator
	void BuildEvaluator();

  // Prepara Desenho em Tela
	void PrepareDraw();

  // Obtém offset do ponto (0,0) de acordo com a matriz ModelView corrente no OpenGL
  void GetCenterOffset(float * offX, float * offY);

public:

	// Construtor. Recebe um descritor de geometria.
	// Opcionalmente, é possível informar a profundidade
	// e o timestep iniciais.
	LicRender(LicGeom * geometry, int k = 0);

	// Destrutor
	virtual ~LicRender();

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

	// Habilita pintura de magnitude usando uma textura 1D fornecida.
	// Caso textura seja NULL, é usada uma escala simples Azul-Vermelho
	// Channel indica o canal da imagem de magnitude a ser considerado (012 = RGB)
	void EnableMagnitudePainting(bool shouldPaint, Image * texture = NULL, int channel = 0);

	// Ajusta retângulo do vetor que será renderizado. 
	// XY indicam o canto inferior da imagem e WH a largura e altura.
	// O canto inferior esquerdo da imagem é (0,0).
	// Caso W ou H sejam 0, renderiza toda a imagem.
	void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

	// Ajusta dimesões de cada campo gerado
	bool SetImageResolution(int w, int h);

	// Ajusta profundidade e timestep da renderização corrente
	bool SetSector (int k);

  // Indica se deve haver um offset da textura em função da projeção
  // para preservar imagem final em caso de zoom ou pan.
  void EnableNoiseOffset(bool enable = true);
};

#endif
