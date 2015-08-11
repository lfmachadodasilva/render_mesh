#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

/***************************************************************************
*  $MCI M�dulo de defini��o: ModelProcessor  Processador de Modelo
*
*  Arquivo gerado:      modelprocessor.h
*  Classe:				      ModelProcessor
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       tmt   17/mai/2011 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Interface para um processador de modelo capaz de gerar as imagens
*     necess�rias para o processamento de Lic 2D e de Surface Lic.
*
***************************************************************************/

#include "image.h"

namespace Lic {

	class ModelProcessor {

	public:

    // Construtor Padr�o
    ModelProcessor();
    
    // Destrutor
    virtual ~ModelProcessor();
		
    // Processa o modelo e gera imagens de textura necess�rias.
    // Para processamento de Lic2D, � necess�rio apenas gerar
    // uma imagem de campo vetorial e uma imagem de coordenada
    // de textura.
    // Para Surface Lic, todas as imagens s�o necess�rias.
    //
    // N�o necessariamente as imagens precisam ser geradas nesse
    // ponto, mas idealmente elas devem ser geradas em uma
    // �nica passada, utilizando Multiple Render Targets.
    //
    // Caso n�o sejam geradas neste ponto, a gera��o pode
    // ocorrer no momento do Get correspondente.
    //
    // Todas as imagens devem ter o mesmo tamanho.
    //
    // Retorna true se modelo foi processado corretamente.
    virtual bool ProcessModel();

    // Retorna imagem com campo vetorial normalizado.
    // RGB - Representa um vetor normalizado (valores em [-1,1])
    // A   - Indica a magnitude do vetor. Por padr�o, considera-se a menor
    //       magnitude como 0 e a maior como 1, mas essa escala pode ser
    //       alterada. (valores em ]-oo,+oo[)
    //
    // Para visualiza��o de superf�cie (SLic), � necess�rio que as componentes XY
    // representem a componente tangencial � superf�cie projetada no espa�o da tela.
    //
    // Isso � feito da seguinte maneira:
    // A componente Z � determinada por vec dot normal
    // A componente tangencial � ft = vec - z * normal
    // 
    // vp = ModelViewProjection * (vertex)
    // ap = ModelViewProjection * (vertex + ft)
    //
    // fs = (ap.x - vp.x, ap.y - vp.y, z)
    // fs.x = width/height
    //
    // fs2 = normalize(fs.xy)
    // vOut = (fs2.xy, z)
	  //
    // Imagem obrigat�ria para Lic2D e SLic
    virtual Image * GetVectorImage() = 0;

    // Retorna imagem de coordenada de textura
    // RG - Coordenadas de textura para acesso indireto ao Noise.
    //      N�o � necess�rio preencher caso acesso indireto n�o seja usado.
    // B  - Valor do Z-Buffer (em [0,1])
    // A  - Em 2D: Escala relativa para valores de Z (an�logo � escala de magnitude)
    //      N�o � necess�rio preencher caso n�o se deseje colora��o com
    //      escala arbitr�ria de Z. Em particular, n�o � necess�rio para
    //      colora��o com paletas de cor.
    //      Em 3D: Percentual para aplica��o de Fog no modelo. � utilizado diretamente
    //      em um mix entre a cor gerada e a cor de fog do OpenGL.
    //
    // Imagem obrigat�ria para Lic2D e SLic
    virtual Image * GetTexCoordImage() = 0;

    // Retorna imagem de ilumina��o do modelo
    // RGBA - Cor do modelo em um dado ponto (valores em [0,1])
    //
    // Opcional para Lic2D e SLic
    virtual Image * GetColorImage();

	};

}

#endif