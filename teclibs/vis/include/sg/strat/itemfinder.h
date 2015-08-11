// Item finder
// fabraham@tecgraf.puc-rio.br
// Mar 2003

#ifndef SG_ITEM_FINDER
#define SG_ITEM_FINDER

#include <sg/strategy.h>

/**
 * Item finder traversal strategy.
 *
 * This strategy will traverse the scene graph looking for the first occurence of an item with a specified type (class name) and name.
 */
class SG_API SGItemFinder : public SGStrategy
{
  const char* m_name;
  const char* m_classname;
  SGItem* m_found_item;
  static SGItemFinder* s_instance;

  SGItemFinder ();
  virtual ~SGItemFinder ();
public:
	/**
	 * Searches the scene graph for an item with name 'name' and type 'classname'. If 'classname' is NULL, items with any type will be accepted.
	 */
  static SGItem * Find(SGNode* node, const char* name,const char* classname=0);

  virtual void Load (SGItem* i);
  virtual int Unload (SGNode* n);
  virtual int Load (SGScene* s);
};

#endif
