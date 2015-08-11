// Item class
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_ITEM_H
#define SG_ITEM_H

#include <ds/hash.h>
#include "defines.h"
#include <string.h>

class UtlWriter;

/**
 * SGItem Class.
 * 
 * This is the base class for all the SG class hierarchy.
 * It defines methods to:
 * - get/check the object's classname.
 * - set/get/check the object's name.
 * - store and access user data
 * - write the object's description.
 */
class SG_API SGItem
{
  char* m_name;
  bool m_enabled;
  DsHash<DsStringKey,void*> m_userdata;
public:
  typedef void (*UserDataWriter)(UtlWriter *w, SGItem *i);
  /**
   * Inserts an userdata writer to the writers list.
   */
  static void InsertWriter (UserDataWriter w);
  /**
   * Removes an userdata writer from the writers list.
   * Returns if the writer was found.
   */
  static bool RemoveWriter (UserDataWriter w);
  /**
   * Obtains the class name. 
   */
  static const char* CLASSNAME () { return "Item"; }
  /**
   * Obtains the object's class name. 
   * This method must be reimplemented in every subclass.
   */
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGItem ();
  /**
   * Destructor
   */
  virtual ~SGItem();
  /**
   * Sets the object's name.
   */
  void SetName (const char* name);
  /**
   * Obtains the object's name.
   */
  const char* GetName () const { return m_name; }
  /**
   * Checks the object's name.
   */
  bool IsNamed(const char* name) const;
  /**
   * Checks the object's class name.
   */
  bool IsOfType(const char* classname) const
  {
    const char* cn = ClassName();
    assert(classname);
    assert(cn);
    return cn == classname || strcmp(cn,classname) == 0;
  }
  /**
   * Enables/disables the item.
   */
  void SetEnabled (bool flag)
  {
    m_enabled = flag; 
  }
  /**
   * Enables item.
   */
  void Enable ()
  {
    SetEnabled(true); 
  }
  /**
   * Disables item.
   */
  void Disable () 
  {
    SetEnabled(false); 
  }
  /**
   * Checks if the item is enabled.
   */
  bool IsEnabled () const
  {
    return m_enabled;
  }
  /**
   * Store user data
   */
  void SetUserData (const char* key, void* data)
  {
    m_userdata.Set(key,data);
  }
  /**
   * Access user data
   */
  void* GetUserData (const char* key)
  {
    return m_userdata.Get(key); 
  }
  /**
   * Writes the object's description.
   */
  virtual void Write (UtlWriter* writer);
};

#endif

