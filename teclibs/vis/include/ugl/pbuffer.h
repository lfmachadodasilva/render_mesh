/* 
  Suporte para UGLPBuffer no OpenGL.
  
  Baseado no código original "pbuffer.h", disponível no OpenGL
  SDK, da NVidia Corp. (www.nvidia.com)

*/

#ifndef UGL_PBUFFER_H
#define UGL_PBUFFER_H

#include "defines.h"

#ifdef _WIN32
# include <windows.h>
# include <GL/wglew.h>
#else
# include <GL/glxew.h>
#endif

class UGL_API UGLPBuffer
{
private:
    unsigned int m_mode;      
    bool         m_sharedctx; 
    bool         m_sharedlists;
    bool         m_initialized; 

#ifdef _WIN32
    HWND         m_window;         // Janela criada para obter um contexto para 
                                   // o PBuffer, quando não há compartilhamento
                                   // de contexto ou lista.
    HGLRC        m_window_glrc;    // Contexto OpenGL da janela.
    HDC          m_dc;             // Informações sobre o UGLPBuffer atual.
    HGLRC        m_wglcontext;    
    HPBUFFERARB  m_pbuffer;       

    HDC          m_old_dc;     // Contexto ativo antes da ativação do PBuffer.
    HGLRC        m_old_wglcontext; 
#else
    Display*     m_alloc_display;  // Display alocado para o Pbuffer quando não 
                                   // há compartilhamento de contexto ou listas. 
                                   // É necessário criar um novo contexto na 
                                   // primeira vez, pois pode 
                                   // não haver um contexto corrente.

    Display*     m_display;       // Informações sobre o UGLPBuffer atual. 
    GLXContext   m_glxcontext;
    GLXPbuffer   m_pbuffer;

    Display*     m_old_display; // Contexto ativo antes da ativação do PBuffer.
    GLXContext   m_old_glxcontext;     
    GLXDrawable  m_old_read_drawable;  
    GLXDrawable  m_old_write_drawable; 
#endif

    int          m_width;
    int          m_height;

    unsigned int m_tex_target;
    unsigned int m_bits_per_comp;

public:

// TODO: Colocar bits per component e number of components....
    enum Mode {
      INDEX   = 1,
      ALPHA   = 2,  // Request alpha bits.
      DOUBLE  = 4,  // Double-buffer.
      SINGLE  = 8,  
      DEPTH   = 16,
      STENCIL = 32,
      ACCUM   = 64,
      FLOAT_BUFFER_NV  = 128, // 32-bit per component float buffer (RGBA).
      FLOAT_BUFFER_ATI = 256,
      RENDER_TEXTURE = 512,
      RENDER_DEPTH_TEXTURE = 1024
    };

    enum TextureTarget {
      TEXTURE_2D = 1,
      TEXTURE_CUBE = 2,
      TEXTURE_RECTANGLE = 4,
    };

  /**
   *   Cria um PBuffer. O método Initialize() deve ser chamado
   *   antes da utilização do PBuffer.
   */
  UGLPBuffer  ();
  ~UGLPBuffer ();

  /**
      Checa se o Pbuffer foi perdido, o que pode ocorrer após
    uma mudança de modo no Windows, e, em caso positivo, destrói o 
    atual e cria um novo. No X Windows, não tem efeito, já que
    o conteúdo do PBuffer é preservado.
  */
  void HandleModeSwitch ();

  /**
      Ativa PBbuffer para desenho, guardando o contexto ativo anterior. 
    @returns Se Ok: 1. Senão: 0.
   */
  int Activate ();

  /**
     Desativa UGLPBuffer ativando o contexto anteriormente ativo.
   */
  int Deactivate();

  bool IsActive();


  /**
     Set the texture target for the pbuffer, when bound to texture.
    The Initialize() method must be called for this attribute make effect.
    @see TextureTarget
  */
  void SetTextureTarget(unsigned int target) { m_tex_target = target; }

  /**
     Set the number of bits per color component (R,G,B or A).
    The Initialize() method must be called for this attribute make effect.
  */
  void SetBitsPerComponent(unsigned int bits) { m_bits_per_comp = bits; }


  /**
      Inicializa PBuffer. 

    @param w Largura requerida. Deve ser checada após a 
    inicialização.
    @param h Altura requerida. Deve ser checada após a 
    inicialização.
    @param mode Máscara "OR" com parâmetros de inicialização de
    "VglPBuffer::Mode". Semelhante à máscara usada em 
    "glutCreateWindow".
    @param shareCtx Se "true", compartilha contexto com
    o canvas ativo. Isso implica que todas as "Display lists" 
    e as texturas serão automaticamente compartilhadas, e que
    já deve haver um contexto ativo. 
    @param shareLst Se "true", compartilha as "Display
    Lists" e as texturas com o canvas ativo. Nesse caso, já deve haver um
    contexto ativo. Se "shareCtx" for "true", esse parâmetro não tem efeito, 
    pois as "Display lists" e texturas já serão automaticamente compartilhadas. 
    @returns Se conseguiu inicializar o Pbuffer: 1. Senão: 0. 
    Deve sempre ser checado!!!

    @see Mode
  */
  int Initialize (int w =64, int h =64, unsigned int mode =SINGLE, 
                  bool sharecontexts = true, bool sharelists = false);


  void SwapBuffers ();
  
#ifdef _WIN32
  HPBUFFERARB GetPBuffer ()
  {
    return m_pbuffer;
  }
#endif
  bool IsInitialized ()   { return m_initialized; }
  int GetWidth ()         { return m_width; }
  int GetHeight ()        { return m_height; }
  unsigned int GetMode () { return m_mode; }

  /**
  TODO: 
    - allow sharecontexts for render_texture.
    - support 1D render_targets.

    Render texture:
      Initialization:
        1 - Get a valid device context (e.g: create a window).
        2 - Initialize pbuffer with TEX_W, TEX_H, mode: RENDER_TEXTURE, 
        sharecontexts = false, sharelists = true (so, ChoosePixelFormat
        is used to select an appropriate pixel format).

      Redering:
        1 - Bind a 2D texture object.
          // create our render texture object
          glGenTextures(1, &render_texture);
          glBindTexture(GL_TEXTURE_2D, render_texture);
          // notice that we don't need to call glTexImage2D
          glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
          glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
          glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
          // Generate mipmap automatically
          glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

        2 - Draw to pbuffer.
          pbuffer.Activate();
          draw_pbuffer();
          pbuffer.Deactivate();

        3 - Bind pbuffer to texture.
          pbuffer.BindTexture();

        4 - Draw to color buffer, using the texture.
          glBindTexture(GL_TEXTURE_2D, render_texture);
          draw();

        5 - Release pbuffer from the texture, so it can be used again for 
        the next redraw.
          pbuffer.ReleaseTexture();


  */
  int  BindTexture();
  int  ReleaseTexture();
};

#endif
