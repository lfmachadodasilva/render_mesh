// stringkey.h
// String key struct, useful for hash usage.
// celes@tecgraf.puc-rio.br
// 24 Feb 2005

#ifndef wds_stringkey_h
#define wds_stringkey_h

#include <stdlib.h>
#include <string.h>

struct DsStringKey {
 char *name;
 DsStringKey() : name(0) { }
 DsStringKey(const char *s) : name(strdup(s)) { }
 ~DsStringKey() { free(name); }
 DsStringKey(const DsStringKey &k) : name(strdup(k.name)) { }
 DsStringKey& operator=(const DsStringKey &k) { free(name); name = strdup(k.name); return *this; }
 /**
  * Attribution to const char* value operator.
  */
 DsStringKey& operator=(const char* s) { free(name); name = strdup(s); return *this; }
 operator const char * () const { return name; }
 /**
  * Explicit conversion to C string (ala std::string).
  */
 const char* c_str () const { return name; }
 int operator == (const char *s) const {
  return (name==s || strcmp(name,s)==0);
 }
};

#endif

