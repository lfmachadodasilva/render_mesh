#ifndef VFL_VECTORFIELD_H
#define VFL_VECTORFIELD_H

//----------//
// Includes //
//----------//

#include "defines.h"
#include "basevectorfield.h"

#include <ds/array.h>
#include <alg/vector.h>
#include <alg/plane.h>

//----------------------//
// Forward Declarations //
//----------------------//

//--------------------------------------------//
// Abstract Class Definition - VflVectorField //
//--------------------------------------------//

class VFLH_API VflVectorField : public VflBaseVectorField
{
public:

  // Constructors and Destructor

  VflVectorField ()
  : VflBaseVectorField()
  {
  }

  virtual ~VflVectorField ()
  {
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos) = 0;

};

//--------------------------------------------------//
// Abstract Class Definition - VflVectorFieldScaled //
//--------------------------------------------------//

class VFLH_API VflVectorFieldScaled : public VflVectorField
{
public:

  // Constructors and Destructor

  VflVectorFieldScaled (float scale = 1.0f)
  : VflVectorField()
  , m_scale(scale)
  {
  }

  virtual ~VflVectorFieldScaled ()
  {
  }

  // Setters and Getters

  void SetScale (float scale)
  {
    m_scale = scale;
  }

  float GetScale ()
  {
    return m_scale;
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos) = 0;

protected:

  float m_scale;
};

//---------------------------------------------------------//
// Abstract Class Definition - VflVectorFieldDistancePower //
//---------------------------------------------------------//

class VFL_API VflVectorFieldDistancePower : public VflVectorFieldScaled
{
public:

  // Constructors and Destructor

  VflVectorFieldDistancePower (float scale = 1.0f)
  : VflVectorFieldScaled(scale)
  , m_power(-2)
  {
  }

  VflVectorFieldDistancePower (int power, float scale = 1.0f)
  : VflVectorFieldScaled(scale)
  , m_power(power)
  {
  }

  virtual ~VflVectorFieldDistancePower ()
  {
  }

  // Setters and Getters

  void SetPower (int power)
  {
    m_power = power;
  }

  int GetPower ()
  {
    return m_power;
  }

  // Distance Factor

  float GetDistanceFactor (float dist);

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos) = 0;

protected:

  int m_power;
};

//-------------------------------------------//
// Class Definition - VflVectorFieldCompound //
//-------------------------------------------//

class VFL_API VflVectorFieldCompound : public VflVectorFieldScaled
{
public:

  // Constructors and Destructor

  VflVectorFieldCompound (float scale = 1.0f)
  : VflVectorFieldScaled(scale)
  {
  }

  virtual ~VflVectorFieldCompound ()
  {
  }

  // Composition Management

  void AddField (VflVectorField* field, float weight = 1.0f);
  VflVectorField* GetField (int index);

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos);

private:

  struct VflVectorFieldWeighted
  {
    VflVectorField* field;
    float weight;
  };

  typedef DsArray<VflVectorFieldWeighted> VflVectorFieldArray;

private:

  VflVectorFieldArray m_components;
};

//-------------------------------------------//
// Class Definition - VflVectorFieldConstant //
//-------------------------------------------//

class VFLH_API VflVectorFieldConstant : public VflVectorField
{
public:

  // Constructors and Destructor

  VflVectorFieldConstant ()
  : VflVectorField()
  , m_value(0.0f, -9.8f, 0.0f)
  {
  }

  VflVectorFieldConstant (const AlgVector& value)
  : VflVectorField()
  , m_value(value)
  {
  }

  VflVectorFieldConstant (const AlgVector& direction, float norm)
  : VflVectorField()
  , m_value(norm * direction.Normalized())
  {
  }

  virtual ~VflVectorFieldConstant ()
  {
  }

  // Setters and Getters

  void SetValue (const AlgVector& value)
  {
    m_value = value;
  }

  void SetValue (const AlgVector& direction, float norm)
  {
    m_value = norm * direction.Normalized();
  }

  void SetDirection (const AlgVector& direction)
  {
    m_value = GetNorm() * direction.Normalized();
  }

  void SetNorm (float norm)
  {
    m_value = norm * GetDirection();
  }

  AlgVector GetValue ()
  {
    return m_value;
  }

  AlgVector GetDirection ()
  {
    return m_value.Normalized();
  }

  AlgVector GetNorm()
  {
    return m_value.Length();
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos)
  {
    return m_value;
  }

private:

  AlgVector m_value;
};

//----------------------------------------//
// Class Definition - VflVectorFieldPoint //
//----------------------------------------//

class VFL_API VflVectorFieldPoint : public VflVectorFieldDistancePower
{
public:

  // Constructors and Destructor

  VflVectorFieldPoint (float scale = 1.0f)
  : VflVectorFieldDistancePower(scale)
  , m_center(0.0f, 0.0f, 0.0f)
  {
  }

  VflVectorFieldPoint (const AlgVector& center, float scale = 1.0f)
  : VflVectorFieldDistancePower(scale)
  , m_center(center)
  {
  }

  VflVectorFieldPoint (const AlgVector& center, int power, float scale = 1.0f)
  : VflVectorFieldDistancePower(power, scale)
  , m_center(center)
  {
  }

  virtual ~VflVectorFieldPoint ()
  {
  }

  // Setters and Getters

  void SetCenter (const AlgVector& center)
  {
    m_center = center;
  }

  AlgVector GetCenter ()
  {
    return m_center;
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos);

private:

  AlgVector m_center;
};

//---------------------------------------//
// Class Definition - VflVectorFieldLine //
//---------------------------------------//

class VFL_API VflVectorFieldLine : public VflVectorFieldDistancePower
{
public:

  // Constructors and Destructor

  VflVectorFieldLine (const AlgVector& direction, float scale = 1.0f)
  : VflVectorFieldDistancePower(scale)
  , m_origin(0.0f, 0.0f, 0.0f)
  , m_direction(direction.Normalized())
  {
  }

  VflVectorFieldLine (const AlgVector& origin, const AlgVector& direction, float scale = 1.0f)
  : VflVectorFieldDistancePower(scale)
  , m_origin(origin)
  , m_direction(direction.Normalized())
  {
  }

  VflVectorFieldLine (const AlgVector& origin, const AlgVector& direction, int power, float scale = 1.0f)
  : VflVectorFieldDistancePower(power, scale)
  , m_origin(origin)
  , m_direction(direction.Normalized())
  {
  }

  virtual ~VflVectorFieldLine ()
  {
  }

  // Setters and Getters

  void SetLine (const AlgVector& direction)
  {
    m_origin = AlgVector(0.0f, 0.0f, 0.0f);
    m_direction = direction.Normalized();
  }

  void SetLine (const AlgVector& origin, const AlgVector& direction)
  {
    m_origin = origin;
    m_direction = direction.Normalized();
  }

  void SetOrigin (const AlgVector& origin)
  {
    m_origin = origin;
  }

  void SetDirection (const AlgVector& direction)
  {
    m_direction = direction.Normalized();
  }

  AlgVector GetOrigin ()
  {
    return m_origin;
  }

  AlgVector GetDirection ()
  {
    return m_direction;
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos);

private:

  AlgVector m_origin;
  AlgVector m_direction;
};

//----------------------------------------//
// Class Definition - VflVectorFieldPlane //
//----------------------------------------//

class VFL_API VflVectorFieldPlane : public VflVectorFieldDistancePower
{
public:

  // Constructors and Destructor

  VflVectorFieldPlane (const AlgPlane& plane, float scale = 1.0f)
  : VflVectorFieldDistancePower(scale)
  , m_plane(plane)
  {
    m_plane.Normalize();
  }

  VflVectorFieldPlane (const AlgPlane& plane, int power, float scale = 1.0f)
  : VflVectorFieldDistancePower(power, scale)
  , m_plane(plane)
  {
    m_plane.Normalize();
  }

  virtual ~VflVectorFieldPlane ()
  {
  }

  // Setters and Getters

  void SetPlane (const AlgPlane& plane)
  {
    m_plane = plane;
  }

  AlgPlane GetPlane ()
  {
    return m_plane;
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos);

private:

  AlgPlane m_plane;
};

//-------------------------------------------//
// Class Definition - VflVectorFieldUniverse //
//-------------------------------------------//

class VFL_API VflVectorFieldUniverse : public VflVectorField
{
public:

  // Constructors and Destructor

  VflVectorFieldUniverse (VflVectorField* baseField, const AlgVector& minVertex, const AlgVector& maxVertex)
  : VflVectorField()
  , m_baseField(baseField)
  , m_minVertex(minVertex)
  , m_maxVertex(maxVertex)
  {
  }

  virtual ~VflVectorFieldUniverse ()
  {
  }

  // Field Value

  virtual AlgVector GetFieldValue (const AlgVector& pos);

private:

  VflVectorField* m_baseField;
  AlgVector m_minVertex;
  AlgVector m_maxVertex;
};

#endif // VFL_VECTORFIELD_H
