// Element/node number renderer
// malf@tecgraf.puc-rio.br
// rodesp@tecgraf.puc-rio.br
// May 2008

#ifndef TPV_NUMBERS_RENDERER_H
#define TPV_NUMBERS_RENDERER_H

#include <ds/list.h>
#include <ufont/fontmanager.h>
#include <topsview/defines.h>
#include <topsview/renderer/renderer.h>

class TpvGeometry;
class TpvTriangleSet;
class TpvPointSet;
class TpvProperty;

class TPV_API TpvNumbersRenderer : public TpvRenderer
{
public: 
  TpvNumbersRenderer ();

  virtual ~TpvNumbersRenderer ();

  void SetGeometry (TpvGeometry* g);

  /**
   * Notifies the renderer that geometry has changed.
   */
  void SetGeometryChanged ();
 
  /**
   * Sets an optional displacement to be applied to element nodes.
   */
  void SetDisplacement (float factor, TpvProperty* disp);

  void SetFont(const char *family_name, int size, bool bold = false, bool italic = false);

  void SetColor (float r, float g, float b, float a);

  void GetColor (float* r, float* g, float* b, float* a);

protected:  
  virtual void DoRender ();
  virtual void RenderBegin ();
  virtual void RenderEnd ();

private:
  void Update();
  void RenderSet (TpvTriangleSet* set);
  void RenderSet (TpvPointSet* set);

private:
  UFontManager* m_fontmanager;
  TpvGeometry* m_geometry;
  bool m_update_dl;
  unsigned int m_face_dl;
  unsigned int m_node_dl;
  float m_color[4];
  float m_disp_factor;
  TpvProperty* m_disp;
};

#endif
