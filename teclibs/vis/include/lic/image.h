#ifndef IMAGE_H
#define IMAGE_H

/***************************************************************************
*  $MCI M�dulo de defini��o: Image  Imagem
*
*  Arquivo gerado:      image.h
*  Classe:				Image
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   16/mar/2010 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Classe que representa uma imagem no processo de LIC. � usada tanto
*	  para fornecimento de imagem de entrada do algoritmo como para a
*	  imagem gerada pelo algoritmo.
*	  Armazena a imagem em formato RAW, sem canal de Alpha.
*	  Para acesso aos pixels da imagem, considera-se que o ponto inferior
*	  esquerdo � o (0,0) e o superior direito o (w-1,h-1)
*
***************************************************************************/

#include <stdlib.h>

namespace Lic {

	class Image {

	private:

    // Estrutura auxiliar para representar cor
    struct Color {
      // RGB da Cor
      float r, g, b;

      // Ajusta RGB da cor
      void Set(float r, float g, float b) {
        this->r = r; this->g = g; this->b = b;
      }

      // Aplica filtro de Screen com a cor C
      void ApplyScreenFilter(Color & c);

      // Calcula cor com base na interpola��o linear
      // entre c1 e c2 por um fator de f (f em [0,1])
      void Lerp(Color & c1, Color & c2, float f);
    };

		// Largura da imagem
		int width;

		// Altura da imagem
		int height;

		// Indica se imagem possui canal de alpha
		bool hasAlpha;

		// Id da textura para onde a imagem foi carregada
		// -1 caso a imagem n�o tenha sido carregada como textura.
		int textureId;

		// Bytes que representam imagem
		unsigned char * rawData;

		// Indica se dados da imagem existem em CPU
		bool hasLocalData;

		// Retorna �ndice de R em rawData para uma determinada posi��o
		inline int GetIndexAt(int x, int y);

		// Obt�m bytes da imagem a partir de valores armazenados em textura
		void RecoverFromTexture(bool reload = false);

	public:
		// Cria uma imagem de tamanho definido, que pode ou n�o
		// ser pintada inteiramente de branco (shouldClear).
		Image(int width, int height, bool shouldClear = true, bool hasAlpha = false);

		// Carrega uma imagem do tipo RAW de um arquivo
		Image(const char * filePath, int width, int height, bool hasAlpha = false);

		// Cria uma objeto Image para uma imagem armazenada em textura
		Image(int texId, int width, int height, bool hasAlpha = false);

		// Destrutor
		virtual ~Image();

		// Pinta um pixel de uma determinada cor (RGBA: 0-255)
    // Caso a imagem esteja armazenada em textura, ela � primeiro 
    // recuperada para cpu e descarregada da textura
		void PaintPixel (int x, int y, int r, int g, int b, int a = 255);

		// Pinta um pixel de uma determinada cor (RGBA: 0.0f-1.0f)
    // Caso a imagem esteja armazenada em textura, ela � primeiro 
    // recuperada para cpu e descarregada da textura
		void PaintPixel (int x, int y, float r, float g, float b, float a = 1.0f);

		// Retorna a cor de um determinado pixel nas vari�veis r, g, b (RGBA: 0-255)
		void GetPixel (int x, int y, int * r, int * g, int * b, int * a = NULL);

		// Retorna a cor de um determinado pixel nas vari�veis r, g, b (RGBA: 0.0f-1.0f)
		void GetPixel (int x, int y, float * r, float * g, float * b, float * a = NULL);

		// Retorna largura da imagem
		int GetWidth();

		// Retorna altura da imagem
		int GetHeight();

		// Informa se imagem possui canal de transpar�ncia
		bool HasAlpha();

		// Retorna bytes da imagem (para uso com OpenGL)
		unsigned char * GetRawData();

		// Armazena bytes em um arquivo de sa�da bin�rio
		bool DumpToFile(char * path);

    // Salva imagem em formato .PNG em um determinado path
    bool SaveAsPNG(char * path);

    // Carrega valores da textura associada
    void LoadFromTexture();

		// Modula a imagem com base em um modulador dado.
		// A modula��o � feita multiplicando o pixel do modulador pela
		// lumin�ncia da imagem. As imagens devem ter o mesmo tamanho.
		// A imagem base n�o � modificada.
		Image * Modulate(Image * modulator);

		// Carrega imagem como textura em um �ndice espec�fico no OpenGL.
		// caso texId seja negativo, gera uma nova textura.
		// Sempre retorna o �ndice onde a textura foi carregada.
		int LoadAsTexture(int texId = -1);

		// Caso imagem tenha sido carregada como textura, destroi a �nidade
		// de textura com base no ID de textura obtido em LoadAsTexture.
		void UnloadTexture();

		// Carrega ret�ngulo do framebuffer do OpenGL para a Imagem.
		// (x,y) representam o ponto inferior esquerdo da tela.
		// O ret�ngulo possuir� largura e profundidade tal como o objeto Imagem.
		void LoadFromFramebuffer(int x, int y);

		// Troca as linhas da imagem de modo que a linha Y passe a ocupar a linha Altura - Y
		void FlipY();

    // Desenha imagem na tela (somente imagens 2D)
    void Draw();

		// Cria uma c�pia da imagem.
		Image * Clone();

		// Gera uma imagem quadrada de white noise com lado w
    // Pixel Width indica quantos pixels ocupa cada ponto do white noise
		static Image * GenerateNoiseImage(int w, int pixelWidth = 1);

    // Gera uma paleta de cores
    static Image * GenerateColorPalette(int w, int h);

    // Gera uma paleta de cores usando OpenGL
    static Image * GenerateGLPalette(int w, int h);

    // Gera uma paleta de cores usando interpola��o bilinear
    static Image * GenerateBilinearPalette(int w, int h);

    // Deleta textura associada, destr�i objeto imagem e ajusta ponteiro como NULL
    static void Clean(Image * & img);
	};

}

#endif
