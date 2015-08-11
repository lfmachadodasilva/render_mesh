#ifndef TWOFOLDEVALUATOR_H
#define TWOFOLDEVALUATOR_H

/***************************************************************************
*  $MCI M�dulo de defini��o: TwofoldEvaluator  Avaliador de LIC Duplo
*
*  Arquivo gerado:      twofoldevaluator.h
*  Classe:				      TwofoldEvaluator
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   19/set/2011 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Classe respons�vel por avaliar um campo vetorial, uma imagem 
*	  de entrada fornecidos e produzir uma imagem ou anima��o com base 
*	  no algoritmo de Line Integral Convolution em duas passadas.
*
***************************************************************************/

#include <GL/glew.h>
#include <GL/glu.h>

#include "evaluator.h"

using std::string;

namespace Lic {

  class TwofoldEvaluator : public Evaluator {

	private:

    // Imagem auxiliar que armazena resultado da primeira passada
    Image * input2;

    // L para a segunda passada do algoritmo
    float passTwoL;

    // Prepara Desenho na textura input2
    GLuint PrepareInput2TextureDraw(void);

    // Encerra Desenho na textura input2
    void EndInput2TextureDraw(GLuint fb);

  protected:

    // Desenha Imagem de Twofold Lic
		virtual void DrawLIC(float l);

	public:

		// Construtor padr�o
		// Tanto o Campo quanto o Kernel s�o atrelados ao Avaliador
		// Caso o avaliador seja deletado, ambos s�o deletados.
		TwofoldEvaluator(VectorField * field, Image * image, bool useAlpha = false);

		// Destrutor
		virtual ~TwofoldEvaluator();

    // Ajusta tamanho da Streamline na segunda passada do algoritmo
    void SetSecondPassL(float l = 10.0f);

	};

}

#endif
