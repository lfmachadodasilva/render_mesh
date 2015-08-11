// background.h
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef SG_BACKGROUND_H
#define SG_BACKGROUND_H

#include "attribute.h"

/**
 * SGBackground Class.
 *
 * This is the base class for all backgrounds.
 *
 * It provides an interface for concrete classes to:
 * - begin the background rendering, done before the scene geometry is rendered.
 * - end the background rendering, done after the scene geometry is rendered.
 */
class SG_API SGBackground : public SGAttribute
{
public:
  static const char* CLASSNAME () { return "Background"; }
  virtual const char* ClassName () const { return CLASSNAME(); }
  /**
   * Constructor
   */
  SGBackground () {}
  /**
   * Destructor
   */
	virtual ~SGBackground () {};
  /**
   * Begins the background rendering stage, done before the scene geometry is rendered.
   */
	virtual void BeginRender () = 0;
  /**
   * Finishes the background rendering stage, done after the scene geometry is rendered.
   */
	virtual void EndRender () = 0;
};

#endif
