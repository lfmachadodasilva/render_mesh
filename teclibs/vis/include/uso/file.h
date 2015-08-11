// file.h
// Portable file manipulator. (Win32 & POSIX)
// Tecgraf/PUC-Rio
// fabraham@tecgraf.puc-rio.br
// Dec 2006

#ifndef USO_FILE_H
#define USO_FILE_H

#define USO_PATH_TYPE_DIR 1
#define USO_PATH_TYPE_FILE 2
#define USO_INVALID_DIR 111

#include "defines.h"
#include <stdio.h>

USO_API bool uso_file_exists (const char *filename);
/**
 * Returns the short path of 'src' (also called 8.3 path).
 */
USO_API char* uso_get_short_path (const char* src);
/**
 * Returns the long path of 'src'.
 */
USO_API char* uso_get_long_path (const char* src);
/**
 * File access time compare
 * Returns -1 if 'f1' is newer than 'f2',
 * 0 if they have the same time or
 * 1 if 'f2' is newer than 'f1'.
 * Returns -2 in case of errors.
 */
USO_API int uso_file_time_cmp (const char *f1, const char *f2);
USO_API size_t uso_file_size (const char *filename);
/**
 * Returns 'true' if 'destfile' exists and is newer than the
 * 'numsrcs' files with filenames 'srcs'.
 */
USO_API bool uso_file_exists_and_is_newer (const char *destfile, int numsrcs, const char* const* srcs);
/**
 * Returns the extension of file 'filepath'. Returns NULL if the file does not have an extension.
 */
USO_API const char* uso_get_file_ext (const char *filepath);
/**
 * Returns file name part of file path 'filepath'. Returns NULL if the path contains a directory.
 */
USO_API const char* uso_get_file_name (const char *filepath);
/**
 * Breaks file path 'filename' into its directory and file parts.
 * Both '/' and '\' are considered slashes.
 * 'directory' and 'file' can be NULL if they are not useful.
 * 'directory', if passed, will hold the file directory containing the final slash.
 * Returns *directory = 'NULL' in case a path without directory was passed.
 * Memory allocated for both pointers must be freed with 'free'.
 */
USO_API void uso_break_path (const char* filename, char** directory, char** file);

/**
 * Copies path 'pathSource' to path 'pathTarget'.
 * 'pathSource' and 'pathTarget' can both be a file or directory.
 *
 * Returns 1 in case of success, 0 or -1 otherwise.
 */
USO_API int uso_copy (const char* pathSource, const char* pathTarget);

/**
 * Returns the path of file 'filename'. Returns NULL if the file does not have an path.
 */
USO_API const char* uso_get_file_path (const char *filename);
#endif

