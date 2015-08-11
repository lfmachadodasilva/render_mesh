// clock.h
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef USO_CLOCK_H
#define USO_CLOCK_H

#include <stdio.h>
#include "defines.h"

USO_API double uso_gettime (void);
USO_API void uso_sleep (double seconds);
USO_API void uso_getsplittime (double *oyears, double *odays=NULL, double *ohours=NULL, double *omins=NULL, double *oseconds=NULL);

class USO_API USOClock
{
  bool m_running;
  double m_ref;
  double m_time;
  double m_lastref;

public:
  USOClock ();

  bool   IsRunning() { return m_running; }
  double Start (double reference);
  double Start ();
  double Stop ();
  void   Pause ();
  double GetStartTime () const;
  double GetTime () const;
  double GetElapsedTime ();
};

#endif
