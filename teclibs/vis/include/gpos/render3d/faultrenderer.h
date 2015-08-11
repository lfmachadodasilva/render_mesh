#ifndef RES_FAULT_RENDERER_H
#define RES_FAULT_RENDERER_H

#include <stdlib.h>
#include <alg/vector.h>
#include <ds/array.h>
#include <ds/hash.h>
#include <gpos/model/faultdata.h>
#include <utility>

// forward declarations
class SciColorScale;
class UGLTriangleSet;
class UGLVertexArray;

/**
 * Fault renderer class definition: render faults geometry and properties.
 */
class ResFaultRenderer
{
public:

public:
  ResFaultRenderer ();
  virtual ~ResFaultRenderer ();
  const char* ClassName () const { return "ResFaultRenderer"; };

  /**
   * Set ResFaultData to be rendered.
   * @return whether fault data actually changed.
   */
  void SetFaultData (const ResFaultData* fault_data);

  /**
   * Set a faults property as active: its values will be used when drawing faults.
   * The action can be forced when necessary.
   */
  void SetActiveProperty (ResFaultProperty::PropName n, bool force);

  /**
   * Turn picking on or off.
   */
  void SetPickActive (bool flag)
  {
    m_pick_active = flag;
  }

  /**
   * Return whether picking is on or not.
   */
  bool IsPickActive () const
  {
    return m_pick_active;
  }

  /**
   * Set a fault plain color.
   * @NOTE: when plain color set for a fault, its scalars
   * are not used in conjunction with color scale.
   */
  void SetFaultColor (int fault_i, AlgVector& color);

  /**
   * Set active color scale for fault properties.
   */
  void SetColorScale (SciColorScale* cs);

  /**
   * Draw faults.
   */
  void Draw ();

  /**
   * Return active property used for faults rendering.
   */
  ResFaultProperty::PropName GetActiveProperty () const
  {
    return m_active_property;
  }

private:
  /**
   * Draw a given fault.
   * @param fault_i fault index to be drawn.
   */
  void DrawFault (int fault_i) const;

  /**
   * Clear inner structures, such as VBO's.
   */
  void Clear ();

  /**
   * Create VBO's for faults.
   */
  void CreateVBOs ();

  /**
   * Update property VBO's.
   */
  void UpdatePropertyVBOs ();

private:
  const ResFaultData* m_fault_data;
  ResFaultProperty::PropName m_active_property;
  DsArray<UGLVertexArray*> m_vertices;
  DsArray<UGLTriangleSet*> m_indices;
  DsArray<bool> m_fault_has_color;   /**< Faults color set flag.            */
  DsArray<AlgVector> m_fault_color;  /**< Faults color.                     */
  SciColorScale* m_cs;               /** Color scale  for fault properties. */
  bool m_cs_needs_update;            /** Color scale needs update?          */
  /** Properties values limits.                                             */
  DsHash< ResFaultProperty::PropName, std::pair<float,float> > m_prop_limits;
  bool m_pick_active;                /**< Active pick flag.                 */
};

#endif  // RES_FAULT_RENDERER_H

