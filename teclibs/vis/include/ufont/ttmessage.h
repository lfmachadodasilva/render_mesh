// True type OpenGL message displayer
// fabraham@tecgraf.puc-rio.br
// nakamura@tecgraf.puc-rio.br
// Oct 2005
#ifndef UFONT_TTMESSAGE_H
#define UFONT_TTMESSAGE_H

#include "message.h"
#ifdef WIN32
#include <wchar.h>
#endif

typedef int FT_Error;
class FTFont;

class UFONT_API UFontTTMessage : public UFontMessage
{
  FTFont* m_currentfont;
public:
  UFontTTMessage (float x=-0.9, float y=0.9, float z = 0.9);
  virtual ~UFontTTMessage ();
  /**
   * Initializes TTMessage.
   * Returns true on success, false otherwise.
   */
  static bool Init ();
  /**
   * Create message with a truetype font family name.
   * @param family_name TT font family name.
   * @param size font size.
   * @param bold flag.
   * @param italic flag.
   * @param render_mode self-explanatory.
   * @param depth font depth.
   * @return pointer to created message, or NULL when error occurred.
   */
  static UFontTTMessage* CreateMessage (const char* family_name,
                                        int size,
                                        bool bold,
                                        bool italic,
                                        UFontMessage::RenderMode render_mode,
                                        float depth = 0.0f);

  /**
   * Create message given a font filename.
   * @param ttm pointer to message with true type font.
   * @param filename font filename to be loaded.
   * @param size font size.
   * @param render_mode self-explanatory.
   * @param depth font depth.
   * @return pointer to created message, or NULL when error occurred.
   */
  static UFontTTMessage* 
  CreateMessageWithFile (const char* filename,
                         int size,
                         UFontMessage::RenderMode render_mode,
                         float depth);

  bool LoadFont (int render_mode, const char* filename, float depth);
  bool LoadBitmapFont (const char* filename);
  bool LoadPolygonFont (const char* filename);
  bool LoadExtrudedFont (const char* filename);
  bool LoadOutlineFont (const char* filename);
  bool LoadTextureFont (const char* filename);
  bool LoadPixmapFont (const char* filename);
  bool SetFontSize (int size);
  bool SetFontDepth (float depth);
  const char *GetFamilyName () const;
  bool IsBold () const;
  bool IsItalic () const;
  virtual int Length (const char* text);
  virtual void GetDimensions (const char* text, int *length=0, int *height=0);
  virtual void GetBBox (const char* text, float *llx=0, float *lly=0, float *llz=0, float *urx=0, float *ury=0, float *urz=0);
  virtual int GetAscender(); 
  virtual int GetDescender();  
  virtual int GetLineHeight();  
protected:
  virtual void Show (const char* text);
private:
  bool ConvertToWideChar (const char* text, wchar_t* textwc);
  void PrintFTErrorMessage (FT_Error err);
};

#endif

