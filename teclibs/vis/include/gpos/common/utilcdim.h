//* utilcdim.h
// Basic utility functions
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef ps_util_cdim_h
#define ps_util_cdim_h

#ifndef GPOSUTILS_DLL
# ifndef TEC_DLL
#  define RESUTILSAPI
# else
#  define RESUTILSAPI __declspec(dllimport)
# endif
#else
# define RESUTILSAPI __declspec(dllexport)
#endif

//* 'PSCDUtil' Class
// Implements CD related utility functions
class RESUTILSAPI PSCDUtil
{
public:

    //* Snapshot
		// Dumps the current active canvas to a file.
		// Format is given by image format enum above.
		// Returns true on success, false otherwise.
	static bool SaveSnapshot(const char *file, int x, int y, int w, int h, int format);
};

//* 'PSGlutUtil' Class
// Implements GL/Glut related utility functions
class RESUTILSAPI PSGlutUtil
{
  static void WriteColorBuffer(void *canvas, int width, int height);
public:

    //* Snapshot
		// Dumps the current color buffer to a file.
		// Format is given by image format enum above.
		// Returns true on success, false otherwise.
	static bool SaveSnapshot(const char *file, int format, int width, int height);

    //* Print
    // Prints the current color buffer.
    // Returns true on success, false otherwise.
  static bool PrintSnapshot(int width, int height);

    //* Clipboard copy
    // Copies the current color buffer to the clipboard.
    // Returns true on success, false otherwise.
  static bool CopySnapshotToClipboard(int width, int height);

};

#endif

