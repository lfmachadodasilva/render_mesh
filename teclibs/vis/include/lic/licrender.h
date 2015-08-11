#ifndef LICRENDER_H
#define LICRENDER_H

/***************************************************************************
*  $MCI Módulo de definição: LicRender  Renderizador de LIC
*
*  Arquivo gerado:      licrender.h
*  Classe:				      LicRender
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   29/set/2010 início desenvolvimento
*     2       tmt   23/mai/2011 suporte a superfícies
*
*  $ED Descrição do módulo
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
    // XY indica canto superior esquerdo e WH dimensões da janela
    int drawRect[4];

    // Largura da imagem gerada
    int width;

    // Altura da imagem gerada
    int height;

    // Indica se deve ser renderizada uma superfície ou um plano
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

    // Indica se imagem de Lic deve ser pós-processada
    bool shouldPostProcess;

    // Indica se Evaluator deve ser reconstruído
    bool shouldRebuildEvaluator;

    // Indica se deve haver teste de descontinuidade em Z
    bool useZTest;

    // Valor Mínimo da Escala de Magnitude
    float magMin;

    // Valor Máximo da Escala de Magnitude
    float magMax;

    // Valor Mínimo da Escala de Z
    float zMin;

    // Valor Máximo da Escala de Z
    float zMax;

    // Imagem de Campo Vetorial
    Image * vectorImage;

    // Imagem de Iluminação
    Image * colorImage;

    // Tipo de mistura da imagem de iluminação
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
    // de acordo com a matriz de projeção corrente
    bool shouldOffsetNoise;

    // Imagem de Textura 1D para coloração
    Image * colorTexture;

    // Indica se campo deve ser colorido
    bool shouldPaint;

    // Cor para regiões pertencentes ao modelo mas com vetores nulos
    float nullVecColor[3];

    // Indica se Z deve ser colorido no lugar da magnitude
    bool paintZ;

    // Indica se animação está sendo feita
    bool isAnimating;

    // Indica se velocidade de animação deve variar com magnitude
    bool useVariableAnimSpeed;

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

    // Indica se Fog deve ser usado
    bool shouldUseFog;

    // Reconstrói Evaluator
    void BuildEvaluator();

    // Prepara Desenho em Tela
    bool PrepareDraw();

    // Obtém offset do ponto (0,0) de acordo com a matriz ModelView corrente no OpenGL
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

    // Ajusta escala de Z (não afeta paleta de cores)
    void SetZScale(float min, float max);

    // Desenha LIC Estático
    void DrawStaticLic(float L);

    // Desenha LIC Estático em Textura
    // Se target for fornecido, desenha na textura associada a ele.
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
    // Se target for fornecido, desenha na textura associada a ele.
    Image * GenerateAnimatedLic(double time = -1, bool drawNewFrame = true, Image * target = NULL);

    // Ajusta constantes de Hanning para animação.
    void SetHanningConstants(float c, float d);

    // Habilita pintura de magnitude usando uma textura 1D fornecida.
    // Caso textura seja NULL, é usada uma escala simples Azul-Vermelho.
    // Caso textura seja 2D, colore magnitude e z simultaneamente.
    // paintZ indica se a componente Z deve ser pintada ao invés da magnitude.
    void EnableColoring(bool shouldPaint, Image * texture = NULL, bool paintZ = false);

    // Indica cor assumida por regiões do modelo com vetores nulos.
    // Estas regiões ainda podem ser afetadas por escalas de cor.
    void SetNullVectorColor(float r, float g, float b);

    // Ajusta retângulo do vetor que será renderizado. 
    // XY indicam o canto inferior da imagem e WH a largura e altura.
    // O canto inferior esquerdo da imagem é (0,0).
    // Caso W ou H sejam 0, renderiza toda a imagem.
    void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

    // Indica se deve haver um offset da textura em função da projeção
    // para preservar imagem final em caso de zoom ou pan.
    void EnableNoiseOffset(bool enable = true);

    // Habilita ou Desabilita uso de acesso indireto a textura de noise
    // Caso esteja habilitado, utiliza os valores de RG na TexImage como
    // coordenadas para acesso.
    void EnableNoiseIndirection(bool enable = true);

    // Habilita/desabilita teste de continuidade com buffer de z
    // É necessário que geometria armazene informação de Z-Buffer
    // no canal de cor G da imagem de coordenada de textura
    void EnableZTest(bool enable = true);

    // Habilita/desabilita iluminação da imagem final. Não tem
    // efeito caso o modelo não produza uma imagem de cor.
    void EnableIllumination(bool enable = true);

    // Ajusta iluminação para ser adicionada via Mix.
    // Fator indica a proporção de combinação (0 = Somente Iluminação, 1 = Somente Lic)
    // Caso factor não esteja em [0,1], mix é ativado com o factor anteriormente
    // ajustado.
    void SetIlluminationMix(float factor = -1.0f);

    // Ajusta iluminação para ser adicionada via Multiply.
    void SetIlluminationMultiply();

    // Habilita/desabilita uso de TwofoldLIC para obter uma imagem
    // final com menos aliasing (a custo de maior processamento)
    void EnableTwofoldLic(bool enable = true);

    // Ajusta tamanho da streamline na segunda passada do algoritmo
    // caso TwofoldLic esteja habilitado.
    void SetTwofoldLicL(float l = 10.0f);

    // Habilita/desabilita pós-processamento da imagem de Lic
    void EnablePostProcessing(bool enable = true);

    // Ajusta tamanho do pixel na imagem de noise
    // Tamanhos maiores geram linhas mais grossas na imagem final
    void SetNoisePixelSize(int size);

    // Habilita/desabilita Fog
    void EnableFog(bool enable = true);

    // Habilita animação com velocidade variável de acordo com magnitude
    void EnableVariableAnimation(bool enable = true);
  };
}

#endif
