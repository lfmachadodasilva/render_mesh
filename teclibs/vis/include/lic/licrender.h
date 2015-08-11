#ifndef LICRENDER_H
#define LICRENDER_H

/***************************************************************************
*  $MCI M�dulo de defini��o: LicRender  Renderizador de LIC
*
*  Arquivo gerado:      licrender.h
*  Classe:				      LicRender
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   29/set/2010 in�cio desenvolvimento
*     2       tmt   23/mai/2011 suporte a superf�cies
*
*  $ED Descri��o do m�dulo
*     Renderizador para a biblioteca de LIC
*
***************************************************************************/

#include <string>

#include "image.h"
#include "evaluator.h"
#include "modelprocessor.h"

namespace Lic {

  class LicRender {

  private:

    // Vetor com Janela de desenho de LIC. XYWH.
    // XY indica canto superior esquerdo e WH dimens�es da janela
    int drawRect[4];

    // Largura da imagem gerada
    int width;

    // Altura da imagem gerada
    int height;

    // Indica se deve ser renderizada uma superf�cie ou um plano
    bool isSurface;

    // Indica se imagem final deve ser iluminada
    bool illuminate;

    // Modelo a ser renderizado
    ModelProcessor * model;

    // Avaliador de LIC corrente
    Evaluator * evaluator;

    // Indica se deve ser usado TwofoldLIC
    bool shouldUseTwofold;

    // Indica tamanho da streamline na segunda passada
    // do algoritmo de TwofoldLic
    float twofoldL;

    // Indica se imagem de Lic deve ser p�s-processada
    bool shouldPostProcess;

    // Indica se Evaluator deve ser reconstru�do
    bool shouldRebuildEvaluator;

    // Indica se deve haver teste de descontinuidade em Z
    bool useZTest;

    // Valor M�nimo da Escala de Magnitude
    float magMin;

    // Valor M�ximo da Escala de Magnitude
    float magMax;

    // Valor M�nimo da Escala de Z
    float zMin;

    // Valor M�ximo da Escala de Z
    float zMax;

    // Imagem de Campo Vetorial
    Image * vectorImage;

    // Imagem de Ilumina��o
    Image * colorImage;

    // Tipo de mistura da imagem de ilumina��o
    Evaluator::BlendType colorBlendType;

    // Fator para blend do tipo Mix
    float colorMixFactor;

    // Imagem de White Noise (Quadrada)
    Image * noiseImage;

    // Lado da imagem de White Noise
    int noiseSize;

    // Tamanho do pixel na imagem de White Noise
    int noisePixelWidth;

    // Indica se imagem de white noise deve ser acessado indiretamente
    bool useNoiseIndirection;

    // Imagem de Textura 
    // RG = ST para Acesso indireto a noise
    // B  = Z-Buffer
    // A  = Escala de Z
    Image * texImage;

    // Indica se deve haver um offset na imagem de textura
    // de acordo com a matriz de proje��o corrente
    bool shouldOffsetNoise;

    // Imagem de Textura 1D para colora��o
    Image * colorTexture;

    // Indica se campo deve ser colorido
    bool shouldPaint;

    // Cor para regi�es pertencentes ao modelo mas com vetores nulos
    float nullVecColor[3];

    // Indica se Z deve ser colorido no lugar da magnitude
    bool paintZ;

    // Indica se anima��o est� sendo feita
    bool isAnimating;

    // Indica se velocidade de anima��o deve variar com magnitude
    bool useVariableAnimSpeed;

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

    // Indica se Fog deve ser usado
    bool shouldUseFog;

    // Reconstr�i Evaluator
    void BuildEvaluator();

    // Prepara Desenho em Tela
    bool PrepareDraw();

    // Obt�m offset do ponto (0,0) de acordo com a matriz ModelView corrente no OpenGL
    void GetCenterOffset(float * offX, float * offY);

  public:

    // Construtor. Recebe um processador de modelo.
    // isSurface indica se deve ser usado SurfaceLIC ou
    // LIC 2D tradicional.
    LicRender(ModelProcessor * model, bool isSurface = true);

    // Destrutor
    virtual ~LicRender();

    // Ajusta escala de Magnitude
    void SetMagScale(float min, float max);

    // Ajusta escala de Z (n�o afeta paleta de cores)
    void SetZScale(float min, float max);

    // Desenha LIC Est�tico
    void DrawStaticLic(float L);

    // Desenha LIC Est�tico em Textura
    // Se target for fornecido, desenha na textura associada a ele.
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
    // Se target for fornecido, desenha na textura associada a ele.
    Image * GenerateAnimatedLic(double time = -1, bool drawNewFrame = true, Image * target = NULL);

    // Ajusta constantes de Hanning para anima��o.
    void SetHanningConstants(float c, float d);

    // Habilita pintura de magnitude usando uma textura 1D fornecida.
    // Caso textura seja NULL, � usada uma escala simples Azul-Vermelho.
    // Caso textura seja 2D, colore magnitude e z simultaneamente.
    // paintZ indica se a componente Z deve ser pintada ao inv�s da magnitude.
    void EnableColoring(bool shouldPaint, Image * texture = NULL, bool paintZ = false);

    // Indica cor assumida por regi�es do modelo com vetores nulos.
    // Estas regi�es ainda podem ser afetadas por escalas de cor.
    void SetNullVectorColor(float r, float g, float b);

    // Ajusta ret�ngulo do vetor que ser� renderizado. 
    // XY indicam o canto inferior da imagem e WH a largura e altura.
    // O canto inferior esquerdo da imagem � (0,0).
    // Caso W ou H sejam 0, renderiza toda a imagem.
    void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

    // Indica se deve haver um offset da textura em fun��o da proje��o
    // para preservar imagem final em caso de zoom ou pan.
    void EnableNoiseOffset(bool enable = true);

    // Habilita ou Desabilita uso de acesso indireto a textura de noise
    // Caso esteja habilitado, utiliza os valores de RG na TexImage como
    // coordenadas para acesso.
    void EnableNoiseIndirection(bool enable = true);

    // Habilita/desabilita teste de continuidade com buffer de z
    // � necess�rio que geometria armazene informa��o de Z-Buffer
    // no canal de cor G da imagem de coordenada de textura
    void EnableZTest(bool enable = true);

    // Habilita/desabilita ilumina��o da imagem final. N�o tem
    // efeito caso o modelo n�o produza uma imagem de cor.
    void EnableIllumination(bool enable = true);

    // Ajusta ilumina��o para ser adicionada via Mix.
    // Fator indica a propor��o de combina��o (0 = Somente Ilumina��o, 1 = Somente Lic)
    // Caso factor n�o esteja em [0,1], mix � ativado com o factor anteriormente
    // ajustado.
    void SetIlluminationMix(float factor = -1.0f);

    // Ajusta ilumina��o para ser adicionada via Multiply.
    void SetIlluminationMultiply();

    // Habilita/desabilita uso de TwofoldLIC para obter uma imagem
    // final com menos aliasing (a custo de maior processamento)
    void EnableTwofoldLic(bool enable = true);

    // Ajusta tamanho da streamline na segunda passada do algoritmo
    // caso TwofoldLic esteja habilitado.
    void SetTwofoldLicL(float l = 10.0f);

    // Habilita/desabilita p�s-processamento da imagem de Lic
    void EnablePostProcessing(bool enable = true);

    // Ajusta tamanho do pixel na imagem de noise
    // Tamanhos maiores geram linhas mais grossas na imagem final
    void SetNoisePixelSize(int size);

    // Habilita/desabilita Fog
    void EnableFog(bool enable = true);

    // Habilita anima��o com velocidade vari�vel de acordo com magnitude
    void EnableVariableAnimation(bool enable = true);
  };
}

#endif
