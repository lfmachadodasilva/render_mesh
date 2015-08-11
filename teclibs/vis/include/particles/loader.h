/************************************************************************
  Loader Class Header
  Interface of a model loader.
  rcosta@tecgraf.puc-rio.br
  Jun 2008
*************************************************************************/

#ifndef _PARTICLES_LOADER_H_
#define _PARTICLES_LOADER_H_

#include "defines.h"

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcModel;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcLoader
{
public:
  enum PtcFieldType
  {
    PTC_FIELD_TYPE_MATERIAL,
    PTC_FIELD_TYPE_SCALAR,
    PTC_FIELD_TYPE_VECTOR,
  };

  enum AnalysisType {
    ANALYSIS_2D,
    ANALYSIS_3D,
  };

public:
  PtcLoader () {};
  virtual ~PtcLoader () {};

  virtual bool LoadBasicInfo () = 0;
  virtual bool LoadParticles (PtcModel* model) = 0;
  virtual bool LoadObstacles (PtcModel* model) = 0;
  virtual bool LoadProperty (PtcModel* model, PtcFieldType fieldtype, int index) = 0;
  virtual bool LoadProperty (PtcModel* model, PtcFieldType fieldtype, const char* fieldname) = 0;

  virtual AnalysisType GetAnalysisType () const = 0;
  virtual void GetBoundingBox (float* xmin, float* xmax, float* ymin, float* ymax, float* zmin, float* zmax) const = 0;
  virtual int GetCaseCount () const = 0;
  virtual const char* GetCaseName (int index) const = 0;
  virtual int GetStepCount () const = 0;
  virtual float GetTimeStep (int index) const = 0;
  virtual int GetTimeStepIndex (float timestep) const = 0;
  virtual int GetFieldCount (PtcFieldType fieldtype) const = 0;
  virtual const char* GetFieldName (PtcFieldType fieldtype, int index) const = 0;
  virtual void GetFieldMinMax (PtcFieldType fieldtype, int index, float* min, float* max) const = 0;
  virtual void GetFieldMinMax (
    PtcFieldType fieldtype, const char* fieldname, float* min, float* max) const = 0;
  virtual void GetGlobalFieldMinMax (
    PtcFieldType fieldtype, int index, float* min, float* max) const = 0;
  virtual void GetGlobalFieldMinMax (
    PtcFieldType fieldtype, const char* fieldname, float* min, float* max) const = 0;
  virtual const char* GetErrorDescription () = 0;
  virtual int GetMaterialCount () const = 0;
  virtual const char* GetMaterialName (int id) const = 0;

  virtual bool SetCase (int index) = 0;
  virtual bool SetCase (const char* name) = 0;
  virtual void SetStep (float timestep) = 0;
  virtual void SetStepByIndex (int index) = 0;

};

#endif