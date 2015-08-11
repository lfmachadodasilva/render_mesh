#ifndef VFL_INK_H
#define VFL_INK_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "defines.h"

class VflVectorField;

//------------------//
// Class Definition //
//------------------//

class VFL_API VflInk
{
public:

  // Constructors and Destructor

  VflInk (int iCells, int jCells, int kCells, float xSize, float ySize, float zSize);
  virtual ~VflInk ();

  // Configuration

  void SetVectorField (VflVectorField* vectorField)
  {
    m_vectorField = vectorField;
    m_fieldSampled = false;
  }

  VflVectorField* GetVectorField () const
  {
    return m_vectorField;
  }

  void SetAdvectionMode (int mode)
  {
    m_advection_mode = mode;
  }

  int GetAdvectionMode () const
  {
    return m_advection_mode;
  }

  void SetAdvectionOrder (int order)
  {
    m_advection_order = order;
  }

  int GetAdvectionOrder () const
  {
    return m_advection_order;
  }

  void SetDiffusionMode (int mode)
  {
    m_diffusion_mode = mode;
  }

  int GetDiffusionMode () const
  {
    return m_diffusion_mode;
  }

  void SetDiffusionOrder (int order)
  {
    m_diffusion_order = order;
  }

  int GetDiffusionOrder () const
  {
    return m_diffusion_order;
  }

  void SetDiffusionMaxIterations (int maxiterations)
  {
    m_diffusion_maxiterations = maxiterations;
  }

  int GetDiffusionMaxIterations () const
  {
    return m_diffusion_maxiterations;
  }

  void SetInterpolant (int order)
  {
    m_interpolant = order;
  }

  int GetInterpolant () const
  {
    return m_interpolant;
  }

  void SetTimeStep (float timeStep)
  {
    m_timeStep = timeStep;
  }

  float GetTimeStep () const
  {
    return m_timeStep;
  }

  void SetDiffusionConstant (float kDiffusion)
  {
    m_kDiffusion = kDiffusion;
  }

  float GetDiffusionConstant () const
  {
    return m_kDiffusion;
  }

  void SetDissipationConstant (float kDissipation)
  {
    m_kDissipation = kDissipation;
  }

  float GetDissipationConstant () const
  {
    return m_kDissipation;
  }

  int GetGridSizeI () const
  {
    return m_gridSizeI;
  }

  int GetGridSizeJ () const
  {
    return m_gridSizeJ;
  }

  int GetGridSizeK () const
  {
    return m_gridSizeK;
  }

  int GetNumCells () const
  {
    return m_nCells;
  }

  float GetCellSizeX () const
  {
    return m_cellSizeX;
  }

  float GetCellSizeY () const
  {
    return m_cellSizeY;
  }

  float GetCellSizeZ () const
  {
    return m_cellSizeZ;
  }

  float GetCellVolume () const
  {
    return m_cellVolume;
  }

  // Source

  void SetSource (int i, int j, int k, float val);
  void SetSource (int cell, float val);
  void ResetSource ();

  // Simulation

  void SimulationStep ();

  // Render

  void DrawAxes ();
  void DrawGrid ();
  void DrawBBox ();
  void DrawBBoxGrid ();
  void DrawNodes ();
  void DrawInk ();

protected:

  // Simulation

  void StepAdvect ();
  void StepDiffuse ();
  void StepSource ();
  void StepDissipate ();

  void StepAdvectForward ();
  void StepAdvectStable ();
  void StepDiffuseForward ();
  void StepDiffuseStable ();

  void StepAdvectForwardRK1 (float*& srcfield, float*& dstfield);
  void StepAdvectForwardRK2 (float*& srcfield, float*& tmpfield, float*& dstfield);
  void StepAdvectForwardRK4 (float*& srcfield, float*& tmpfield1, float*& tmpfield2, float*& tmpfield3, float*& tmpfield4, float*& dstfield);
  void StepAdvectStableRK1 (float* srcfield, float* dstfield);
  void StepAdvectStableRK2 (float* srcfield, float* dstfield);
  void StepAdvectStableRK4 (float* srcfield, float* dstfield);
  void StepDiffuseForwardRK1 (float diffusion, float*& srcfield, float*& dstfield);
  void StepDiffuseForwardRK2 (float diffusion, float*& srcfield, float*& tmpfield, float*& dstfield);
  void StepDiffuseForwardRK4 (float diffusion, float*& srcfield, float*& tmpfield1, float*& tmpfield2, float*& tmpfield3, float*& tmpfield4, float*& dstfield);
  void StepDiffuseStable (float diffusion, float*& srcfield, float*& dstfield);
  void StepSource (float factor, float*& source, float*& field);
  void StepDissipate (float*& field);

  void GetInterpValue (float* field, float x, float y, float z, float* val);
  void GetInterp1Value (float* field, float x, float y, float z, float* val);
  void GetInterp2Value (float* field, float x, float y, float z, float* val);

  // Debug

  void PrintField (const char* name, float* field, int i0, int i1, int j0, int j1, int k0, int k1);
  void CheckField (float* field, int i0, int i1, int j0, int j1, int k0, int k1);

protected:

  // Field Sampling

  void AssertFieldSampled ();
  void ResampleField ();

protected:

  VflVectorField* m_vectorField;

  int m_advection_mode;
  int m_advection_order;
  int m_diffusion_mode;
  int m_diffusion_order;
  int m_diffusion_maxiterations;
  int m_interpolant;

  float m_timeStep;
  float m_kDiffusion;
  float m_kDissipation;

  int m_gridSizeI;
  int m_gridSizeJ;
  int m_gridSizeK;
  int m_gridPlane;
  int m_nCells;

  float m_cellSizeX;
  float m_cellSizeY;
  float m_cellSizeZ;
  float m_cellVolume;

  float* m_inkSource;
  float* m_inkDensities;
  float* m_inkDensities2;
  float* m_inkDensities3;
  float* m_inkDensities4;
  float* m_inkDensities5;
  float* m_inkDensities6;

  float* m_fieldX;
  float* m_fieldY;
  float* m_fieldZ;

  bool m_fieldSampled;
};

#endif // VFL_INK_H
