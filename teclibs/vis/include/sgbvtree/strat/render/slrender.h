// Sort Last Render Strategy
// fabraham@tecgraf.puc-rio.br
// Sep 2004

#ifndef SG_SLRENDER
#define SG_SLRENDER

#include <sg/camera.h>
#include <sg/strat/render/render.h>
#include <stdlib.h>
#include <sgbvtree/sgbvtree.h>

class SGBVTREEAPI SGSLRender : public SGRender
{
public:
  typedef void (*NewTileFunc)(int x, int y, int w, int h, int dest);
  typedef void (*NewExpectedTileFunc)(int src);
private:
  unsigned short m_drawn_planes, m_notdrawn_planes;
  unsigned short m_planes;
  int m_reqx, m_reqy, m_reqwidth, m_reqheight;
  int m_drawx, m_drawy, m_drawwidth, m_drawheight;
  int m_intsize;
  bool m_useinnerprojection;
public:
  SGSLRender ();
  virtual ~SGSLRender ();
  void SetCullingWindow (int reqx, int reqy, int reqwidth, int reqheight)
  {
    m_reqx = reqx;
    m_reqy = reqy;
    m_reqwidth = reqwidth;
    m_reqheight = reqheight;
  }
  void SetDrawingWindow (int drawx, int drawy, int drawwidth, int drawheight)
  {
    m_drawx = drawx;
    m_drawy = drawy;
    m_drawwidth = drawwidth;
    m_drawheight = drawheight;
  }
  void SetIntersectionSize (int numpixels)
  {
    m_intsize = numpixels;
  }
  void SetPlanes (unsigned short planes)
  {
    m_planes = planes;
  }
  void InitPlanes ()
  {
    m_drawn_planes = m_notdrawn_planes = 0;
  }
  void AddDrawnPlanes (int planes)
  {
    m_drawn_planes |= planes;
  }
  void AddNotDrawnPlanes (int planes)
  {
    m_notdrawn_planes |= planes;
  }
  bool DrawnIntersectedWith (int plane)
  {
    return (m_drawn_planes & (1<<plane)) != 0;
  }
  bool NotDrawnIntersectedWith (int plane)
  {
    return (m_notdrawn_planes & (1<<plane)) != 0;
  }
  void SetUseInnerProjection (bool f)
  {
    m_useinnerprojection = f;
  }
  void CalcTiles (NewTileFunc newtilefunc, NewExpectedTileFunc newexpectedtilefunc, int peermaster, int peerleft, int peerright, int peerbottom, int peertop);
};

#endif
