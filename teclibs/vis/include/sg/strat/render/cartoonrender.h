/**
* Estrategia de renderizacao em cartoon.
* 
* Jeronimo Silvério Venetillo
* 07/12/2004
*/

#ifndef jsv_cartoonStrategy
#define jsv_cartoonStrategy

#include "flexrender.h"
#include <sg/shp/line.h>
#include <sg/shp/mesh.h>
#include <sg/state/texture.h>

#ifndef M_1_PI 
#define M_1_PI     0.318309886183790671538
#endif

/**
* Cartoon Rendering Strategy
*
* Esta estrategia de rendering desenha a 
*  cena em estilo cartoon.
*
* Possui os seguintes metodos para controle da renderização:
* - usingBorders
* - usingCreases
* - usingAntiAlias
* - usingTexture
* - usingShade
*/
class SGCartoonRender : public SGFlexRender
{
public:
	
	SGCartoonRender();
	
	void usingBorders  ( bool value ){ vBorders   = value; }
	void usingCreases  ( bool value ){ vCreases   = value; }
	void usingAntiAlias( bool value ){ vAntiAlias = value; }
	void usingTexture  ( bool value ){ vTextures  = value; }
	void usingShade    ( bool value ){ vShade     = value; }
	
	bool usingBorders()  { return vBorders;   }
	bool usingCreases()  { return vCreases;   }
	bool usingAntiAlias(){ return vAntiAlias; }
	bool usingTexture()  { return vTextures;  }
	bool usingShade()    { return vShade;     }

	/**
	* Deve ser chamada uma vez antes da primeira renderização da cena.
	*
	* Todos os elementos que farão parte da cena devem estar HABILITADOS.
	* Chamadas posteriores nao farao efeito até que PosRender seja chamado.
	*
	* @param s        Cena que será renderizada.
	*/
	void PreRender( SGScene* s, float minAngle, float maxAngle );

	/**
	* Deve ser chamada uma vez depois da ultima renderização da cena.
	*
	* Todos os elementos que farão parte da cena devem estar HABILITADOS.
	* Chamadas posteriores só terão efeito após uma chamada de PreRender.
	*
	* @param s Cenas que não será mais renderizada.
	*/
	void PosRender( SGScene* s );

	/**
	* Caso um objeto seja adicionado na cena apos um PreRender,
	*   uma chamada a este metodo deverá ser feita antes do objeto
	*   ser renderizado.
	* Este método inicializa todos os shapes ligados a este objeto.
	*/
	void PreRender(SGObject* o);
	
	/**
	* Caso um shape seja adicionado na cena apos um PreRender,
	*   uma chamada a este metodo deverá ser feita antes do shape
	*   ser renderizado.
	*/
	void PreRender(SGShape* s);
	
	/**
	* Renderiza a cena.
	*/
	void Render( SGScene* s );
	
	int Load( SGLight* l );
	
	int Load (SGObject* o);
	
	void Load( SGState* s );
	
	void Unload( SGState* s );
	
	void Load(SGShape* s);
	
protected:

	/**
	* Usado no PosRender da Cena.
	*/
	void PosRender(SGShape* s);
	
	/**
	* Usado no PosRender da Cena.
	*/
	void PosRender(SGObject* o);

	/**
	* Retorna a coordenada de textura apropriada.
	*
	* @param vertex Coordenadas do vertice.
	* @param lightPosition Coordenadas da Luz.
	* @param normal Vetor normal ao vertice que a textura sera aplicada
	* @returns A coordenada de textura ou -1 caso nao se aplique.
	*/
	float getTextureCoordinate(const float* vertex, float* lightPosition, const float* normal);
	
	/**
	* Cria uma textura baseado no tipo de material e no tipo de iluminacao.
	*/
	float* createTexture();
	
	/**
	* Cria a lista de arestas da malha.
	*/
	SGLines* buildCreaseVector(SGMesh* m);
	
	/**
	* Calcula a normal do triangulo formado por p1,p2 e p3.
	*/
	void CalculateNormal( const float* p1, const float* p2, const float* p3, float* n );
	
	/**
	* @param v1 Vetor com as coordenadas (x,y,z)
	* @param v2 Vetor com as coordenadas (x,y,z)
	* @returns O menor angulo em graus entre os dois vetores. Caso um dos vetores seja nulo, o valor retornado e 90º.
	*/
	float angle( float* v1, float* v2 );
	
	
	//Controle
	SGLines** vCreasesList;		/** Lista das arestas dos modelos da cena. */
	SGMesh**  vMeshList;			/** Lista dos modelos da cena. */
	SGShape**  vSGitedShapeList;	/** Lista auxiliar com os shapes da cena. */
	int vFirstIndex;				/** Indice de controle. */
	int vLastIndex;					/** Indice de controle. */
	bool vok;						/** Variavel de controle. */
	bool first;						/** Variavel de controle. Indica se podemos chamar PreRender. */
	bool last;						/** Variavel de controle. Indica se estamos na PosRender. */
	float vMinAngle;				/** Menor angulo entre normais para que o lado dos triangulos adjacentes seja considerado uma aresta. */
	float vMaxAngle;				/** Maior angulo entre normais para que o lado dos triangulos adjacentes seja considerado uma aresta. */
	bool isShadeLoaded;				/** Indica se a textura do cartoon Shade está ou não carregada. */

	//Shade
	AlgVector vLightPos;			/** Posicao da luz no espaco global. */
	AlgVector vLightLocalPos;		/** Posicao da luz no espaco local. */
	float vLightAmbientColor[3];	/** Componente ambiente da luz. */
	float vLightDiffuseColor[3];	/** Componente difusa da luz. */
	float vLightIntensity;			/** Intensidade da luz. */
	float vGlobalAmbientColor[3];	/** Componente ambiente global. */
	bool vLinearFilter;				/** Indica se o shade tera o filtro LINEAR ou NEAREST */
	int vNTexels;					/** Numero de texels do shade. */
	int vNLightTexels;				/** Numero de texels iluminados. */
	int vNTransitionTexels;			/** Numero de texels de transicao. */
	int vNDarkTexels;				/** Numero de texels nao iluminados. */
	float* vTexture;				/** Vetor com os valores de textura do cartoon Shade. */
	SGTexture* texture;			/** Objeto de textura que representa o cartoon Shade. */
	bool vTextures;					/** Indica se os modelos tem ou não textura. */
	bool vShade;					/** Indica se os modelos usarao cartoon Shade (iluminacao). */

	//Linhas
	bool vAntiAlias;				/** Indica se o openGl fara AntiAlias das linhas. */
	bool vBorders;					/** Indica se os modelos serão desenhados com silhueta. */
	bool vCreases;					/** Indica se os modelos serão desenhados com arestas. */
	float vBorderColor[3];			/** Cor da silhueta.*/
	float vCreasesColor[3];			/** Cor das arestas.*/
	float vBorderWidth;				/** Espessura da silhueta.*/
	float vCreasesWidth;			/** Espessura das arestas.*/


};
#endif
