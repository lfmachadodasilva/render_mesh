#ifndef IMAGEVECTORFIELD_H
#define IMAGEVECTORFIELD_H

/***************************************************************************
*  $MCI Módulo de definição: ImageVectorField  Campo Vetorial em Imagens
*
*  Arquivo gerado:      imagevectorfield.h
*  Classe:				ImageVectorField
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   24/out/2010 início desenvolvimento
*
*  $ED Descrição do módulo
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

		// Constrói um campo vetorial a partir de uma imagem de campo
		ImageVectorField(Image * vecImage, Image * texImage = NULL);

		// Destrutor
		virtual ~ImageVectorField();

		// Não tem efeito. Como não é editável, um ImageVectorField está sempre preparado.
		// Override é para que imagens não sejam destruídas inadvertidamente.
		virtual void UnprepareField();

		// Carrega uma imagem de magnitude
		void SetTexImage(Image * img);

		// Carrega uma imagem de campo
		void SetFieldImage(Image * img);
	};

}

#endif