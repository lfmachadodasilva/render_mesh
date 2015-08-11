/**
* Modulo de declaracao da classe COLLISION_OBB_TREE. Esta classe tem como objetivo implementar
* uma obb_tree para ser usada junto a testes de colisao entre malhas triangulares.
* @author : Fabio Nakamura
*/

#ifndef __COL_LIB_OBB_TREE_H__
#define __COL_LIB_OBB_TREE_H__

#include "../../math_library/math_includes.h"
#include "../../math_library/boundingvolumes/bounding_obb.h"
#include "../collision_contact_pair.h"
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_SIZE 100

//extern int Num_Box_Test;
//extern int Num_Miss_Test;
class COLLISION_OBB_TREE
{

	private:

		/*
		* Esta estrutura serve apenas para ajudar no calculo da mediana ao se projetar
		* todos os triangulos sobre o maior eixo.
		*/
		class PROJECTION
		{

			public:

				/**
				* Construtor e destrutor default
				*/
				PROJECTION(void)
				{
				};

				~PROJECTION(void)
				{
				};

				/**
				* Funcao de comparacao
				*/
				static int Compare(const void* Element_0,const void* Element_1);
				
				
				/**
				* O valor da projecao
				*/
				float Projection_Value;

				/**
				* O indice do triangulo
				*/
				unsigned int Triangle_Index;

		};


		class OBB_NODE
		{
			public:

				typedef struct Triangle_Storage
				{
					// O triangulo
					TRIANGLE3D<float> Triangle;

					// O identificador deste triangulo
					int Triangle_Id;
				
				}TRIANGLE_STORAGE;

			

				/**
				* Construtor
				*/
				OBB_NODE(unsigned int Max_Num_of_Triangles_per_Leaf = 1)
				{
					this->Num_of_Triangles = 0;
					this->Pointer_1 = this->Pointer_2 = NULL;
				}

				/**
				* Destrutor
				*/
				~OBB_NODE(void)
				{
					this->Destroy_Nodes();
				}

				/**
				* Cria a caixa orientada deste no
				*/
				void Create_OBB(const float* Vertex,const unsigned int* Triangles_Index,unsigned int Num_of_Vertex,
								unsigned int Start,unsigned int End,unsigned int* Input_Split);

				/**
				* Divide os triangulos entre as sub arvores
				*/
				void Split_Triangles(VECTOR3f* Centroids,unsigned int Start,unsigned int End,unsigned int* Input_Split,
							         unsigned int* Start_Out,unsigned int* End_Out,unsigned int* Output_Split);

				void Build_Nodes(const float* Vertex,const unsigned int* Triangles_Index,const int* Triangles_Ids,
								 unsigned int Num_of_Triangles,unsigned int Num_of_Vertex,VECTOR3f* Centroids,
								 unsigned int Start,unsigned int End,unsigned int* Input_Split,unsigned int* Output_Split,unsigned int Max_Tri_Per_Leaf);

	
				/**
				* Destroi os nos da COLLISION_OBB_TREE
				*/
				void Destroy_Nodes(void);

				/**
				* Funcoes de DEBUG
				*/
				void Render_OBB_Tree(void);
				void Render_Model(void);

				
				/**
				* a caixa orientada de cada no
				*/
				BOUNDING_OBB<float> OBB_Bound;

				/**
				* dois ponteiros tipo void
				*/
				/**
				* No caso de um no interno, entao Pointer_1 e Pointer_2 serao 
				* respectivamente filho da esquerda e filho da direita.No caso de no folha,
				* entao Pointer_1 sera a lista de triangulos do no folha e Pointer_2 sera NULL;
				*/
				void* Pointer_1;
				void* Pointer_2;


				/**
				* O numero de triangulos no no' folha
				*/
				unsigned int Num_of_Triangles;
				

				bool Is_Leaf(void)const
				{
					return(this->Num_of_Triangles > 0);
				}

				float Get_Size(void)const
				{
					// Retorna Considera que o "tamanho" do no , sera o volume da caixa
					return(this->OBB_Bound.Get_Volume());
				}

		};

		/**
		* Metodos de teste de colisao
		*/

		/**
		* Faz o teste de colisao de todos os triangulos de um no folha,
		* contra todos os triangulos de outro no folha.
		*/
		static bool Test_Triangle_Intersect(const OBB_NODE* Node_A,const MATRIX4<float>* Node_A_Matrix,
											const OBB_NODE* Node_B,const MATRIX4<float>* Node_B_Matrix);

		static bool Test_Triangle_Intersect_Contacts(const OBB_NODE* Node_A,const MATRIX4<float>* Node_A_Matrix,
													 const OBB_NODE* Node_B,const MATRIX4<float>* Node_B_Matrix,COLLISION_CONTACT_PAIR& Contacts);

		/**
		* Determina se um raio intercepta a obb_Tree e no caso de um no folha, se intercepta seus triangulos
		* Retorna a menor distancia entre os testes de colisao
		*/
		static float Test_Triangle_Ray(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
									   const RAY3D<float>& Ray);

		/**
		* Determina se um raio intercepta a obb_Tree e no caso de um no folha, se intercepta seus triangulos
		* Retorna a menor distancia entre os testes de colisao e o triangulo interceptado
		*/
		static float Test_Triangle_Ray(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
									   const RAY3D<float>& Ray,COLLISION_CONTACT_PAIR& Contacts);

		/**
		* Determina se um plano colide com a COLLISION_OBB_TREE e seus triangulos no caso de nos folhas.
		*/
		static bool Test_Triangle_Plane(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,const PLANE3<float>& Plane);

		/**
		* Determina se um volume envolvente esta colidindo contra os triangulos de um no folha da OBB_Tree
		*/
		static bool Test_Triangle_BV_Intersection(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
												  const BOUNDING_VOLUME<float>* Bound_Volume,const MATRIX4<float>* Bound_Matrix);

        static bool Test_Triangle_BV_Intersection_Contacts(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
												           const BOUNDING_VOLUME<float>* Bound_Volume,const MATRIX4<float>* Bound_Matrix,
                                                           COLLISION_CONTACT_PAIR& Contacts);

		static bool Test_OBB_NODE_Against_OBB_NODE(const OBB_NODE* Node_A,const MATRIX4<float>* Node_A_Matrix,
												   const OBB_NODE* Node_B,const MATRIX4<float>* Node_B_Matrix,bool Triangle_Against_Triangle);

		static void Test_OBB_NODE_Against_OBB_NODE_Contacts(const OBB_NODE* Node_A,const MATRIX4<float>* Node_A_Matrix,
															const OBB_NODE* Node_B,const MATRIX4<float>* Node_B_Matrix,COLLISION_CONTACT_PAIR& Contacts);

		static bool Test_OBB_NODE_Against_Bounding_Volume(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
														  const BOUNDING_VOLUME<float>* Bound_Volume,const MATRIX4<float>* Bound_Matrix,bool Triangle_Agaist_BV);

        static void Test_OBB_NODE_Against_Bounding_Volume_Contacts(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
														           const BOUNDING_VOLUME<float>* Bound_Volume,const MATRIX4<float>* Bound_Matrix,COLLISION_CONTACT_PAIR& Contacts);


		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um raio
		*/
		static float Test_OBB_Tree_Against_Ray(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
											   const RAY3D<float>& Ray,bool Ray_Against_Triangle);

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um raio. Se Colidir 
		* entao retorna os indices dos triangulos interceptados e a menor distancia.
		*/
		static float Test_OBB_Tree_Against_Ray_Contacts(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
											            const RAY3D<float>& Ray,COLLISION_CONTACT_PAIR& Contacts);

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um plano
		*/
		static bool Test_OBB_Tree_Against_Plane(const OBB_NODE* Node,const MATRIX4<float>* Node_Matrix,
												const PLANE3<float>& Plane,bool Plane_Against_Triangle);

		/**
		* Guarda o endereco dos vertices e da lista de indices dos triangulos para fazer insercao um de cada vez
		*/
		unsigned int Num_of_Primitives;
		unsigned int Max_Num_of_Primitives;
		float* Vertex;
		unsigned int* Triangle_Index;
		int* Triangle_Ids;

		/**
		* O numero maximo de triangulos por no'
		*/
		unsigned int Max_Num_of_Triangles;


		/**
		* A COLLISION_OBB_TREE
		*/
		OBB_NODE* Obb_Tree;

		/**
		* Constroi a COLLISION_OBB_TREE dado os vertices e os triangulos
		*/
		OBB_NODE* Build_OBB_Tree(const float* Vertex,unsigned int Num_of_Vertex,
								 const unsigned int* Tri_List,const int* Tri_Ids,unsigned int Num_of_Triangles);
	
	public:

		/**
		* Construtor
		*/
		COLLISION_OBB_TREE(unsigned int Max_Triangles_per_Leaf = 1):
						   Vertex(0),Triangle_Index(0),
						   Triangle_Ids(0),Max_Num_of_Triangles(Max_Triangles_per_Leaf),Obb_Tree(0)
		{
		}

		/**
		* Constroi dado os vertices e os triangulos
		*/
		COLLISION_OBB_TREE(const float* Vertex,unsigned int Num_of_Vertex,
				 const unsigned int* Tri_List,const int* Tri_Ids,unsigned int Num_of_Triangles,unsigned int Max_Triangles_per_Leaf):
				 Vertex(0),Triangle_Index(0),Triangle_Ids(0),Max_Num_of_Triangles(Max_Triangles_per_Leaf)
		{
			Obb_Tree = this->Build_OBB_Tree(Vertex,Num_of_Vertex,Tri_List,Tri_Ids,Num_of_Triangles);
			this->Num_of_Primitives = 0;
			this->Max_Num_of_Primitives = 0;
		}

		/**
		* Destrutor
		*/
		~COLLISION_OBB_TREE(void)
		{
			this->Destroy_OBB_Tree();
		}

		/**
		* Constroi a OBB_TREE dado os vertices e os triangulos
		*/
		bool Create_OBB_Tree(const float* Vertex,unsigned int Num_of_Vertex,
							 const unsigned int* Tri_List,const int* Tri_Ids,unsigned int Num_of_Triangles)
		{
			this->Obb_Tree = this->Build_OBB_Tree(Vertex,Num_of_Vertex,Tri_List,Tri_Ids,Num_of_Triangles);
			
			if(this->Obb_Tree)
				return(true);
			else
				return(false);
		}


		/**
		* Destroi a arvore se estiver criada
		*/
		void Destroy_OBB_Tree(void)
		{
			if(this->Obb_Tree)
			{
				this->Obb_Tree->Destroy_Nodes();
				delete this->Obb_Tree;
				this->Obb_Tree = NULL;
			}
			return;
		}


		/**
		* Metodos de intersecao
		*/

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra outra COLLISION_OBB_TREE a nivel de triangulo
		*/
		static bool Test_OBB_Tree_Against_OBB_Tree(const COLLISION_OBB_TREE* Obb_Tree_A,const MATRIX4<float>* Obb_Tree_A_Matrix,
												   const COLLISION_OBB_TREE* Obb_Tree_B,const MATRIX4<float>* Obb_Tree_B_Matrix,
                                                   bool Triangle_Against_Triangle)
		{
			//Num_Box_Test = 0;
			//Num_Miss_Test = 0;
			return(Test_OBB_NODE_Against_OBB_NODE(Obb_Tree_A->Obb_Tree,Obb_Tree_A_Matrix,
				   Obb_Tree_B->Obb_Tree,Obb_Tree_B_Matrix,Triangle_Against_Triangle));
		}

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra outra COLLISION_OBB_TREE a nivel de triangulo
		*/
		static bool Test_OBB_Tree_Against_OBB_Tree_Contacts(const COLLISION_OBB_TREE* Obb_Tree_A,const MATRIX4<float>* Obb_Tree_A_Matrix,
																	            const COLLISION_OBB_TREE* Obb_Tree_B,const MATRIX4<float>* Obb_Tree_B_Matrix,
                                                                                COLLISION_CONTACT_PAIR& Contacts)
		{
			//Num_Box_Test = 0;
			//Num_Miss_Test = 0;
			Test_OBB_NODE_Against_OBB_NODE_Contacts(Obb_Tree_A->Obb_Tree,Obb_Tree_A_Matrix,Obb_Tree_B->Obb_Tree,
				                                    Obb_Tree_B_Matrix,Contacts);
			if(Contacts.Contact_Pairs.Get_Total_Elements()> 0)
				return(true);
			else
				return(false);
		}

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um volume envolvente
		*/
		static bool Test_OBB_Tree_Against_Bounding_Volume(const COLLISION_OBB_TREE* Obb_Tree,const MATRIX4<float>* Obb_Tree_Matrix,
														  const BOUNDING_VOLUME<float>* BV,const MATRIX4<float>* BV_Space,
                                                          bool Triangle_Agaist_BV)
		{
			return(Test_OBB_NODE_Against_Bounding_Volume(Obb_Tree->Obb_Tree,Obb_Tree_Matrix,
														 BV,BV_Space,Triangle_Agaist_BV));
		}

        /**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um volume envolvente
		*/
		static bool Test_OBB_Tree_Against_Bounding_Volume_Contacts(const COLLISION_OBB_TREE* Obb_Tree,const MATRIX4<float>* Obb_Tree_Matrix,
														  const BOUNDING_VOLUME<float>* BV,const MATRIX4<float>* BV_Space,
                                                          COLLISION_CONTACT_PAIR& Contacts)
		{
           Test_OBB_NODE_Against_Bounding_Volume_Contacts(Obb_Tree->Obb_Tree,Obb_Tree_Matrix,BV,BV_Space,Contacts);
            if(Contacts.Contact_Pairs.Get_Total_Elements() > 0)
                return(true);
            else
                return(false);
            
		}

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um raio
		*/
		static float Test_OBB_Tree_Against_Ray(const COLLISION_OBB_TREE* Obb_Tree,const MATRIX4<float>* Obb_Tree_Matrix,
											   const RAY3D<float>& Ray,bool Ray_Against_Triangle)
		{
			return(Test_OBB_Tree_Against_Ray(Obb_Tree->Obb_Tree,Obb_Tree_Matrix,
											 Ray,Ray_Against_Triangle));
		}

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um raio e retorna o triangulo no caso
		* de intersecao.Tri_Vertex_List deve ser um vetor de tipo unsigned int de tamanho 3. (Somente 1 triangulo)
		*/
		static float Test_OBB_Tree_Against_Ray_Contacts(const COLLISION_OBB_TREE* Obb_Tree,const MATRIX4<float>* Obb_Tree_Matrix,
											            const RAY3D<float>& Ray,COLLISION_CONTACT_PAIR& Contacts)
		{
			return(Test_OBB_Tree_Against_Ray_Contacts(Obb_Tree->Obb_Tree,Obb_Tree_Matrix,Ray,Contacts));
		}

		/**
		* Determina se uma COLLISION_OBB_TREE esta em colisao contra um plano
		*/
		static bool Test_OBB_Tree_Against_Plane(const COLLISION_OBB_TREE* Obb_Tree,const MATRIX4<float>* Obb_Tree_Matrix,
												const PLANE3<float>& Plane,bool Plane_Against_Triangle)
		{
			return(Test_OBB_Tree_Against_Plane(Obb_Tree->Obb_Tree,Obb_Tree_Matrix,
											   Plane,Plane_Against_Triangle));
		}				
			
		/**
		* Retorna o numero maximo de triangulos por no
		*/
		unsigned int Get_Max_Triangles_per_Leaf(void)const
		{
			return(this->Max_Num_of_Triangles);
		}

		
		/**
		* Funcoes de debug
		* Desenha a arvore ou o modelo.
		*/
		void Render_Tree(void)
		{
			if(this->Obb_Tree)
				this->Obb_Tree->Render_OBB_Tree();
			return;
		};
		
		void Render_Model(void)
		{
			if(this->Obb_Tree)
				this->Obb_Tree->Render_Model();
			return;
		};

		/**
		* Deve ser chamada para arrumar o estado para comecar a receber os triangulos
		*/
		void Begin_Triangle_Insertion(void);

		/**
		* Processa todos os triangulos inseridos
		*/
		void End_Triangle_Insertion(unsigned int Max_Tri_Per_Leaf = 1);

		/**
		* Adiciona um novo triangulo a OBB-TRee
		*/
		void Add_Triangle(float* V1,float* V2,float* V3,int Tri_Id);
		
    /**
    * Determina se a OBB_Tree foi criada
    */
    bool Is_OBB_Tree_Created(void)const
    {
      return(this->Obb_Tree != NULL);
    }
};

#endif
