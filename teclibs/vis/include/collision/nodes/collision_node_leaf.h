/**
* Modulo de declaracao da classe COLLISION_NODE_LEAF.COLLISION_NODE_LEAF e um no folha
* da hierarquia.Os nos folhas da hierarquia obrigatoriamente necessita conhecer a 
* a geometria para a criacao dos volumes envolventes das malhas.
* @author Fabio Nakamura
* @version 1.0b
*/

#ifndef __COL_LIB_COLLISION_NODE_LEAF_H__
#define __COL_LIB_COLLISION_NODE_LEAF_H__

#include "collision_node.h"
#include "obbtree/obbtree.h"

class COLLISION_NODE_LEAF :public COLLISION_NODE
{
	protected:

		/**
		* Se quisermos saber a colisao entre dois triangulos de dois BV entao
		* devemos criar a COLLISION_OBB_TREE do modelo. Note que somente nos folhas
		* possuem o volume envolvente de uma malha,
		* logo somente nos folhas precisam ter uma COLLISION_OBB_TREE.
		*/
		COLLISION_OBB_TREE* Obb_Tree;
			
		/**
		* Se este no ao invez de ter uma OBB_Tree, possuir uma referencia para
		* outra OBB_Tree, entao Obb_Tree_Copy e igual a true,false caso contrario.
		*/
		bool Obb_Tree_Copy;

		
		
	public:

		/**
		* Faz o Update deste no e de todos os seus filhos.
		*/
		int Update(void)
		{
			return(0);
		};

		/**
		* Construtor:
		* Cria um no folha e o seu respectivo volume envolvente 
		* @param Vertex Um vetor de vertices para a criacao do volume envolvete.
						Deve ser do tipo float.
		* @param Num_of_Vertex O numero de vertices da malha.
		* @param Type O tipo de volume envolvete que sera criado
		*/
		COLLISION_NODE_LEAF(const float* Vertex,unsigned int Num_of_Vertex,COLLISION_NODE::BV_TYPES Type);
		
		/**
		* Construtor
		* Somente inicializa os atributos da classe.Nao cria nenhum volume 
		* envolvente.O cliente deve chamar o metodo Create_New_BV para
		* criar o volume envolvente.
		*/
		COLLISION_NODE_LEAF();

		/**
		* Destrutor
		*/
		~COLLISION_NODE_LEAF(void)
		{
			this->Destroy();
		};
		
		/**
		* 
		* Cria um volume envolvente.Se ja existir um volume envolvente, entao
		* destroi o volume antigo e cria-se um novo.
		* @param Vertex Um vetor de vertices para a criacao do volume envolvete.
						Deve ser do tipo float.
		* @param offset A distancia me bytes entre dois vertices consecutivos.
		* @param Num_of_Vertex O numero de vertices da malha.
		* @param Type O tipo de volume envolvete que sera criado
		*/
		void Create_New_BV(const float* Vertex,unsigned int Num_of_Vertex,COLLISION_NODE::BV_TYPES Type);
		

		/**
		* Cria a Obb_Tree associada a este no folha.
		* @param Vertex Um vetor de vertices para a criacao do volume envolvete.
						Deve ser do tipo float.
		* @param Triangle_Index Um vetor de indices de triangulos.
		* @param Num_of_Vertex O numero de vertice da malha.
		* @param Num_of_Triangles O numero de triangulos da malha.
		* @param Num_Tri_Per_Leaf O numero maximo de triangulos por folha.
		*/
		void Create_OBB_Tree(const float* Vertex,const unsigned int* Triangle_Index,int* Triangle_Ids,unsigned int Num_of_Vertex,unsigned int Num_of_Triangles,unsigned int Num_Tri_Per_Leaf )
		{
			if(this->Obb_Tree)
			{
				this->Obb_Tree->Destroy_OBB_Tree();
				delete this->Obb_Tree;
				this->Obb_Tree = NULL;
			}
			this->Obb_Tree = new COLLISION_OBB_TREE(Vertex,Num_of_Vertex,Triangle_Index,Triangle_Ids,Num_of_Triangles,Num_Tri_Per_Leaf);
			return;
		};

		void Create_OBB_Tree(void)
		{
			this->Obb_Tree = new COLLISION_OBB_TREE();
			return;
		};

		
			
		/**
		* Retorna se este no folha possui uma Obb_Tree construida
		* @result true se houver uma Obb_Tree construida, false caso contrario
		*/
		bool Has_OBB_Tree(void)const
		{
            return(this->Obb_Tree->Is_OBB_Tree_Created());
		};		
		
		/**
		* Atribui a este leaf uma OBB_tree.Isto e util
		* no caso de termos multiplas instancias de um objeto,
		* basta construirmos somente uma Obb_tree.
		* @param OBB_tree A Obb_tree deste modelo
		*/
		void Set_OBB_Tree(const COLLISION_OBB_TREE* OBB_Tree)
		{
			if(this->Obb_Tree)
			{
				this->Obb_Tree->Destroy_OBB_Tree();
				this->Obb_Tree = NULL;
			}
			this->Obb_Tree_Copy = true;
			this->Obb_Tree = (COLLISION_OBB_TREE*)OBB_Tree;
			return;
					
		};

		/**
		* Retorna a OBB_Tree deste no folha
		*/
		COLLISION_OBB_TREE* Get_OBB_Tree(void)const
		{
			return(this->Obb_Tree);
		};
		
		/**
		* Metodo para destruir a Obb_Tree e os recursos alocados deste no se houver.
		*/
		void Destroy(void)
		{
			this->Destroy_Bounding_Volume();
			if(this->Obb_Tree && !this->Obb_Tree_Copy )
			{
				this->Obb_Tree->Destroy_OBB_Tree();
				delete this->Obb_Tree;
				this->Obb_Tree = NULL;
			}
			return;
		};		

		/**
		* Desenha Volume Envolvente correspondente ao no.
		* Funcao de teste visual por enquanto
		*/
		void Render_BV(void)
		{
			glPushMatrix();
			{
				glMultMatrixf(this->Matrix.Elements);
				//if(this->Bounding_Volume)
				//	this->Bounding_Volume->Render_BV();	
				
				if(this->Obb_Tree)
				{
					this->Obb_Tree->Render_Tree();
					this->Obb_Tree->Render_Model();
				}
			}
			glPopMatrix();
			return;
		};		

};

#endif
