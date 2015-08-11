
#ifndef _TOP_NIKE3D_READER_H
#define _TOP_NIKE3D_READER_H

#include "defines.h"

class  TopModel;

class TOPSRD_API TopNIKE3DReader
{
public: 

  /**
    Reads elements from node and element files into a model.

    Elements adjacencies are automaticaly updated. 
  */
  static int Read(TopModel* model, const char* filename);
};


#endif
