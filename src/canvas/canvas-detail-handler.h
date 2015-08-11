// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_CANVAS_DETAIL_HANDLER_H
#define ANFLEX_INTERFACE_CANVAS_DETAIL_HANDLER_H

#include <string>
#include <vector>

#include <vgl/vgl.h>
#include <vgl/vgliup.h>

#include <iupgl.h>

class cCanvasDetach;
class cCanvasMain;

class cCanvasDetailHandler : public VglZoomHandler
{                                                                                                        
private:
  VglCanvas   *m_canvas;
  VglCamera   *m_camera;
  cCanvasMain *m_canvas_main;
  void        *m_data;

  std::string m_icon;
  std::string m_title;
  std::string m_parent;

  std::vector<cCanvasDetach*> m_vec_canvas_detach;      
  std::vector<Ihandle*> m_vec_dialog;
  bool isAnimating;

  VglFunction m_idle_function;
  VglFunction m_redraw_function;
  VglFunction m_redraw_end_function;

  void *m_idle_data;
  int m_idle_repeat;

  void (*m_menu_popup_function)(void*);

protected:
  virtual void Zoom(float dx, float dy, float x=0.5f, float y=0.5f);

public:
  cCanvasDetailHandler(VglViewSurface *surface, cCanvasMain *canvas_main, void *data);
  virtual ~cCanvasDetailHandler ();

  void set_canvas_main(cCanvasMain* canvas_main) { m_canvas_main = canvas_main; }

  void create_canvas_detach(int w, int h, VglCamera *camera);

  void redraw_detail_windows(void);

  void set_detach_attribute(VglFunction func, 
                            VglFunction func_end, 
                            VglFunction idle,
                            void *data,
                            int repeat,
                            void(*poupup_func)(void*),
                            std::string icon,
                            std::string title, 
                            std::string parent)
  {
    m_redraw_function = func;
    m_redraw_end_function = func_end;
    m_idle_function = idle;
    m_idle_data = data;
    m_idle_repeat = repeat;
    m_menu_popup_function = poupup_func;
    m_icon = icon;
    m_title = title;
    m_parent = parent;
  }

  void set_detail_window_icon(char *icon) { m_icon = icon; }
  void set_detail_window_title(char *title) { m_title = title; }
  void set_detail_window_parent(char *parent) { m_parent = parent; } 
  void set_detail_window_idle(VglFunction, void *data, int repeat);
  void set_detail_window_animation(bool is_animating);
  void close_detail_windows(void);
  void set_menu_popup_function(void(*func)(void*)) { m_menu_popup_function = func; }
  
  void set_redraw_detail_function(VglFunction func) { m_redraw_function = func; }
  void set_redraw_detail_end_function(VglFunction func) { m_redraw_end_function = func; }

};

#endif // ANFLEX_INTERFACE_CANVAS_DETAIL_HANDLER_H
