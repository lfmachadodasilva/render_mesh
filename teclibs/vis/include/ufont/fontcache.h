// OpenGL Fonts pool and cache for messages.
// Tecgraf/PUC-Rio
// cpalomo@tecgraf.puc-rio.br
// April 2011 

#ifndef UFONT_FONT_CACHE_H
#define UFONT_FONT_CACHE_H

#include "defines.h"
#include <ds/hash.h>
#include <ds/array.h>
#include "fontfactory.h"
#include "ttmessage.h"

#define UFONT_DEFAULT_CACHE_SIZE 50

class UFONT_API UFontCache
{
public:
  /**
   * Default constructor.
   */
  UFontCache ();

  /**
   * Shuts down the font cache, and release allocated resources.
   */
  virtual ~UFontCache ();

  /**
   * Setup cache size.
   */
  void SetCacheSize (int entry_count);

  /**
   * Given a font setup, return corresponding UFontMessage.
   * When configuration is not possible, returns NULL.
   */
  UFontMessage* GetMessage (const char *family_name, 
                            int size, 
                            bool bold, 
                            bool italic, 
                            int render_mode = UFontMessage::PIXMAP_FONT,
                            float depth = 0.0f);
  
  /**
   * Adds a path to a folder with true type fonts.
   */
  static void AddFontsPath (const char* path);

  /**
   * Obtains the number of available fonts.
   */
  static int GetFontFamilyCount ();

  /**
   * Obtains family name of index 'index'. (0 based)
   */
  static const char* GetFontFamilyName (int index);

  /**
   * Returns the number of sizes available for the font.
   */
  static int GetFontAvailableSizes (const char *family_name);

  /**
   * Returns the 'index'th available size for the font.
   */
  static int GetFontAvailableSize (const char *family_name, int index);

private:
  class CacheEntry {
  public:
    CacheEntry () {}
    ~CacheEntry() 
    {
      delete message;
    }
    int lastused;
    UFontMessage* message;
  };

private:
  // cache management
  DsArray<CacheEntry*> m_cache;
  DsHash<DsStringKey, CacheEntry*> m_cache_hash;
  int m_cache_ts;

  // UFont's pool
  static DsArray<UFontFactory::Font*>* s_pool;
  static DsHash<DsStringKey,UFontFactory::Font*>* s_pool_hash;

  static int s_ref_count;

private:
  // pool management
  static void UpdateFontsList ();
  static void CreateTTFont (const char* family_name);
  static void CreateGlutFont (const char* family_name);
  static UFontMessage* CreateMessage (const char* family_name, 
                                      int size,
                                      bool bold,
                                      bool italic, 
                                      int render_mode = UFontMessage::PIXMAP_FONT,
                                      float depth = 0.0f);

  // cache management
  static void ComputeCacheKey (const char* key, 
                               int size, 
                               bool bold,
                               bool italic,
                               float depth, 
                               int render_mode,
                               char cache_key[128]);
  void AddCacheEntry (const char* cache_key, UFontMessage* msg);
  void UpdateCacheEntry (CacheEntry* cache_entry);
};

#endif
