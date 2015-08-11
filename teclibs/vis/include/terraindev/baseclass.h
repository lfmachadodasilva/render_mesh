#ifndef TERRAIN_BASECLASS_H
#define TERRAIN_BASECLASS_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include "defines.h"
#include "typedefs.h"

//----------------------//
// TrnTileManager Class //
//----------------------//

class TERRAINAPI TrnBaseClass
{
public:

  // Class Name

  static const char* CLASSNAME () {return "TrnBaseClass";}
  virtual const char* ClassName () const {return CLASSNAME();}
  bool IsOfType (const char* classname) const;

  // Constructor and Destructor

  TrnBaseClass () {}
  virtual ~TrnBaseClass () {}

};

#endif // TERRAIN_BASECLASS_H
