#ifndef TERRAIN_DATA_LOADER_IM_H
#define TERRAIN_DATA_LOADER_IM_H

#include "dataloader.h"

typedef struct _imImage imImage;

class TERRAINAPI TrnDataLoaderIm : public TrnDataLoader
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnDataLoaderIm";}
  virtual const char* ClassName () const {return CLASSNAME();}

  // Constructor and Destructor

  TrnDataLoaderIm ();
  ~TrnDataLoaderIm ();

  // Load and CleanUp

  bool Load (const char* filename, int dataType);
  void CleanUp ();

  // Getters

  int GetComponentType ();
  int GetComponentCount ();
  int GetTotalWidth ();
  int GetTotalHeight ();
  int GetDataType ();
  float GetValuesOrigin ();

  // Data Getters

  void* GetData (int x, int y, int dx, int dy, void* data = 0, int line_skip = 0);
  void* GetFlagData (int x, int y, int dx, int dy, void* data = 0, int line_skip = 0);
  void* GetDataMinMax (int x, int y, int dx, int dy, void* min, void* max, void* data = 0);

private:
  imImage* m_image;
  imImage* m_flagimage;
  int m_dataType;
};

#endif // TERRAIN_DATA_LOADER_IM_H
