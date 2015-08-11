#ifndef IMAGE_H
#define IMAGE_H

/***************************************************************************
*  $MCI Módulo de definição: Image  Imagem
*
*  Arquivo gerado:      image.h
*  Classe:				Image
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   16/mar/2010 início desenvolvimento
*
*  $ED Descrição do módulo
*     Classe que representa uma imagem no processo de LIC. É usada tanto
*	  para fornecimento de imagem de entrada do algoritmo como para a
*	  imagem gerada pelo algoritmo.
*	  Armazena a imagem em formato RAW, sem canal de Alpha.
*	  Para acesso aos pixels da imagem, considera-se que o ponto inferior
*	  esquerdo é o (0,0) e o superior direito o (w-1,h-1)
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

      // Calcula cor com base na interpolação linear
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
		// -1 caso a imagem não tenha sido carregada como textura.
		int textureId;

		// Bytes que representam imagem
		unsigned char * rawData;

		// Indica se dados da imagem existem em CPU
		bool hasLocalData;

		// Retorna índice de R em rawData para uma determinada posição
		inline int GetIndexAt(int x, int y);

		// Obtém bytes da imagem a partir de valores armazenados em textura
		void RecoverFromTexture(bool reload = false);

	public:
		// Cria uma imagem de tamanho definido, que pode ou não
		// ser pintada inteiramente de branco (shouldClear).
		Image(int width, int height, bool shouldClear = true, bool hasAlpha = false);

		// Carrega uma imagem do tipo RAW de um arquivo
		Image(const char * filePath, int width, int height, bool hasAlpha = false);

		// Cria uma objeto Image para uma imagem armazenada em textura
		Image(int texId, int width, int height, bool hasAlpha = false);

		// Destrutor
		virtual ~Image();

		// Pinta um pixel de uma determinada cor (RGBA: 0-255)
    // Caso a imagem esteja armazenada em textura, ela é primeiro 
    // recuperada para cpu e descarregada da textura
		void PaintPixel (int x, int y, int r, int g, int b, int a = 255);

		// Pinta um pixel de uma determinada cor (RGBA: 0.0f-1.0f)
    // Caso a imagem esteja armazenada em textura, ela é primeiro 
    // recuperada para cpu e descarregada da textura
		void PaintPixel (int x, int y, float r, float g, float b, float a = 1.0f);

		// Retorna a cor de um determinado pixel nas variáveis r, g, b (RGBA: 0-255)
		void GetPixel (int x, int y, int * r, int * g, int * b, int * a = NULL);

		// Retorna a cor de um determinado pixel nas variáveis r, g, b (RGBA: 0.0f-1.0f)
		void GetPixel (int x, int y, float * r, float * g, float * b, float * a = NULL);

		// Retorna largura da imagem
		int GetWidth();

		// Retorna altura da imagem
		int GetHeight();

		// Informa se imagem possui canal de transparência
		bool HasAlpha();

		// Retorna bytes da imagem (para uso com OpenGL)
		unsigned char * GetRawData();

		// Armazena bytes em um arquivo de saída binário
		bool DumpToFile(char * path);

    // Salva imagem em formato .PNG em um determinado path
    bool SaveAsPNG(char * path);

    // Carrega valores da textura associada
    void LoadFromTexture();

		// Modula a imagem com base em um modulador dado.
		// A modulação é feita multiplicando o pixel do modulador pela
		// luminância da imagem. As imagens devem ter o mesmo tamanho.
		// A imagem base não é modificada.
		Image * Modulate(Image * modulator);

		// Carrega imagem como textura em um índice específico no OpenGL.
		// caso texId seja negativo, gera uma nova textura.
		// Sempre retorna o índice onde a textura foi carregada.
		int LoadAsTexture(int texId = -1);

		// Caso imagem tenha sido carregada como textura, destroi a únidade
		// de textura com base no ID de textura obtido em LoadAsTexture.
		void UnloadTexture();

		// Carrega retângulo do framebuffer do OpenGL para a Imagem.
		// (x,y) representam o ponto inferior esquerdo da tela.
		// O retângulo possuirá largura e profundidade tal como o objeto Imagem.
		void LoadFromFramebuffer(int x, int y);

		// Troca as linhas da imagem de modo que a linha Y passe a ocupar a linha Altura - Y
		void FlipY();

    // Desenha imagem na tela (somente imagens 2D)
    void Draw();

		// Cria uma cópia da imagem.
		Image * Clone();

		// Gera uma imagem quadrada de white noise com lado w
    // Pixel Width indica quantos pixels ocupa cada ponto do white noise
		static Image * GenerateNoiseImage(int w, int pixelWidth = 1);

    // Gera uma paleta de cores
    static Image * GenerateColorPalette(int w, int h);

    // Gera uma paleta de cores usando OpenGL
    static Image * GenerateGLPalette(int w, int h);

    // Gera uma paleta de cores usando interpolação bilinear
    static Image * GenerateBilinearPalette(int w, int h);

    // Deleta textura associada, destrói objeto imagem e ajusta ponteiro como NULL
    static void Clean(Image * & img);
	};

}

#endif
