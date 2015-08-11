//* percellcolorprop.h
// Special property that defines rgba color per cell.
// Tecgraf/PUC-Rio
// June 2011
// @author Cesar Palomo <cpalomo@tecgraf.puc-rio.br>

#ifndef percellcolor_property_h
#define percellcolor_property_h

#include <ds/array.h>
#include <gpos/model/property.h>

class ResModel;

// 'ResPerCellColorProperty' Class
// Represents a special reservoir property that defines one color per cell.
class RES_API ResPerCellColorProperty : public ResProperty
{
public:
  /**
   * Constructor receiving reservoir model, property symbol and description.
   */
  ResPerCellColorProperty (ResModel* mdl, const char* symbol, const char* desc);

  /**
   * Destructor. Clients should be aware that inner array of colors is
   * released at this point.
   */
  ~ResPerCellColorProperty ();

  /**
   * Access to array of RGBA colors per cell (each component in (0,1) range).
   */
  DsArray<float>* ResPerCellColorProperty::GetPerCellColors ()
  {
    return m_cells_colors;
  }

  /**
   * Setup array of RGBA colors per cell (each component in (0,1) range).
   */
  void SetPerCellColors (const float* rgba_colors, int cells_count );

  /**
   * Access property symbol text.
   */
  const char* GetSymbol() const { return m_symbol; }

  /**
   * Access property text description.
   */
  const char* GetDescription() const { return m_desc; }

  // virtual methods in superclass
  bool UseColorScale() { return false; }
  void GetCellColor (int cell_index, float* r, float* g, float* b, float* a);
  void GetCellColor(int index, float *r, float *g, float *b);

  // pure virtual methods in superclass
  bool IsInitial () { return false; }
  const char * GetUnit () const { return ""; }
  float GetMinValue () { return 0.0f; }
  float GetMaxValue () { return 0.0f; }
  float GetNull () const { return 0.0f; };
  int GetNumberOfStepsLoaded () { return 0; }
  bool IsComplete () const { return true; }
  float GetValue (int index) { return 0.0f; }
  void GetValues (float* buf, int bufsize[], int slice[]) {}
  bool HasValue (int index) { return true; }

protected:
  // pure virtual methods in superclass
  int doLoad (const ResStep* t) { return 1; }
  int doUnLoad (const ResStep* t) { return 1; }

private:
  char* m_symbol;                 /**< Property symbol.              */
  char* m_desc;                   /**< Text description.             */
  DsArray<float>* m_cells_colors; /**< Array of RGBA color per cell. */
};
#endif

