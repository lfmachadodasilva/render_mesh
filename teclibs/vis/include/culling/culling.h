/* culling.h
 * Otavio Braga (obraga@tecgraf.puc-rio.br), 2002-2003 */

#ifndef CULLING_H
#define CULLING_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
# ifdef CULLING_DLL
#  define CULLINGAPI __declspec(dllexport)
# else
#  define CULLINGAPI 
# endif
#else
# define CULLINGAPI
#endif

#define CULL_MAXFRUSTUMS 10
  
typedef enum {
    
    /* Resultados do teste de intersecao com o frustum */
    CULL_OUTSIDE = 0,
    CULL_INSIDE,
    CULL_INTERSECT,

    /* numero de planos de clipping alem dos 6 do frustum */
    CULL_MAX_CLIP_PLANES = 10,

    CULL_LEFT_PLANE = 0,
    CULL_RIGHT_PLANE,
    CULL_BOTTOM_PLANE,
    CULL_TOP_PLANE,
    CULL_NEAR_PLANE,
    CULL_FAR_PLANE,

} cull_enum;

/* Especificacao de planos de clipping. */

/* Quando e' feito um teste de visibilidade, temos um conjunto de planos de
 * clipping definidos (com um maximo de 6 + MAX_CLIP_PLANES). Um objeto nao
 * esta' visivel quando estiver completamente contido em algum semi-espaco
 * positivo definido por um plano, i.e, quando para algum plano definido pela
 * equacao Ax + By + Cz + D = 0 tenhamos Ax + By + Cz + D > 0 para todos os
 * pontos do volume. 
 * O argumento equation aponta para os quatro coeficientes da equacao do
 * plano Ax + By + Cz + D = 0, onde os pontos descartados sao aqueles onde
 * Ax + By + Cz + D > 0 (0 <= plane < 6+MAX_CLIP_PLANES).
 * 
 * Esta funcao adiciona o plano ao frustum de id 'id'.
 * (0 <= id < CULL_MAXFRUSTUMS).
 */
CULLINGAPI void cull_addplanef(int id, int plane, float *equation);

/* Desabilita um plano de cliping no frustum de id 'id'.
 * (0 <= id < CULL_MAXFRUSTUMS).
 */
CULLINGAPI void cull_disableplanef(int id, int plane);

/* Habilita um plano de cliping no frustum de id 'id'.
 * (0 <= id < CULL_MAXFRUSTUMS).
 */
CULLINGAPI void cull_enableplanef(int id, int plane);

/* Extrai os 6 planos do frustum a partir da matriz m, que leva os pontos
 * do sistema de coordenadas onde o frustum esta' definido para o espaco
 * normalizado [-1,1]^3.
 * Os planos sao guardados com os identificadores de 0 a 5, na ordem:
 * esquerdo, direito, baixo, cima, perto, longe.
 * Esta funcao armazena os planos no frustum de id 'id'.
 * (0 <= id < CULL_MAXFRUSTUMS).
 */
CULLINGAPI void cull_setfrustumf(int id, float *m);

/* Teste de intersecao entre o volume bv e os planos de clipping, onde a
 * transformacao m leva o volume bv para o sistema de coordenadas onde os
 * planos foram definidos. Se m for NULL, a transformacao e' a identidade.
 * Retorna CULL_OUTSIDE caso o volume esteja no semi-espaco positivo de
 * algum plano, CULL_INSIDE caso esteja no semi-espaco negativo de todos
 * os planos ou CULL_INTERSECT caso contrario.
 * Esta funcao utiliza os planos do frustum de id 'id'.
 * (0 <= id < CULL_MAXFRUSTUMS).
 */
CULLINGAPI int cull_intersectfrustumf(int id, bv_t *bv, float *m);

/* Retorna a distancia com sinal do centro do volume bv ao plano plane, no
 * sistema de coordenadas do frustum. As distancias positivas estao na direcao
 * do exterior do frustum.
 * Esta funcao utiliza os planos do frustum de id 'id'.
 * (0 <= id < CULL_MAXFRUSTUMS).
 */
CULLINGAPI float cull_distancetoplanef(int id, bv_t *bv, int plane, float *m);

/* Retorna 1 se o volume bv esta' totalmente no semi-espaco negativo do plano 'plane',
 * 0 caso contrario.
 */
CULLINGAPI int cull_neghalfspace(bv_t *bv, int plane);

#define cull_setfrustum(m)               cull_setfrustumf(0,m)
#define cull_addplane(plane,equation)    cull_addplanef(0,plane,equation)
#define cull_enableplane(plane)          cull_enableplanef(0,plane)
#define cull_disableplane(plane)         cull_disableplanef(0,plane)
#define cull_intersectfrustum(bv,m)      cull_intersectfrustumf(0,bv,m)
#define cull_distancetoplane(bv,plane,m) cull_distancetoplanef(0,bv,plane,m)

#ifdef __cplusplus
}
#endif

#endif /* CULLING_H */
