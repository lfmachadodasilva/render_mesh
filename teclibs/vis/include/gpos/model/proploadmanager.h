#ifndef RES_PROP_LOAD_MANAGER_H
#define RES_PROP_LOAD_MANAGER_H

#include <stdlib.h>
#include <gpos/defines.h>

class ResModel;
class ResProperty;

class RES_API ResPropertyLoadManager
{
public:
  ResPropertyLoadManager (ResModel* model, const char* propname);

  ~ResPropertyLoadManager ();

  ResProperty* Load (int stepi);

  void Unload ();

private:
  struct StringArray {
    StringArray (int length = 0, const char** values = NULL)
    : length(length)
    , values(values)
    {
    }
    int length;
    const char** values;
  };

private:
  ResProperty* Get (ResModel* model, const char* propname);

private:
  ResModel* m_model;
  ResProperty* m_prop;
  bool m_is_loaded;
  int m_stepi;
};

#endif

