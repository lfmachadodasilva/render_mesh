// UtlIupLeaf/UtlIupBranch class
// fabraham@tecgraf.puc-rio.br
// Sep 2003
#ifndef IUP_TREE_UTIL_CB_H
#define IUP_TREE_UTIL_CB_H

#include "iuptreeutil.h"
#include "utliup.h"
#include <stdio.h>

class UtlIupLeaf;
class UtlIupBranch;
class UtlIupRootBranch;

typedef int (*UtlIupLeafSelectionFunc)       (UtlIupLeaf* leaf, int status,                                       void* leafdata, void *funcdata); 
typedef int (*UtlIupLeafExecuteFunc)         (UtlIupLeaf* leaf, char *name,                                       void* leafdata, void *funcdata);
typedef int (*UtlIupLeafRenameFunc)          (UtlIupLeaf* leaf, char *name,                                       void* leafdata, void *funcdata);
typedef int (*UtlIupLeafRightClickFunc)      (UtlIupLeaf* leaf,                                                   void* leafdata, void *funcdata);
typedef void (*UtlIupLeafDroppedToLeafFunc)  (UtlIupLeaf* leaf, UtlIupLeaf *node,   bool isshift, bool iscontrol, void* leafdata, void *funcdata);
typedef void (*UtlIupLeafDroppedToBranchFunc)(UtlIupLeaf* leaf, UtlIupBranch *node, bool isshift, bool iscontrol, void* leafdata, void *funcdata);

class UTLIUPAPI UtlIupLeaf : public IupLeafWrapper
{
  UtlIupLeafSelectionFunc m_selfunc;
  UtlIupLeafExecuteFunc m_execfunc;
  UtlIupLeafRenameFunc m_renfunc;
  UtlIupLeafRightClickFunc m_rightclickfunc;
  UtlIupLeafDroppedToLeafFunc m_droppedtoleaffunc;
  UtlIupLeafDroppedToBranchFunc m_droppedtobranchfunc;
  void* m_seldata;
  void* m_execdata;
  void* m_rendata;
  void* m_rightclickdata;
  void* m_droppedtoleafdata;
  void* m_droppedtobranchdata;
public:
  UtlIupLeaf(char* name) :
    IupLeafWrapper(name),
    m_selfunc(NULL),
    m_execfunc(NULL),
    m_renfunc(NULL),
    m_rightclickfunc(NULL),
    m_droppedtoleaffunc(NULL),
    m_droppedtobranchfunc(NULL),
    m_seldata(NULL),
    m_execdata(NULL),
    m_rendata(NULL),
    m_rightclickdata(NULL),
    m_droppedtoleafdata(NULL),
    m_droppedtobranchdata(NULL)
  {
  }
  virtual ~UtlIupLeaf ()
  {
  }
  void SetSelectionFunc (UtlIupLeafSelectionFunc func, void *data)
  {
    m_selfunc = func;
    m_seldata = data;
  }
  void SetExecuteFunc (UtlIupLeafExecuteFunc func, void *data)
  {
    m_execfunc = func;
    m_execdata = data;
  }
  void SetRenameFunc (UtlIupLeafRenameFunc func, void *data)
  {
    m_renfunc = func;
    m_rendata = data;
  }
  void SetRightClickFunc (UtlIupLeafRightClickFunc func, void *data)
  {
    m_rightclickfunc = func;
    m_rightclickdata = data;
  }
  void SetDroppedToLeafFunc (UtlIupLeafDroppedToLeafFunc func, void *data)
  {
    m_droppedtoleaffunc = func;
    m_droppedtoleafdata = data;
  }
  void SetDroppedToBranchFunc (UtlIupLeafDroppedToBranchFunc func, void *data)
  {
    m_droppedtobranchfunc = func;
    m_droppedtobranchdata = data;
  }
  virtual int selection(int status)
  {
    if (m_selfunc)
      return m_selfunc(this,status,getData(),m_seldata);
    else
      return IUP_DEFAULT; 
  }
  virtual int execute(char* name)
  {
    if (m_execfunc)
      return m_execfunc(this,name,getData(),m_execdata);
    else
      return IUP_DEFAULT; 
  }
  virtual int rename(char* name)
  {
    if (m_renfunc)
      return m_renfunc(this,name,getData(),m_rendata);
    else
      return IUP_DEFAULT; 
  }
  virtual int rightClick(void)
  {
    if (m_rightclickfunc)
      return m_rightclickfunc(this,getData(),m_rightclickdata);
    else
      return IUP_DEFAULT; 
  }
  virtual void droppedTo(IupTreeWrapper *node, bool isshift, bool iscontrol)
  {
     if (m_droppedtobranchfunc)
       m_droppedtobranchfunc(this,(UtlIupBranch*)node,isshift,iscontrol,getData(),m_droppedtobranchdata);
  }
  virtual void droppedTo(IupLeafWrapper *node, bool isshift, bool iscontrol)
  {
     if (m_droppedtoleaffunc)
       m_droppedtoleaffunc(this,(UtlIupLeaf*)node,isshift,iscontrol,getData(),m_droppedtoleafdata);
  }
};

typedef int  (*UtlIupBranchSelectionFunc)      (UtlIupBranch *branch, int status,                                       void* branchdata, void *funcdata); 
typedef int  (*UtlIupBranchRenameFunc)         (UtlIupBranch *branch, char *name,                                       void* branchdata, void *funcdata);
typedef int  (*UtlIupBranchBranchOpenFunc)     (UtlIupBranch *branch,                                                   void* branchdata, void *funcdata);
typedef int  (*UtlIupBranchBranchCloseFunc)    (UtlIupBranch *branch,                                                   void* branchdata, void *funcdata);
typedef int  (*UtlIupBranchRightClickFunc)     (UtlIupBranch *branch,                                                   void* branchdata, void *funcdata);
typedef void (*UtlIupBranchDroppedToLeafFunc)  (UtlIupBranch *branch, UtlIupLeaf *node,   bool isshift, bool iscontrol, void* branchdata, void *funcdata);
typedef void (*UtlIupBranchDroppedToBranchFunc)(UtlIupBranch *branch, UtlIupBranch *node, bool isshift, bool iscontrol, void* branchdata, void *funcdata);

class UTLIUPAPI UtlIupBranch : public IupTreeWrapper
{
  UtlIupBranchSelectionFunc m_selfunc;
  UtlIupBranchRenameFunc m_renfunc;
  UtlIupBranchBranchOpenFunc m_branchopenfunc;
  UtlIupBranchBranchCloseFunc m_branchclosefunc;
  UtlIupBranchRightClickFunc m_rightclickfunc;
  UtlIupBranchDroppedToLeafFunc m_droppedtoleaffunc;
  UtlIupBranchDroppedToBranchFunc m_droppedtobranchfunc;
  void* m_seldata;
  void* m_rendata;
  void* m_branchopendata;
  void* m_branchclosedata;
  void* m_rightclickdata;
  void* m_droppedtoleafdata;
  void* m_droppedtobranchdata;
public:
  UtlIupBranch(char* name) :
    IupTreeWrapper(name),
    m_selfunc(NULL),
    m_renfunc(NULL),
    m_branchopenfunc(NULL),
    m_branchclosefunc(NULL),
    m_rightclickfunc(NULL),
    m_droppedtoleaffunc(NULL),
    m_droppedtobranchfunc(NULL),
    m_seldata(NULL),
    m_rendata(NULL),
    m_branchopendata(NULL),
    m_branchclosedata(NULL),
    m_rightclickdata(NULL),
    m_droppedtoleafdata(NULL),
    m_droppedtobranchdata(NULL)
  {
  }
  virtual ~UtlIupBranch ()
  {
  }
  void SetSelectionFunc (UtlIupBranchSelectionFunc func, void *data)
  {
    m_selfunc = func;
    m_seldata = data;
  }
  void SetRenameFunc (UtlIupBranchRenameFunc func, void *data)
  {
    m_renfunc = func;
    m_rendata = data;
  }
  void SetBranchOpenFunc (UtlIupBranchBranchOpenFunc func, void *data)
  {
    m_branchopenfunc = func;
    m_branchopendata = data;
  }
  void SetBranchCloseFunc (UtlIupBranchBranchCloseFunc func, void *data)
  {
    m_branchclosefunc = func;
    m_branchclosedata = data;
  }
  void SetRightClickFunc (UtlIupBranchRightClickFunc func, void *data)
  {
    m_rightclickfunc = func;
    m_rightclickdata = data;
  }
  void SetDroppedToLeafFunc (UtlIupBranchDroppedToLeafFunc func, void *data)
  {
    m_droppedtoleaffunc = func;
    m_droppedtoleafdata = data;
  }
  void SetDroppedToBranchFunc (UtlIupBranchDroppedToBranchFunc func, void *data)
  {
    m_droppedtobranchfunc = func;
    m_droppedtobranchdata = data;
  }
  virtual int selection(int status)
  {
    if (m_selfunc)
      return m_selfunc(this,status,getData(),m_seldata);
    else
      return IUP_DEFAULT; 
  }
  virtual int rename(char* name)
  {
    if (m_renfunc)
      return m_renfunc(this,name,getData(),m_rendata);
    else
      return IUP_DEFAULT; 
  }
  virtual int branchOpen(void)
  {
    if (m_branchopenfunc)
      return m_branchopenfunc(this,getData(),m_branchopendata);
    else
      return IUP_DEFAULT; 
  }
  virtual int branchClose(void)
  {
    if (m_branchclosefunc)
      return m_branchclosefunc(this,getData(),m_branchclosedata);
    else
      return IUP_DEFAULT; 
  }
  virtual int rightClick(void)
  {
    if (m_rightclickfunc)
      return m_rightclickfunc(this,getData(),m_rightclickdata);
    else
      return IUP_DEFAULT; 
  }
  virtual void droppedTo(IupTreeWrapper *node, bool isshift, bool iscontrol)
  {
     if (m_droppedtobranchfunc)
       m_droppedtobranchfunc(this,(UtlIupBranch*)node,isshift,iscontrol,getData(),m_droppedtobranchdata);
  }
  virtual void droppedTo(IupLeafWrapper *node, bool isshift, bool iscontrol)
  {
     if (m_droppedtoleaffunc)
       m_droppedtoleaffunc(this,(UtlIupLeaf*)node,isshift,iscontrol,getData(),m_droppedtoleafdata);
  }
};

typedef int  (*UtlIupRootBranchSelectionFunc)      (UtlIupRootBranch *branch, int status,                                       void* branchdata, void *funcdata); 
typedef int  (*UtlIupRootBranchRenameFunc)         (UtlIupRootBranch *branch, char *name,                                       void* branchdata, void *funcdata);
typedef int  (*UtlIupRootBranchBranchOpenFunc)     (UtlIupRootBranch *branch,                                                   void* branchdata, void *funcdata);
typedef int  (*UtlIupRootBranchBranchCloseFunc)    (UtlIupRootBranch *branch,                                                   void* branchdata, void *funcdata);
typedef int  (*UtlIupRootBranchRightClickFunc)     (UtlIupRootBranch *branch,                                                   void* branchdata, void *funcdata);
typedef void (*UtlIupRootBranchDroppedToLeafFunc)  (UtlIupRootBranch *branch, UtlIupLeaf *node,   bool isshift, bool iscontrol, void* branchdata, void *funcdata);
typedef void (*UtlIupRootBranchDroppedToBranchFunc)(UtlIupRootBranch *branch, UtlIupBranch *node, bool isshift, bool iscontrol, void* branchdata, void *funcdata);

class UTLIUPAPI UtlIupRootBranch : public IupTreeRootWrapper
{
  UtlIupRootBranchSelectionFunc m_selfunc;
  UtlIupRootBranchRenameFunc m_renfunc;
  UtlIupRootBranchBranchOpenFunc m_branchopenfunc;
  UtlIupRootBranchBranchCloseFunc m_branchclosefunc;
  UtlIupRootBranchRightClickFunc m_rightclickfunc;
  UtlIupRootBranchDroppedToLeafFunc m_droppedtoleaffunc;
  UtlIupRootBranchDroppedToBranchFunc m_droppedtobranchfunc;
  void* m_seldata;
  void* m_rendata;
  void* m_branchopendata;
  void* m_branchclosedata;
  void* m_rightclickdata;
  void* m_droppedtoleafdata;
  void* m_droppedtobranchdata;
public:
  UtlIupRootBranch(Ihandle* tree, char* rootname, bool deletetree) :
    IupTreeRootWrapper(tree,rootname,deletetree),
    m_selfunc(NULL),
    m_renfunc(NULL),
    m_branchopenfunc(NULL),
    m_branchclosefunc(NULL),
    m_rightclickfunc(NULL),
    m_droppedtoleaffunc(NULL),
    m_droppedtobranchfunc(NULL),
    m_seldata(NULL),
    m_rendata(NULL),
    m_branchopendata(NULL),
    m_branchclosedata(NULL),
    m_rightclickdata(NULL),
    m_droppedtoleafdata(NULL),
    m_droppedtobranchdata(NULL)
  {
  }
  virtual ~UtlIupRootBranch ()
  {
  }
  void SetSelectionFunc (UtlIupRootBranchSelectionFunc func, void *data)
  {
    m_selfunc = func;
    m_seldata = data;
  }
  void SetRenameFunc (UtlIupRootBranchRenameFunc func, void *data)
  {
    m_renfunc = func;
    m_rendata = data;
  }
  void SetBranchOpenFunc (UtlIupRootBranchBranchOpenFunc func, void *data)
  {
    m_branchopenfunc = func;
    m_branchopendata = data;
  }
  void SetBranchCloseFunc (UtlIupRootBranchBranchCloseFunc func, void *data)
  {
    m_branchclosefunc = func;
    m_branchclosedata = data;
  }
  void SetRightClickFunc (UtlIupRootBranchRightClickFunc func, void *data)
  {
    m_rightclickfunc = func;
    m_rightclickdata = data;
  }
  void SetDroppedToLeafFunc (UtlIupRootBranchDroppedToLeafFunc func, void *data)
  {
    m_droppedtoleaffunc = func;
    m_droppedtoleafdata = data;
  }
  void SetDroppedToBranchFunc (UtlIupRootBranchDroppedToBranchFunc func, void *data)
  {
    m_droppedtobranchfunc = func;
    m_droppedtobranchdata = data;
  }
  virtual int selection(int status)
  {
    if (m_selfunc)
      return m_selfunc(this,status,getData(),m_seldata);
    else
      return IUP_DEFAULT; 
  }
  virtual int rename(char* name)
  {
    if (m_renfunc)
      return m_renfunc(this,name,getData(),m_rendata);
    else
      return IUP_DEFAULT; 
  }
  virtual int branchOpen(void)
  {
    if (m_branchopenfunc)
      return m_branchopenfunc(this,getData(),m_branchopendata);
    else
      return IUP_DEFAULT; 
  }
  virtual int branchClose(void)
  {
    if (m_branchclosefunc)
      return m_branchclosefunc(this,getData(),m_branchclosedata);
    else
      return IUP_DEFAULT; 
  }
  virtual int rightClick(void)
  {
    if (m_rightclickfunc)
      return m_rightclickfunc(this,getData(),m_rightclickdata);
    else
      return IUP_DEFAULT; 
  }
  virtual void droppedTo(IupTreeWrapper *node, bool isshift, bool iscontrol)
  {
     if (m_droppedtobranchfunc)
       m_droppedtobranchfunc(this,(UtlIupBranch*)node,isshift,iscontrol,getData(),m_droppedtobranchdata);
  }
  virtual void droppedTo(IupLeafWrapper *node, bool isshift, bool iscontrol)
  {
     if (m_droppedtoleaffunc)
       m_droppedtoleaffunc(this,(UtlIupLeaf*)node,isshift,iscontrol,getData(),m_droppedtoleafdata);
  }
};

#endif
