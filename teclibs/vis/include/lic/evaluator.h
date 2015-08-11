#ifndef EVALUATOR_H
#define EVALUATOR_H

/***************************************************************************
*  $MCI Módulo de definição: Evaluator  Avaliador de LIC
*
*  Arquivo gerado:      evaluator.h
*  Classe:				      Evaluator
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   16/mar/2010 início desenvolvimento
*	  2		  tmt	28/abr/2010 cálculos em glsl
*     3       tmt   31/out/2011 suporte a slic
*     4       tmt   29/nov/2011 suporte a pós-processamento
*
*  $ED Descrição do módulo
*     Classe responsável por avaliar um campo vetorial, uma imagem 
*	  de entrada fornecidos e produzir uma imagem ou animação com base 
*	  no algoritmo de Line Integral Convolution.
*
***************************************************************************/

#include <math.h>
#include <string>

#include <GL/glew.h>
#include <GL/glu.h>

#include <shader/glslshader.h>

#include "image.h"
#include "vectorfield.h"

using std::string;

namespace Lic {

  class Evaluator {

  private:

    // Shader
    GLSLShader evalShader;

    // Shader de Pós-Processamento
    GLSLShader postProcShader;

    // Shader Corrente
    GLSLShader * currShader;

    // Carrega uma Textura no programa de Shader
    void LoadTexture(const char * varName, GLuint texId, int texUnit, int edgeMode = GL_REPEAT, int filterMin = GL_LINEAR, int filterMag = GL_LINEAR, bool is2D = true);

    // Carrega animBValues em um shader
    void LoadAnimBValues(GLuint texId, int texUnit);

    // Ajusta Variáveis Uniformes
    void SetupCommonVariables(GLSLShader & shader, int & texUnit);

  protected:

    // Largura do campo
    int width;

    // Altura do campo
    int height;

    // Indica se imagens geradas possuem alpha
    bool hasAlpha;

    // Constante L do algoritmo de Lic
    float L;

    // Constante de Dilatação da função de Janela de Hanning (para Animação)
    float c;

    // Constante de Dilatação da função de Ripple de Hanning (para Animação)
    float d;

    // Phase Shift da função de Ripple de Hanning (para Animação)
    float B;

    // Espaçamento do Phase Shift
    float BSpacing;

    // Indica se a imagem sendo desenhada no momento é parte de uma animação
    bool isDrawingAnimation;

    // Offset da imagem de entrada em X
    float imageOffsetX;

    // Offset da imagem de entrada em Y
    float imageOffsetY;

    // Indica se imagem de indireção de input deve ser usada
    bool useIndirection;

    // Indica se deve haver teste de descontinuidade em Z
    bool useZTest;

    // Indica se haverá pós-processamento da imagem gerada
    bool usePostProcessing;

    // Indica se Imagem sendo gerada será pré-processada no futuro
    bool drawingPostProcess;

    // Peso de borda para o filtro de passa alta no pós-processamento
    float postProcFilterWeight;

    // Imagem com iluminação difusa
    Image * illumImage;

    // Indica tipo de combinação com imagem de iluminação
    int illumBlend;

    // Indica fator de combinação com imagem de iluminação (para Mix)
    float illumMixFactor;

    // Imagem de Input
    Image * inputImage;

    // Imagem intermediária de Lic para pós-processamento
    Image * licImage;

    // Valor Mínimo da Escala de Magnitude
    float magMin;

    // Valor Máximo da Escala de Magnitude
    float magMax;

    // Valor Mínimo da Escala de Z
    float zMin;

    // Valor Máximo da Escala de Z
    float zMax;

    // Campo Vetorial
    VectorField * vectorField;

    // Retângulo indicando (Xmin, Ymin, Xmax, Ymax) a ser desenhado
    int drawRectangle[4];

    // Quadrado onde será desenhado algoritmo (Xmin, Ymin, Xmax, Ymax)
    float baseRectangle[4];

    // Textura com escala de cor
    Image * colorTex;

    // Cor para regiões pertencentes ao modelo mas com vetores nulos
    float nullVecColor[3];

    // Indica se resultado deve ser colorido de acordo com magnitude
    bool shouldPaintMagnitude;

    // Indica se resultado deve ser colorido de acordo com Z
    bool shouldPaintZ;

    // Indica se coloração deve ser feita com a textura de magnitude
    bool shouldUseMagnitudeTex;

    // Indica se Fog deve ser usado
    bool shouldUseFog;

    // Indica se velocidade de animação deve variar com magnitude
    bool useVariableAnimSpeed;

    // Textura 1D para valores de variação de velocidade na animação
    Image * animBValues;

    // Realiza preparação para renderização em uma Textura usando um determinado Framebuffer Object
    void PrepareTextureDraw(GLuint fb, GLuint tex);

    // Encerra renderização em Textura
    void EndTextureDraw(GLuint fb, GLint lastFb = 0);

    // Desenha Imagem de Lic
    virtual void DrawLIC(float l);

    // Realiza Pós-Processamento de uma imagem Lic
    virtual void PostProcessLIC(Image * lic);

    // Testa estado do framebuffer
    static bool TestFramebufferStatus();

  public:

    // Indica tipo de blend com imagem de iluminação
    enum BlendType {
      BLEND_MULTIPLY,
      BLEND_MIX
    };

    // Indica tipo de coloração
    enum ColorType {
      NO_COLOR,
      MAG_COLOR,
      Z_COLOR
    };

    // Construtor padrão
    // Tanto o Campo quanto o Kernel são atrelados ao Avaliador
    // Caso o avaliador seja deletado, ambos são deletados.
    Evaluator(VectorField * field, Image * image, bool useAlpha = false);

    // Destrutor
    virtual ~Evaluator();

    // Indica retângulo a ser desenhado com lic. Deve estar contido dentro do campo vetorial.
    // Caso w = 0 ou h = 0, será considerado um retângulo que englobe todo o campo.
    void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

    // Ajusta Retângulo base onde algoritmo será desenhado
    void SetBaseRectangle(float xMin = 0, float xMax = 1, float yMin = 0, float ymax = 1);

    // Desenha uma imagem de Lic estática usando OpenGL.
    void DrawStaticLIC(float l = 30.0f);

    // Gera uma imagem de Lic estática com uma determinada constante L.
    // A renderização é feita em textura.
    // Caso target seja fornecido, renderização é feita para textura
    // associada à imagem.
    Image * GenerateStaticLIC(float l = 30.0f, Image * target = NULL);

    // Indica se imagens geradas devem ser coloridas com uma escala de cor.
    // Se texture for NULL, é utilizada uma escala indo do azul ao vermelho.
    void EnableColoring(ColorType type, Image * texture = NULL);

    // Ajusta constantes de dilatação de Hanning para cálculo de animações
    // C é a dilatação da função de janela e D a dilatação da função de ripple
    // Se C e D não podem ser iguais.
    void SetHanningConstants(float c, float d);

    // Ajusta offset na localização de pontos na imagem de entrada
    // Serve para manter a imagem uniforme caso manipulações sejam feitas
    // Sem o Offset, a imagem de entrada ficaria fixa enquanto a imagem
    // de vetor mudaria e haveria impressão de movimento, ainda que o
    // resultado final seja correto.
    // É relevante no uso de ImageVectorField em que a manipulação
    // (zoom, pan) é realizada através da alteração das imagens do campo.
    void SetInputImageOffset(float xOffset = 0.0f, float yOffset = 0.0f);

    // Gera um vetor de imagens com uma animação de Lic
    Image ** GenerateAnimatedLIC(int frames = 12, float l = 15.0f, float bSpacing = 3.1415f/6.0f);

    // Inicia uma animação de LIC
    // L é constante para geração do LIC
    // B Spacing é o espaçamento do phase shift da função de ripple, em radianos.
    void StartAnimatedLIC(float l = 30.0f, float bSpacing = 3.1415f/6.0f);

    // Desenha próximo quadro da animação.
    // Antes de ser usada, deve ser chamada StartAnimatedLIC
    void DrawNextFrame();

    // Desenha quadro atual da animação (Sem avançar B)
    // Antes de ser usada, deve ser chamada StartAnimatedLIC
    void DrawCurrentFrame();

    // Gera um quadro de animação de LIC. NextFrame indica se a
    // animação deve ser avançada. A renderização é feita em textura.
    // Caso target seja fornecido, utiliza a textura associada à imagem.
    Image * GenerateFrame(bool nextFrame = true, Image * target = NULL);

    // Ajusta passo atual de B
    // No caso de controle externo de B, deve ser usada a função DrawCurrentFrame.
    void SetCurrentB(float currB);

    // Obtém passo atual de B
    float GetCurrentB();

    // Ajusta imagem de indireção de input.
    void EnableNoiseIndirection(bool enable);

    // Ajusta imagem de iluminação. NULL desabilita uso.
    void SetIlluminationImage(Image * img);

    // Habilita/desabilita Fog
    void EnableFog(bool enable = true);

    // Ajusta escala de Magnitude
    void SetMagScale(float min, float max);

    // Ajusta escala de Z
    void SetZScale(float min, float max);

    // Habilita/desabilita teste de continuidade com buffer de z.
    // Esse valor deve ser informado na imagem de magnitude fornecida
    // através do canal de cor G.
    void EnableZTest(bool enable);

    // Indica tipo de blend com imagem de iluminação.
    // Para MULTIPLY, factor é irrelevante
    // Para MIX, factor é o fator de mistura entre [0,1]
    // Valores de factor fora do limite esperados não alteram factor corrente.
    void SetIlluminationBlendType(BlendType type, float factor = -1);

    // Indica cor assumida por regiões do modelo com vetores nulos.
    // Estas regiões ainda podem ser afetadas por escalas de cor.
    void SetNullVectorColor(float r, float g, float b);

    // Habilita pós processamento da imagem de Lic. BorderWeight indica o peso
    // que devem ter os pixels de borda no filtro de passa alta.
    void EnablePostProcessing(bool enable = true, float borderWeight = 1.0f);

    // Habilita animação com velocidade variável de acordo com magnitude
    void EnableVariableAnimation(bool enable = true);
  };

}

#endif
