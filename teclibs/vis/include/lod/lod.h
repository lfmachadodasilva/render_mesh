/* lod.h */

#ifndef LOD_H
#define LOD_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
# ifdef LOD_DLL
#  define LODAPI __declspec(dllexport)
# else
#  define LODAPI 
# endif
#else
# define LODAPI
#endif

typedef struct lod {
    unsigned int *faces;
    unsigned int *colfaces;
    float *colvertex_ptr;
    int nfaces;
} lod_t;

typedef struct arrays {
    int nvertices;
    float *vertex_ptr;
    float *normal_ptr;
} arrays_t;

/*
 * Dado um modelo original, retorna um conjunto de modelos simplificados.
 * 
 *     arrays - estrutura que deve ser preenchida com os vertex/normal arrays do
 *              modelo original.
 *     faces  - lista de triangulos no modelo original
 *     nfaces - número de triangulos no modelo original
 *     new_arrays - arrays dos modelos simplificados (compartilhados entre os
 *                  modelos)
 *     lods   - faces dos modelos simplificados
 *     nlods  - número de modelos gerados
 *     maxlods - numero maximo de modelos que devem ser gerados
 */
LODAPI int lod_simplify(const arrays_t *arrays, const unsigned int *faces, int nfaces,
                        arrays_t *new_arrays, lod_t **lods, int *nlods, int maxlods);

#if 0
void lod_enablearray(lod_enum array);
void lod_disablearray(lod_enum array);

void lod_vertexpointer(int size, float *ptr);
void lod_normalpointer(float *ptr);
void lod_colorpointer(float *ptr);
void lod_texcoordpointer(int size, float *ptr);

void lod_getpointer(lod_enum array, float **ptr);

int lod_simplify(unsigned int *faces, int nfaces, lod_t **lods, int *nlods, int maxlods,
    int *nvertices);

#endif

LODAPI int lod_saveply(const char *basename, arrays_t *arrays, lod_t *lods, int nlods);

LODAPI int lod_loadply(const char *path, lod_t **lods, int *nlods);

LODAPI int lod_getlod(double t, int nlods);

#ifdef __cplusplus
}
#endif

#endif
