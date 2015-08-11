// dataloader.h
//
// This file declares the TrnDataLoader interface.
// Classes that implement TrnDataLoader must provide methods that allow the
// application to access terrain and texture information, as well as 2D
// blocks of data at arbitrary locations.
//
// Data blocks have their origin at the UPPER LEFT corner.

#ifndef TERRAIN_DATA_LOADER_H
#define TERRAIN_DATA_LOADER_H

#include "baseclass.h"

class TERRAINAPI TrnDataLoader : public TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnDataLoader";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Enums

  enum DataType
  {
    T_GEOMETRY = 0, // Data to be used as geometry
    T_TEXTURE  = 1,  // Data to be used as texture
  };

  enum GeometryDataType // Other types must be converted to one of these
  {
    GEOMETRY_INVALID = 10,
    GEOMETRY_SHORT   = 11,  // 2-byte signed integer
    GEOMETRY_INT     = 12,  // 4-byte signed integer
    GEOMETRY_FLOAT   = 13,  // 4-byte signed float
    GEOMETRY_DOUBLE  = 14,  // 8-byte signed float
  };

  enum TextureDataType // Other types must be converted to one of these
  {
    TEXTURE_INVALID = 20,
    TEXTURE_BYTE    = 21,  // 1-byte   signed integer
    TEXTURE_UBYTE   = 22,  // 1-byte unsigned integer
    TEXTURE_SHORT   = 23,  // 2-byte   signed integer
    TEXTURE_USHORT  = 24,  // 2-byte unsigned integer
    TEXTURE_INT     = 25,  // 4-byte   signed integer
    TEXTURE_UINT    = 26,  // 4-byte unsigned integer
    TEXTURE_FLOAT   = 27,  // 4-byte   signed float
  };

  // Constructor

  TrnDataLoader ()
  : TrnBaseClass()
  , m_baseValuesOrigin(0.0f)
  {
  }

  // Virtual Methods

  virtual int GetComponentType () = 0;
  virtual int GetComponentCount () = 0;
  virtual int GetTotalWidth () = 0;
  virtual int GetTotalHeight () = 0;
  virtual int GetDataType () = 0;
  virtual int GetComponentSize ()
  {
    switch(GetComponentType())
    {
    case TEXTURE_BYTE:
    case TEXTURE_UBYTE:
      return sizeof(char);            // usually 1
    case GEOMETRY_SHORT:
    case TEXTURE_SHORT:
    case TEXTURE_USHORT:
      return sizeof(short);           // usually 2
    case GEOMETRY_INT:
    case TEXTURE_INT:
    case TEXTURE_UINT:
      return sizeof(int);             // usually 4
    case GEOMETRY_FLOAT:
    case TEXTURE_FLOAT:
      return sizeof(float);           // usually 4
    case GEOMETRY_DOUBLE:
      return sizeof(double);          // usually 8
    default:
      return 0;
    }
  }

  // Sets the base value that needs to be added to each data component
  void SetBaseValuesOrigin (float origin)
  {
    m_baseValuesOrigin = origin;
  }

  // Returns the value that needs to be added to each data component,
  // accounting for any internal conversions performed on the data.
  virtual float GetValuesOrigin ()
  {
    return m_baseValuesOrigin;
  }

  // Fills an array with a square block of data
  // If no array is supplied, returns an array internally allocated with malloc()
  // 'line_skip' indicates an additional offset size (in elements) between each
  // pair of lines of data
  virtual void* GetData (int x, int y, int dx, int dy, void* data = 0, int line_skip = 0) = 0;

  // Fills an array with a square block of flag data (geometry data only)
  // If no array is supplied, returns an array internally allocated with malloc()
  // 'line_skip' indicates an additional offset size (in elements) between each
  // pair of lines of data
  // Returns NULL if not a geometry loader or if no flag data available
  virtual void* GetFlagData (int x, int y, int dx, int dy, void* data = 0, int line_skip = 0) = 0;

  // Fills an array with a square block of data
  // If no array is supplied, returns an array internally allocated with malloc()
  // The 'min' and 'max' arrays must be supplied to be filled with each data
  // component's minimum and maximum value, according to the source data type.
  virtual void* GetDataMinMax (int x, int y, int dx, int dy, void* min, void* max, void* data = 0);

  // Fills an array with a square block of data.
  // If no array is supplied, returns an array internally allocated with malloc()
  // If data is requested outside the original valid limits, the original
  // data's borders are replicated to fill up the requested values
  virtual void* GetBorderFilledData (int x, int y, int dx, int dy, void* data = 0);

private:

  float m_baseValuesOrigin;
};

#endif // TERRAIN_DATA_LOADER_H
