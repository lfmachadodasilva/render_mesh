/************************************************************************
  PtcNFLoader Class Header
  Loads a model from a neutral file.
  rcosta@tecgraf.puc-rio.br
  Nov 2008
*************************************************************************/

#ifndef _NFLOADER_H_
#define _NFLOADER_H_

#define NF_CASE_NAME_SIZE   128 /* max: 500 */
#define NF_FIELD_NAME_SIZE  64
#define NF_FILE_NAME_SIZE   260

#include "loader.h"
#include "defines.h"
#include <alg/vector.h>
#include <alg/quatern.h>
#include <ds/array.h>
#include <ds/hash.h>

/************************************************************************
  Forward Declarations
*************************************************************************/

class PtcModel;
class PtcRenderer;
class PtcObstacle;

/************************************************************************
  Class Declaration
*************************************************************************/

class PARTICLES_API PtcNFLoader : public PtcLoader
{
public:
  PtcNFLoader ();
  ~PtcNFLoader ();

  bool SetSourceFile (const char* filename);

  virtual bool LoadBasicInfo ();
  virtual bool LoadParticles (PtcModel* model);
  virtual bool LoadObstacles (PtcModel* model);
  virtual bool LoadProperty (PtcModel* model, PtcFieldType fieldtype, int index);
  virtual bool LoadProperty (PtcModel* model, PtcFieldType fieldtype, const char* fieldname);

  virtual AnalysisType GetAnalysisType () const;
  virtual void GetBoundingBox (float* xmin, float* xmax, float* ymin, float* ymax, float* zmin, float* zmax) const;
  virtual int GetCaseCount () const;
  virtual const char* GetCaseName (int index) const;
  virtual int GetStepCount () const;
  virtual float GetTimeStep (int index) const;
  virtual int GetTimeStepIndex (float timestep) const;
  virtual int GetFieldCount (PtcFieldType fieldtype) const;
  virtual const char* GetFieldName (PtcFieldType fieldtype, int index) const;
  virtual void GetFieldMinMax (PtcFieldType fieldtype, int index, float* min, float* max) const;
  virtual void GetFieldMinMax (
    PtcFieldType fieldtype, const char* fieldname, float* min, float* max) const;
  virtual void GetGlobalFieldMinMax (
    PtcFieldType fieldtype, int index, float* min, float* max) const;
  virtual void GetGlobalFieldMinMax (
    PtcFieldType fieldtype, const char* fieldname, float* min, float* max) const;
  virtual const char* GetErrorDescription () { return m_error; }
  virtual int GetMaterialCount () const;
  virtual const char* GetMaterialName (int id) const;

  virtual bool SetCase (int index);
  virtual bool SetCase (const char* name);
  virtual void SetStep (float timestep);
  virtual void SetStepByIndex (int index);

private:
#ifdef _WIN32
    typedef __int64 FileOffset;
#else
    typedef size_t FileOffset;
#endif
  bool CreateBinaryFile (FILE** file, char* filename);
  int GetFieldId (PtcFieldType fieldtype, const char* fieldname) const;
  bool ReadOffset (FILE* fp, FileOffset* offset);
  bool WriteOffset (FILE* fp, FileOffset offset);
  int GotoOffset (FILE* fp, FileOffset offset);
  FileOffset GetCurrentOffset (FILE* fp);
  bool WriteBasicInfo (FILE* fp);
  void AddObstacle (PtcObstacle* obstacle, int id);

private:
  char m_error[512];
  FILE* m_cfgfile;
  char m_cfgfilename[NF_FILE_NAME_SIZE+1];
  FILE* m_tmpbinfile;
  FILE* m_currentfile;
  char m_currentfilename[NF_FILE_NAME_SIZE+1];

  AnalysisType m_analysis;

  struct ScalarField
  {
    char name[NF_FIELD_NAME_SIZE+1];
    float vmin, vmax;
    FileOffset offset;
    ScalarField& operator= (const ScalarField& o) 
    {
      strcpy(name, o.name);
      vmin = o.vmin; vmax = o.vmax;
      offset = o.offset;
      return *this;
    }
  };
  struct VectorField
  {
    char name[NF_FIELD_NAME_SIZE+1];
    float vxmin, vymin, vzmin, vxmax, vymax, vzmax;
    float vmin, vmax;
    FileOffset offset;
    VectorField& operator= (const VectorField& o) 
    {
      strcpy(name, o.name);
      vxmin = o.vxmin; vxmax = o.vxmax;
      vymin = o.vymin; vymax = o.vymax;
      vzmin = o.vzmin; vzmax = o.vzmax;
      vmin = o.vmin; vmax = o.vmax;
      offset = o.offset;
      return *this;
    }
  };
  
  struct Obstacle
  {
    PtcObstacle* obstacle;
    int id;

    Obstacle() : id(-1){}
  };
  DsArray<Obstacle> m_obstacles;

  struct ObstacleMovement
  {
    ObstacleMovement () {}
    ObstacleMovement (float tx, float ty, float tz, float ra, float rx, float ry, float rz)
      : translate(tx, ty, tz)
      , rotate(rx,ry,rz)
      , rangle(ra)
    {}
    AlgVector translate;
    AlgVector rotate;
    float rangle;
  };

  struct Step
  {
    float timestep;
    int numparticles;
    char filename[NF_FILE_NAME_SIZE+1];
    FileOffset materialoffset, radiusoffset, positionoffset;
    float xmin, ymin, zmin, xmax, ymax, zmax;
    DsArray<ScalarField> scalarfields;
    DsArray<VectorField> vectorfields;
    DsHash<int, ObstacleMovement> obstmovements;
    DsArray<Obstacle> obstacles;
    Step ()
      : timestep(-1.f), numparticles(-1)
      , materialoffset(-1), radiusoffset(-1), positionoffset(-1)
      , xmin(0), ymin(0), zmin(0), xmax(0), ymax(0), zmax(0)
    {
    }
    Step& operator= (const Step& o)
    {
      timestep = o.timestep;
      numparticles = o.numparticles;
      strcpy(filename, o.filename);
      materialoffset = o.materialoffset;
      radiusoffset = o.radiusoffset;
      positionoffset = o.positionoffset;
      xmin = o.xmin; ymin = o.ymin; zmin = o.zmin;
      xmax = o.xmax; ymax = o.ymax; zmax = o.zmax;
      scalarfields.Resize(o.scalarfields.Size());
      for (int i = 0; i < o.scalarfields.Size(); i++)
        scalarfields.Set(i, o.scalarfields.GetRef(i));
      vectorfields.Resize(o.vectorfields.Size());
      for (int i = 0; i < o.vectorfields.Size(); i++)
        vectorfields.Set(i, o.vectorfields.GetRef(i));
      return *this;
    }
  };
  struct Case
  {
    char name[NF_CASE_NAME_SIZE+1];
    DsArray<Step> steps;
  };
  DsArray<Case> m_cases;
  int m_currentcase;
  int m_currentstep;
  int m_currentfield;

  struct Material
  {
    char name[NF_FIELD_NAME_SIZE+1];
    //int id;
  };
  DsArray<Material> m_materials;

  unsigned int m_numparticles;
  DsArray<float> m_posbuffer;
  DsArray<float> m_radiusbuffer;
  DsArray<float> m_scalarbuffer;
  DsArray<float> m_vectorbuffer;
  DsArray<int> m_matbuffer;
  char m_cfgdir[NF_FILE_NAME_SIZE+1];
};

/************************************************************************
  Inline Methods
*************************************************************************/

inline int PtcNFLoader::GetMaterialCount () const
{
  return m_materials.Size();
}

inline const char* PtcNFLoader::GetMaterialName (int id) const
{
  if (!m_materials.ValidIndex(id-1)) {
    return NULL;
  }
  return m_materials[id-1].name;
}

inline bool PtcNFLoader::SetCase (int index)
{
  if (index < 0 || index >= m_cases.Size()) {
    return false;
  }
  m_currentcase = index;
  return true;
}

#endif
