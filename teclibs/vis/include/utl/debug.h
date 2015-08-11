// debug.h
// Debug utility methods
// Sept 2009
// cpalomo@tecgraf.puc-rio.br

#ifndef utl_debug_h
#define utl_debug_h

#include <utl/defines.h>

#include <ds/hash.h>

#include <assert.h>
#include <stdio.h>

class UTL_API UtlDebug
{
public:
  static bool GetFlag (const char* id);
  static void SetFlag (const char* id, bool flag);
  static bool InvertFlag (const char* id);
  static double GetNumber (const char* id);
  static void SetNumber (const char* id, double v);
  
public:
  static const double UTL_DEBUG_UNDEFINED_NUMBER;

private:
  static DsHash<DsStringKey, bool> s_flags_hash;  /**< keep record of active/inactive flags */
  static DsHash<DsStringKey, double> s_numbers_hash;  /**< store numbers */
};

/**
 * Checks the integrity of dynamic memory heap.
 * Returns true if the heap is consistent, and false otherwise.
 *
 * Note: Currently, Windows/Visual Studio only. Always returns true otherwise. 
 */
UTL_API bool utlDebugCheckHeapConsistency ();


#endif

