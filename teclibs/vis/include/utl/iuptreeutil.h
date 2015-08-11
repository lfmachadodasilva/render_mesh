#ifndef _IUP_TREE_UTIL_H_
#define _IUP_TREE_UTIL_H_



#include <iup.h>
#include <iuptree.h>
#include <list>
#include <ds/hash.h>
#include "utliup.h"

class IupLeafWrapper;
class IupTreeWrapper;
class IupTreeRootWrapper;

class UTLIUPAPI IupNodeWrapper
{
public:
   virtual ~IupNodeWrapper ();
   int id(void);

   void setData(void* data) { _data = data; }
   void* getData() { return _data; }

   char* getName(void) { return _name; }
   void setName(char* name);

   void setRenamable(bool renamable) { _renamable = renamable; }
   bool getRenamable() { return _renamable; }

   void setSelected(bool status);

   IupTreeWrapper* getParent(void) { return _parent; }
   IupTreeRootWrapper* getRoot(void);
   virtual int selection(int status)
   {
     return IUP_DEFAULT;
   }
   virtual void droppedTo(IupTreeWrapper *node, bool isshift, bool iscontrol)
   {
   }
   virtual void droppedTo(IupLeafWrapper *node, bool isshift, bool iscontrol)
   {
   }
   void redraw(void);
protected:
   IupNodeWrapper(char* name, void* data = 0);
   void setTree(Ihandle* tree) { _tree = tree; }
   Ihandle* _tree;
   IupTreeWrapper* _parent;
   char* _name;
   void* _data;
   bool _renamable;
};

class UTLIUPAPI IupLeafWrapper : public IupNodeWrapper
{
public:
   IupLeafWrapper(char* nome, void* data = 0);

   virtual ~IupLeafWrapper ()
   {
   }
   void setColor(const char *color);
   const char* getColor(void) const
   {
     return _color;
   }
   // callbacks
   virtual int selection(int status);
   virtual int execute(char* name);
   virtual int rename(char* name);
   virtual int rightClick(void);

protected:
   friend class IupTreeWrapper;
private:
   bool hasColor() const
   {
     return _color != NULL;
   }
   void setColor();
private:
   char* _color;
};

class UTLIUPAPI IupTreeWrapper : public IupNodeWrapper
{
public:
   IupTreeWrapper(char* name, void* data = 0);
   virtual ~IupTreeWrapper ();
   // Addition of leaves and branches
   void addLeafFront(IupLeafWrapper* leaf);
   void addLeafBack(IupLeafWrapper* leaf);

   void addSubTreeFront(IupTreeWrapper* subTree);
   void addSubTreeBack(IupTreeWrapper* subTree);

   // findLeaf in subtree
   IupLeafWrapper* findLeaf(void* data, bool searchSubTrees = true);
   
   // removal of leaves and branches
   bool removeLeaf(IupLeafWrapper* leaf, bool deleteLeaf = false);
   bool removeLeaves(bool includeSubTrees = true, bool deleteLeaves = false);

   bool removeSubTree(IupTreeWrapper* subTree, bool deleteSubTree = false);
   bool removeSubTrees(bool deleteSubTrees = false, bool deleteLeaves = false);
   
   // callbacks

   virtual int selection(int status);
   virtual int branchOpen(void);
   virtual int branchClose(void);
   virtual int rename(char* name);
   virtual int rightClick(void);

protected:

   typedef std::list<IupTreeWrapper*> TreeList;
   typedef std::list<IupLeafWrapper*> LeafList;

   TreeList _subTrees;
   LeafList _leaves;


   int tree(void);

   int subTreeFrontPosition(void);
   int subTreeBackPosition(void);

   int leafFrontPosition(void);
   int leafBackPosition(void);


   int getDepth(void* userId);
   void setDepth(void* userId, int depth);

};

class UTLIUPAPI IupTreeRootWrapper : public IupTreeWrapper
{
public:
  IupTreeRootWrapper(Ihandle* tree, char* rootName, bool deletetree, void* data = 0);
  virtual ~IupTreeRootWrapper();

  void setSelectedNodes(int *ids,int n,bool selected);
  void clearSelectedNodes();

  void callDroppedToLeaf(IupLeafWrapper *leaf, bool isshift, bool iscontrol);
  void callDroppedToBranch(IupTreeWrapper *branch, bool isshift, bool iscontrol);
private:
  IupNodeWrapper *getNodeByID(int id);
  IupNodeWrapper** getSelectedNodes();
  DsHash<IupNodeWrapper*,bool> _selectedNodes;
  bool _deletetree;
};

#endif
