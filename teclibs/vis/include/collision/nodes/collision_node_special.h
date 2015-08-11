/**
* Modulo de declaracao da classe COLLISION_SPECIAL_NODE.COLLISION_SPECIAL_NODE e um
* no da hierarquia, responsavel somente pela criacao de um volume envolvente sem geometria 
* associada. Util para criacao de volumes envolventes de camera, envoltorias, etc...
* @author Fabio I Nakamura
* @version 1.0b
*/

#ifndef __COL_LIB_COLLISION_SPECIAL_NODE_H__
#define __COL_LIB_COLLISION_SPECIAL_NODE_H__

#include "collision_node_internal.h"

class COLLISION_NODE_SPECIAL:public COLLISION_NODE_INTERNAL
{
	protected:

		/**
		* Redefine a funcao Re_Compute_BV , para nao fazer nada.
		*/
		void Re_Compute_BV(void);
		
	public:

		/**
		* Construtor:
		*/
		COLLISION_NODE_SPECIAL(BV_TYPES Type);

		/**
		* Cria o volume envolvente para o no.
		* Se Type for igual a BV_SPHERE entao Param_1 e um vetor de dimensao 3 que
		* corresponde ao centro da esfera e Param_2 e igual ao raio da esfera.
		* Se Type for igual a BV_AABB entao Param_1 e o ponto minimo da caixa AABB e Param_2
		* e o ponto maximo da caixa AABB
		* Se Type for igual a BV_OBB entao Param_1 e o centro da caixa, Param_2 
		* sao as extensoes nos eixos da caixa (vetor de dim 3) e Param_3 sao 
		* os 3 eixos (i,j,k) da OBB. Param 3 deve ser um vetor de dimensao 9 tal que 
		* os 3 primeiros elementos correspondem ao eixo i, os outros 3 elementos 
		* correspondem ao eixo j,e os ultimos 3 ao eixo k
		*/
		void Create_Bounding_Volume(float* Param_1,float* Param_2,float* Param_3);
			
};
#endif
