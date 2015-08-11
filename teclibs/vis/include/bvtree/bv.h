/* bv.h: volumes envolventes 
 * Otavio Braga (obraga@tecgraf.puc-rio.br), 2002-2003*/

#ifndef BV_H
#define BV_H

#include "bvtree.h"

struct bv {
    int type;
    int (*construct)(struct bv *);
    void (*destroy)(struct bv *);
    void (*empty)(struct bv *);
    int (*isempty)(struct bv *);
    void (*addpoints)(struct bv *, float (*point)[3], int npoints);
    void (*merge)(struct bv *, struct bv *bv);
    void (*mergetransformed)(struct bv *, struct bv *bv, float *m);
    int (*halfspace)(struct bv *, float *plane);
    void (*draw)(struct bv *);
    void (*copy)(struct bv *, struct bv *bv);
    void (*getcenter)(struct bv *, float *x, float *y, float *z);
    float (*getradius)(struct bv *);
    void (*getaabb)(struct bv *, float *xmin, float *xmax, float *ymin, float *ymax, float *zmin, float *zmax);
    void (*getaabbdimensions)(struct bv *, float *dx, float *dy, float *dz);
    void *priv;
};

struct bv *bv_new(bvtree_enum type);

#define declare_bv_ops(bvname) \
    int bvname##_construct(struct bv *); \
    void bvname##_destroy(struct bv *); \
    void bvname##_empty(struct bv *);  \
    int bvname##_isempty(struct bv *); \
    void bvname##_addpoints(struct bv *, float (*points)[3], int npoints); \
    void bvname##_merge(struct bv *, struct bv *bv); \
    void bvname##_mergetransformed(struct bv *, struct bv *bv, float *m); \
    int bvname##_halfspace(struct bv *, float *plane); \
    void bvname##_draw(struct bv *); \
    void bvname##_copy(struct bv *, struct bv *bv); \
    void bvname##_getcenter(struct bv *, float *x, float *y, float *z); \
    float bvname##_getradius(struct bv *); \
    void bvname##_getaabb(struct bv *, float *xmin, float *xmax, float *ymin, float *ymax, float *zmin, float *zmax); \
    void bvname##_getaabbdimensions(struct bv *, float *dx, float *dy, float *dz);

declare_bv_ops(aabb)
declare_bv_ops(obb)
declare_bv_ops(sphere)

#endif /* BV_H */
