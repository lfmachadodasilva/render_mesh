// well.h
// Well rendering routines (2D).
// Tecgraf/PUC-Rio
// Jan 2010

#ifndef WELL_RENDER_2D_H
#define WELL_RENDER_2D_H

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <alg/vector.h>
#include <ugl/shape.h>
#include <ugl/texture.h>
#include <ds/array.h>
#include "well.h"

#ifndef M_PI
#define M_PI              3.14159265358979f
#endif
#ifndef DEG2RAD
# define DEG2RAD           M_PI/180.0f
#endif
// Enables gluDisk drawing when in Bubble mode. If disabled,
// Disks will be drawn using opengl primitives.
//#define USE_GLU_DISK_DRAWING
// Pick ids for some modes
#define NOT_A_PROPERTY    5
// Indicates there are no completions visible
#define NO_COMPLETIONS_VISIBLE 0xffffffff

class W2dWell;

/**
 * Class responsible for drawing a disk-like graph divided in up to 4 sections.
 */
class W2dWellSectionDrawing
{
public:
  enum NumSectionsType {
    ONE_SECTION    = 1,
    TWO_SECTIONS   = 2,
    THREE_SECTIONS = 3,
    FOUR_SECTIONS  = 4,
  };

  W2dWellSectionDrawing ();
  ~W2dWellSectionDrawing ();
  void SetSlices (int slices);
  void DrawSection    (NumSectionsType nSec, float radius, float startAngle);
  void DrawSilhouette (NumSectionsType nSec, float radius, float startAngle);

private:
  void CreateDisplayLists ();
  void DrawCircle (float angle);
  void DrawSectionOneType  ();
  void DrawSectionTwoType  ();
  void DrawSectionThreeType();
  void DrawSectionFourType ();

private:
  // Display Lists
  // Sections
  GLuint m_secOneDL;
  GLuint m_secTwoDL;
  GLuint m_secThreeDL;
  GLuint m_secFourDL; 
  // Silhouettes
  GLuint m_silhOneDL;
  GLuint m_silhTwoDL;
  GLuint m_silhThreeDL;
  GLuint m_silhFourDL; 

  int m_slices;
};

class W2dWellSet
{
public:
  W2dWellSet ();
  ~W2dWellSet ();
  /**
   * Inserts well 'well' to the set.
   * Returns the well id.
   */
  int AddWell (W2dWell* well);  
  /**
   * Obtains the set well count.
   */
  int GetWellCount () const;
  /**
   * Obtains the well of id 'id'.
   */
  W2dWell* GetWell (int id) const;
  /**
   * Specifies the rendering mode for the set.
   */
  void SetRenderMode (W3dWellSet::RenderMode mode);
  /**
   * Draws the well set.
   */
  void Draw ();
  /**
   * This function draws an unit quad with a texture applied to it.
   */
  static void DrawTextureQuad (bool use_two_textures = false);
  /**
   * Returns or destroys a display list for the function above.
   */ 
  static GLuint BuildAndGetTexturedQuadDisplayList (bool use_two_textures);
  static void DestroyTexturedQuadDisplayList (GLuint disp_list_id);
  /**
  * Initializes Well attributes
  */
  static void RenderBegin ();
  static void RenderEnd ();

private:
  DsArray<W2dWell*> m_wellset;
  int m_wellcount;
  W3dWellSet::RenderMode m_render_mode;
};

class W2dWell : public WWell
{
public:
  enum 
  {
    PICK_TYPE_WELL = 1, // 0 is reserved for 'cells': has to match gpos/model/render.h WELL and COMP for now.
    PICK_TYPE_COMP,
    PICK_TYPE_CELL,
  }; 
  /**
   * Specifies which section (plane) the well and completions will be drawn in.
   * There are 3 sections (i,j k), where each pair refers to a plane where
   * the well and completions will be drawn.
   */
  enum WellSection 
  {
    SECTION_I = 0,//SECTION_JK = 0,
    SECTION_J,    //SECTION_IK,
    SECTION_K,    //SECTION_IJ,     // Map view
  };
  /**
   * Completion Symbol relative to section, or layer. There are 3 different symbols,
   * one in the current section, and other 2 that specifies if the completion is before
   * or after the current section.
   */
  enum CompletionSymbol 
  {
    AT_SECTION = 0,
    AFTER_SECTION,
    BEFORE_SECTION,
  };
  enum FlowSymbol
  {
    ACTIVE = 0,
    INACTIVE,
  };
  /** 
   * Specifies the completion render mode. If PLAIN, completions will be drawn with 
   * symbols specified above. If BUBBLE, well is drawn
   * with a pizza like graph, where it may be divided in maximum of 4 partings.
   * If FLOW, well is drawn as circles representing the well flow.
   */
  enum WellMode
  {
    PLAIN_MAP,
    BUBBLE_MAP,
    FLOW_MAP,
  };

public:
  W2dWell();
  ~W2dWell();  
  /**
   * Specifies the section to which the well belongs to.
   * Completion will be in different planes depending on the section.
   */
  void SetWellSection (WellSection section);
  /**
   * Specifies the grid position to which the completion belongs to.
   */
  void SetCompletionRootGridPosition(int comp_id, int i, int j, int k);
  /**
   * Specifies a style which the completions will be drawn with. 
   * See 'CompletionSymbol'definition above.
   */
  void SetCompletionSymbol (int comp_id, CompletionSymbol symbol);
  /**
   * Specifies image texture that will be drawn as a completions.
   * Receives the type of symbol associated to the image (see 'CompletionSymbol'
   * definion above) and the image texture. 
   * 'scale' is a scale factor applied to the image in case it is too small.
   * 'margin' defines the picking available limit of the texture.
   * Well2d DOES NOT take ownership of the texture.
   */
  void SetCompletionSymbolImage (CompletionSymbol symbol, UGLTexture* tex, float scale = 1.0f, float margin = 1.0f);
  /**
  * Specifies image texture that will be drawn as flow map symbols.
  * 'scale' is a scale factor applied to the image in case it is too small.
  */
  void SetFlowSymbolImage (UGLTexture* tex, float scale = 1.0f);
  /**
   * Sets an external display list id for drawing the completion symbols.
   * Useful if user needs one display list shared by many wells.
   */
  void SetCompletionSymbolsDispLists (GLuint displayList);
  /**
   * Sets the id of the first valid completion from which the well head will 
   * be drawn. Default value is 0.
   */
  void SetFirstValidCompletionId (int comp_id);
  /**
   * Specifies a rendering mode for the well. (See definition of 'Well2DRenderMode').
   */
  void SetWellMode (WellMode mode);
  /**
   * Sets the Bubble rendering mode attributes.
   * Colors are tightly packed in groups of 3 (r, g, b)
   */
  void SetWellBubbleAttr (AlgVector coord, float* colors, float* innerRadius, float* outerRadius, int n);
  /**
   * Sets bubble properties for well (pick ids).
   * Properties are related to each bubble parting.
   */
  void SetWellBubbleProps (int* props, int n);
  /**
   * Sets the Flow rendering mode attributes.
   */
  void SetWellFlowAttr (AlgVector coord, const float color[3], float inner_radius, float outer_radius, float scale = 1.0f);
  /**
   * Sets flow properties for well (pick id).
   */
  void SetWellFlowProp (int prop); 
  /**
   * Specifies a style which the completions will be drawn with.
   */
  void SetInvertCameraMapping (bool invert);
  /**
   * Specifies the Well Line Width
   */
  void SetWellWidth (float width);
  /**
   * Specifies the Completion circle tesselation used when drawing.
   */
  void SetCompletionGeometry (int slices);
  /**
   * Draws the well.
   */
  void Draw ();
  /**
   * Clears the well.
   **/
  void ClearWell2D ();

protected:
  void BuildLink (int link_id);

private:
  /**
   * Calculates which completions will be visible or not depending on the current viewed section.
   * Completions that are on the same depth section are candidates for not being visualized. 
   * (e.g. In SECTION_J, completions with the same value for IK and different values for J are tested
   *  to avoid overlapping)
   */
  void CalcCompVisibilityMode();
  /**
   * Builds all display lists used for drawing the well and completions.
   */
  void CreateCompletionsDL();
  void CreateWellDL();
  void CreateLinksDL();
  void CreateLineDL();
  void CreateCompSymbolsDL();
  /**
   * Obtains color for each parting (bubble map) (maximum of 4)
   */
  void GetBubbleColor(int c, float* color);
  /**
   * Builds link properties, which are defined by an array containg the transformations
   * used in the texture matrix. The texture matrix is accessed in Link Attribute structure
   * defined above, and contains consecutive pairs defining a scale and translation. 
   * (one pair for each stack).
   */
  void BuildLinkProp(int link_id);
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
   * Checks if the completion symbol has an associated image.
   */
  bool HasImageSymbol(CompletionSymbol symbol);
  /**
   * Loads properties, textures, and opengl context in rendering. 
   */
  void LoadProperty(W3dWellSet::RenderMode mode, float scale, float translation);
  void UnloadProperty();
  void LoadPlainMode();
  void UnloadPlainMode();
  void LoadCompletion(int comp_id);
  void UnloadCompletion(int comp_id);
  void LoadFlowTexture();
  void UnloadFlowTexture();
  /**
   * WELL RENDERING FUNCTIONS
   */
  void InitDraw();
  void DrawDisk();
  /**
   * Draws the well in section graph modes (bubble) when on BUBBLE mode
   * (see Well2DRenderMode definition).
   */
  void DrawBubble(); 
  /**
   * Draws the well in FLOW mode.
   * (see Well2DRenderMode definition).
   */
  void DrawFlow (); 
  /**
   * Draws the completions in symbol mode when in PLAIN mode 
   * (see Well2DRenderMode definition).
   */
  void DrawAtSectionSymbol();
  void DrawBeforeSectionSymbol();
  void DrawAfterSectionSymbol();
  void DrawCompletionSymbol(int comp_id); 
  void DrawCompletion(int comp_id);
  void RenderLink(int link_id);
  void RenderLastCylinder();
  void RenderCompletions();
  void RenderWell();

private: 
  /**
   * Flow Map Attributes.
   */
  struct Well2DFlowAttr
  {
    Well2DFlowAttr()
    : coord(0,0,0)
    , inner_radius(0.0f)
    , outer_radius(0.0f)
    , scale(1.0f)
    {
    } 
    AlgVector coord;              // Coordinate of the flow (usually is the last valid completion).
    float color[3];               // Colors for the well in flow drawing.
    float inner_radius;           // Inner radius of the flow drawing.
    float outer_radius;           // Outer radius of the flow drawing.
    float scale;                  // A scale factor so that symbol does not appear small enough.
    int property;                 // Pick id for flow drawings.
  };

  /**
   * Bubble Map Attributes.
   */
  struct Well2DBubbleAttr
  {
    Well2DBubbleAttr()
      : numPartings(0)
      , colors(NULL)
      , innerRadius(NULL)
      , outerRadius(NULL)
      , properties(NULL)
    {
    }
    
    int numPartings;              // Number of partial divisions when in BUBBLE render mode.
    AlgVector coord;              // Coordinate of the bubble (usually is the last valid completion).
    DsArray<float>* colors;        // Colors for the compeletion parting drawing (maximum of 4).
    DsArray<float>* innerRadius;   // Inner radius of the completion parting graph.
    DsArray<float>* outerRadius;   // Outer radius of the completion parting graph.
    DsArray<int>* properties;      // Pick ids for parting drawings.
  };

  struct Completion2DAttr
  {
    Completion2DAttr() 
      : symbol(AT_SECTION)
      , i(-1)
      , j(-1)
      , k(-1)
      , blocked(false)
    {
    }
    CompletionSymbol  symbol;     // One of the 3 symbols described previously 
                                  // (can be a texture symbol if texture is set)
    int i, j, k;                  // Completion grid position.
    bool blocked;                 // Checks if one completion is blocked by another. 
                                  // e.g. when one completion is under another in
                                  // view mode.
  };

  /**
   * Additional information used in drawing lines as a Well.
   */
  struct Link2DAttr
  {
    Link2DAttr() 
      : startStack()
      , endStack()
    {
    }
    DsArray<AlgVector>* startStack;  
    DsArray<AlgVector>* endStack;   // startStack/endStack : 3D coordinate limits of each stack
  };

  /**
   * Display Lists for each completion symbol.
   */
  struct CompletionSymbolDL
  {
    CompletionSymbolDL()
      : atSectionDL(0)
      , afterSectionDL(0)
      , beforeSectionDL(0)
    {
    }
    GLuint atSectionDL;
    GLuint afterSectionDL;
    GLuint beforeSectionDL; 
  };

  struct CompSymbolTextures
  {
    CompSymbolTextures()
      : atSectionTex       (NULL)
      , atSectionMargin    (1.0f)
      , atSectionScale     (1.0f)
      , afterSectionTex    (NULL)
      , afterSectionMargin (1.0f)
      , afterSectionScale  (1.0f)
      , beforeSectionTex   (NULL)
      , beforeSectionMargin(1.0f)
      , beforeSectionScale (1.0f)
    {
    }

    UGLTexture* atSectionTex;
    float atSectionMargin;
    float atSectionScale;
    UGLTexture* afterSectionTex;
    float afterSectionMargin;
    float afterSectionScale;
    UGLTexture* beforeSectionTex;
    float beforeSectionMargin;
    float beforeSectionScale;
  };

  struct FlowSymbolTextures
  {
    FlowSymbolTextures()
    : active(NULL)
    {
    }
    UGLTexture* active;
  };

  DsArray<Completion2DAttr> m_compAttr2D;
  DsArray<Link2DAttr*> m_linkAttr2D;
  Well2DBubbleAttr m_wellBubbleAttr2D;
  Well2DFlowAttr m_wellFlowAttr2D;
  WellMode m_wellMapMode;
  WellSection m_section;          // One of the 3 sections described previously
  bool m_mapCameraInvert;         // Transforms the completion drawing axis orientation
  /* completion and well geometry */
  int m_firstValidCompletion;
  float m_compSlices;
  float m_flowScale;
  float m_lineWidth;
  GLUquadricObj* m_quadric;
  W2dWellSectionDrawing* s_section2D;
  /* Display Lists */
  GLuint m_wellDL;
  GLuint m_lineDL;
  GLuint m_diskDL;  
  GLuint m_texQuadDL;
  bool m_tex_quad_ext_disp_list; // Indicates if the display lists were set from an external source.
                                 // Useful if there are many well classes and the user needs one
                                 // display list for all of them.
  CompletionSymbolDL m_compSymbolDL;
  /* Completions and flow symbol textures */
  CompSymbolTextures m_compSymbolTex;
  FlowSymbolTextures m_flowSymbolTex;
  bool m_compHasImage;     // 'true' if at least one of the symbols must be drawn with an image
  bool m_flowHasImage; // 'true' if at least one of the flow symbols must be drawn with an image
};

#endif
