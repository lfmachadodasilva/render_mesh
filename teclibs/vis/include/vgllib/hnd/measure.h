// measure.h
// fabraham@tecgraf.puc-rio.br
// Tecgraf/PUC-Rio
// Nov 2007

#ifndef VGL_MEASURE_H
#define VGL_MEASURE_H

#include <vgl/handler.h>
#include <ds/array.h>
#include <vgllib/defines.h>
#include <float.h>

class VGLLIBAPI VglMeasureHandler : public VglHandler
{
public:
  static const char* CLASSNAME() { return "MeasureHandler"; }
  virtual const char* ClassName() const { return CLASSNAME(); }
  VglMeasureHandler ();
  ~VglMeasureHandler ();
  void SetMeasureFrequency(int freq)
  {
    m_averagenumframes = freq;
  }
  /**
   * Specifies that the virtual time must pass according to
   * 'fps'.
   */
  void SetFrameRate (double fps);
  /**
   * Specifies that the virtual time must be equal to the current time.
   */
  void SetNoFrameRate ();
  double GetFPS() const
  {
    return m_fps;
  }
  /**
   * Specifies how many extra fields will be stored for later averaging
   * and saving.
   */
  void SetExtraFieldCount (int n);
  /**
   * Specifies the name of the i'th extra field.
   */
  void SetExtraFieldName (int i, const char* name);
  /**
   * Specifies, for the current frame, the value associated with the
   * i'th extra field.
   */
  void SetExtraFieldValueForFrame (int i, double v);
  /**
   * Saves frame time history to file 'fileName'.
   * 'max_considerable_render_time' specifies the amount of frame
   * render time that is to be disconsidered (the last
   * frame time is used instead). This can be used to discard outliers.
   *
   * Returns 'true' if successful, 'false' otherwise.
   */
  bool SaveHistory (const char* fileName, double max_considerable_render_time=DBL_MAX);
  // reimplemented virtual methods
  int PreRedraw();
  int AfterRedraw();
private:
  double GetVirtualTime (double clocktime);
private:
  struct FrameInfo
  {
    double time;
    double rendertime;
    double* extra_fields;
    FrameInfo ()
    : extra_fields(NULL)
    {
    }
  };
  int m_averagenumframes;
  int m_nframes;
  double m_fps;
  double m_t0;
  double m_firstframetime;
  double m_last_compl_t;
  double* m_vt_fps;
  DsArray<FrameInfo*> m_framehistory;
  DsArray<char*> m_extra_field_names;
  DsArray<double> m_extra_field_values;
};

#endif
