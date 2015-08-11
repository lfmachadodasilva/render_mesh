#ifndef VECTOR_H
#define VECTOR_H

/***************************************************************************
*  $MCI Módulo de definição: Vector  Vetor
*
*  Arquivo gerado:      vector.h
*  Classe:				Vector
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   16/mar/2010 início desenvolvimento
*
*  $ED Descrição do módulo
*     Classe que representa um vetor 2D.
*
***************************************************************************/


namespace Lic {

	class Vector {

	public:
		
		// X do vetor
		float x;

		// Y do Vetor
		float y;

		// Z do Vetor
		float z;

		// Construtor padrão
		Vector();

		// Construtor que define X,Y
		Vector(float x, float y, float z = 0.0f);
		
		// Destrutor
		~Vector();

		// Ajusta valores de (X,Y)
		void Set(float x, float y, float z = 0.0f)
    {
      this->x = x; 
	    this->y = y;
	    this->z = z;
    }

		// Normaliza vetor e retorna sua magnitude anterior
		float Normalize();

		// Retorna magnitude do vetor
		float GetLength();

		// Retorna magnitude do vetor elevada ao quadrado
		float GetLength2();

		// Retorna Dot Product contra um vetor v
		float Dot(const Vector & v);

	};

}

#endif