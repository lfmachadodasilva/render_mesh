/* bvtree_be.h: arvore de volumes envolventes
 * Otavio Braga (obraga@tecgraf.puc-rio.br), 2002-2003 */

#ifndef BVTREE_BE_H
#define BVTREE_BE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bvtree.h"
#include "bv.h"

struct bvtree_node {
    struct bv *bv;                        /* volume no sistema local */
    float *transform;                     /* transformacao em relacao ao pai */
    bv_t *lchild, *rsibling, *parent;     /* hierarquia */
    
    unsigned int unboundeddesc;           /* numero de descendentes ilimitados */
                                          /* um volume com um numero de descendentes
                                           * ilimitados diferente de zero e' considerado
                                           * ilimitado */
    char unbounded:1;                     /* indica se o volume foi definido explicitamente
                                           * como ilimitado */

    char isupdate:1;                      /* indica se o volume esta' atualizado */

#ifdef CULLING
    signed char plane_hint;   /* plano que descartou o volume no ultimo teste */
    unsigned short maskedoff; /* mascara indicando em que planos o volume esta'
                                 completamente no semi-espaco negativo (os
                                 filhos desse no' nao precisam ser testados
                                 contra esses planos) */
#endif
};

/* Forca a atualizacao de todos os volumes desatualizados na sub-arvore com
 * raiz em bv. Um volume passa a estar desatualizado quando um descendente e'
 * acrescentado ou removido ou a transformacao de um descendente e' alterada. */
BVTREEAPI void bvtree_flushupdates(bv_t *bv);

#ifdef __cplusplus
}
#endif

#endif /* BVTREE_BE_H */
