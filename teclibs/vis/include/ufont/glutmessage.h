// GLUT Message class
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jul 2002

#ifndef UFONT_GLUT_MESSAGE_H
#define UFONT_GLUT_MESSAGE_H

#include "message.h"
#include <GL/glew.h>
#include <GL/glut.h>

class UFONT_API UFontGLUTMessage : public UFontMessage
{
public:
  UFontGLUTMessage (float x=-0.9, float y=0.9, float z = 0.9);
  virtual ~UFontGLUTMessage ();

  /**
   * Create message with a GLUT font family name.
   * @param family_name GLUT font family name.
   * @param size font size.
   * @param bold actually this must always be false.
   * @param italic actually this must always be false.
   * @return pointer to created message, or NULL when error occurred.
   */
  static UFontGLUTMessage* CreateMessage (const char* family_name,
                                          int size, 
                                          bool bold, 
                                          bool italic);

  /**
   * Create message given a font filename.
   * @param glut_font glut font.
   * @param size font size.
   * @return pointer to created message, or NULL when error occurred.
   */
  static UFontGLUTMessage* CreateMessageWithFont (void* glut_font,
                                                  int size);

  void SetFont (void* font);
  virtual int Length (const char *text);
  virtual void GetDimensions (const char* text, int *length=0, int *height=0);
  virtual int GetAscender();
  virtual int GetDescender();
  virtual int GetLineHeight();  
protected:
  virtual void Show (const char* text);
private:
  void* m_font;
};

#endif
