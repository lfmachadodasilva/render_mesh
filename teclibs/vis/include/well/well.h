// well.h
// Well rendering routines (2D and 3D).
// Tecgraf/PUC-Rio
// Jan 2010

#ifndef WELL_RENDER_3D_H
#define WELL_RENDER_3D_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <alg/vector.h>
#include <sciutils/colorscaletex.h>
#include <ugl/shape.h>
#include <ugl/texture.h>
#include <ds/array.h>

#ifndef M_PI
# define M_PI 3.14159265358979f
#endif
#ifndef DEG2RAD
# define DEG2RAD M_PI/180.0f
#endif

// Defines a threshold to establish the limit cosine of the angle
// that will determine if a joint will be drawn
#define JOINT_THRESHOLD 1.0e-3f

// Defines a threshold to avoid numerical imprecision
// on axis calculation
#define AXIS_ANGLE_THRESHOLD 1.0e-1f

// A default value for inactive cells
#define WWELL_INACTIVE_CELL 0xffffffff

// Specular factor for well drawn as line
#define WELL_LINE_SPECULAR_FACTOR 0.1f

// Brightness factor for well
#define WELL_BRIGHTNESS_FACTOR 0.15f

class W3dWell;

class W3dWellSet
{
public:
  /**
  * Describes the Rendering mode for this well.
  * Can be:
  *   PLAIN:    rendered with well and completion colors.
  *   WELLPROP: well and completions are rendered according to the well 
  *             property color.
  *   COMPPROP: each completion has a property associated to itself,
  *             and the links colors are interpolated according to
  *             both completions ('comp_from' and 'comp_to').
  *   CELLPROP: links are rendered in intersection mode (crossed cells)
  *             and each intersection (segment) of each link is rendered 
  *             according to the cell property to which it belongs.
  **/
  enum RenderMode
  {
    PLAIN,
    WELLPROP,
    COMPPROP,
    CELLPROP
  };
  /**
  * Describes the well type.
  * Can be:
  *   UNDEFINED: well type if undefined (neither cases below),
  *   PRODUCER,
  *   INJECTOR.
  **/
  enum WellType
  {
    WELL_PRODUCER = 0,
    WELL_INJECTOR,
    WELL_UNDEFINED
  };
  W3dWellSet ();
  ~W3dWellSet ();
  /**
   * Inserts well 'well' to the set.
   * Returns the well id.
   */
  int AddWell (W3dWell* well);  
  /**
   * Obtains the set well count.
   */
  int GetWellCount () const;
  /**
   * Obtains the well of id 'id'.
   */
  W3dWell* GetWell (int id) const;
  /**
  * Specifies the 'ith' well type.
  */
  void SetWellType (WellType mode, int well);
  /**
   * Specifies the rendering mode for the set.
   */
  void SetRenderMode (RenderMode mode);
  /**
   * Draws the well set.
   */
  void Draw ();
  /**
   * Initializes Well attributes
   */
  static void RenderBegin ();
  static void RenderEnd ();

private:
  DsArray<W3dWell*> m_wellset;
  int m_wellcount;
  RenderMode m_render_mode;
  WellType m_well_type;
};

class WWell
{
public:
  WWell();
  ~WWell();
  /**
   * Inserts a completion to well with coordinates 'x', 'y' and 'z'.
   * Returns the completion id.
   */
  int AddCompletion (float x, float y, float z);
  /**
   * Updates a completion with id 'comp_id' with coordinate 'x', 'y' and 'z'.
   * Returns the completion id.
   */
  int SetCompletion (int comp_id, float x, float y, float z);
  /**
   * Inserts a connection from the completion with id 'comp_from' to
   * the completion with id 'comp_to'.
   * Returns the new link id.
   */
  int AddLink (int comp_from, int comp_to);
  /**
   * Specifies intersections between the well link 'link_id' and the reservoir
   * cells.
   * 'num_int' intersections are passed through parameters 'tmin[i]' and
   * 'tmax[i]', assuming 0.0 is at the position of completion 'from' and 1.0 is
   * at the position of completion 'to'.
   * Assuming that 'tmin' and 'tmax' are in order: 'tmin[i]'<'tmin[i+1]' and
   * 'tmax[i]'<'tmax[i+1]'.
   * Ids of the cells are passed as well, used for picking.
   */
  void SetCrossedCells (int link_id, int num_int, const float* tmin, const float* tmax, const int* pick_ids);
  /**
  * Specifies intersections between the well link that goes from coompletion 0 to
  * 'well_top'int the reservoir well head.
  * 'num_int' intersections are passed through parameters 'tmin[i]' and
  * 'tmax[i]', assuming 0.0 is at the position of completion 'from' and 1.0 is
  * at the position of completion 'to'.
  * Assuming that 'tmin' and 'tmax' are in order: 'tmin[i]'<'tmin[i+1]' and
  * 'tmax[i]'<'tmax[i+1]'.
  * 'well_top' indicates the limit of the well head crossed cells.
  * Ids of the cells are passed as well, used for picking.
  * Returns the new link id. 
  * --> Assumes this method will be called after setting all links.
  */
  int SetWellHeadCrossedCells (int num_int, const float* tmin, const float* tmax, const AlgVector& well_top, const int* pick_ids);
  /**
   * Returns true if SetWellHeadCrossedCells has been called, false otherwise.
   */
  bool HasWellHeadCrossedCells () const
  {
    return m_haswellheadcrossedcells;
  }
  /**
   * Specifies the top-most z coordinate for the intersection
   * between well and reservoir.
   */
  void SetWellTop (float z);
  /**
   * Specifies the well top head lenght (in z direction). 
   * Assuming cylinder direction is (0,0,-1).
   * Well's top-most cylinder will have one end at well's top+
   * and well's head length.
   */
  void SetWellHeadLength (float len);
  /**
   * Inserts 'numpoints' intermediary points between the positions of
   * completions 'from' and 'to' of the link. These points have coordinates
   * 'x[i]', 'y[i]' and 'z[i]', 0 <= i < numpoints.
   * If this method is not called, the connection between the two completions
   * is a straight line. See definition of 'GeomAttr' further below.
   */
  void SetLinkGeometry (int link_id, int numpoints, const float* x, const float* y, const float* z);
  /**
   * Sets a color scale which is identifies the property of the well/completions/cells.
   */
  void SetPropColorScale (SciColorScaleTex* colorScale);
  /**
   * Specifies a property value for the entire well. 
   */
  void SetWellPropValue (float v);
  /**
   * Specifies a property value for each of the well's completions. 
   */
  void SetCompPropValue (int comp_id, float v);
  /**
   * Specifies property values for each of the cells intersected by link 'link_id'.
   * 'v' has size 'num_int' from the call to SetCrossedCells.
   */
  void SetCellPropValues (int link_id, const float* v);
  /**
   * Specifies the well radius.
   */
  void SetWellRadius (float radius);
  /**
   * Specifies the completion radius.
   */
  void SetCompRadius (float radius);
  /**
   * Specifies if the well is visible or not.
   */
  void SetVisible (bool flag);
  /**
   * Specifies if all completions are visible.
   */
  void SetAllCompVisible (bool flag);
  /**
   * Specifies if completion 'comp_id' is visible.
   */
  void SetCompVisible (int comp_id, bool flag);
  /**
   * Specifies a color for the entire well (when on PLAIN render mode).
   */
  void SetWellColor (float r, float g, float b);
  /**
   * Specifies a color for the well completions (when in PLAIN render mode).
   */
  void SetCompColor (int id, float r, float g, float b);
   /**
   * Turns on/off well and completion pickings.
   */
  void SetActivePick (bool flag);
  /**
   * Specifies a pick id for the well.
   */
  void SetWellPickID (unsigned int pick_id);
  /**
   * Specifies a pick id for the completion with id 'comp_id'.
   */
  void SetCompPickID (int comp_id, unsigned int pick_id);
  /**
   * Specifies a cell pick id for the completion with id 'comp_id' which intersects that cell.
   */
  void SetCompIntersCellPickID (int comp_id, unsigned int pick_id);
  /**
   * Sets camera 'znear' (used for well LOD).
   */
  void SetZnear (float z);
  /**
  * Specifies this well type.
  * See W3dWellSet::WellType for more details.
  * Default: UNDEFINED
  */
  void SetWellType(W3dWellSet::WellType type);
  /**
   * Specifies the rendering mode for the well.
   * See W3dWellSet::RenderMode for more details.
   * Default: PLAIN
   */
  void SetRenderMode (W3dWellSet::RenderMode mode);
  /**
   * Draws the well.
   */
  virtual void Draw () = 0;
  /**
   *  Returns the number of well completions.
   */
  int GetWellNumCompletions () const
  {
    return m_ncompl;
  }
  /**
  *  Returns the number of well links.
  */
  int GetWellNumLinks () const
  {
    return m_link_attr.Size();
  }
  /**
   * Clears the entire well list, removing all completion and link entries 
   * from data structure.
   */
  virtual void ClearWell ();

  /**
   * Debug functions
   */
  void _debugIntersections ();
  void _debugTexCoords ();
  bool WellGetError ();

protected:
  /*
   * Calculates and obtains well bounding box including all links
   */
  void CalcWellBBox ();
  void GetWellBBox (AlgVector* bbmin, AlgVector* bbmax);
  /**
   * Builds the link with id link_id. Since the link depends on the type of well,
   * this method must be redefined on its subclass. 
   */
  virtual void BuildLink (int link_id) = 0;
  /**
   * Loads and Unloads properties and opengl context
   */
  void LoadProperty(W3dWellSet::RenderMode mode, float scale, float translation);
  void UnloadProperty();
  virtual void LoadPlainMode();
  virtual void UnloadPlainMode();
  /**
   * Gets the base point of the first stack of the link (comp_from).
   */
  AlgVector GetLinkBase (int link_id);
  /**
   * Gets the direction and length of the link from comp_from to comp_to
   * (ignoring geometry, as if it is a straight line).
   */
  AlgVector GetLinkVectorAndLength (int link_id, float* length);
  /**
   * Auxiliary function used to get the first stack (starting in tmin) and the last stack (tmax),
   * considering cases where link has geometry points between them.
   */
  void GetFirstandLastStack (int link_id, float tmin, float tmax, int* firstseg, int* lastseg);
  /**
   * Calculates length and directions for links considering ONLY geometry points (not crossed cells).
   * Returns the unit vector direction and length of each stack, the number of stacks and the
   * total length of the link (sum of stack lengths).
   */ 
  float CalcLinkGeometryMode (int link_id, AlgVector** segdir, float** seglen, int* size);
  /**
   * Calculates base points, directions, lengths for links containing geometry points AND 
   * crossed cells. 
   * -- 'totlinklen' is the total length of the the link considering the sum of all geometry stacks.
   * -- 'stackdir' is the direction of each geometric stack.
   * Returns the segments direction unit vectors, the base points, and their lengths. Also 
   * returns the total number of stacks in the link.
   */
  void CalcLinkCrossedCellsGeometry (int link_id, 
                                     float totlinklen,
                                     AlgVector* stackdir,
                                     int n,  
                                     AlgVector** bases,
                                     AlgVector** dir,
                                     float** lengths,
                                     int** jointcyl,
                                     int* numstacks);
  /**
   * Calculates the start index and number of stacks in each intersection defined
   * by a tmin and tmax.
   */
  void CalcLinkIntersStartAndNumStacks (int link_id);
  /**
   * Builds a link that does not have an associated crossed cells geometry.
   */
  void BuildNormalStacks  (int link_id);
  /**
   * Builds link that HAS an associated crossed cells geometry.
   */
  void BuildCrossedCellsStacks (int link_id);
  /**
   * Obtains the completion 'comp_id' color.
   */
  void GetCompColor(int comp_id, float* r, float* g, float* b) const
  {
    *r = GetCompAttr(comp_id)->color[0];
    *g = GetCompAttr(comp_id)->color[1];
    *b = GetCompAttr(comp_id)->color[2];
  }
  /**
   * Checks if there was a change in context. The context is described below.
   */
  bool IsChanged (unsigned int which) const
  {
    return (m_changed_ctx & which) != 0;
  }

protected: 
  /**
  * Notifies a change in the well context.
  */
  enum
  {
    CTX_UNCHANGED    = 0, // No change in context
    CTX_WELLGEOMETRY = 1, // Well geometry changed, rebuild links again
    CTX_WELLPROP     = 2, // Well properties changed, recalculate properties and tex coords.
    CTX_DISPLAYLIST  = 4, // Recompile all display lists
    CTX_WELLSECTION  = 8, // (Re)Calculate completions visibility relative to the viewed section.
                          // When the well is viewed in a certain section (i, j, k), some completions
                          // may appear on top of others (same section), so they don´t need to be drawn.
    CTX_FIRST_RENDER = 16,// First render. Used to initialize variables in the first pass.
  };

  /**
  * Sets the well type. See W3dWellSet::WellType for details.
  */
  W3dWellSet::WellType m_well_type;
  
  /**
   * Sets the Rendering mode for this well. See W3dWellSet::RenderMode for details.
   */
  W3dWellSet::RenderMode m_render_mode;

  /**
  * Crossed Cells:
  * 
  * Contains attributes involving a link that intersects cells, its characteristics 
  * such as geometry, property and picking. 
  * Intersections are passed through parameters 'tmin[i]' and 'tmax[i]', 
  * assuming 0.0 is at the position of completion 'comp_from' and 1.0 is
  * at the position of completion 'comp_to'.
  * Assuming that 'tmin' and 'tmax' are in order: 'tmin[i]' < 'tmin[i+1]',
  * 'tmax[i]' < 'tmax[i+1]', and 'tmax[i]' <= 'tmin[i+1]'.
    */
  struct CrossedAttr
  {
    CrossedAttr()
      : num_int(0)
      , tmin()
      , tmax()
      , num_stacks()
      , stack_start()
      , cell_property()
      , cell_pick_id()
    {
    }
    ~CrossedAttr()
    {
      tmin.Clear();
      tmax.Clear();
      num_stacks.Clear();
      stack_start.Clear();
      cell_property.Clear();
      cell_pick_id.Clear();
    }
    void Empty()
    {
      tmin.Clear();
      tmax.Clear();
      num_stacks.Clear();
      stack_start.Clear();
      cell_property.Clear();
      cell_pick_id.Clear();
      num_int = 0;
    }
    int num_int;                    // number of intersected cells
    DsArray<float> tmin;            // see definition of 'Crossed Cells' above.
    DsArray<float> tmax;          
    DsArray<int> num_stacks;        // number of stacks between tmin and tmax
    DsArray<int> stack_start;       // index of the first stack between tmin and tmax
    DsArray<float> cell_property;   //Property of the intersected cell
    DsArray<unsigned int> cell_pick_id;
  };
  /**
   * Link Geometry Attributes:
   * 
   * Describes a link that has intermediary points, i.e., it´s not a straight line.
   * 'num_points' intermediary points between the positions of
   * completions 'from' and 'to' (described in 'LinkAttr'). These points have coordinates
   * 'points' packed in x,y,z.
  */
   /*********************************************************************************/
   /*                                O  comp_to                                     */
   /*                joint 3 ._____./ joint 4                                       */
   /*                       /                                                       */
   /*        joint 1 .____./                                                        */     
   /*               /       joint 2                                                 */
   /*              /                                                                */
   /*             O comp_from                                                       */
   /*********************************************************************************/
  struct GeomAttr
  {
    GeomAttr()
      : num_points(0)
      , points()
      , points_factor()
      , must_draw_joint()
      , joint_stack()
    {
    }
    ~GeomAttr()
    {
      points.Clear();
      points_factor.Clear();
      must_draw_joint.Clear();
    }    
    int num_points;                // number of intermediary points in link
    DsArray<AlgVector> points;     // points inside link
    DsArray<float> points_factor;  // point percentage relative to the link length 
    DsArray<bool> must_draw_joint; // indicates if a joint must be drawn in place of the point between stacks
    DsArray<int> joint_stack;      // indicates which stack the joint belongs to (used for associating a property to a joint)
  };
  /**
  * Link:
  * 
  * Describes the link itself, containg all attributes relative to its geometry and
  * property. May be a staright line or contain a geometry. It may also intersect cells.
  * Contains joint option to avoid sudden discontinuities between non-straight cylinders
  * when in crossed cells or geometry mode. 
  * A link can belong to two completions only, but a completion can belong to several links.
  * 'comp_from' and 'comp_to' indicate the start and end of the link, respectively.
  *  The definition of a stack is a segment of the link. In the case of geometry, the link 
  *  contains intermediary points which form stacks between them. In the case of intersections
  *  (or crossed cells), the link is formed by stacks between 'tmin' and 'tmax' (see definition 
  *  in 'CrossedAttr' above) or outside them.
  *  Notice that a link may contain both attributes (geometry and intersection), which can 
  *  be divided in more stacks. E.g. A stack in W3dWell class refers to cylinder. 
  */
  struct LinkAttr
  {
    LinkAttr() 
      : num_stacks(0) 
      , hasCrossedCells(false)
      , hasGeometry(false)
      , joints(NULL)
      , texmat(NULL)
      , rotangles(NULL)
      , stacklengths(NULL)
      , rotaxis(NULL)
      , stackbases(NULL)
      , stackdir(NULL)
      , crossed_cells(NULL)
      , geometry(NULL)
    {
    }
    ~LinkAttr()
    {
      delete joints;       
      delete texmat;       
      delete rotangles;    
      delete stacklengths; 
      delete rotaxis;    
      delete stackbases; 
      delete stackdir;   
      delete crossed_cells;
      delete geometry;     
    }
    int link_id;                    
    int comp_from;                
    int comp_to;
    int num_stacks;            
    float link_length;
    bool hasCrossedCells;
    bool hasGeometry;
    DsArray<float>* joints;          // curves on link edges (if in geometry mode)
    DsArray<float>* texmat;          // texture matrix´s scale (array position [2*i]) and translation ([2*i+1])
    DsArray<float>* rotangles;       // angle between z axis
    DsArray<float>* stacklengths;    // stack lengths
    DsArray<AlgVector>* rotaxis;     // axis needed for rotation
    DsArray<AlgVector>* stackbases;  // stack base points 
    DsArray<AlgVector>* stackdir;    // stacks direction unit vector
    CrossedAttr* crossed_cells;      // crossed cells (if set)
    GeomAttr* geometry;              // link geometry points (if set)
  };
  /**
  * Completion:
  *
  * Describes the well completions attributes, such as color, property and
  * 3D-coordinates. A completion can belong to several links. 'inc_links' 
  * contains the indices of the links to which this completion belongs.
  * If 'must_draw' is enabled, joints will be drawn the the completions
  * place (if the completions are not visible) to avoid sudden discontinuities
  * when incident links are not parallel.
  */
  struct CompletionAttr
  {
    CompletionAttr() 
      : inc_links()
      , texmat(0)
      , prop_value(-1) 
      , pick_id(0)
      , cell_pick_id(WWELL_INACTIVE_CELL)
      , use_texcoord(false)
      , must_draw(true)
      , visible(true)
    {
    }
    ~CompletionAttr()
    {
      inc_links.Clear();
    }
    AlgVector coord;          // completion coordinate
    DsArray<int> inc_links;   // list of incident links
    float color[3];           // completion color
    float texmat;             // texture matrix used for property
    float prop_value;         // completion property value
    unsigned int pick_id;     // completion pick id
    unsigned int cell_pick_id;// cell pick id to which the completion belongs (used in crossed cells render mode).
    bool  use_texcoord;       // indicates if texture coord will be used
    bool  must_draw;          // indicates if joint must be drawn in completion place
    bool  visible;            // current completion is visible?
  };
protected:
  CompletionAttr* GetCompAttr (int id) const
  {
    return m_comp_attr.Get(id);
  }
protected:

  DsArray<LinkAttr*> m_link_attr;
  DsArray<CompletionAttr*> m_comp_attr;

  /**
  * Indicates a change in the context. 
  * Used to recompile the display lists.
  */
  unsigned int m_changed_ctx;
  bool m_wellvisible; 
  // indicates if all completions are visible
  bool m_compvisible;
  bool m_activepick;
  /* Well properties */
  float m_wellradius;
  float m_wellpropvalue;
  float m_wellcolor[3];
  unsigned int m_wellpickid;  
  SciColorScaleTex* m_colorScale;
  /* completions */
  int m_ncompl;
  float m_compradius;
  float*  m_compltexcoords;
  /* last cylinder attributes */
  bool m_haswellheadcrossedcells;
  float m_head_ztop;
  float m_head_length;
  int m_well_head_crossed_cells_link_id; // link id containing well head crossed cells
  int m_well_head_comp_start_id; // completion id from which well head starts; default is id = 0.
  /* Display Lists */
  GLuint m_completionsDL;
  GLuint m_linkDL;
  /* Well bounding box */
  AlgVector m_bbox_min;
  AlgVector m_bbox_max;
  float m_znear;
};

class W3dWell : public WWell
{
public:
  enum 
  {
    PICK_TYPE_WELL = 1, // 0 is reserved for 'cells': has to match gpos/model/render.h WELL and COMP for now.
    PICK_TYPE_COMP,
    PICK_TYPE_CELL,
  }; 

  W3dWell();
  ~W3dWell();
  /**
   * Specifies the cylinder slices used when drawing.
   */
  void SetCylinderGeometry (int slices, int stacks);
  /**
   * Specifies the sphere tesselation used when drawing.
   */
  void SetSphereGeometry (int lat, int lon);
  /**
   * Draws the well.
   */
  void Draw ();

protected:
  /**
   *  Builds the link stacks´ geometric transformations (rotation angle and axis).
   **/
  void BuildLink (int link_id);

private:
  /**
   * Builds all display lists used for drawing the well and completions.
   */
  void CreateCompletionsDL();
  void CreateWellDL();
  void CreateLastCylDL();
  void CreateLinksDL();
  void CreateCapDL();
  void CreateLineDL();
  /**
   * Indicates if a joint must be drawn between links when not drawing completions. 
   * A joint will be drawn if two or more links belong to the same completion and 
   * at least two links are almost parallel to each other (defined by a threshold).
   */
  void MustDrawCompletion(int comp_id);
  /**
   * Builds link properties, which are defined by an array containg the transformations
   * used in the texture matrix. The texture matrix is accessed in Link Attribute structure
   * defined above, and contains consecutive pairs defining a scale and translation. 
   * (one pair for each stack (cylinder)).
   */
  void BuildLinkProp(int link_id);
  /**
   * Builds joints between links geometry stacks to avoid sudden visual discontinuity.
   * It is different from drawing joints between links, which is handled by completions
   * drawings.
   * Joints are indices to the actual texture matrix array which is used to transform 
   * texture coordinates for links and their stacks (cylinders).
   */
  void BuildJoints(int link_id);
  /**
   * Same principle of BuildLinkprop, where a texture transformation array is built for
   * completions texture coordinates. 
   */
  void BuildCompProp(int comp_id);
  /**
   * Calls all built-in properties functions above.
   */
  void BuildWellRendering();
  /**
   * Builds cap and used to cover last cylinder end.
   */
  void BuildCap();
  /**
   * Builds sphere used for drawing the completions.
   */
  void BuildSphere();
  /**
  *  Checks if well must be drawn as line (LOD)
  */
  bool DrawWellAsLine();
  /**
   * Check for display lists update if well LOD drawing changes from
   * line to cylinder (or the opposite) due to camera position.
   */
  void CheckWellLODUpdate();
  /**
   * WELL RENDERING FUNCTIONS
   */
  virtual void LoadPlainMode();
  virtual void UnloadPlainMode();
  void LoadWellMaterial(float ambient_r, float ambient_g, float ambient_b);
  void LoadCompMaterial(float ambient_r, float ambient_g, float ambient_b);
  void DrawSphere();
  void InitDraw();
  void RenderLink(int link_id);
  void RenderJoints(int link_id);
  void RenderCompletions();
  void RenderLastCylinder();
  void RenderCap ();
  void RenderWell ();

private: 
  /* sphere geometry */
  float * m_sphvertex;
  unsigned int* m_sphere_index;
  int     m_numIndices;
  int     m_nSegAlpha, m_nSegTheta; //sphere discretization
  int     m_numtriangles;
  /* cap geometry */
  float * m_circle;
  int     m_vertices;
  /* cylinder geometry*/
  int m_slices;
  int m_stacks;
  UGLCylinder*  m_uglcylinder;
  /* Display Lists */
  GLuint m_sphereDL;
  GLuint m_wellDL;
  GLuint m_topcylDL;
  GLuint m_capDL;  
  GLuint m_lineDL;  
  /* LOD: cylinders need to be drawn? */
  bool m_draw_well_as_line;
  float m_well_model_matrix[16]; // model matrix for well
};

#endif
