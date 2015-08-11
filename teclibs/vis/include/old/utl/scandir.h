#ifndef UTL_SCANDIR_H_OLD
#define UTL_SCANDIR_H_OLD

#include <uso/scandir.h>

class UtlScanDir : public USOScanDir
{
public:
  UtlScanDir(const char *path, const char *file, bool acceptdirectories=false) :
    USOScanDir(path,file,acceptdirectories)
  {
  }
};

#endif

