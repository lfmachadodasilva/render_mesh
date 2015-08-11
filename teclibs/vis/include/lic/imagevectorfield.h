#ifndef IMAGEVECTORFIELD_H
#define IMAGEVECTORFIELD_H

/***************************************************************************
*  $MCI M�dulo de defini��o: ImageVectorField  Campo Vetorial em Imagens
*
*  Arquivo gerado:      imagevectorfield.h
*  Classe:				ImageVectorField
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   24/out/2010 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Classe que representa um campo vetorial armazenado exclusivamente
*	  em objetos de imagem (um descritor de vetores e um descritor de
*	  magnitudes). Permite que texturas preparadas externamente possam
*	  ser utilizadas diretamente para descrever um campo vetorial no
*	  algoritmo de LIC.
*
***************************************************************************/

#include "vectorfield.h"
#include "image.h"

namespace Lic {

	class ImageVectorField : public VectorField {

	public:

		// Constr�i um campo vetorial a partir de uma imagem de campo
		ImageVectorField(Image * vecImage, Image * texImage = NULL);

		// Destrutor
		virtual ~ImageVectorField();

		// N�o tem efeito. Como n�o � edit�vel, um ImageVectorField est� sempre preparado.
		// Override � para que imagens n�o sejam destru�das inadvertidamente.
		virtual void UnprepareField();

		// Carrega uma imagem de magnitude
		void SetTexImage(Image * img);

		// Carrega uma imagem de campo
		void SetFieldImage(Image * img);
	};

}

#endif