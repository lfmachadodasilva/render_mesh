/* bvtree.h: árvore de volumes envolventes
 * Otávio Braga (obraga@tecgraf.puc-rio.br), 
 * Última modificação: Aug 29 2003 */

#ifndef BVTREE_H
#define BVTREE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
# ifdef BVTREE_DLL
#  define BVTREEAPI __declspec(dllexport)
# else
#  define BVTREEAPI 
# endif
#else
# define BVTREEAPI
#endif

typedef enum {

    /* Tipos de volumes envolventes suportados*/
    BVTREE_BV_AABB,       /* caixa alinhada com os eixos */
    BVTREE_BV_OBB,        /* caixa orientada */
    BVTREE_BV_SPHERE,

} bvtree_enum;

typedef struct bvtree_node bv_t;

/* Operacões de construção/atualização da árvore de volumes envolventes. */

/* Retorna um volume envolvente vazio do tipo escolhido ou NULL caso não
 * tenha sido possível criar o volume. */
BVTREEAPI bv_t *bvtree_newbv(bvtree_enum bvtype);

/* Destrói um volume envolvente e o remove da hierarquia. */
BVTREEAPI void bvtree_delbv(bv_t *bv);

/* O volume bv passa a envolver (somente) os pontos fornecidos entre
 * bvtree_(begin/end)points. */
BVTREEAPI void bvtree_beginpoints(void);
BVTREEAPI int bvtree_addpoint(float x, float y, float z);
BVTREEAPI void bvtree_endpoints(bv_t *bv);

/* Esvazia o volume bv */
BVTREEAPI void bvtree_empty(bv_t *bv);

/* torna o volume bv ilimitado/limitado. Os ancestrais de um volume ilimitado
 * sao automaticamente considerados ilimitados. */
BVTREEAPI void bvtree_setunbounded(bv_t *bv);
BVTREEAPI void bvtree_setbounded(bv_t *bv);

/* parentbv passa a também envolver childbv transformado por sua transformação
 * local. Os dois volumes devem ser do mesmo tipo. */
BVTREEAPI void bvtree_addchild(bv_t *parentbv, bv_t *childbv);

/* Remove o volume 'childbv' da lista de filhos de seu pai, caso haja um.
 * Retorna 1 caso bem sucedido (se childbv tiver um pai), 0 caso contrario. */
BVTREEAPI int bvtree_detachfromparent (bv_t *childbv);

/* m passa a ser a transformação do volume bv no sistema de coordenadas do pai.
 * É guardada uma cópia da matriz m. Retorna um valor diferente de zero caso a
 * transformação tenha sido alterada corretamente. */
BVTREEAPI int bvtree_settransform(bv_t *bv, float m[16]);

/* Desenha o volume bv em seu sistema de coordenadas local. */
BVTREEAPI void bvtree_drawbv(bv_t *bv);

/* Retorna o centro do volume bv em seu sistema de coordenadas local. */
BVTREEAPI void bvtree_getcenter(bv_t *bv, float *x, float *y, float *z);

/* Retorna o raio de uma esfera que envolve o volume em seu sistema de
 * coordenadas local. */
BVTREEAPI float bvtree_getradius(bv_t *bv);

/* Retorna uma caixa orientada que envolve o volume em seu
 * sistema de coordenadas local. */ 
BVTREEAPI void bvtree_getaabb(bv_t *bv, float *xmin, float *xmax, float *ymin, float *ymax, float *zmin, float *zmax);

/* Retorna as dimensoes de uma caixa orientada que envolve o volume em seu
 * sistema de coordenadas local. */ 
BVTREEAPI void bvtree_getaabbdimensions(bv_t *bv, float *dx, float *dy, float *dz);

#ifdef __cplusplus
}
#endif

#endif /* BVTREE_H */
