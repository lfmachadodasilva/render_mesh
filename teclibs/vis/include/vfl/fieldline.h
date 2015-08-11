#ifndef VFL_FIELDLINE_H
#define VFL_FIELDLINE_H

//----------//
// Includes //
//----------//

#include "defines.h"

#include <ds/list.h>
#include <ugl/vertexarray.h>
#include <ugl/interleavedarray.h>

#include <stdio.h>

//-------------//
// Definitions //
//-------------//

#define VFL_FILE_VERSION 1.2
#define VFL_FILE_EXTENSION "vfl"

#define VFL_LINE      100
#define VFL_LINELIST  101
#define VFL_MULTILINE 102

#define VFL_END       0
#define VFL_VERTEX    1
#define VFL_TANGENT   2
#define VFL_MAGNITUDE 3
#define VFL_DIFFUSE   4
#define VFL_SPECULAR  5
#define VFL_COLOR     6
#define VFL_TEXTURE   7

//----------------------//
// Forward Declarations //
//----------------------//

//------------------//
// Static Functions //
//------------------//

VFL_API char* vfl_adjustFilename (const char* filename, const char* extension);
VFL_API bool  vfl_writeCurrentVersion (FILE* file);
VFL_API bool  vfl_skipLine(FILE* file);
VFL_API bool  vfl_skipLineList(FILE* file);

//---------------------------------//
// Class Definition - VflFieldLine //
//---------------------------------//

class VFL_API VflFieldLine
{
public:

  // Constructors and Destructor

  VflFieldLine (unsigned int vertexCount = 0, bool useBufferObject = false, bool gpuGeneration = false, bool useStrips = true);
  virtual ~VflFieldLine ();

  // Memory management

  void CleanUp ();
  bool Resize (unsigned int vertexCount); // Automatically resizes any existing arrays

  UGLArray* ReserveVertices        ();
  UGLArray* ReserveTangents        ();
  UGLArray* ReserveMagnitudes      ();
  UGLArray* ReserveDiffuseNormals  ();
  UGLArray* ReserveSpecularNormals ();
  UGLArray* ReserveColors          (unsigned int components = 3); // 3 (RGB) or 4 (RGBA) components
  UGLArray* ReserveTexCoords       (unsigned int components = 1); // 1 (s)   to 3 (stp)  components

  void FreeVertices        ();
  void FreeTangents        ();
  void FreeMagnitudes      ();
  void FreeDiffuseNormals  ();
  void FreeSpecularNormals ();
  void FreeColors          ();
  void FreeTexCoords       ();

  // Setters and Getters

  UGLArray* GetVertices          () const {return m_vertices;}
  UGLArray* GetTangents          () const {return m_tangents;}
  UGLArray* GetMagnitudes        () const {return m_magnitudes;}
  UGLArray* GetDiffuseNormals    () const {return m_diffuseNormals;}
  UGLArray* GetSpecularNormals   () const {return m_specularNormals;}
  UGLArray* GetColors            () const {return m_colors;}
  UGLArray* GetTexCoords         () const {return m_texCoords;}

  void SetBaseColor (unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
  {
    m_colorR = r;
    m_colorG = g;
    m_colorB = b;
    m_colorA = a;
  }

  void GetBaseColor (unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a) const
  {
    if (r) *r = m_colorR;
    if (g) *g = m_colorG;
    if (b) *b = m_colorB;
    if (a) *a = m_colorA;
  }

  unsigned int GetVertexCount        () const {return m_vertexCount;}
  unsigned int GetTexCoordComponents () const {return m_texCoordComponents;}
  unsigned int GetColorComponents    () const {return m_colorComponents;}

  void SetGpuGeneration   (bool state) {m_gpuGeneration = state;}
  void SetUseBufferObject (bool state);

  bool GetGpuGeneration   () {return m_gpuGeneration;}
  bool GetUseBufferObject () {return m_useBufferObject;}
  bool GetUseStrips       () {return m_useStrips;}

  // File Management

  virtual bool SaveToFile (const char* filename);
  virtual bool LoadFromFile (const char* filename);

  virtual bool WriteLine (FILE* file);
  virtual bool ReadLine  (FILE* file);
  virtual bool WriteArray (UGLArray* array, unsigned int code, unsigned int components, FILE* file);
  virtual bool ReadArray (UGLArray* array, unsigned int components, FILE* file);

private:

  bool ResizeArray (UGLArray *whichArray);

  UGLArray* m_vertices;        // UGLArray::V_POSITION
  UGLArray* m_tangents;        // UGLArray::V_NORMAL
  UGLArray* m_magnitudes;      // UGLArray::V_TEXCOORD
  UGLArray* m_diffuseNormals;  // UGLArray::V_NORMAL
  UGLArray* m_specularNormals; // UGLArray::V_NORMAL
  UGLArray* m_colors;          // UGLArray::V_COLOR
  UGLArray* m_texCoords;       // UGLArray::V_TEXCOORD

  unsigned int m_vertexCount;
  unsigned int m_colorComponents;
  unsigned int m_texCoordComponents;

  bool m_gpuGeneration;
  bool m_useBufferObject;
  bool m_useStrips;

  unsigned char m_colorR;
  unsigned char m_colorG;
  unsigned char m_colorB;
  unsigned char m_colorA;
};

//-------------------------------------//
// Class Definition - VflFieldLineList //
//-------------------------------------//

class VFL_API VflFieldLineList
{
public:
  typedef DsList<VflFieldLine*>::Iterator Iterator;

  VflFieldLineList()
  {
  }

  virtual ~VflFieldLineList()
  {
    Clear();
  }

  Iterator Begin ()
  {
    return m_fieldLineList.Begin();
  }

  void Append (VflFieldLine *fldLine)
  {
    m_fieldLineList.Append(fldLine);
  }

  void Insert (VflFieldLine *fldLine)
  {
    m_fieldLineList.Insert(fldLine);
  }

  void Remove (VflFieldLine *fldLine)
  {
    m_fieldLineList.Remove(fldLine);
  }

  int Size ()
  {
    return m_fieldLineList.Size();
  }

  void Clear (bool destroyLines = true)
  {
    if (destroyLines)
    {
      for (Iterator it = m_fieldLineList.Begin(); it.Valid(); ++it)
      {
        VflFieldLine *fldLine = it.Self();
        if (fldLine) delete fldLine;
      }
    }
    m_fieldLineList.Clear();
  }

  void SetUseBufferObject (bool state)
  {
    for (Iterator it = m_fieldLineList.Begin(); it.Valid(); ++it)
    {
      VflFieldLine *fldLine = it.Self();
      if (fldLine) fldLine->SetUseBufferObject(state);
    }
  }

  // File management

  virtual bool SaveToFile (const char* filename);
  virtual bool LoadFromFile (const char* filename);

  virtual bool WriteLineList (FILE* file);
  virtual bool ReadLineList  (FILE* file);

private:
  DsList<VflFieldLine*> m_fieldLineList;
};


//--------------------------------------//
// Class Definition - VflMultiFieldLine //
//--------------------------------------//

class VFL_API VflMultiFieldLine
{
public:

  // Constructors and Destructor

  VflMultiFieldLine (bool useBufferObject = false, bool gpuGeneration = false, bool useStrips = true);
  virtual ~VflMultiFieldLine ();

  // Setters and Getters

  void SetUseBufferObject (bool state);
  bool GetUseBufferObject ()
  {
    return m_useBufferObject;
  }

  void SetGpuGeneration (bool state);
  bool GetGpuGeneration ()
  {
    return m_gpuGeneration;
  }

  bool GetUseStrips ()
  {
    return m_useStrips;
  }

  // Memory Management

  bool Allocate (int maxFieldLineCount, int maxVertexCount)
  {
    int usedVertexCount = m_fieldLinesArray->GetUsedVertexCountCpu();
    return m_fieldLinesArray->ReserveCpu(usedVertexCount + maxFieldLineCount * maxVertexCount);
  }

  bool Reserve (int maxFieldLineCount, int maxVertexCount)
  {
    return m_fieldLinesArray->ReserveCpu(maxFieldLineCount * maxVertexCount);
  }

  bool ResizeTight ()
  {
    return m_fieldLinesArray->ResizeTightCpu(true, true);
  }

  // Fieldline Management

  int AddFieldLine (int vertexCount)
  {
    return m_fieldLinesArray->AddSubArrayCpu(vertexCount, vertexCount);
  }

  void RemoveFieldLine (int fieldLineId)
  {
    return m_fieldLinesArray->RemoveSubArray(fieldLineId);
  }

  int GetFieldLineCount () const
  {
    return m_fieldLinesArray->GetSubArrayCount();
  }

  // Internal Arrays

  UGLInterleavedArray* GetArray ()
  {
    return m_fieldLinesArray;
  }

  void SetMagnitudes (int fieldLineId, float* magnitudes) const
  {
    return m_fieldLinesArray->SetDataArrayCpu(fieldLineId, m_idMagnitudes, magnitudes);
  }

  void SetVertices (int fieldLineId, float* vertices) const
  {
    return m_fieldLinesArray->SetDataArrayCpu(fieldLineId, m_idVertices, vertices);
  }

  void SetTangents (int fieldLineId, float* tangents) const
  {
    return m_fieldLinesArray->SetDataArrayCpu(fieldLineId, m_idTangents, tangents);
  }

  //virtual bool WriteMultiLine (FILE* file); // ToDo
  //virtual bool ReadMultiLine  (FILE* file); // ToDo

private:

  UGLInterleavedArray* m_fieldLinesArray;

  int m_idMagnitudes;
  int m_idVertices;
  int m_idTangents;

  bool m_gpuGeneration;
  bool m_useBufferObject;
  bool m_useStrips;

};

#endif // VFL_FIELDLINE_H
