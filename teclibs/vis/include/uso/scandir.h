//* scandir.h
// Portable directory contents scanner. (Win32 & POSIX)
// Tecgraf/PUC-Rio
// Jun 2004

#ifndef USO_SCANDIR_H
#define USO_SCANDIR_H

#include "defines.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <glob.h>
#include <stdlib.h>
#endif

class USO_API USOScanDir
{
  bool m_valid;
  bool m_acceptdirs;
#ifdef _WIN32
  bool m_first;
  WIN32_FIND_DATA m_filedata;
  HANDLE m_hsearch;
#else
  glob_t m_buf;
  unsigned int m_curr;
  char *m_path;
#endif
public:
  /**
   * Constructor
   * 'path' is a valid path to an existing directory.
   * 'file' is file pattern, where usual wildcards can be used. (Ex: "*.txt")
   * 'acceptdirectories' directories must be returned in the search.
   */
  USOScanDir(const char *path, const char *file, bool acceptdirectories=false);
  ~USOScanDir();
  /**
   * Returns the name of the next file that satisfies the pattern given.
   * Returns NULL if there are no more files or if the path given is invalid or
   * the next file could not be accessed.
   */
  const char * FindNext(bool *isdirectory=NULL);
};

#endif

