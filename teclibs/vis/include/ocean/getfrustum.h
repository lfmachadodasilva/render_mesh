#ifndef FRUSTUM_POINTS
#define FRUSTUM_POINTS

#include "defines.h"

struct frustum_points
{
  double near_down_left_x;
  double near_down_left_y;
  double near_down_left_z;

  double near_down_right_x;
  double near_down_right_y;
  double near_down_right_z;

  double near_up_right_x;
  double near_up_right_y;
  double near_up_right_z;

  double near_up_left_x;
  double near_up_left_y;
  double near_up_left_z;

  double far_down_left_x;
  double far_down_left_y;
  double far_down_left_z;

  double far_down_right_x;
  double far_down_right_y;
  double far_down_right_z;

  double far_up_right_x;
  double far_up_right_y;
  double far_up_right_z;

  double far_up_left_x;
  double far_up_left_y;
  double far_up_left_z;
};

float intersectPoints[12][3];
float intersectPointsMark[12];

float minPoint[3], maxPoint[3];

frustum_points p;


static float frustumPlanes[6][4];

void calculateFrustumPlanes()
{
	float	proj[16];									// For Grabbing The PROJECTION Matrix
	float	modl[16];									// For Grabbing The MODELVIEW Matrix
	float	clip[16];									// Result Of Concatenating PROJECTION and MODELVIEW
	
	glGetFloatv( GL_PROJECTION_MATRIX, proj );			// Grab The Current PROJECTION Matrix
	glGetFloatv( GL_MODELVIEW_MATRIX, modl );			// Grab The Current MODELVIEW Matrix

	// Concatenate (Multiply) The Two Matricies
	clip[ 0] = modl[ 0] * proj[ 0] + modl[ 1] * proj[ 4] + modl[ 2] * proj[ 8] + modl[ 3] * proj[12];
	clip[ 1] = modl[ 0] * proj[ 1] + modl[ 1] * proj[ 5] + modl[ 2] * proj[ 9] + modl[ 3] * proj[13];
	clip[ 2] = modl[ 0] * proj[ 2] + modl[ 1] * proj[ 6] + modl[ 2] * proj[10] + modl[ 3] * proj[14];
	clip[ 3] = modl[ 0] * proj[ 3] + modl[ 1] * proj[ 7] + modl[ 2] * proj[11] + modl[ 3] * proj[15];

	clip[ 4] = modl[ 4] * proj[ 0] + modl[ 5] * proj[ 4] + modl[ 6] * proj[ 8] + modl[ 7] * proj[12];
	clip[ 5] = modl[ 4] * proj[ 1] + modl[ 5] * proj[ 5] + modl[ 6] * proj[ 9] + modl[ 7] * proj[13];
	clip[ 6] = modl[ 4] * proj[ 2] + modl[ 5] * proj[ 6] + modl[ 6] * proj[10] + modl[ 7] * proj[14];
	clip[ 7] = modl[ 4] * proj[ 3] + modl[ 5] * proj[ 7] + modl[ 6] * proj[11] + modl[ 7] * proj[15];

	clip[ 8] = modl[ 8] * proj[ 0] + modl[ 9] * proj[ 4] + modl[10] * proj[ 8] + modl[11] * proj[12];
	clip[ 9] = modl[ 8] * proj[ 1] + modl[ 9] * proj[ 5] + modl[10] * proj[ 9] + modl[11] * proj[13];
	clip[10] = modl[ 8] * proj[ 2] + modl[ 9] * proj[ 6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[ 8] * proj[ 3] + modl[ 9] * proj[ 7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[ 0] + modl[13] * proj[ 4] + modl[14] * proj[ 8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[ 1] + modl[13] * proj[ 5] + modl[14] * proj[ 9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[ 2] + modl[13] * proj[ 6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[ 3] + modl[13] * proj[ 7] + modl[14] * proj[11] + modl[15] * proj[15];


	// Extract the RIGHT clipping plane
	frustumPlanes[0][0] = clip[ 3] - clip[ 0];
	frustumPlanes[0][1] = clip[ 7] - clip[ 4];
	frustumPlanes[0][2] = clip[11] - clip[ 8];
	frustumPlanes[0][3] = clip[15] - clip[12];
/*
	// Normalize it
	t = (float) sqrt( frustumPlanes[0][0] * frustumPlanes[0][0] + frustumPlanes[0][1] * frustumPlanes[0][1] + frustumPlanes[0][2] * frustumPlanes[0][2] );
	frustumPlanes[0][0] /= t;
	frustumPlanes[0][1] /= t;
	frustumPlanes[0][2] /= t;
	frustumPlanes[0][3] /= t;
*/

	// Extract the LEFT clipping plane
	frustumPlanes[1][0] = clip[ 3] + clip[ 0];
	frustumPlanes[1][1] = clip[ 7] + clip[ 4];
	frustumPlanes[1][2] = clip[11] + clip[ 8];
	frustumPlanes[1][3] = clip[15] + clip[12];
/*
	// Normalize it
	t = (float) sqrt( frustumPlanes[1][0] * frustumPlanes[1][0] + frustumPlanes[1][1] * frustumPlanes[1][1] + frustumPlanes[1][2] * frustumPlanes[1][2] );
	frustumPlanes[1][0] /= t;
	frustumPlanes[1][1] /= t;
	frustumPlanes[1][2] /= t;
	frustumPlanes[1][3] /= t;
*/

	// Extract the BOTTOM clipping plane
	frustumPlanes[2][0] = clip[ 3] + clip[ 1];
	frustumPlanes[2][1] = clip[ 7] + clip[ 5];
	frustumPlanes[2][2] = clip[11] + clip[ 9];
	frustumPlanes[2][3] = clip[15] + clip[13];
/*
	// Normalize it
	t = (float) sqrt( frustumPlanes[2][0] * frustumPlanes[2][0] + frustumPlanes[2][1] * frustumPlanes[2][1] + frustumPlanes[2][2] * frustumPlanes[2][2] );
	frustumPlanes[2][0] /= t;
	frustumPlanes[2][1] /= t;
	frustumPlanes[2][2] /= t;
	frustumPlanes[2][3] /= t;
*/

	// Extract the TOP clipping plane
	frustumPlanes[3][0] = clip[ 3] - clip[ 1];
	frustumPlanes[3][1] = clip[ 7] - clip[ 5];
	frustumPlanes[3][2] = clip[11] - clip[ 9];
	frustumPlanes[3][3] = clip[15] - clip[13];
/*
	// Normalize it
	t = (float) sqrt( frustumPlanes[3][0] * frustumPlanes[3][0] + frustumPlanes[3][1] * frustumPlanes[3][1] + frustumPlanes[3][2] * frustumPlanes[3][2] );
	frustumPlanes[3][0] /= t;
	frustumPlanes[3][1] /= t;
	frustumPlanes[3][2] /= t;
	frustumPlanes[3][3] /= t;
*/

	// Extract the FAR clipping plane
	frustumPlanes[4][0] = clip[ 3] - clip[ 2];
	frustumPlanes[4][1] = clip[ 7] - clip[ 6];
	frustumPlanes[4][2] = clip[11] - clip[10];
	frustumPlanes[4][3] = clip[15] - clip[14];
/*
	// Normalize it
	t = (float) sqrt( frustumPlanes[4][0] * frustumPlanes[4][0] + frustumPlanes[4][1] * frustumPlanes[4][1] + frustumPlanes[4][2] * frustumPlanes[4][2] );
	frustumPlanes[4][0] /= t;
	frustumPlanes[4][1] /= t;
	frustumPlanes[4][2] /= t;
	frustumPlanes[4][3] /= t;
*/

	// Extract the NEAR clipping plane.  This is last on purpose (see pointinfrustumPlanes() for reason)
	frustumPlanes[5][0] = clip[ 3] + clip[ 2];
	frustumPlanes[5][1] = clip[ 7] + clip[ 6];
	frustumPlanes[5][2] = clip[11] + clip[10];
	frustumPlanes[5][3] = clip[15] + clip[14];
/*
	// Normalize it
	t = (float) sqrt( frustumPlanes[5][0] * frustumPlanes[5][0] + frustumPlanes[5][1] * frustumPlanes[5][1] + frustumPlanes[5][2] * frustumPlanes[5][2] );
	frustumPlanes[5][0] /= t;
	frustumPlanes[5][1] /= t;
	frustumPlanes[5][2] /= t;
	frustumPlanes[5][3] /= t;
*/
}

inline bool PointInFrustum( float x, float y, float z )
{
  if( frustumPlanes[5][0] * x + frustumPlanes[5][1] * y + frustumPlanes[5][2] * z + frustumPlanes[5][3] < 0 )
    return false;
  if( frustumPlanes[0][0] * x + frustumPlanes[0][1] * y + frustumPlanes[0][2] * z + frustumPlanes[0][3] < 0 )
    return false;
  if( frustumPlanes[1][0] * x + frustumPlanes[1][1] * y + frustumPlanes[1][2] * z + frustumPlanes[1][3] < 0 )
    return false;
  if( frustumPlanes[2][0] * x + frustumPlanes[2][1] * y + frustumPlanes[2][2] * z + frustumPlanes[2][3] < 0 )
    return false;
  if( frustumPlanes[3][0] * x + frustumPlanes[3][1] * y + frustumPlanes[3][2] * z + frustumPlanes[3][3] < 0 )
    return false;
  if( frustumPlanes[4][0] * x + frustumPlanes[4][1] * y + frustumPlanes[4][2] * z + frustumPlanes[4][3] < 0 )
    return false;
  return true;
}

inline bool BoxInFrustum( float x, float y, float z, float xSize, float ySize, float zSize )
{
	// *Note* - This will sometimes say that a cube is inside the frustum when it isn't.
	// This happens when all the corners of the bounding box are not behind any one plane.
	// This is rare and shouldn't effect the overall rendering speed.

	for(int i = 0; i < 6; i++ )
	{
		if(frustumPlanes[i][0] * (x - xSize) + frustumPlanes[i][1] * (y - ySize) + frustumPlanes[i][2] * (z - zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x + xSize) + frustumPlanes[i][1] * (y - ySize) + frustumPlanes[i][2] * (z - zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x - xSize) + frustumPlanes[i][1] * (y + ySize) + frustumPlanes[i][2] * (z - zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x + xSize) + frustumPlanes[i][1] * (y + ySize) + frustumPlanes[i][2] * (z - zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x - xSize) + frustumPlanes[i][1] * (y - ySize) + frustumPlanes[i][2] * (z + zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x + xSize) + frustumPlanes[i][1] * (y - ySize) + frustumPlanes[i][2] * (z + zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x - xSize) + frustumPlanes[i][1] * (y + ySize) + frustumPlanes[i][2] * (z + zSize) + frustumPlanes[i][3] > 0)
		   continue;
		if(frustumPlanes[i][0] * (x + xSize) + frustumPlanes[i][1] * (y + ySize) + frustumPlanes[i][2] * (z + zSize) + frustumPlanes[i][3] > 0)
		   continue;

		// If we get here, it isn't in the frustum
		return false;
	}
	return true;
}





inline void getFrustumPoints()
{
  int viewport[4];
  double projMatrix[16];
  double modelMatrix[16];

  glGetIntegerv( GL_VIEWPORT, viewport );
  glGetDoublev( GL_PROJECTION_MATRIX, projMatrix );			// Pega a Matriz de Projecao corrente
  glGetDoublev( GL_MODELVIEW_MATRIX, modelMatrix );			// Pega a Matriz ModelView corrente

  gluUnProject( 0.0, 0.0, 0.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.near_down_left_x,
				&p.near_down_left_y,
				&p.near_down_left_z
			  );

  gluUnProject( viewport[2], 0.0, 0.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.near_down_right_x,
				&p.near_down_right_y,
				&p.near_down_right_z
			  );

  gluUnProject( viewport[2], viewport[3], 0.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.near_up_right_x,
				&p.near_up_right_y,
				&p.near_up_right_z
			  );

  gluUnProject( 0.0, viewport[3], 0.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.near_up_left_x,
				&p.near_up_left_y,
				&p.near_up_left_z
			  );

  gluUnProject( 0.0, 0.0, 1.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.far_down_left_x,
				&p.far_down_left_y,
				&p.far_down_left_z
			  );

  gluUnProject( viewport[2], 0.0, 1.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.far_down_right_x,
				&p.far_down_right_y,
				&p.far_down_right_z
			  );

  gluUnProject( viewport[2], viewport[3], 1.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.far_up_right_x,
				&p.far_up_right_y,
				&p.far_up_right_z
			  );

  gluUnProject( 0.0, viewport[3], 1.0,
	            modelMatrix,
	            projMatrix,
				viewport,
	            &p.far_up_left_x,
				&p.far_up_left_y,
				&p.far_up_left_z
			  );

  return;
}

void drawFrustum()
{
  glPushAttrib (GL_LIGHTING_BIT);
  glDisable (GL_LIGHTING);
  glColor3f( 1.0f, 0.0f, 0.0f );
  glBegin(GL_LINES);

    glVertex3d( p.near_down_left_x, p.near_down_left_y, p.near_down_left_z );
    glVertex3d( p.near_down_right_x, p.near_down_right_y, p.near_down_right_z );

    glVertex3d( p.near_down_left_x, p.near_down_left_y, p.near_down_left_z );
    glVertex3d( p.near_up_left_x, p.near_up_left_y, p.near_up_left_z );

    glVertex3d( p.near_down_left_x, p.near_down_left_y, p.near_down_left_z );
    glVertex3d( p.far_down_left_x, p.far_down_left_y, p.far_down_left_z );

    glVertex3d( p.near_up_right_x, p.near_up_right_y, p.near_up_right_z );
    glVertex3d( p.near_down_right_x, p.near_down_right_y, p.near_down_right_z );

    glVertex3d( p.near_up_right_x, p.near_up_right_y, p.near_up_right_z );
    glVertex3d( p.near_up_left_x, p.near_up_left_y, p.near_up_left_z );

    glVertex3d( p.far_up_right_x, p.far_up_right_y, p.far_up_right_z );
    glVertex3d( p.far_down_right_x, p.far_down_right_y, p.far_down_right_z );

    glVertex3d( p.far_up_right_x, p.far_up_right_y, p.far_up_right_z );
    glVertex3d( p.far_up_left_x, p.far_up_left_y, p.far_up_left_z );

    glVertex3d( p.far_up_right_x, p.far_up_right_y, p.far_up_right_z );
    glVertex3d( p.near_up_right_x, p.near_up_right_y, p.near_up_right_z );

    glVertex3d( p.far_down_right_x, p.far_down_right_y, p.far_down_right_z );
    glVertex3d( p.near_down_right_x, p.near_down_right_y, p.near_down_right_z );

    glVertex3d( p.far_up_left_x, p.far_up_left_y, p.far_up_left_z );
    glVertex3d( p.near_up_left_x, p.near_up_left_y, p.near_up_left_z );

    glVertex3d( p.far_down_left_x, p.far_down_left_y, p.far_down_left_z );
    glVertex3d( p.far_down_right_x, p.far_down_right_y, p.far_down_right_z );

    glVertex3d( p.far_down_left_x, p.far_down_left_y, p.far_down_left_z );
    glVertex3d( p.far_up_left_x, p.far_up_left_y, p.far_up_left_z );

  glEnd();
  glPopAttrib();
}

int getInterceptionFrustumPlaneDefault()
{
/*  float plane_normal_x = 0;
  float plane_normal_y = 1;  
  float plane_normal_z = 0;

  float plane_origin_x = 0;
  float plane_origin_y = 0;
  float plane_origin_z = 0;

  float d = - (plane_normal_x * plane_origin_x + plane_normal_z * plane_origin_z + plane_normal_z * plane_origin_z);
*/
  float d = 0;
  d = 16;
  int i;

  for ( i = 0; i <= 12; i++ ) intersectPointsMark[i] = 0;

  int firstPlaneIntercepted = 0;
  int intersectionsCounter = 0;

  if (((p.near_down_left_y < d)&&(p.near_down_right_y > d)) || ((p.near_down_left_y > d)&&(p.near_down_right_y < d)))
  {
//	float t = p.near_down_left_y / (p.near_down_left_y - p.near_down_right_y);
	float t = (p.near_down_left_y - d) / ((p.near_down_left_y - d) - (p.near_down_right_y - d));
	intersectPoints[intersectionsCounter][0] = p.near_down_left_x + t * ( p.near_down_right_x - p.near_down_left_x );
	intersectPoints[intersectionsCounter][1] = p.near_down_left_y + t * ( p.near_down_right_y - p.near_down_left_y );
	intersectPoints[intersectionsCounter][2] = p.near_down_left_z + t * ( p.near_down_right_z - p.near_down_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_down_left_y < d)&&(p.near_up_left_y > d)) || ((p.near_down_left_y > d)&&(p.near_up_left_y < d)))
  {
//	float t = p.near_down_left_y / (p.near_down_left_y - p.near_up_left_y);
	float t = (p.near_down_left_y  - d)/ ((p.near_down_left_y - d) - (p.near_up_left_y - d));
	intersectPoints[intersectionsCounter][0] = p.near_down_left_x + t * ( p.near_up_left_x - p.near_down_left_x );
	intersectPoints[intersectionsCounter][1] = p.near_down_left_y + t * ( p.near_up_left_y - p.near_down_left_y );
	intersectPoints[intersectionsCounter][2] = p.near_down_left_z + t * ( p.near_up_left_z - p.near_down_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_down_left_y < d)&&(p.far_down_left_y > d)) || ((p.near_down_left_y > d)&&(p.far_down_left_y < d)))
  {
//	float t = p.near_down_left_y / (p.near_down_left_y - p.far_down_left_y);
	float t = (p.near_down_left_y - d) / ((p.near_down_left_y - d) - (p.far_down_left_y - d));
	intersectPoints[intersectionsCounter][0] = p.near_down_left_x + t * ( p.far_down_left_x - p.near_down_left_x );
	intersectPoints[intersectionsCounter][1] = p.near_down_left_y + t * ( p.far_down_left_y - p.near_down_left_y );
	intersectPoints[intersectionsCounter][2] = p.near_down_left_z + t * ( p.far_down_left_z - p.near_down_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (((p.near_up_right_y < d)&&(p.far_up_right_y > d)) || ((p.near_up_right_y > d)&&(p.far_up_right_y < d)))
  {
//	float t = p.near_up_right_y / (p.near_up_right_y - p.far_up_right_y);
	float t = (p.near_up_right_y - d) / ((p.near_up_right_y - d) - (p.far_up_right_y - d));
	intersectPoints[intersectionsCounter][0] = p.near_up_right_x + t * ( p.far_up_right_x - p.near_up_right_x );
	intersectPoints[intersectionsCounter][1] = p.near_up_right_y + t * ( p.far_up_right_y - p.near_up_right_y );
	intersectPoints[intersectionsCounter][2] = p.near_up_right_z + t * ( p.far_up_right_z - p.near_up_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_up_right_y < d)&&(p.near_down_right_y > d)) || ((p.near_up_right_y > d)&&(p.near_down_right_y < d)))
  {
//	float t = p.near_up_right_y / (p.near_up_right_y - p.near_down_right_y);
	float t = (p.near_up_right_y - d) / ((p.near_up_right_y - d) - (p.near_down_right_y - d));
	intersectPoints[intersectionsCounter][0] = p.near_up_right_x + t * ( p.near_down_right_x - p.near_up_right_x );
	intersectPoints[intersectionsCounter][1] = p.near_up_right_y + t * ( p.near_down_right_y - p.near_up_right_y );
	intersectPoints[intersectionsCounter][2] = p.near_up_right_z + t * ( p.near_down_right_z - p.near_up_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_up_right_y < d)&&(p.near_up_left_y > d)) || ((p.near_up_right_y > d)&&(p.near_up_left_y < d)))
  {
//	float t = p.near_up_right_y / (p.near_up_right_y - p.near_up_left_y);
	float t = (p.near_up_right_y - d) / ((p.near_up_right_y - d) - (p.near_up_left_y - d));
	intersectPoints[intersectionsCounter][0] = p.near_up_right_x + t * ( p.near_up_left_x - p.near_up_right_x );
	intersectPoints[intersectionsCounter][1] = p.near_up_right_y + t * ( p.near_up_left_y - p.near_up_right_y );
	intersectPoints[intersectionsCounter][2] = p.near_up_right_z + t * ( p.near_up_left_z - p.near_up_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (((p.far_up_left_y < d)&&(p.far_up_right_y > d)) || ((p.far_up_left_y > d)&&(p.far_up_right_y < d)))
  {
//	float t = p.far_up_left_y / (p.far_up_left_y - p.far_up_right_y);
	float t = (p.far_up_left_y - d) / ((p.far_up_left_y - d) - (p.far_up_right_y - d));
	intersectPoints[intersectionsCounter][0] = p.far_up_left_x + t * ( p.far_up_right_x - p.far_up_left_x );
	intersectPoints[intersectionsCounter][1] = p.far_up_left_y + t * ( p.far_up_right_y - p.far_up_left_y );
	intersectPoints[intersectionsCounter][2] = p.far_up_left_z + t * ( p.far_up_right_z - p.far_up_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_up_left_y < d)&&(p.far_down_left_y > d)) || ((p.far_up_left_y > d)&&(p.far_down_left_y < d)))
  {
//	float t = p.far_up_left_y / (p.far_up_left_y - p.far_down_left_y);
	float t = (p.far_up_left_y - d) / ((p.far_up_left_y - d) - (p.far_down_left_y - d));
	intersectPoints[intersectionsCounter][0] = p.far_up_left_x + t * ( p.far_down_left_x - p.far_up_left_x );
	intersectPoints[intersectionsCounter][1] = p.far_up_left_y + t * ( p.far_down_left_y - p.far_up_left_y );
	intersectPoints[intersectionsCounter][2] = p.far_up_left_z + t * ( p.far_down_left_z - p.far_up_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_up_left_y < d)&&(p.near_up_left_y > d)) || ((p.far_up_left_y > d)&&(p.near_up_left_y < d)))
  {
//	float t = p.far_up_left_y / (p.far_up_left_y - p.near_up_left_y);
	float t = (p.far_up_left_y - d) / ((p.far_up_left_y - d) - (p.near_up_left_y - d));
	intersectPoints[intersectionsCounter][0] = p.far_up_left_x + t * ( p.near_up_left_x - p.far_up_left_x );
	intersectPoints[intersectionsCounter][1] = p.far_up_left_y + t * ( p.near_up_left_y - p.far_up_left_y );
	intersectPoints[intersectionsCounter][2] = p.far_up_left_z + t * ( p.near_up_left_z - p.far_up_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (((p.far_down_right_y < d)&&(p.far_up_right_y > d)) || ((p.far_down_right_y > d)&&(p.far_up_right_y < d)))
  {
//	float t = p.far_down_right_y / (p.far_down_right_y - p.far_up_right_y);
	float t = (p.far_down_right_y - d) / ((p.far_down_right_y - d) - (p.far_up_right_y - d));
	intersectPoints[intersectionsCounter][0] = p.far_down_right_x + t * ( p.far_up_right_x - p.far_down_right_x );
	intersectPoints[intersectionsCounter][1] = p.far_down_right_y + t * ( p.far_up_right_y - p.far_down_right_y );
	intersectPoints[intersectionsCounter][2] = p.far_down_right_z + t * ( p.far_up_right_z - p.far_down_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_down_right_y < d)&&(p.far_down_left_y > d)) || ((p.far_down_right_y > d)&&(p.far_down_left_y < d)))
  {
//	float t = p.far_down_right_y / (p.far_down_right_y - p.far_down_left_y);
	float t = (p.far_down_right_y - d) / ((p.far_down_right_y - d) - (p.far_down_left_y - d));
	intersectPoints[intersectionsCounter][0] = p.far_down_right_x + t * ( p.far_down_left_x - p.far_down_right_x );
	intersectPoints[intersectionsCounter][1] = p.far_down_right_y + t * ( p.far_down_left_y - p.far_down_right_y );
	intersectPoints[intersectionsCounter][2] = p.far_down_right_z + t * ( p.far_down_left_z - p.far_down_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_down_right_y < d)&&(p.near_down_right_y > d)) || ((p.far_down_right_y > d)&&(p.near_down_right_y < d)))
  {
//	float t = p.far_down_right_y / (p.far_down_right_y - p.near_down_right_y);
	float t = (p.far_down_right_y - d) / ((p.far_down_right_y - d) - (p.near_down_right_y - d));
	intersectPoints[intersectionsCounter][0] = p.far_down_right_x + t * ( p.near_down_right_x - p.far_down_right_x );
	intersectPoints[intersectionsCounter][1] = p.far_down_right_y + t * ( p.near_down_right_y - p.far_down_right_y );
	intersectPoints[intersectionsCounter][2] = p.far_down_right_z + t * ( p.near_down_right_z - p.far_down_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (intersectionsCounter > 0)
  {
    minPoint[0] = maxPoint[0] = intersectPoints[0][0];
    minPoint[1] = maxPoint[1] = intersectPoints[0][1];
    minPoint[2] = maxPoint[2] = intersectPoints[0][2];
    
	for ( i = 1; i < intersectionsCounter; i++ )
	{
	  if ( intersectPoints[i][0] > maxPoint[0] )
	  {
	    maxPoint[0] = intersectPoints[i][0];
	  }
	  else if ( intersectPoints[i][0] < minPoint[0] )
	  {
	    minPoint[0] = intersectPoints[i][0];
	  }	    
	  if ( intersectPoints[i][2] > maxPoint[2] )
	  {
	    maxPoint[2] = intersectPoints[i][2];
	  }
	  else if ( intersectPoints[i][2] < minPoint[2] )
	  {
	    minPoint[2] = intersectPoints[i][2];
	  }	    
	}
    firstPlaneIntercepted = 1;
  }

  intersectionsCounter = 0;

  if (((p.near_down_left_y < -d)&&(p.near_down_right_y > -d)) || ((p.near_down_left_y > -d)&&(p.near_down_right_y < -d)))
  {
	float t = p.near_down_left_y / (p.near_down_left_y - p.near_down_right_y);
//	float t = (p.near_down_left_y + d) / ((p.near_down_left_y + d) - (p.near_down_right_y + d));
	intersectPoints[intersectionsCounter][0] = p.near_down_left_x + t * ( p.near_down_right_x - p.near_down_left_x );
	intersectPoints[intersectionsCounter][1] = p.near_down_left_y + t * ( p.near_down_right_y - p.near_down_left_y );
	intersectPoints[intersectionsCounter][2] = p.near_down_left_z + t * ( p.near_down_right_z - p.near_down_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_down_left_y < -d)&&(p.near_up_left_y > -d)) || ((p.near_down_left_y > -d)&&(p.near_up_left_y < -d)))
  {
	float t = p.near_down_left_y / (p.near_down_left_y - p.near_up_left_y);
//	float t = (p.near_down_left_y  + d)/ ((p.near_down_left_y + d) - (p.near_up_left_y + d));
	intersectPoints[intersectionsCounter][0] = p.near_down_left_x + t * ( p.near_up_left_x - p.near_down_left_x );
	intersectPoints[intersectionsCounter][1] = p.near_down_left_y + t * ( p.near_up_left_y - p.near_down_left_y );
	intersectPoints[intersectionsCounter][2] = p.near_down_left_z + t * ( p.near_up_left_z - p.near_down_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_down_left_y < -d)&&(p.far_down_left_y > -d)) || ((p.near_down_left_y > -d)&&(p.far_down_left_y < -d)))
  {
	float t = p.near_down_left_y / (p.near_down_left_y - p.far_down_left_y);
//	float t = (p.near_down_left_y + d) / ((p.near_down_left_y + d) - (p.far_down_left_y + d));
	intersectPoints[intersectionsCounter][0] = p.near_down_left_x + t * ( p.far_down_left_x - p.near_down_left_x );
	intersectPoints[intersectionsCounter][1] = p.near_down_left_y + t * ( p.far_down_left_y - p.near_down_left_y );
	intersectPoints[intersectionsCounter][2] = p.near_down_left_z + t * ( p.far_down_left_z - p.near_down_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (((p.near_up_right_y < -d)&&(p.far_up_right_y > -d)) || ((p.near_up_right_y > -d)&&(p.far_up_right_y < -d)))
  {
	float t = p.near_up_right_y / (p.near_up_right_y - p.far_up_right_y);
//	float t = (p.near_up_right_y + d) / ((p.near_up_right_y + d) - (p.far_up_right_y + d));
	intersectPoints[intersectionsCounter][0] = p.near_up_right_x + t * ( p.far_up_right_x - p.near_up_right_x );
	intersectPoints[intersectionsCounter][1] = p.near_up_right_y + t * ( p.far_up_right_y - p.near_up_right_y );
	intersectPoints[intersectionsCounter][2] = p.near_up_right_z + t * ( p.far_up_right_z - p.near_up_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_up_right_y < -d)&&(p.near_down_right_y > -d)) || ((p.near_up_right_y > -d)&&(p.near_down_right_y < -d)))
  {
	float t = p.near_up_right_y / (p.near_up_right_y - p.near_down_right_y);
//	float t = (p.near_up_right_y + d) / ((p.near_up_right_y + d) - (p.near_down_right_y + d));
	intersectPoints[intersectionsCounter][0] = p.near_up_right_x + t * ( p.near_down_right_x - p.near_up_right_x );
	intersectPoints[intersectionsCounter][1] = p.near_up_right_y + t * ( p.near_down_right_y - p.near_up_right_y );
	intersectPoints[intersectionsCounter][2] = p.near_up_right_z + t * ( p.near_down_right_z - p.near_up_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.near_up_right_y < -d)&&(p.near_up_left_y > -d)) || ((p.near_up_right_y > -d)&&(p.near_up_left_y < -d)))
  {
	float t = p.near_up_right_y / (p.near_up_right_y - p.near_up_left_y);
//	float t = (p.near_up_right_y + d) / ((p.near_up_right_y + d) - (p.near_up_left_y + d));
	intersectPoints[intersectionsCounter][0] = p.near_up_right_x + t * ( p.near_up_left_x - p.near_up_right_x );
	intersectPoints[intersectionsCounter][1] = p.near_up_right_y + t * ( p.near_up_left_y - p.near_up_right_y );
	intersectPoints[intersectionsCounter][2] = p.near_up_right_z + t * ( p.near_up_left_z - p.near_up_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (((p.far_up_left_y < -d)&&(p.far_up_right_y > -d)) || ((p.far_up_left_y > -d)&&(p.far_up_right_y < -d)))
  {
	float t = p.far_up_left_y / (p.far_up_left_y - p.far_up_right_y);
//	float t = (p.far_up_left_y + d) / ((p.far_up_left_y + d) - (p.far_up_right_y + d));
	intersectPoints[intersectionsCounter][0] = p.far_up_left_x + t * ( p.far_up_right_x - p.far_up_left_x );
	intersectPoints[intersectionsCounter][1] = p.far_up_left_y + t * ( p.far_up_right_y - p.far_up_left_y );
	intersectPoints[intersectionsCounter][2] = p.far_up_left_z + t * ( p.far_up_right_z - p.far_up_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_up_left_y < -d)&&(p.far_down_left_y > -d)) || ((p.far_up_left_y > -d)&&(p.far_down_left_y < -d)))
  {
	float t = p.far_up_left_y / (p.far_up_left_y - p.far_down_left_y);
//	float t = (p.far_up_left_y + d) / ((p.far_up_left_y + d) - (p.far_down_left_y + d));
	intersectPoints[intersectionsCounter][0] = p.far_up_left_x + t * ( p.far_down_left_x - p.far_up_left_x );
	intersectPoints[intersectionsCounter][1] = p.far_up_left_y + t * ( p.far_down_left_y - p.far_up_left_y );
	intersectPoints[intersectionsCounter][2] = p.far_up_left_z + t * ( p.far_down_left_z - p.far_up_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_up_left_y < -d)&&(p.near_up_left_y > -d)) || ((p.far_up_left_y > -d)&&(p.near_up_left_y < -d)))
  {
	float t = p.far_up_left_y / (p.far_up_left_y - p.near_up_left_y);
//	float t = (p.far_up_left_y + d) / ((p.far_up_left_y + d) - (p.near_up_left_y + d));
	intersectPoints[intersectionsCounter][0] = p.far_up_left_x + t * ( p.near_up_left_x - p.far_up_left_x );
	intersectPoints[intersectionsCounter][1] = p.far_up_left_y + t * ( p.near_up_left_y - p.far_up_left_y );
	intersectPoints[intersectionsCounter][2] = p.far_up_left_z + t * ( p.near_up_left_z - p.far_up_left_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (((p.far_down_right_y < -d)&&(p.far_up_right_y > -d)) || ((p.far_down_right_y > -d)&&(p.far_up_right_y < -d)))
  {
	float t = p.far_down_right_y / (p.far_down_right_y - p.far_up_right_y);
//	float t = (p.far_down_right_y + d) / ((p.far_down_right_y + d) - (p.far_up_right_y + d));
	intersectPoints[intersectionsCounter][0] = p.far_down_right_x + t * ( p.far_up_right_x - p.far_down_right_x );
	intersectPoints[intersectionsCounter][1] = p.far_down_right_y + t * ( p.far_up_right_y - p.far_down_right_y );
	intersectPoints[intersectionsCounter][2] = p.far_down_right_z + t * ( p.far_up_right_z - p.far_down_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_down_right_y < -d)&&(p.far_down_left_y > -d)) || ((p.far_down_right_y > -d)&&(p.far_down_left_y < -d)))
  {
	float t = p.far_down_right_y / (p.far_down_right_y - p.far_down_left_y);
//	float t = (p.far_down_right_y + d) / ((p.far_down_right_y + d) - (p.far_down_left_y + d));
	intersectPoints[intersectionsCounter][0] = p.far_down_right_x + t * ( p.far_down_left_x - p.far_down_right_x );
	intersectPoints[intersectionsCounter][1] = p.far_down_right_y + t * ( p.far_down_left_y - p.far_down_right_y );
	intersectPoints[intersectionsCounter][2] = p.far_down_right_z + t * ( p.far_down_left_z - p.far_down_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }
  if (((p.far_down_right_y < -d)&&(p.near_down_right_y > -d)) || ((p.far_down_right_y > -d)&&(p.near_down_right_y < -d)))
  {
	float t = p.far_down_right_y / (p.far_down_right_y - p.near_down_right_y);
//	float t = (p.far_down_right_y + d) / ((p.far_down_right_y + d) - (p.near_down_right_y + d));
	intersectPoints[intersectionsCounter][0] = p.far_down_right_x + t * ( p.near_down_right_x - p.far_down_right_x );
	intersectPoints[intersectionsCounter][1] = p.far_down_right_y + t * ( p.near_down_right_y - p.far_down_right_y );
	intersectPoints[intersectionsCounter][2] = p.far_down_right_z + t * ( p.near_down_right_z - p.far_down_right_z );
	intersectPointsMark[intersectionsCounter] = 1;
    intersectionsCounter++;
  }

  if (intersectionsCounter > 0)
  {
	for ( i = 0; i < intersectionsCounter; i++ )
	{
	  if ( intersectPoints[i][0] > maxPoint[0] )
	  {
	    maxPoint[0] = intersectPoints[i][0];
	  }
	  else if ( intersectPoints[i][0] < minPoint[0] )
	  {
	    minPoint[0] = intersectPoints[i][0];
	  }	    
	  if ( intersectPoints[i][2] > maxPoint[2] )
	  {
	    maxPoint[2] = intersectPoints[i][2];
	  }
	  else if ( intersectPoints[i][2] < minPoint[2] )
	  {
	    minPoint[2] = intersectPoints[i][2];
	  }	    
	}
    return 1;
  }

  else return firstPlaneIntercepted;
}

void getInterceptionFrustumPlane()
{
  float plane_normal_x = 0;
  float plane_normal_y = 1;  
  float plane_normal_z = 0;

  float plane_origin_x = 0;
  float plane_origin_y = 0;
  float plane_origin_z = 0;

  float d = - (plane_normal_x * plane_origin_x + plane_normal_z * plane_origin_z + plane_normal_z * plane_origin_z);

}


#endif

