#ifndef VGL_ROTATION_AXIS_H
#define VGL_ROTATION_AXIS_H

#include <alg/vector.h>
#include <vgl/handler.h>
#include <vgl/hnd/selection.h>
#include <vgl/hnd/pointpick.h>
#include <vgl/utils/axis.h>
#include <vgl/viewsurface.h>

class VGL_API VglRotationAxisHandler : public VglHandler
{
public:
   typedef void (*NewAxisPosFunction)(float x, float y, float z, void *data);
protected:
   VglViewSurface *m_surface;
   VglAxisRender m_render_axis;
   AlgVector m_pos;
   AlgVector m_axis;
   NewAxisPosFunction m_newaxisposfunc;
   void *m_newaxisposdata;
   bool m_drawaxis;
   bool m_moving;
   bool m_posset;
   char m_constraint;

   static void RepeatTransform (void* data);
   static void RenderAxis (void *data);

   void RenderAxis ()
   {
     m_render_axis.RenderAxis();
   }
public:
   static const char* CLASSNAME () { return "RotationAxisHandler"; }
   virtual const char* ClassName () const { return CLASSNAME(); }
   VglRotationAxisHandler (VglViewSurface* surface) :
      m_surface(surface),
      m_render_axis(surface),
      m_axis(0.0f,1.0f,0.0f),
      m_newaxisposfunc(NULL),
      m_newaxisposdata(NULL),
      m_drawaxis(true),
      m_moving(false),
      m_posset(false),
      m_constraint(0)
   {
   }
   virtual ~VglRotationAxisHandler ()
   {
   }
   void SetAxis (const AlgVector &axis)
   {
      m_axis = axis;
      m_render_axis.SetAxis(axis);
   }

   void SetAxis (float x, float y, float z)
   {
      SetAxis(AlgVector(x, y, z));
   }

   void SetAxisPosition (const AlgVector &pos)
   {
      m_pos = pos;
      m_posset = true;
      if (m_newaxisposfunc)
        m_newaxisposfunc(pos.x,pos.y,pos.z,m_newaxisposdata);
      m_render_axis.SetAxisPosition(pos);
   }

   void UnsetAxisPosition ()
   {
     m_posset = false;
     m_render_axis.UnsetAxisPosition();
   }

   void SetAxisPosition (float x, float y, float z)
   {
      SetAxisPosition(AlgVector(x,y,z));
   }

   void SetNewAxisPosFunc (NewAxisPosFunction func, void *data)
   {
     m_newaxisposfunc = func;
     m_newaxisposdata = data;
   }

   AlgVector &GetAxis ()
   {
      return m_axis;
   }

   void GetAxis (float *x, float *y, float *z)
   {
      *x = m_axis.x;
      *y = m_axis.y;
      *z = m_axis.z;
   }

   bool HasAxisPosition () const
   {
     return m_posset;
   }

   AlgVector &GetAxisPosition ()
   {
      return m_pos;
   }

   void GetAxisPosition (float *x, float *y, float *z)
   {
      *x = m_pos.x;
      *y = m_pos.y;
      *z = m_pos.z;
   }

   void SetThickness (float thickness)
   {
     m_render_axis.SetThickness(thickness);
   }

   float GetThickness ()
   {
     return m_render_axis.GetThickness();
   }

   void SetLineSize (float size)
   {
     m_render_axis.SetAxisSize(size);
   }

   float GetLineSize ()
   {
     return m_render_axis.GetAxisSize();
   }

   bool IsDrawingAxis ()
   {
      return m_drawaxis;
   }

   void DrawAxis (bool draw)
   {
      m_drawaxis = draw;
   }
   /**
    * Returns true in case the model/scene is moving because of this manipulator, false otherwise.
    */
   bool IsMoving ()
   {
      return m_moving;
   }
   virtual void End ();
   virtual int Keyboard (int k, int st, float x, float y);
   virtual int MouseButton (int bt, int st, float x, float y);
   virtual int MouseMotion (int bt, float x, float y);
   virtual int PostRedraw ();
};

class VGL_API VglRotationHandler : public VglRotationAxisHandler
{
public:
   VglRotationHandler(VglViewSurface* surface) :
      VglRotationAxisHandler(surface),
      m_pick(surface)
   {
   }
   virtual ~VglRotationHandler()
   {
   }
   static const char* CLASSNAME () { return "RotationHandler"; }
   virtual const char* ClassName () const { return CLASSNAME(); }

   virtual int MouseButton (int bt, int st, float x, float y);

   void SetSelectionRenderFunc(VglSelectionHandler::SelectionFunc f, void *data)
   {
      m_pick.SetSelectionRenderFunc(f,data);
   }
   void SetSelBufferSize (int sel_buf_size)
   {
      m_pick.SetSelBufferSize(sel_buf_size);
   }
protected:
   VglPointPickHandler m_pick;
   float m_x, m_y;
};

#endif

