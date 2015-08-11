//* step.h
// A viewable step.
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef vis_step_h
#define vis_step_h

#include <gpos/defines.h>
#include <gpos/common/util.h>

//* 'ResStep' Class
// Represents a step suitable for viewing.
class RES_API ResStep
{
public:
  ResStep ()
  : m_number(-1)
  {
  }
  virtual ~ResStep ()
  {
  }
  void SetNumber(int number)
  {
    m_number = number;
  }
  /**
   * Obtains the time step number in the entire simulation,
   * including map and well time steps.
   * The first time step has number '1'.
   */
  int GetNumber() const
  {
    return m_number;
  }

    //* Number of days query
    // Returns the number of days.
  virtual double GetNumberOfDays() const = 0;

    //* Day query
    // Returns the day number.
  virtual int GetDay() const = 0;

    //* Month query
    // Returns the month number.
  virtual int GetMonth() const = 0;

    //* Year query
    // Returns the year number.
  virtual int GetYear() const = 0;

    //* Date query
    // Returns the date in floating point format.
  float GetDate() const
  {
    return (float)PSUtil::DateToDouble(GetDay(), GetMonth(), GetYear());
  }

  bool operator >= (const ResStep *t2)
  {
    return GetNumberOfDays() >= t2->GetNumberOfDays();
    /*
    return GetYear() > t2->GetYear() ||
           (GetYear() == t2->GetYear() && 
            (GetMonth() > t2->GetMonth() ||
             (GetMonth() == t2->GetMonth() && GetDay() >= t2->GetDay())));
    */
  }
private:
  int m_number;
};

#endif

