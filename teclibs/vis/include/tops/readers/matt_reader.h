
#ifndef _TOP_MATT_READER_H
#define _TOP_MATT_READER_H

#include "defines.h"

class  TopModel;

class TOPSRD_API TopMattReader
{
  static int Read(TopModel* model,
      const char* fnodes, const char* felem);
public: 
  static int Read(TopModel* model, 
      const char* filename);
};


#endif
