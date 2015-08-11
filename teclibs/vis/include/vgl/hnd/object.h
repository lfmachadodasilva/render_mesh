//* object.h
// sam@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef VGL_OBJECT_HANDLER_H
#define VGL_OBJECT_HANDLER_H

#include "manipulatable.h"
#include "selection.h"
#include <vgl/hitrecord.h>

/**
 * This class acts as a helper class to assist in the construction of new 
 * "object oriented handlers".
 *
 * The usual mouse events are redefined so that they receive the object on which 
 * the event occured as a parameter. 
 * 
 * In order to create a useful handler the user of the class must redefined the 
 * MouseButton3d and/or the MouseMotion3d methods.
 *
 * A callback responsible for the retrieval of object references must also be 
 * registered. This callback receives as parameters the top of OpenGL name stack 
 * (used to identify the objects) and a void* data that was previously registered 
 * by the user.
 */
class VglObjectHandler : public VglSelectionHandler
{
public: 
  /**
   * Returns the event handler class classname.
   */
   static const char* CLASSNAME() { return "ObjectHandler"; }
   virtual const char* ClassName() const { return CLASSNAME(); }
  /**
   * Constructs an object handler
   * surface      - Visualization surface associated with the handler.
   * sel_buf_size - Selection buffer size.
   * tolw         - Horizontal picking tolerance in raster coordinates.
   * tolh         - Vertical picking tolerance in raster coordinates.
   */
   VglObjectHandler(VglCanvas* canvas, int sel_buf_size = 512, double tolw = 5.0, double tolh = 5.0);
  /**
   * Destroys the object handler
   */
   virtual ~VglObjectHandler();
  /**
   * Process function that selects the closes hit record to the camera
   */
   virtual void ProcessFunction(VglSelectionHit* hits, int n);
  /**
   * Type of the functions that retrieve object references.
   * This consists in converting object ids (unsigned ints) to object references
   */
   typedef void* (*ObjectRetrievalFunction)(unsigned int id, void* data);
  /**
   * Sets the object retrieval function and the data it receives on every call
   */
   void SetObjectRetrievalFunction(ObjectRetrievalFunction f, void * data);
  /**
   * Object oriented mouse button event
   */
   virtual int MouseButton3d(
      void* obj, 
      VglSelectionHit* hit,
      int bt, int st, 
      float x, float y, float z);
  /**
   * Object oriented mouse motion event
   */
   virtual int MouseMotion3d(
      void* obj,
      VglSelectionHit* hit,
      int bt,
      float x, float y, float z);
  /**
   * Regular mouse button event (should not be redefined)
   */
   virtual int MouseButton(int bt, int st, float x, float y);
  /**
   * Regular mouse motion event (should not be redefined)
   */
   virtual int MouseMotion(int bt, float x, float y);

  /**
   * Indicates if mouse motion events are to be generated or not
   */
	void SetMouseMotionTracking(bool b) { m_trackMotion = b; }
	bool GetMouseMotionTrackinf(void) { return m_trackMotion; }

protected:

	bool m_trackMotion;

   // object retrieval function
   ObjectRetrievalFunction m_retrieveObject;

   // object retrieval data
   void* m_retrieveData;
   VglSelectionHit m_hit;
   VglSelectionHit *m_pclosesthit;
};

#endif
