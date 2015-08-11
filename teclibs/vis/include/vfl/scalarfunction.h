#ifndef VFL_SCALARFUNCTION_H
#define VFL_SCALARFUNCTION_H

//----------//
// Includes //
//----------//

#include "defines.h"
#include "basescalarfunction.h"

#include <ds/array.h>

//----------------------//
// Forward Declarations //
//----------------------//

//-----------------------------------------------//
// Abstract Class Definition - VflScalarFunction //
//-----------------------------------------------//

class VFLH_API VflScalarFunction : public VflBaseScalarFunction
{
public:

  // Constructors and Destructor

  VflScalarFunction ()
  : VflBaseScalarFunction()
  {
  }

  virtual ~VflScalarFunction ()
  {
  }

  // Function Value

  virtual double GetFunctionValue (double x) = 0;

};

//-----------------------------------------------------//
// Abstract Class Definition - VflScalarFunctionScaled //
//-----------------------------------------------------//

class VFLH_API VflScalarFunctionScaled : public VflScalarFunction
{
public:

  // Constructors and Destructor

  VflScalarFunctionScaled (double scale = 1.0)
  : VflScalarFunction()
  , m_scale(scale)
  {
  }

  virtual ~VflScalarFunctionScaled ()
  {
  }

  // Setters and Getters

  void SetScale (double scale)
  {
    m_scale = scale;
  }

  double GetScale ()
  {
    return m_scale;
  }

  // Function Value

  virtual double GetFunctionValue (double x) = 0;

protected:

  double m_scale;
};

//----------------------------------------------//
// Class Definition - VflScalarFunctionCompound //
//----------------------------------------------//

class VFL_API VflScalarFunctionCompound : public VflScalarFunctionScaled
{
public:

  // Constructors and Destructor

  VflScalarFunctionCompound (double scale = 1.0)
  : VflScalarFunctionScaled(scale)
  {
  }

  virtual ~VflScalarFunctionCompound ()
  {
  }

  // Composition Management

  void AddFunction (VflScalarFunction* function, double weight = 1.0);
  VflScalarFunction* GetFunction (int index);

  // Function Value

  virtual double GetFunctionValue (double x);

private:

  struct VflScalarFunctionWeighted
  {
    VflScalarFunction* function;
    double weight;
  };

  typedef DsArray<VflScalarFunctionWeighted> VflScalarFunctionArray;

private:

  VflScalarFunctionArray m_components;
};

//----------------------------------------------//
// Class Definition - VflScalarFunctionConstant //
//----------------------------------------------//

class VFLH_API VflScalarFunctionConstant : public VflScalarFunction
{
public:

  // Constructors and Destructor

  VflScalarFunctionConstant ()
  : VflScalarFunction()
  , m_value(0.0)
  {
  }

  VflScalarFunctionConstant (double value)
  : VflScalarFunction()
  , m_value(value)
  {
  }

  virtual ~VflScalarFunctionConstant ()
  {
  }

  // Setters and Getters

  void SetValue (double value)
  {
    m_value = value;
  }

  double GetValue ()
  {
    return m_value;
  }

  // Function Value

  virtual double GetFunctionValue (double x)
  {
    return m_value;
  }

private:

  double m_value;
};

//----------------------------------------------//
// Class Definition - VflScalarFunctionUniverse //
//----------------------------------------------//

class VFL_API VflScalarFunctionUniverse : public VflScalarFunction
{
public:

  // Constructors and Destructor

  VflScalarFunctionUniverse (VflScalarFunction* baseFunction, double minX, double maxX)
  : VflScalarFunction()
  , m_baseFunction(baseFunction)
  , m_minX(minX)
  , m_maxX(maxX)
  {
  }

  virtual ~VflScalarFunctionUniverse ()
  {
  }

  // Function Value

  virtual double GetFunctionValue (double x);

private:

  VflScalarFunction* m_baseFunction;
  double m_minX;
  double m_maxX;
};

//-----------------------------------------------//
// Class Definition - VflScalarFunctionSinePower //
//-----------------------------------------------//

class VFLH_API VflScalarFunctionSinePower : public VflScalarFunctionScaled
{
public:

  // Constructors and Destructor

  VflScalarFunctionSinePower (double scale = 1.0, double power = 1.0)
  : VflScalarFunctionScaled(scale)
  , m_power(power)
  {
  }

  virtual ~VflScalarFunctionSinePower ()
  {
  }

  // Setters and Getters

  void SetPower (double power)
  {
    m_power = power;
  }

  double GetPower ()
  {
    return m_power;
  }

  // Function Value

  virtual double GetFunctionValue (double x);

protected:

  double m_power;
};

//-------------------------------------------------//
// Class Definition - VflScalarFunctionCosinePower //
//-------------------------------------------------//

class VFLH_API VflScalarFunctionCosinePower : public VflScalarFunctionScaled
{
public:

  // Constructors and Destructor

  VflScalarFunctionCosinePower (double scale = 1.0, double power = 1.0)
  : VflScalarFunctionScaled(scale)
  , m_power(power)
  {
  }

  virtual ~VflScalarFunctionCosinePower ()
  {
  }

  // Setters and Getters

  void SetPower (double power)
  {
    m_power = power;
  }

  double GetPower ()
  {
    return m_power;
  }

  // Function Value

  virtual double GetFunctionValue (double x);

protected:

  double m_power;
};

#endif // VFL_SCALARFUNCTION_H
