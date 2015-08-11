#ifndef VECTORFIELD_H
#define VECTORFIELD_H

/***************************************************************************
*  $MCI Módulo de definição: VectorField  Campo Vetorial
*
*  Arquivo gerado:      vectorfield.h
*  Classe:				VectorField
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   16/mar/2010 início desenvolvimento
*	    2		    tmt	  03/mai/2010 otimizações para uso com lic (prepare)
*     3       tmt   25/out/2011 suporte à nova esquematização lic
*
*  $ED Descrição do módulo
*     Classe que representa o campo vetorial 2D no algoritmo de LIC.
*	  Para acesso às células, considera-se um sistema onde o canto
*	  inferior esquerdo é o (0,0) e o superior direito o (w-1,h-1).
*
***************************************************************************/

#include <shader/glslshader.h>
#include "vector.h"
#include "image.h"

namespace Lic {

	class VectorField {

  private:
    // Shader de processamento de imagem de campo vetorial
    GLSLShader vecShader;

	protected:
		// Vetor nulo a ser retornado em acessos fora do limite do campo
		Vector nullVector;

		// Campo vetorial
		Vector * field;

		// Largura do Campo
		int width;

		// Altura do campo
		int height;

		// Estrutura com dados de preparação para algoritmo de Lic
		struct LicPreparation {
			// Indica se campo está preparado para ser usado com Lic.
			bool prepared;

      // Indica se as imagens devem ser descarregadas da placa ao serem destruídas
      bool shouldUnload;

			// Imagem em cache com vetores do campo
			Image * vectorImage;

			// Imagem em cache com textura do campo
			Image * texImage;

			// Magnitude mínima do campo
			float minValue;

			// Magnitude máxima do campo
			float maxValue;

      // Indica se destrutor deve limpar imagens de vetor e textura
      bool shouldCleanImages;

			// Construtor
			LicPreparation();

			// Destrutor
			~LicPreparation();

		} lic;

		// Construtor em branco para subclasses
		VectorField();

    // Processa Campo Vetorial para estar entre [-1,1] e normalizado
    Image * ProcessVectorField(Image * in);

	public:

		// Cria o campo vetorial com base em uma lista de vetores que preencha
		// o campo horizontalmente, de cima (y = w-1) para baixo (y = 0).
		// A lista original não é modificada.
		VectorField(Vector * vectors, int w, int h, bool shouldNormalize = true);

		// Cria o campo vetorial com base em uma lista de floats que preencha
		// o campo horizontalmente, de cima (y = w-1) para baixo (y = 0).
		// A lista original não é modificada.
		// A variável vectorSize deve indicar se a lista possui 2 ou 3
		// termos por vetor.
		VectorField(float * vectors, int vectorSize, int w, int h, bool shouldNormalize = true);

		// Cria um campo vetorial de tamanho fixo
		VectorField(int w, int h);

		// Constrói um campo vetorial a partir de uma imagem de campo
		VectorField(Image * image);

		// Destrutor
		virtual ~VectorField();

		// Normaliza todos os vetores do campo
		virtual void Normalize();

		// Retorna Vetor em uma determinada posição
		virtual Vector GetVectorAt(int x, int y);

		// Ajusta vetor em uma determinada posição
		// Caso campo esteja preparado, acontecerá um UnprepareField antes.
		virtual void SetVectorAt(int x, int y, Vector v);

		// Retorna largura do campo
		int GetWidth();

		// Retorna altura do campo
		int GetHeight();

		// Transforma uma campo em 3D em um campo em 2D com base em 2 eixos arbitrários
		// Se xAxis = c * yAxis, nada é feito e a função retorna false, por ser impossível 
		// a transformação.
		// Opcionalmente, é possível verificar se xAxis e yAxis são ortonormais.
		// Caso não sejam e a verificação tenha sido pedida, a função retorna false
		// Caso o campo esteja preparado, acontecerá um UnprepareField antes.
		virtual bool TransformTo2D(Vector xAxis, Vector yAxis, bool checkOrthonormal = true);

		// Gera uma imagem contendo os vetores do campo.
		// Nenhum vetor do campo pode ter valores de x,y fora do intervalo [-1,1]
		Image * GenerateVectorImage(float minVal, float maxVal, bool shouldNormalize = false);

		// Retorna imagem de campo armazenada em cache, caso o campo tenha sido preparado.
		// Esta imagem não deve ser deletada nem modificada externamente.
		// Retorna NULL se campo não estiver preparado.
		Image * GetCachedVectorImage();

		// Gera uma imagem de coordenada de textura para o campo vetorial.
		// Opcionalmente, pode normalizar o campo durante o processo.
		Image * GenerateTexImage();

		// Retorna imagem de coordenada de textura armazenada em cache, caso 
    // o campo tenha sido preparado.
		// Esta imagem não deve ser deletada nem modificada externamente.
		// Retorna NULL se campo não estiver preparado.
		Image * GetCachedTexImage();

		// Prepara campo vetorial para uso com Lic
		// minVal e maxVal indicam as magnitudes mínima e máxima do campo.
		// Caso algum vetor do campo seja alterado, o estado de prepared é perdido.
		// Após ser preparado, todos o campo estará normalizado.
		virtual void PrepareField(float minVal, float maxVal);

		// Prepara campo vetorial para uso com Lic
		// Procura maior e menor magnitudes do campo para criar campo de magnitude.
		virtual void PrepareField();

		// Indica se campo vetorial está preparado para algoritmo de lic.
		bool IsPrepared();

		// Desfaz preparação para lic, revertendo magnitude dos vetores a partir do mapa
		// de magnitude e liberando memória alocada para imagens.
		virtual void UnprepareField();

		// Carrega dados de um mapa de magnitude para determinar
		// isNormalized indica se é necessário normalizar os vetores antes de multiplicar
		// pela magnitude lida no mapa.
		virtual void LoadMagnitudeImage(Image * img, float minVal, float maxVal, bool isNormalized = false);

	};

}

#endif