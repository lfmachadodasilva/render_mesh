/*****************************************************************
*                                                                *
*         @module: Handler                                       *
*           @file: util.h                                        *
*             @id: VglLibUtil                                    *
*        @package: VglLib                                        *
*          @owner: TecGraf                                       *
*         @author: CPALOMO                                       *
*        @version: 1.0                                           *
*   @creationdate: sep/2011                                      *
*                                                                *
******************************************************************/

/*****************************************************************
 *   Module Controls                                             *
 *****************************************************************/
#ifndef VGL_LIB_UTIL_H
#define VGL_LIB_UTIL_H

/*****************************************************************
 *   Includes                                                    *
 *****************************************************************/
#include <alg/vector.h>
#include <alg/plane.h>
#include <vgl/hnd/selection.h>
#include <vgllib/plane.h>
#include <vgllib/defines.h>

/*****************************************************************
 *  Class Definition                                             *
 *  VglUtil.                                                     *
 *  Provides utilities for vgl libraries.                        *
 *****************************************************************/
class VGLLIBAPI VglLibUtil
{
public:
  /**
   * Compute radius in world space, given the desired radius in
   * window space.
   * @param radiusWinSpace desired radius in pixels.
   * @param isOrthoProjection whether camera has an ortho proj.
   */
  static float GetRadiusInWorldSpace (int radiusWinSpace, 
                                      bool isOrthoProjection);

  /**
   * Compute radius in world space, given the desired radius in
   * window space and original point in world space.
   * @param pointWorldSpace reference point in world space
   * @param radiusWinSpace desired radius in pixels.
   * @param isOrthoProjection whether camera has an ortho proj.
   */
  static float GetRadiusInWorldSpace (const AlgVector& pointWorldSpace,
                                      float radiusWinSpace, 
                                      bool isOrthoProjection);

  static const char* ClassName () { return "VglUtil"; }
};

#endif
