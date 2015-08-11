#ifndef RES_UNIT_H
#define RES_UNIT_H

#include <ds/array.h>

class ResUnit
{
public:
  ResUnit ();
  ~ResUnit ();
  bool AddNumerator (const char* numerator);
  bool AddDenominator (const char* denominator);
  const char* GetSymbol () const;
  /**
   * Returns the multiplication factor (a) and addition factor (b)
   * to convert a value from unit 'this' to unit 'to'.
   */
  bool GetFactors (ResUnit* to, double* o_factor_mult, double* o_factor_add);
private:
  void Update ();
private:
  DsArray<char*> m_numerator;
  DsArray<char*> m_denominator;
  char* m_symbol;
};

#endif

