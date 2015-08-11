/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 -W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef _TOP_ERROR_H
#define _TOP_ERROR_H

#include <assert.h>
#include "defines.h"

class TopModel;
class TopErrorHandler;

#define TOP_ERROR_MAX_STRING 256

class TOPS_API TopErrorListener
{
public:
  virtual ~TopErrorListener() {}
  virtual bool ErrorReported(const TopErrorHandler* e) = 0;
};

class TOPS_API TopErrorHandler
{
private:
  TopModel* m_model;
  int  m_error;
  TopErrorListener* m_listener; 

public:
  enum ErrorType {
    ERR_NONE = 0,
    ERR_ERROR,
    ERR_OUT_OF_MEMORY
  };

  TopErrorHandler();
  ~TopErrorHandler();

  TopModel* GetModel() const;

  int GetError() const;

  void Clear(); 

  void SetListener(TopErrorListener* l);

  TopErrorListener* GetListener();

  /** @internal */
  void SetModel(TopModel* m);
  int ReportError(int err);
  bool Assert(bool v, int err)
  {
    if (!v)
      ReportError(err);
#ifdef _DEBUG
      assert(v);
#endif
    return v;
  }
};

#endif

