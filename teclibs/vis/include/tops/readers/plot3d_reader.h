

#ifndef _TOP_PLOT3D_READER_H
#define _TOP_PLOT3D_READER_H

#include "defines.h"

class  TopModel;

class TOPSRD_API TopPlot3DReader
{
public: 

  /**
      Reads elements from node and element files into a model.
      Currently, only works for plot3d single-zoned structured binary
    big-endian (like NASA Bluntfin model) format.
  */
  static int Read(TopModel* model, const char* fgrid, const char* fsol, int scalar_id = 0, bool hexa = false);
};


#endif
