#ifndef _TIMEMANAGER_H
#define _TIMEMANAGER_H

#include "defines.h"
#include <uso/clock.h>

class AUTOCAM_API TimeManager
{
private:
   bool m_running;
   bool m_paused;
   double m_timepassed;
   double m_speed;
   double m_lasttime;
   USOClock m_clock;

public:
   TimeManager(){m_speed=1.0f;m_timepassed=0.0f;m_lasttime=0;m_running=false;m_paused=false;};
   ~TimeManager(){};

   void SetTime(double time); // define um novo tempo
   double GetTime();   // retorna o tempo total
   double Start();     // recomeça o tempo ou despausa o tempo
   double Start(double reference);  // recomeça o tempo ou despausa o tempo
   double Pause();     // pausa
   double Resume();    // reinicia
   double Stop();      // para o tempo
   double GetElapsedTime();
   void SetSpeed(double speed);
   double GetSpeed(){return m_speed;};
   bool IsRunning(){return m_running;};
   bool IsPaused(){return m_paused;};
};

#endif
