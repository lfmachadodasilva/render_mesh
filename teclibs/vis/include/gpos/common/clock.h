//* clock.h
// Time measure (Win32/UNIX)
// Tecgraf/PUC-Rio
// Jan 2004

#ifndef ps_clock_h
#define ps_clock_h

#define PS_CLOCK_MAX_SLOTS 256

//* 'PSClock' Class
// Simple time measure
class PSClock
{
private:
  static double m_ct[PS_CLOCK_MAX_SLOTS];
  static int m_n;

  static double ctime(void);

public:
    //* New timer request
    // Returns timer id , -1 if there are no more timers available.
  static int NewID(void);

    //* Timer start
    // Starts given timer
  static void Start(int id);

    //* Timer query
    // Returns the number of seconds elapsed in given timer
    // since last start.
    // Returns -1 if the given timer is stopped.
  static double Time(int id);

    //* Timer stop
    // Stops given timer
    // Returns the number of seconds elapsed in given timer
    // sice last start.
    // Returns -1 if the given timer is stopped.
  static double Stop(int id);
};

#endif
