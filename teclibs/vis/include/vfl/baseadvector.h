#ifndef VFL_BASEADVECTOR_H
#define VFL_BASEADVECTOR_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <alg/vector.h>

//----------------------//
// Forward Declarations //
//----------------------//

class VflFieldLineList;
class VflMultiFieldLine;
class VflFieldLine;

//---------------------------------------------//
// Abstract Class Definition - VflBaseAdvector //
//---------------------------------------------//

class VFL_API VflBaseAdvector
{
public:

  // Constructors and Destructor

  VflBaseAdvector ();
  virtual ~VflBaseAdvector ();

  // Getters and Setters

  int GetMaxVertsForward ()
  {
    return m_maxVertsForward;
  }

  int GetMaxVertsBackward ()
  {
    return m_maxVertsBackward;
  }

  bool GetUseBufferObjects ()
  {
    return m_useBufferObjects;
  }

  bool GetUseStrips ()
  {
    return m_useStrips;
  }

  void SetMaxVertsForward (int maxVertsForward)
  {
    m_maxVertsForward = maxVertsForward;
  }

  void SetMaxVertsBackward (int maxVertsBackward)
  {
    m_maxVertsBackward = maxVertsBackward;
  }

  void SetUseBufferObjects (bool state)
  {
    m_useBufferObjects = state;
  }

  void SetUseStrips (bool state)
  {
    m_useStrips = state;
  }

  // Advection

  VflFieldLineList* AdvectPacked ();
  VflMultiFieldLine* AdvectInterleaved ();

  int AdvectPacked (VflFieldLineList* fieldLineList);
  int AdvectInterleaved (VflMultiFieldLine* multiFieldLine);

protected:

  // Advection

  virtual int GetSeedCount () = 0;

  bool AdvectPacked (VflFieldLine* fieldLine, int seedNumber);
  bool AdvectInterleaved (VflMultiFieldLine* multiFieldLine, int seedNumber);

  int Advect (int seedNumber);

  virtual int Advect (float* magnitudes,
                      float* vertices,
                      float* tangents,
                      int seedNumber,
                      int maxVerts,
                      bool backwards) = 0;

  // Memory Management

  bool AssertAuxArrays (int maxVerts);

protected:

  int m_maxVertsForward;
  int m_maxVertsBackward;

  int m_auxVertexCount;

  float* m_auxMagnitudes;
  float* m_auxVertices;
  float* m_auxTangents;

  bool m_useBufferObjects;
  bool m_useStrips;

};

#endif // VFL_BASEADVECTOR_H
