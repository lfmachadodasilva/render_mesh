/*****************************************************************
*                                                                *
*         @module: Handler                                       *
*           @file: plane.h                                       *
*             @id: VglManipPlaneHandler                          *
*        @package: VglLib                                        *
*          @owner: TecGraf                                       *
*         @author: MALF/RODESP/TCS                               *
*        @version: 1.0                                           *
*   @creationdate: oct/2006                                      *
*                                                                *
******************************************************************/

/*****************************************************************
 *   Module Controls                                             *
 *****************************************************************/
#ifndef VGL_MANIP_PLANE_H
#define VGL_MANIP_PLANE_H

/*****************************************************************
 *   Includes                                                    *
 *****************************************************************/
#include <alg/matrix.h>
#include <alg/vector.h>
#include <alg/plane.h>
#include "defines.h"

/*****************************************************************
 *   Class Definition                                            *
 *   Model class for VglPlaneHandler.                            *
 *   Represents the plane which is manipulated.                  *
 *****************************************************************/
class VGLLIBAPI VglManipPlane
{
private:
  AlgVector m_center;
  AlgVector m_normal;
  AlgVector m_up;
  AlgVector m_right;
  AlgVector m_minbox;
  AlgVector m_maxbox;
  AlgVector m_points[9];
  float     m_width;
  float     m_height;

  int IntersectRay( AlgPlane plane, AlgVector p0, AlgVector dir, float* t );
  void UpdatePoints( void );

  /*****************************************************************
   * @Method GetBaseMatrix                                         *
   * Gets the plane base matrix at the given plane center.         *
   *****************************************************************/
  AlgMatrix GetBaseMatrix( AlgVector center );
  AlgMatrix GetInverseBaseMatrix( AlgVector center );

public:

  enum
  {
    POINT_CENTER = 0  ,
    POINT_BOTTOM_RIGHT,
    POINT_RIGHT       ,
    POINT_TOP_RIGHT   ,
    POINT_TOP         ,
    POINT_TOP_LEFT    ,
    POINT_LEFT        ,
    POINT_BOTTOM_LEFT ,
    POINT_BOTTOM      ,
    POINT_MAX         ,
  };

  /*****************************************************************
   * @Method Constructor                                           *
   *****************************************************************/
  VglManipPlane( void );

  /*****************************************************************
   * @Method Destructor                                            *
   *****************************************************************/
  ~VglManipPlane( void );

  /*****************************************************************
   * @Method GetPlane                                              *
   *****************************************************************/
  AlgPlane GetPlane( void )
  {
    return AlgPlane( m_normal, -m_normal.Dot( m_center ) );
  }
  void GetPlane( float *x, float *y, float *z, float *w )
  {
    *x = m_normal.x;
    *y = m_normal.y;
    *z = m_normal.z;
    *w = -m_normal.Dot( m_center );
  }

  /*****************************************************************
   * @Method SetSize                                               *
   * Sets plane dimensions.                                        *
   *****************************************************************/
  void SetSize( float width, float height );

  float GetWidth( void )
  {
    return m_width;
  }

  float GetHeight( void )
  {  
    return m_height;
  }

  /*****************************************************************
   * @Method SetBox                                                *
   * Sets model bounding box used for plane fit.                   *
   *****************************************************************/
  void SetBox( float xmin, float xmax,
               float ymin, float ymax,
               float zmin, float zmax );

  void GetBox( float* xmin, float* xmax,
               float* ymin, float* ymax,
               float* zmin, float* zmax )
  {
    *xmin = m_minbox.x; *xmax = m_maxbox.x;
    *ymin = m_minbox.y; *ymax = m_maxbox.y;
    *zmin = m_minbox.z; *zmax = m_maxbox.z;


  }
  
  /*****************************************************************
   * @Method Fit                                                   *
   * Fits plane size to the defined bounding box.                  *
   *****************************************************************/
  void Fit( void );

  /*****************************************************************
   * @Method SetCenter                                             *
   * Sets plane center.                                            *
   *****************************************************************/
  void SetCenter( AlgVector center );
  void SetCenter( float x, float y, float z );
  
  AlgVector GetCenter( void )
  {
    return m_center;
  }

  /*****************************************************************
   * @Method SetRight                                              *
   * Sets plane normal.                                            *
   *****************************************************************/
  void SetNormal( AlgVector normal );
  void SetNormal( float x, float y, float z );

  AlgVector GetNormal( void )
  {
    return m_normal;
  }

  /*****************************************************************
   * @Method SetRight                                              *
   * Sets plane up vector.                                         *
   *****************************************************************/
  void SetUp( AlgVector up );
  void SetUp( float x, float y, float z );

  AlgVector GetUp( void )
  {
    return m_up;
  }

  /*****************************************************************
   * @Method SetRight                                              *
   * Sets plane right vector.                                      *
   *****************************************************************/
  void SetRight( AlgVector right );
  void SetRight( float x, float y, float z );

  AlgVector GetRight( void )
  {
    return m_right;
  }

  /*****************************************************************
   * @Method SetRight                                              *
   * Sets positions of the plane corners.                          *
   * {BOTTOM_LEFT, BOTTOM_RIGHT, TOP_LEFT, TOP_RIGHT}              *
   *****************************************************************/
  void SetCorners( float* corners )
  {
    float bl[3], br[3], tl[3], tr[3];

    bl[0] = corners[0];
    bl[1] = corners[1];
    bl[2] = corners[2];

    br[0] = corners[3];
    br[1] = corners[4];
    br[2] = corners[5];

    tr[0] = corners[6];
    tr[1] = corners[7];
    tr[2] = corners[8];

    tl[0] = corners[9];
    tl[1] = corners[10];
    tl[2] = corners[11];

    SetPoint( POINT_BOTTOM_LEFT , bl[0], bl[1], bl[2] );
    SetPoint( POINT_BOTTOM_RIGHT, br[0], br[1], br[2] );
    SetPoint( POINT_TOP_LEFT    , tl[0], tl[1], tl[2] );
    SetPoint( POINT_TOP_RIGHT   , tr[0], tr[1], tr[2] );
  }

  void GetCorners( float* corners )
  {
    AlgVector bl = GetPoint(POINT_BOTTOM_LEFT);
    AlgVector br = GetPoint(POINT_BOTTOM_RIGHT);
    AlgVector tl = GetPoint(POINT_TOP_LEFT);
    AlgVector tr = GetPoint(POINT_TOP_RIGHT);

    corners[0]  = bl.x;
    corners[1]  = bl.y;
    corners[2]  = bl.z;

    corners[3]  = br.x;
    corners[4]  = br.y;
    corners[5]  = br.z;

    corners[6]  = tr.x;
    corners[7]  = tr.y;
    corners[8]  = tr.z;

    corners[9]  = tl.x;
    corners[10] = tl.y;
    corners[11] = tl.z;
  }

  /*****************************************************************
   * @Method SetRight                                              *
   * Gets one of the plane points, defined by enum in this class.  *
   *****************************************************************/
  void SetPoint( int i, AlgVector point );

  void SetPoint( int i, float x, float y, float z );

  AlgVector GetPoint( int i )
  {
    return m_points[ i ];
  }

  void GetPoint( int i, float* x, float* y, float* z )
  {
    *x = m_points[i].x; *y = m_points[i].y; *z = m_points[i].z;
  }
};

#endif

