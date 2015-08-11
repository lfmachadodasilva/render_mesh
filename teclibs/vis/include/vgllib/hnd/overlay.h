/*****************************************************************
*
*   @module       Handler
*   @file         overlay.h
*   @id           VglOverLayHandler
*   @package      -
*   @owner        Tecgraf
*   @author       TCS - Thiago Crispino Santos
*   @version      1.0
*   @approvaldate june/2006
*
******************************************************************/
/*****************************************************************
*   Module Controls
*****************************************************************/
#if ! defined( OVERLAYHANDLER_ )
   #define OVERLAYHANDLER_
#if defined( OVERLAYHANDLER_OWN )
   #define OVERLAYHANDLER_EXT
#else
   #define OVERLAYHANDLER_EXT extern
#endif

/*****************************************************************
*   Includes
*****************************************************************/
#include <vgl/subcanvas.h>
#include <vgl/handler.h>
#include <vgllib/defines.h>

class VGLLIBAPI VglOverLayHandlerModel 
{
public:
  virtual ~VglOverLayHandlerModel() {}
  virtual void Move(float dx, float dy) = 0;
  virtual void SetWindow(float x, float y, float w, float h) = 0;
  virtual void GetWindow(float* x, float* y, float* w, float* h) = 0;
};

/*****************************************************************
*   Class Definition
*****************************************************************/
class VGLLIBAPI VglOverLayHandler : public VglHandler
{
public:  
 /**
  * Class constructor.
  */
  VglOverLayHandler( VglSubCanvas * subcanvas );

  /**
  * 
  */
  void SetModel( VglOverLayHandlerModel* model );

  /**
  * Sets whether the subcanvas can be resized.
  * Default: true
  */
  void SetResizeEnabled( bool f );

  /**
  * Sets the desired move button.
  */
  void SetMoveButton( int VglButton );

  /**
  * Sets the desired resize button.
  */
  void SetResizeButton( int VglButton );

  /**
  * Sets the desired custom button.
  */
  void SetCustomButton( int VglButton );

 /**
  * Sets the desired lower bound.
  */
  void SetBorderSize( float borderSize );

  /**
  * Sets the desired resize region.
  */
  void SetResizeRegion( float resizeRegion );

 /**
  * Returns the event handler classname.
  */
  const char * ClassName          (  void   ) const;

  /**
   * Method called whenever the handler is activated/inserted into a notifier.
   */
  void Begin();

protected:
 /**
  * Checks if the mouse is within the canvas region.
  */
  int MouseEntry            ( bool st );
    
  /**
  * Handles mouse click events.
  */
  int MouseButton           ( int bt, int st, float x, float y );
 
  /**
  * Handles mouse motion events.
  */
  int MouseMotion           ( int bt, float x, float y );

  /**
  * Cursor is within lower left resizing region.
  */
  virtual void CursorLowerLeft ( void );

  /**
  * Cursor is within upper left resizing region.
  */
  virtual void CursorUpperLeft ( void );

  /**
  * Cursor is within lower right resizing region.
  */
  virtual void CursorLowerRight( void );

  /**
  * Cursor is within upper right resizing region.
  */
  virtual void CursorUpperRight( void );

  /**
  * Cursor is within lower portion.
  */
  virtual void CursorLowerPortion( void );

  /**
  * Cursor is within upper portion.
  */
  virtual void CursorUpperPortion( void );

  /**
  * Cursor is within left portion.
  */
  virtual void CursorLeftPortion ( void );

  /**
  * Cursor is within right portion.
  */
  virtual void CursorRightPortion( void );

  /**
  * Cursor is outside resizing region.
  */
  virtual void CursorDefault( void );

  /**
  * Saves the current cursor for restoring later.
  */
  virtual void SaveCurrentCursor( void );

  /**
  * Restores the last saved cursor.
  */
  virtual void RestoreSavedCursor( void );

  /**
  * Clears the last saved cursor.
  */
  virtual void ClearSavedCursor( void );

  /**
  * Sets the custom action functionality.
  */
  virtual void CustomAction( void );
  
  /**
  * After redraw method.
  */
  int AfterRedraw ()
  { 
    return 1; 
  }
  
  //virtual int Keyboard (int k, int st, float x, float y);
  //virtual int PreRedraw (void);
  //void SetFilterEvents (bool f);

protected:  
  VglSubCanvas * m_subcanvas;       // assiciated subcanvas
  bool           m_isResizing;      // canvas is being resized
  bool           m_resizeEnabled;   // canvas resizing is enabled
  int            m_corner;          // window corner position
  int            m_resizeButton;    // holds the desired resizing button
  int            m_moveButton;      // holds the desired moving button
  int            m_customButton;    // holds the additional button functionality
  VglOverLayHandlerModel* m_model;  // holds the model affected by the events 
                                    // of this handler  
private:
  enum WindowPortion
  {
    WP_NONE          = 0,   // does not apply
    WP_UPPER_RIGHT   = 1,   // resizing is being performed by the upper right corner
    WP_UPPER_LEFT    = 2,   // resizing is being performed by the upper left  corner
    WP_LOWER_RIGHT   = 3,   // resizing is being performed by the lower right corner
    WP_LOWER_LEFT    = 4,   // resizing is being performed by the lower left  corner
    WP_UPPER         = 5,   // resizing is being performed by the top         portion
    WP_LOWER         = 6,   // resizing is being performed by the botton      portion 
    WP_LEFT          = 7,   // resizing is being performed by the left        side
    WP_RIGHT         = 8    // resizing is being performed by the right       side
  }; 

private:
  WindowPortion GetWindowPortion (float x, float y) const;

  void SetResizeCursor (float x, float y);

  void MoveWindow (float dx, float dy);

  bool ResizeWindow (float dx0, float dy0, float dxw, float dyh);

  bool IsInCenterRegion (float x, float y) const
  {
     return x >= m_left_bound && x <= m_right_bound &&
            y >= m_lower_bound && y <= m_upper_bound;
  }

  bool IsInLowerResizeRegion (float x, float y) const
  {
    return x >= m_left_bound && x <= m_right_bound &&
           y >= 0.0f && y <= m_lower_bound;
  }

  bool IsInUpperResizeRegion (float x, float y) const
  {
    return x >= m_left_bound && x <= m_right_bound &&
           y >= m_upper_bound && y <= 1.0f;
  }

  bool IsInLeftResizeRegion (float x, float y) const
  {
    return x >= 0.0f && x <= m_left_bound && 
           y >= m_lower_bound && y <= m_upper_bound;
  }

  bool IsInRightResizeRegion (float x, float y) const
  {
    return x >= m_right_bound && x <= 1.0f &&
           y >= m_lower_bound && y <= m_upper_bound;
  }

  bool IsInUpperLeftResizeRegion (float x, float y) const
  {
    return x >= 0.0f && x <= m_left_bound &&
           y >= 0.0f && y >= m_upper_bound;
  }

  bool IsInUpperRightResizeRegion (float x, float y) const
  {
    return x >= m_right_bound && x <= 1.0f &&
           y >= m_upper_bound && y <= 1.0f;
  }

  bool IsInLowerLeftResizeRegion (float x, float y) const
  {
    return x >= 0.0f && x <= m_left_bound &&  
           y >= 0.0f && y <= m_lower_bound;
  }

  bool IsInLowerRightResizeRegion (float x, float y) const
  {
    return x >= m_right_bound && x < 1.0f &&
           y >= 0.0f && y <= m_lower_bound;
  }

private:
  float m_lower_bound;   // defines lower bound resize region
  float m_upper_bound;   // defines upper bound resize region
  float m_left_bound;   // defines left bound resize region
  float m_right_bound;   // defines right bound resize region
  float m_min_resize_region;   // defines minimum resize region
  float m_border_size;   // defines border size in pixels
};

#endif

