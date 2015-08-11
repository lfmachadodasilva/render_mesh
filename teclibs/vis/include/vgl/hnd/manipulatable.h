//* object.h
// sam@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef VGL_MANIPULATABLE_H
#define VGL_MANIPULATABLE_H


#include <vgl/defines.h>
#include <alg/matrix.h>

/**
 * Interface for the manipulation of objects
 *
 */
class VGL_API VglManipulatable
{
public:
  /**
   * Constructs a VglManipulatable object, assigning an unique identifier to the object
   */
   VglManipulatable();
  /**
   * Destroys a VglManipulatable object.
   */
   virtual ~VglManipulatable();
  /**
   * Translation callback. Indicates the displacement of the object.
   */
   virtual bool Translate(double dx, double dy, double dz) = 0;
  /**
   * Resize callback. Indicates the new size of the object.
   */
   virtual bool SetSize(double xi, double yi, double zi, double xf, double yf, double zf) = 0;
  /**
   * Returns the size of the object (its bounding box)
   */
   virtual void GetSize(double& xi, double& yi, double& zi, double& xf, double& yf, double& zf) = 0;
  /**
   * Scale callback. Indicates the scale factor on each coordinate.
   */
   virtual bool Scale(double sx, double sy, double sz) = 0;
	/**
	 * Returns the matrix that takes from the global space to the object's local space.
	 */
	 virtual AlgMatrix GetToLocal(void) = 0;
  /**
   * Returns the Id of the object
   */
   unsigned int GetId(void)
   { 
      return m_id; 
   }
  /**
   * Sets a new Id for the object
   */
   void SetId(unsigned int id) 
   { 
      m_id = id; 
   }
  /**
   * Used to verify whether the object handles events of type mode
   * with the degrees of freedom dofx, dofy and dofz. Can be used, for example,
   * to restrict the translation of the object along the x axis
   */
   virtual bool AcceptEvent(int mode, bool dofx, bool dofy, bool dofz) { return true; }

private:

   unsigned int m_id;

   static unsigned int s_lastId;
};



#endif

