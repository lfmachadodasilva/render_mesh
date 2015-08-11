// Lines class
// fabraham@tecgraf.puc-rio.br
// Set 2003

#ifndef SG_LINES_H
#define SG_LINES_H

#include <sg/shape.h>

class UGLLineSet;
class UGLLineStrip;

class SG_API SGLines : public SGShape
{
  typedef DsPList<UGLLineSet> SetList;
  typedef DsPList<UGLLineStrip> StripList;

  static char* s_path;
  static char* s_prefix;
  static int   s_file_count;

  SetList m_sets;
  StripList m_strips;
public:
  static const char* CLASSNAME () { return "Line"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  static void SetPath (const char* path);
  static void SetFilePrefix (const char* prefix);
  static void ResetFileCount ();

  SGLines ();
  SGLines (int ns, float* v);
  virtual ~SGLines ();

  void AddLineSet (UGLLineSet* set);
  void AddLineStrip (UGLLineStrip* strip);

  bool ReadFromFile  (char * filename);
  bool WriteToFile (char * filename);

  virtual int GetTriangleCount ();
  virtual int GetLineCount ();
  virtual void Draw ();
  virtual void Write (UtlWriter* writer);
};

#endif
