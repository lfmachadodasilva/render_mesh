#ifndef SG_SHADOWCASTER_H
#define SG_SHADOWCASTER_H

//-----------------------------------//
// Includes and Forward Declarations //
//-----------------------------------//

#include <sgshadow/sgshadow.h>
#include <sg/object.h>

class SGLight;

//-------------------//
// Class Declaration //
//-------------------//

class SGSHADOWAPI SGShadowCaster : public SGObject
{
public:

  static const char* CLASSNAME () { return "SGShadowCaster"; }
  virtual const char* ClassName () const { return CLASSNAME(); }

  // Constructors and Destructor

  SGShadowCaster (SGLight* light);

  virtual ~SGShadowCaster (void);

  // Setters and Getters

  SGLight* GetLight (void);

  // Traverse method

  virtual int Traverse (SGStrategy *s);

protected:

  // Associated light

  SGLight  *m_light;

};

#endif

// Ideas:
// - be able to monitor a ShadowCaster just as a Light
// - When a shadow mapper is fake-flagged, collect ShadowCasters as well as lights
// - Maybe shadowmap(per) can be required to update the ShadowCaster's light, not the ShadowCaster (?)

