//* aabbhandlemanip.h
// sam@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// September 2004

#ifndef _AABB_HANDLE_MANIP_H_
#define _AABB_HANDLE_MANIP_H_


#include <vgl/hnd/object.h>
#include <alg/matrix.h>


class VglAABBHandleManipulator : public VglSelectionHandler
{
public:
  /**
   * Returns the event handler class classname.
   */
   static const char* CLASSNAME() { return "AABBHandleManipulator"; }
   virtual const char* ClassName() { return CLASSNAME(); }
  /**
   * Constructs a AABB manipulator
   */ 
   VglAABBHandleManipulator(VglCanvas* canvas, int sel_buf_size = 512, double tolw = 5.0, double tolh = 5.0);
  /**
   * Destroys a AABB manipulator
   */
   virtual ~VglAABBHandleManipulator();
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
  /**
	* Specifies if the canvas has an idle redrawing the canvas.
	*/
	void SetAnimated(bool flag) {	m_animated = flag; }

   virtual void Begin();

   virtual void End();
  /**
   * Specifies the color of the handles
	*/
	void SetHandleColor(double r, double g, double b);
  /**
   * Specifies the color of the selected handles
	*/
	void SetHandleSelectionColor(double r, double g, double b);
  /**
   * Specifies the color of the bounding box
	*/
	void SetWireBoxColor(double r, double g, double b);
  /**
   * Specifies the limits of the manipulation area
	*/
	void SetManipulationAreaLimits(double xi, double yi, double zi, double xf, double yf, double zf);
  /**
   * Indicates that the object cannot be moved outside the manipulation area
   */
	void SetManipulationLimitsUsage(bool b) { _useManipulationLimits = b; }
  /**
   * Indicates if the manipulation area is 
	*/
	bool GetManipulationLimitsUsage(void) { return _useManipulationLimits; }

	enum 
	{
		PARALLEL_ONLY,
		PERPENDICULAR_AND_PARALLEL
	};

  /**
   * Indicates how movements over the handles affect the AABB
   *
   * PARALLEL_ONLY mode:
   * The handles are moved over the plane of the face on which they are contained. 
   *
   * PERPENDICULAR_AND_PARALLEL mode:
   * The motion of the corner handles occur over the plane of the face. 
   * The motion of the other handles occur in the plane perpendicular to
   * the face. 
   * In this mode, it is possible to choose a translation perpendicular to the 
   * face or on its plane, by pressing the CTRL key.
   */
	void SetManipulationMode(int mode) { _manipulationMode = mode; }
  /**
   * Returns the current manipulation mode
	*/
	int GetManipulationMode(void) { return _manipulationMode; }
  /**
   * Indicates the default translation for the PERPENDICULAR_AND_PARALLEL mode.
   * If true, when the CTRL key is pressed, the translation occurs in the 
   * plane perpendicular to the face. Without the CTRL key, the translation
   * occurs on the plane of the face.
   */
	void SetParallelTranslationAsDefault(bool b) { _parallelTranslation = b; }
  /**
   * Returns if parallel translation is the default translation when in 
	* PERPENDICULAR_AND_PARALLEL mode.
	*/
	bool GetParallelTranslationAsDefault(void) { return _parallelTranslation; }

	// manipulation handles
	struct Handles
	{
		double x[36];
		double y[36];
		double z[36];	
	};

	void SetMinRatio(double r) { _minRatio = r; }

	double GetMinRatio(void) { return _minRatio; }

protected:

	enum maniputation_state
	{
		NO_SELECTION,
		SELECTION,
		DRAGGING
	};

	// State of the handler
	int _state;

	// Object being manipulated
	VglManipulatable* m_selection;

   // Retrieval function and data
   ObjectRetrievalFunc m_retrieveObject;
   void* m_retrieveObjectData;

	// Colors used in the feedback drawing
	double _boxWireColor_r, _boxWireColor_g, _boxWireColor_b;
	double _handleColor_r, _handleColor_g, _handleColor_b;
	double _handleSelectionColor_r, _handleSelectionColor_g, _handleSelectionColor_b;

	// Manipulation area
	double _mxi, _myi, _mzi, _mxf, _myf, _mzf;

	// Indicates that the bounding box cannot be moved outside the manipulation area
	bool _useManipulationLimits;

	// Bounding box of the selected object
	double _bbxi, _bbyi, _bbzi, _bbxf, _bbyf, _bbzf;

	// Dimensions of the bounding box of the selected object
	double _dimx, _dimy, _dimz;

	// Reference plane equation (ax + by + cz + d = 0)
	double _a, _b, _c, _d; 

	// Indicates if a face of the AABB is visible or not
	bool _drawFace[6];

	// Minimum ratio 
	double _minRatio;
	
	// Manipulation handles
	Handles _handle[7];

	// Indicates the face selected by the user
	int m_selectedFace;

	// Indicates the handle selected by the user
	int m_selectedHandle;

	// Mouse event data
   bool m_firstEvent; 
	double _mouseClick_x, _mouseClick_y;

	// Values used in the computation of translations
	double _deltaxi, _deltayi, _deltazi, _deltaxf, _deltayf, _deltazf;

	// Values used in the computation of resize operations
	double _ratioxi, _ratioyi, _ratiozi, _ratioxf, _ratioyf, _ratiozf;

	// Indicates the existence of a repaint callback that is called repeatedly
	bool m_animated;

	// Manipulation mode
	int _manipulationMode;
	bool _parallelTranslation;
	bool _ctrlPressed;

   // Draws the selection feedback 
   void drawFeedbackCube(VglManipulatable* m);

	// Performs the selection of objects for manipulation
   void pickObjects(double x, double y);
	
	// Performs the selection on the handle manipulator (faces and handles)
	
	void pickManipulator(double x, double y);
	
	// Process the object selection buffer
	void processFunction_object(VglSelectionHit* hits, int n);
	
	// Process the manipulation box selection buffer
	void processFunction_manipulator(VglSelectionHit* hits, int n);
	
	// Mouse Motion callback used when the handler is in the DRAGGING state
	int mouseMotion_dragging(int bt, float x, float y);
	
	// Handles a translation mouse event
	void handleTranslation(double wx, double wy, double wz);
	
	// Handles a resize mouse event
	void handleResize(double wx, double wy, double wz);
	
	// Configures the reference plane
	void setupReferencePlaneEquation(VglSelectionHit* hits, int n, double wndx, double wndy, int face, int handle);
   
	// Changes the state of the handler
	void setState(maniputation_state st);
	
	// Prints the selection buffer (for debugging)
	void printHits(VglSelectionHit* h, int n);

	// Indicates if the coordinate of the manipulator is to be updated
	int updateCoordinate(int face, int handle, int coord);

	// Indicates a possible reference plane
	int referencePlane(int face, int handle, int n = -1);

	// Indicates which faces of the AABB are visible
	// Receives as parameter the transpose of the modelview matrix
	void computeVisibleFaces(AlgMatrix& mvt);

private:
	
	static const int updateTable_facePlanes[6][9][6];

	static const int updateTable_perpPlanes[6][9][6];
	static const int updateTable_perpPlanes_ctrl[6][9][6];

	static const int referencePlanes_perpPlanes[6][9][2];
	static const int referencePlanes_perpPlanes_ctrl[6][9][2];
};


#endif
