//* aabbmanip.h
// sam@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef VGL_AABB_MANIP_H
#define VGL_AABB_MANIP_H

#include "object.h"
#include "manipulatable.h"
#include <vgl/defines.h>
#include <ufont/glutmessage.h>

/**
 * This class allows the manipulation of objects in space by manipulating
 * their bounding boxes. 
 *
 * Using this class, it is possible to translate and resize objects.
 * 
 * Two callbacks must be registered in this class. One responsible for
 * selection rendering and the other responsible for retrieving objects
 * by their identification numbers (which are usually defined by the 
 * VglManipulatable interface).
 *
 */
class VGL_API VglAABBManipulator : public VglSelectionHandler
{
public:
  /**
   * Returns the event handler class classname.
   */
   static const char* CLASSNAME() { return "AABBManipulator"; }
   virtual const char* ClassName() { return CLASSNAME(); }
  /**
   * Constructs a AABB manipulator
   */ 
   VglAABBManipulator(VglCanvas* canvas, int sel_buf_size = 512, double tolw = 5.0, double tolh = 5.0);
  /**
   * Destroys a AABB manipulator
   */
   virtual ~VglAABBManipulator();
  /**
   * Type of the functions that retrieve references to manipulatable objects.
   * This consists in converting object ids (unsigned ints) to object references
   */
   typedef VglManipulatable* (*ObjectRetrievalFunc) (unsigned int id, void* data);
  /**
   * Sets the object retrieval function and the data it receives on every call
   */
   void SetObjectRetrievalFunc(ObjectRetrievalFunc f, void* data);
  /**
   * Indicates the manipulation performed by the user. The parameter 'mode' can be 
   * any of the following: VGL_TRANSLATION_1D, VGL_TRANSLATION_2D, VGL_RESIZE_1D 
   */
   void SetManipulationMode(int mode);
  /**
   * Returns the current manipulation mode of the handler
   */
   int GetManipulationMode(void);
  /**
   * Sets the text displayed in the axes of the feedback cube.
   * 'direction' indicates which axis is being modified. It can assume
   * the following values: VGL_X_AXIS, VGL_Y_AXIS, VGL_Z_AXIS
   */
   void SetAxisString(int direction, char* str);
  /**
   * Sets the color of the axis string 
   */
   void SetAxisStringColor (float red, float green, float blue) { m_message.SetColor(red, green, blue); }
  /**
   * Sets the font of the axis string
   */
   void SetAxisStringFont (void* font)
	 {
		 m_message.SetFont(font); 
	 }
	/**
	 * Specifies if the canvas has an idle redrawing the canvas.
	 */
   void SetAnimated(bool flag)
	 {
		 m_animated = flag;
	 }
  /**
   * Enables/Disables the snap
   */
   void SnapToGrid(bool active);
  /**
   * Setups the values of snap at each direction
   */
   void SetupSnap(double deltax, double deltay, double deltaz);
  /**
	 * Draw reference plane?
	 */
	void SetDrawReferencePlane (bool flag)
	{
	  m_drawrefplane = flag;
	}
  /**
   * Mouse button callback
   */
   virtual int MouseButton(int bt, int st, float x, float y);
  /**
   * Mouse motion callback
   */
   virtual int MouseMotion(int bt, float x, float y);
  /**
   * Function to process hit records
   */
   virtual void ProcessFunction(VglSelectionHit* hits, int n);
  /**
   * Post redraw callback (responsible for drawing the feedback cube)
   */
   virtual int PostRedraw(void);
   
   virtual void Begin();
   virtual void End();

protected:

   int m_manipulationMode;

   VglManipulatable* m_selection;

   // mouse event data
   bool m_dragging;
   bool m_firstEvent; 
   double m_wx1, m_wy1, m_wz1;
   double m_firstx, m_firsty, m_firstz;

   // names of the axes
   char* m_xString;
   char* m_yString;
   char* m_zString;

   // vertices of the reference plane
   double m_x1, m_y1, m_z1;
   double m_x2, m_y2, m_z2;
   double m_x3, m_y3, m_z3;
   double m_x4, m_y4, m_z4;

   // degrees of freedom for manipulation
   bool m_dofx, m_dofy, m_dofz;

   // snap to grid data
   bool m_snapEnabled;
   double m_snapDx, m_snapDy, m_snapDz;

   // face of the manipulation AABB selected by the user
   int m_selectedFace;

   // index of the hit record that is closer to the camera
   VglSelectionHit m_hit;
   VglSelectionHit *m_pclosesthit;

   // retrieval function and data
   ObjectRetrievalFunc m_retrieveObject;
   void* m_retrieveObjectData;

	 // matrix that takes the plane from the object coordinates to the global coordinates
	 AlgMatrix m_planematrix;
   
	 bool m_drawrefplane;
	 bool m_animated;

   UFontGLUTMessage m_message;

   // Performs the selection of objects for manipulation
   void pickObjects(double x, double y);

   // draws the feedback cube
   void drawFeedbackCube(VglManipulatable* m);

   // draws the feedback cube using XOR
   void drawFeedbackCube_XOR(VglManipulatable* m);

   // selection rendering function for the manipulation AABB
   void drawSelectionAABB(VglManipulatable* m);

   // process the pick of the manipulation AABB 
   void processAABBPick(VglSelectionHit* hit);

   // selection rendering function for the reference plane
   void referencePlanePick(void);

   // calls the manipulation callbacks of the object being manipulated
   bool handleDisplacement(double x1, double y1, double z1, double x2, double y2, double z2);

   // computes the reference plane used in the manipulation
   void setupReferencePlanes(
      int cubeFace, 
      int manipMode, 
      double limXi, double limXf,
      double limYi, double limYf,
      double limZi, double limZf);

   // creates the coordinates of the face used to render the reference plane
   void referencePlane(
      double x, double y, double z,
      double xi, double yi, double zi,
      double xf, double yf, double zf,
      int axisx, int axisy, int axisz);

   // draws the reference axes of the feedback cube
   void drawAxes(
      double l, double w, double h,
      bool drawX, bool drawY, bool drawZ);

   // displays a text on the canvas
   void drawText(double worldx, double worldy, double worldz, char* txt);
};



#endif

