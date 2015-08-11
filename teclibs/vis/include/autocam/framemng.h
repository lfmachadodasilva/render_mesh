#ifndef _AUTOCAM_FRAMEMANAGER_H
#define _AUTOCAM_FRAMEMANAGER_H

#include "defines.h"

class AUTOCAM_API ACFrameManager
{
   bool m_running;
   bool m_paused;
   int m_frame;
   int m_lastframe;
   int m_ref;
   double m_temp;
   double m_speed;

public:
   ACFrameManager();
   virtual ~ACFrameManager(){};

   /** Set current frame. */
   void SetFrame(int frame);

   /** Return furrent frame. */
   int GetFrame(){return m_frame+m_ref;};

   /** Update frame counter. */
   void Update();

   /** Start frame counter.
   * The counter is restarted if the counter is running. The paused state is kept. 
   */
   int Start(int reference);
   int Start();

   /** Pause frame counter.
   * If counter is already paused or isn't running, nothing happens
   */
   int Pause();

   /** Resume frame counter.
   * If frame counter is running or isn't paused nothing happens
   */
   int Resume();

   /** Stop frame counter. */
   int Stop();

   /** Get number of frames elapsed beetween the last updates */
   int GetElapsedFrame(){return m_frame-m_lastframe;};

   void SetSpeed(double speed){m_speed = speed;};
   double GetSpeed(){return m_speed;};
   
   bool IsRunning(){return m_running;};
   bool IsPaused(){return m_paused;};
};

#endif
