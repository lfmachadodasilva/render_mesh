/************************************************************************
  Renders particle obstacles.

  rcosta@tecgraf.puc-rio.br
  rodesp@tecgraf.puc-rio.br

  Fev 2011
*************************************************************************/

#ifndef _PARTICLES_OBSTACLE_RENDERER_H_
#define _PARTICLES_OBSTACLE_RENDERER_H_

#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcModel;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcObstacleRenderer
{
public:
  PtcObstacleRenderer ();

  ~PtcObstacleRenderer ();

  void Draw ();

  void SetModel (PtcModel* model);

  void SetWireframeEnabled (bool enable);

private:
  PtcModel* m_model;
  bool m_wireframe;
};


#endif