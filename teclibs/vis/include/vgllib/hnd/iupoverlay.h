/*****************************************************************
*
*   @module       Handler
*   @file         iupoverlay.h
*   @id           VglIupOverLayHandler
*   @packet       -
*   @owner        Tecgraf
*   @author       TCS - Thiago Crispino Santos
*   @version      1.0
*   @approvaldate june/2006
*
******************************************************************/
/*****************************************************************
*   Module Controls
*****************************************************************/
#if ! defined( IUPOVERLAY_ )
   #define IUPOVERLAY_
#if defined( IUPOVERLAY_OWN )
   #define IUPOVERLAY_EXT
#else
   #define IUPOVERLAY_EXT extern
#endif

/*****************************************************************
*   Includes
*****************************************************************/

#include "overlay.h"
#include <vgllib/vgllibiup.h>

class VglSubCanvas;

/*****************************************************************
*   Class Definition / Implementation
*****************************************************************/
class VGLLIBIUPAPI VglIupOverLayHandler : public VglOverLayHandler
{
public:
 /**
  * Class constructor.
  */
  VglIupOverLayHandler( VglSubCanvas * subcanvas );

  /**
  * Returns the event handler classname.
  */
  const char * ClassName          (  void   ) const;
  
protected:
 /**
  * Changes cursor when it is located in the lower rigth portion of the canvas.
  */
  void CursorLowerRight( void );    
    
 /**
  * Changes cursor when it is located in the upper left portion of the canvas.
  */
  void CursorUpperLeft ( void );
    
 /**
  * Changes cursor when it is located in the lower left portion of the canvas.
  */
  void CursorLowerLeft ( void );
  
 /**
  * Changes cursor when it is located in the upper right portion of the canvas.
  */
  void CursorUpperRight( void );

  /**
  * Changes cursor when it is located in the lower portion of the canvas.
  */
  void CursorLowerPortion( void );

  /**
  * Changes cursor when it is located in the upper portion of the canvas.
  */
  void CursorUpperPortion( void );

  /**
  * Changes cursor when it is located in the left portion of the canvas.
  */
  void CursorLeftPortion ( void );
  
  /**
  * Changes cursor when it is located in the right portion of the canvas.
  */
  void CursorRightPortion( void );
    
 /**
  * Changes cursor to its default icon.
  */
  void CursorDefault( void );

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

private:
  char m_saved_cursor[64];
};

#endif

