#ifndef MODELPROCESSOR_H
#define MODELPROCESSOR_H

/***************************************************************************
*  $MCI Módulo de definição: ModelProcessor  Processador de Modelo
*
*  Arquivo gerado:      modelprocessor.h
*  Classe:				      ModelProcessor
*
*  Projeto: Biblioteca de Line Integral Convolution
*  Autores: Thiago Marques Toledo (tmt)
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       tmt   17/mai/2011 início desenvolvimento
*
*  $ED Descrição do módulo
*     Interface para um processador de modelo capaz de gerar as imagens
*     necessárias para o processamento de Lic 2D e de Surface Lic.
*
***************************************************************************/

#include "image.h"

namespace Lic {

	class ModelProcessor {

	public:

    // Construtor Padrão
    ModelProcessor();
    
    // Destrutor
    virtual ~ModelProcessor();
		
    // Processa o modelo e gera imagens de textura necessárias.
    // Para processamento de Lic2D, é necessário apenas gerar
    // uma imagem de campo vetorial e uma imagem de coordenada
    // de textura.
    // Para Surface Lic, todas as imagens são necessárias.
    //
    // Não necessariamente as imagens precisam ser geradas nesse
    // ponto, mas idealmente elas devem ser geradas em uma
    // única passada, utilizando Multiple Render Targets.
    //
    // Caso não sejam geradas neste ponto, a geração pode
    // ocorrer no momento do Get correspondente.
    //
    // Todas as imagens devem ter o mesmo tamanho.
    //
    // Retorna true se modelo foi processado corretamente.
    virtual bool ProcessModel();

    // Retorna imagem com campo vetorial normalizado.
    // RGB - Representa um vetor normalizado (valores em [-1,1])
    // A   - Indica a magnitude do vetor. Por padrão, considera-se a menor
    //       magnitude como 0 e a maior como 1, mas essa escala pode ser
    //       alterada. (valores em ]-oo,+oo[)
    //
    // Para visualização de superfície (SLic), é necessário que as componentes XY
    // representem a componente tangencial à superfície projetada no espaço da tela.
    //
    // Isso é feito da seguinte maneira:
    // A componente Z é determinada por vec dot normal
    // A componente tangencial é ft = vec - z * normal
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
    // Imagem obrigatória para Lic2D e SLic
    virtual Image * GetVectorImage() = 0;

    // Retorna imagem de coordenada de textura
    // RG - Coordenadas de textura para acesso indireto ao Noise.
    //      Não é necessário preencher caso acesso indireto não seja usado.
    // B  - Valor do Z-Buffer (em [0,1])
    // A  - Em 2D: Escala relativa para valores de Z (análogo à escala de magnitude)
    //      Não é necessário preencher caso não se deseje coloração com
    //      escala arbitrária de Z. Em particular, não é necessário para
    //      coloração com paletas de cor.
    //      Em 3D: Percentual para aplicação de Fog no modelo. É utilizado diretamente
    //      em um mix entre a cor gerada e a cor de fog do OpenGL.
    //
    // Imagem obrigatória para Lic2D e SLic
    virtual Image * GetTexCoordImage() = 0;

    // Retorna imagem de iluminação do modelo
    // RGBA - Cor do modelo em um dado ponto (valores em [0,1])
    //
    // Opcional para Lic2D e SLic
    virtual Image * GetColorImage();

	};

}

#endif