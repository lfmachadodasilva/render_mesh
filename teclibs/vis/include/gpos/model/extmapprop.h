//* extmapprop.h
// A viewable external map property.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_extmapproperty_h
#define vis_extmapproperty_h

#include "property.h"
#include "model.h"
#include "geometry.h"

#include <common/util.h>

#include <stdio.h>
#include <assert.h>

//* 'ResExtMapProperty' Class
// Represents an external map property suitable for viewing.
class RES_API ResExtMapProperty : public ResProperty
{
  char d_symbol[512];
  char d_desc[2048];
  char d_srcfile[2048];
  char *d_unit;
  float d_maxvalue, d_minvalue;
  int d_ni, d_nj, d_nk;

  float **d_values;

  /*
   * file format:
   *  for t = 1, nsteps do
   *    for k = 1, nk do
   *      for j = 1, nj do
   *        for i = 1, ni do
   *          READ/WRITE value
   */

protected:
  virtual ~ResExtMapProperty();

public:
  ResExtMapProperty(ResModel *model);

    //* Property data export
    // Writes an external property file, given the model, the property and the file name.
    // 'stepindex' defines which time step to export. If equal to '-1', exports all time steps.
    // 'i0'/'i1' define the range of 'i' sections to export.
    // 'j0'/'j1' define the range of 'j' sections to export.
    // 'k0'/'k1' define the range of 'k' sections to export.
    // Returns non zero in case the step index and the section range were
    // correctly defined and the file was successfully written, zero otherwise.
  static int WriteFile(
    ResModel *m,
    ResProperty *p,
    char *filename,
    int stepindex,
    int i0,
    int i1,
    int j0,
    int j1,
    int k0,
    int k1);

  /**
   * Data file read.
   *
   * Reads property values from a file containing ASCII float values.
   *
   * Parameters:
   *  name:          property name.
   *  one_step_only: if true, the method will read 'number-of-cells' floats and
   *                 replicates the read values to all model time steps.
   *
   * Return values:
   *  Returns true in case the file contains exactly the number of expected
   *  float values.
   *  Otherwise:
   *  - returns false;
   *  - places the number of values read in pointer 'o_nread';
   *  - places the number of values expected in pointer 'o_nexpected'.
   */
  bool ReadFile(char *name, bool one_step_only, int *o_nread, int *o_nexpected);
  const char * GetSourceFile() const { return d_srcfile; }
  void SetUnit(const char *unit)
  {
    free(d_unit);
    d_unit = strdup(unit);
  }
  const char * GetUnit() const
  {
    return d_unit;
  }
  bool IsInitial()
  {
    return false; // TODO: handle initial properties as well
  }
  
  void SetSymbol(const char *s)
  {
    strcpy(d_symbol, s);
  }

  const char * GetSymbol() const
  {
    return d_symbol;
  }

  void SetDescription(const char *s)
  {
    strcpy(d_desc, s);
  }

  const char * GetDescription() const
  {
    return d_desc;
  }

  float GetMinValue()
  {
    return d_minvalue;
  }

  float GetMaxValue()
  {
    return d_maxvalue;
  }

  float GetNull() const
  {
    return ResExtMapProperty::GetNullValue();
  }
  
  int GetNumberOfStepsLoaded()
  {
    return m_mdl->GetNumberOfSteps();
  }

  float GetValue (int index)
  {
    int step_index = GetCurrentStepIndex();
    assert(step_index >= 0);
    if (!d_values[step_index])
      return -1.0f;
    return d_values[step_index][index];
  }

  void GetValues(float *buf, int bufsize[], int slice[]);
  bool IsComplete () const
  {
    return true;
  }
protected:
  int doLoad(const ResStep *t = 0);

  int doUnLoad(const ResStep *t = 0);

  void SetValue(int step, float value, int i, int j, int k)
  {
    d_values[step][index(i,j,k)] = value;
  }

  int getmstep(const ResStep *t);

  void cleanup();

  int index(int i, int j, int k)
  {
    return ((k*d_nj)+j)*d_ni+i;
  }
private:
  static float GetNullValue()
  {
    return 97654321.0f;
  }
};

#endif
