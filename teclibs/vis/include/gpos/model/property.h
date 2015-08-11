//* property.h
// A viewable property.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_property_h
#define vis_property_h

#include <stdio.h>
#include <gpos/defines.h>

class ResStep;
class ResModel;

//* 'ResProperty' Class
// Represents a property suitable for viewing.
class RES_API ResProperty
{
  int *m_refcount;

protected:
  ResModel *m_mdl;
  float *m_dvalues;
  int m_ndvalues;
protected:
  ResProperty (ResModel *mdl);
  virtual ~ResProperty();
public:
  ResModel *GetModel() const
  {
    return m_mdl;
  }

  void Release();

    //* Step Load
    // Loads the data of a specific step or NULL to load
    // all steps.
    // Returns non zero in case of success, zero otherwise.
    // Updates reference counts.
  int Load(const ResStep *t = 0);

    //* Step Unload
    // Unloads the data of a specific step or NULL to unload
    // all steps.
    // Returns non zero in case of success, zero otherwise.
    // Updates reference counts.
  int UnLoad(const ResStep *t = 0);

  /**
   * Obtains the current time step, NULL if there is no current
   * time step.
   */
  ResStep* GetCurrentStep();

    //* Initial property query
    // Returns true if this property is an initial property
    // false if its recurrent
  virtual bool IsInitial() = 0;

    //* Reference count query
    // Returns the current number of references to the given timestep
  int GetRefCount(const ResStep *t);

    //* Reference step adjust
    // Adjusts the reference step to be used when retrieving values.
  virtual void SetStep(const ResStep *t);

  /**
   * Obtains the current time step index. If there is no current time step,
   * returns a negative value.
   */    
  virtual int GetCurrentStepIndex() const
  {
    return m_step_index;
  }
    //* Symbol query
    // Returns the property symbol.
  virtual const char * GetSymbol() const = 0;

    //* Description query
    // Returns the property description.
  virtual const char * GetDescription() const = 0;

    //* Unit query
    // Returns the property unit symbol.
  virtual const char * GetUnit() const = 0;

    //* Minimum value query
    // Returns the minimum property value.
  virtual float GetMinValue() = 0;

    //* Maximum value query
    // Returns the maximum property value.
  virtual float GetMaxValue() = 0;
  /**
   * Builds a per-node property.
   * smooth_values[i] = value at node of posid 'i'.
   * Memory must be freed by caller using 'free'.
   */
  float* CreateSmoothProperty (ResStep* step);
    //* Null value query
    // Returns the value which is considered to be a null property value.
  virtual float GetNull() const = 0;

    //* Amount of loaded steps query
    // Returns the number of steps that have been loaded.
  virtual int GetNumberOfStepsLoaded() = 0;
  /**
   * Returns true if the property has values for all cells,
   * false if only for active cells.
   */
  virtual bool IsComplete () const = 0;
    //* Cell value query
    // Returns the value of the cell, given it's grid position.
    // It must be an active cell.
  float GetValue (int i, int j, int k);
    // Returns the value of the cell, given it's index.
  virtual float GetValue(int index) = 0;
    //* All values query
    // Fills in 'buf' will all property values or slicing at 'slice'
    // Used for fast computations (aka "macro")
    // Dimensions of size 1 are replicated
    // The number of dimensions of buf is necessarily 4 (the dimension of a ResProperty)
  virtual void GetValues(float *buf, int bufsize[], int slice[]) = 0;

    //* Inactive cell value query
    // Returns true if the given inactive cell has a value associated with it
  virtual bool HasValue(int index)
  {
    return GetValue(index) != GetNull();
  }
  virtual float GetInactiveCellValue(int index) { return -1.0f; }


    //* ColorScale usage query
    // Returns true if this property should be rendered using regular color scales
    // or if it provides the cell colors.
  virtual bool UseColorScale() { return true; }
   
    //* Cell color query
    // Must be implemented by properties that provide it's cells' color.
  virtual void GetCellColor(int index, float *r, float *g, float *b) {}

    //* Cell value description query
    // Must be implemented by properties that provide it's cells' color.
  virtual int GetNumberOfCellValues() { return 1; }
  float GetCellValue(int v, int i, int j, int k);
  virtual float GetCellValue(int v, int index) { return 0.0f; }
  virtual const char * GetCellValueDesc(int v) { return 0; }
  /**
   * Sets the property as a discrete property.
   */
  void SetDiscrete()
  {
    m_discrete = true;
  }
  void SetDiscreteValues(int numvalues, const float *values);
  /**
   * Is the property a discrete property?
   */
  bool IsDiscrete() const
  {
    return m_discrete;
  }
  int GetNumberOfDiscreteValues() const
  {
    return m_ndvalues;
  }
  float GetDiscreteValue(int i);
  int GetIndirection (int index);
  const int* GetIndirection ();
protected:
  int GetStepIndex(const ResStep *t);
  // effectively load and unload data
  virtual int doLoad(const ResStep *t) = 0;
  virtual int doUnLoad(const ResStep *t) = 0;
private:
  void ResetDiscreteValues ();
  void ComputeDiscreteValues ();
  /**
   * Recomputes the number of discrete values and saves their values.
   */
  void RecomputeDiscreteValues ();
private:
  int m_step_index;
  bool m_discrete;
  bool m_computing_disc_values;
};

#endif

