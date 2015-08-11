//* scandir.h
// Portable directory contents scanner. (Win32 & POSIX)
// Tecgraf/PUC-Rio
// Jun 2004

#ifndef ps_scandir_h
#define ps_scandir_h

#ifdef _WIN32
#include <windows.h>
#else
#include <glob.h>
#include <stdlib.h>
#endif
#include <gpos/defines.h>

//* 'PSScanDir' Class
// Portable directory contents scanner.
class RES_API PSScanDir
{
	bool m_valid;
#ifdef _WIN32
  WIN32_FIND_DATA m_filedata;
  HANDLE m_hsearch;
  bool m_first;
#else
	glob_t m_buf;
	int m_curr;
	char *m_path;
#endif

  PSScanDir()
  {
  }

public:
  //* Constructor
  // The client specifies a valid path to an existing directory
  // and a file pattern, where usual wildcards can be used. (Ex: "*.txt")
  PSScanDir(const char *path, const char *file);
  
  ~PSScanDir();

  //* FindNext
  // Returns the name of the next file that satisfies the pattern given.
  // Returns NULL if there are no more files or if the path given is invalid or
  // the next file could not be accessed.
  const char * FindNext();
};

#endif
