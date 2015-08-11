#ifndef EVALUATOR_H
#define EVALUATOR_H

/***************************************************************************
*  $MCI M�dulo de defini��o: Evaluator  Avaliador de LIC
*
*  Arquivo gerado:      evaluator.h
*  Classe:				      Evaluator
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   16/mar/2010 in�cio desenvolvimento
*	  2		  tmt	28/abr/2010 c�lculos em glsl
*     3       tmt   31/out/2011 suporte a slic
*     4       tmt   29/nov/2011 suporte a p�s-processamento
*
*  $ED Descri��o do m�dulo
*     Classe respons�vel por avaliar um campo vetorial, uma imagem 
*	  de entrada fornecidos e produzir uma imagem ou anima��o com base 
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

    // Shader de P�s-Processamento
    GLSLShader postProcShader;

    // Shader Corrente
    GLSLShader * currShader;

    // Carrega uma Textura no programa de Shader
    void LoadTexture(const char * varName, GLuint texId, int texUnit, int edgeMode = GL_REPEAT, int filterMin = GL_LINEAR, int filterMag = GL_LINEAR, bool is2D = true);

    // Carrega animBValues em um shader
    void LoadAnimBValues(GLuint texId, int texUnit);

    // Ajusta Vari�veis Uniformes
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

    // Constante de Dilata��o da fun��o de Janela de Hanning (para Anima��o)
    float c;

    // Constante de Dilata��o da fun��o de Ripple de Hanning (para Anima��o)
    float d;

    // Phase Shift da fun��o de Ripple de Hanning (para Anima��o)
    float B;

    // Espa�amento do Phase Shift
    float BSpacing;

    // Indica se a imagem sendo desenhada no momento � parte de uma anima��o
    bool isDrawingAnimation;

    // Offset da imagem de entrada em X
    float imageOffsetX;

    // Offset da imagem de entrada em Y
    float imageOffsetY;

    // Indica se imagem de indire��o de input deve ser usada
    bool useIndirection;

    // Indica se deve haver teste de descontinuidade em Z
    bool useZTest;

    // Indica se haver� p�s-processamento da imagem gerada
    bool usePostProcessing;

    // Indica se Imagem sendo gerada ser� pr�-processada no futuro
    bool drawingPostProcess;

    // Peso de borda para o filtro de passa alta no p�s-processamento
    float postProcFilterWeight;

    // Imagem com ilumina��o difusa
    Image * illumImage;

    // Indica tipo de combina��o com imagem de ilumina��o
    int illumBlend;

    // Indica fator de combina��o com imagem de ilumina��o (para Mix)
    float illumMixFactor;

    // Imagem de Input
    Image * inputImage;

    // Imagem intermedi�ria de Lic para p�s-processamento
    Image * licImage;

    // Valor M�nimo da Escala de Magnitude
    float magMin;

    // Valor M�ximo da Escala de Magnitude
    float magMax;

    // Valor M�nimo da Escala de Z
    float zMin;

    // Valor M�ximo da Escala de Z
    float zMax;

    // Campo Vetorial
    VectorField * vectorField;

    // Ret�ngulo indicando (Xmin, Ymin, Xmax, Ymax) a ser desenhado
    int drawRectangle[4];

    // Quadrado onde ser� desenhado algoritmo (Xmin, Ymin, Xmax, Ymax)
    float baseRectangle[4];

    // Textura com escala de cor
    Image * colorTex;

    // Cor para regi�es pertencentes ao modelo mas com vetores nulos
    float nullVecColor[3];

    // Indica se resultado deve ser colorido de acordo com magnitude
    bool shouldPaintMagnitude;

    // Indica se resultado deve ser colorido de acordo com Z
    bool shouldPaintZ;

    // Indica se colora��o deve ser feita com a textura de magnitude
    bool shouldUseMagnitudeTex;

    // Indica se Fog deve ser usado
    bool shouldUseFog;

    // Indica se velocidade de anima��o deve variar com magnitude
    bool useVariableAnimSpeed;

    // Textura 1D para valores de varia��o de velocidade na anima��o
    Image * animBValues;

    // Realiza prepara��o para renderiza��o em uma Textura usando um determinado Framebuffer Object
    void PrepareTextureDraw(GLuint fb, GLuint tex);

    // Encerra renderiza��o em Textura
    void EndTextureDraw(GLuint fb, GLint lastFb = 0);

    // Desenha Imagem de Lic
    virtual void DrawLIC(float l);

    // Realiza P�s-Processamento de uma imagem Lic
    virtual void PostProcessLIC(Image * lic);

    // Testa estado do framebuffer
    static bool TestFramebufferStatus();

  public:

    // Indica tipo de blend com imagem de ilumina��o
    enum BlendType {
      BLEND_MULTIPLY,
      BLEND_MIX
    };

    // Indica tipo de colora��o
    enum ColorType {
      NO_COLOR,
      MAG_COLOR,
      Z_COLOR
    };

    // Construtor padr�o
    // Tanto o Campo quanto o Kernel s�o atrelados ao Avaliador
    // Caso o avaliador seja deletado, ambos s�o deletados.
    Evaluator(VectorField * field, Image * image, bool useAlpha = false);

    // Destrutor
    virtual ~Evaluator();

    // Indica ret�ngulo a ser desenhado com lic. Deve estar contido dentro do campo vetorial.
    // Caso w = 0 ou h = 0, ser� considerado um ret�ngulo que englobe todo o campo.
    void SetDrawingRectangle(int x = 0, int y = 0, int w = 0, int h = 0);

    // Ajusta Ret�ngulo base onde algoritmo ser� desenhado
    void SetBaseRectangle(float xMin = 0, float xMax = 1, float yMin = 0, float ymax = 1);

    // Desenha uma imagem de Lic est�tica usando OpenGL.
    void DrawStaticLIC(float l = 30.0f);

    // Gera uma imagem de Lic est�tica com uma determinada constante L.
    // A renderiza��o � feita em textura.
    // Caso target seja fornecido, renderiza��o � feita para textura
    // associada � imagem.
    Image * GenerateStaticLIC(float l = 30.0f, Image * target = NULL);

    // Indica se imagens geradas devem ser coloridas com uma escala de cor.
    // Se texture for NULL, � utilizada uma escala indo do azul ao vermelho.
    void EnableColoring(ColorType type, Image * texture = NULL);

    // Ajusta constantes de dilata��o de Hanning para c�lculo de anima��es
    // C � a dilata��o da fun��o de janela e D a dilata��o da fun��o de ripple
    // Se C e D n�o podem ser iguais.
    void SetHanningConstants(float c, float d);

    // Ajusta offset na localiza��o de pontos na imagem de entrada
    // Serve para manter a imagem uniforme caso manipula��es sejam feitas
    // Sem o Offset, a imagem de entrada ficaria fixa enquanto a imagem
    // de vetor mudaria e haveria impress�o de movimento, ainda que o
    // resultado final seja correto.
    // � relevante no uso de ImageVectorField em que a manipula��o
    // (zoom, pan) � realizada atrav�s da altera��o das imagens do campo.
    void SetInputImageOffset(float xOffset = 0.0f, float yOffset = 0.0f);

    // Gera um vetor de imagens com uma anima��o de Lic
    Image ** GenerateAnimatedLIC(int frames = 12, float l = 15.0f, float bSpacing = 3.1415f/6.0f);

    // Inicia uma anima��o de LIC
    // L � constante para gera��o do LIC
    // B Spacing � o espa�amento do phase shift da fun��o de ripple, em radianos.
    void StartAnimatedLIC(float l = 30.0f, float bSpacing = 3.1415f/6.0f);

    // Desenha pr�ximo quadro da anima��o.
    // Antes de ser usada, deve ser chamada StartAnimatedLIC
    void DrawNextFrame();

    // Desenha quadro atual da anima��o (Sem avan�ar B)
    // Antes de ser usada, deve ser chamada StartAnimatedLIC
    void DrawCurrentFrame();

    // Gera um quadro de anima��o de LIC. NextFrame indica se a
    // anima��o deve ser avan�ada. A renderiza��o � feita em textura.
    // Caso target seja fornecido, utiliza a textura associada � imagem.
    Image * GenerateFrame(bool nextFrame = true, Image * target = NULL);

    // Ajusta passo atual de B
    // No caso de controle externo de B, deve ser usada a fun��o DrawCurrentFrame.
    void SetCurrentB(float currB);

    // Obt�m passo atual de B
    float GetCurrentB();

    // Ajusta imagem de indire��o de input.
    void EnableNoiseIndirection(bool enable);

    // Ajusta imagem de ilumina��o. NULL desabilita uso.
    void SetIlluminationImage(Image * img);

    // Habilita/desabilita Fog
    void EnableFog(bool enable = true);

    // Ajusta escala de Magnitude
    void SetMagScale(float min, float max);

    // Ajusta escala de Z
    void SetZScale(float min, float max);

    // Habilita/desabilita teste de continuidade com buffer de z.
    // Esse valor deve ser informado na imagem de magnitude fornecida
    // atrav�s do canal de cor G.
    void EnableZTest(bool enable);

    // Indica tipo de blend com imagem de ilumina��o.
    // Para MULTIPLY, factor � irrelevante
    // Para MIX, factor � o fator de mistura entre [0,1]
    // Valores de factor fora do limite esperados n�o alteram factor corrente.
    void SetIlluminationBlendType(BlendType type, float factor = -1);

    // Indica cor assumida por regi�es do modelo com vetores nulos.
    // Estas regi�es ainda podem ser afetadas por escalas de cor.
    void SetNullVectorColor(float r, float g, float b);

    // Habilita p�s processamento da imagem de Lic. BorderWeight indica o peso
    // que devem ter os pixels de borda no filtro de passa alta.
    void EnablePostProcessing(bool enable = true, float borderWeight = 1.0f);

    // Habilita anima��o com velocidade vari�vel de acordo com magnitude
    void EnableVariableAnimation(bool enable = true);
  };

}

#endif
