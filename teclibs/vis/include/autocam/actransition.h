#ifndef _AUTOCAM_TRANSITION_H
#define _AUTOCAM_TRANSITION_H

#include "defines.h"
#include <splib/splib.h>

#define AUTOCAM_TRANSITION_CUT      "AUTOCAM_TRANSITION_CUT"
#define AUTOCAM_TRANSITION_LINEAR   "AUTOCAM_TRANSITION_LINEAR"
#define AUTOCAM_TRANSITION_CUBIC    "AUTOCAM_TRANSITION_CUBIC"

#define AUTOCAM_CUT     0
#define AUTOCAM_LINEAR  1
#define AUTOCAM_CUBIC   2

class AUTOCAM_API ACTransition
{
public:
   ACTransition(){m_id = m_nextid; m_nextid++;};
   virtual ~ACTransition(){};

   virtual const char *ClassName() const = 0;
   virtual bool GetState(float s, AlgVector *pos, AlgQuatern *ori, Spline *spline, QSpline *qspline) = 0;

   int GetId(){return m_id;};

   bool Load(FILE *fp);
   bool Save(FILE *fp);
   void Save(UtlWriter *writer);

protected:
   static int m_nextid;
   int m_id;
};

class AUTOCAM_API ACTransitionCut : public ACTransition
{
public:
   ACTransitionCut():ACTransition(){};
   virtual const char *ClassName() const {return AUTOCAM_TRANSITION_CUT;};
   virtual ~ACTransitionCut(){};
   virtual bool GetState(float s, AlgVector *pos, AlgQuatern *ori, Spline *spline, QSpline *qspline);
};

class AUTOCAM_API ACTransitionLinear : public ACTransition
{
public:
   ACTransitionLinear():ACTransition(){};
   virtual ~ACTransitionLinear(){};
   virtual const char *ClassName() const {return AUTOCAM_TRANSITION_LINEAR;};
   virtual bool GetState(float s, AlgVector *pos, AlgQuatern *ori, Spline *spline, QSpline *qspline);
};

class AUTOCAM_API ACTransitionCubic : public ACTransition
{
public:
   ACTransitionCubic():ACTransition(){};
   virtual ~ACTransitionCubic(){};
   virtual const char *ClassName() const {return AUTOCAM_TRANSITION_CUBIC;};
   virtual bool GetState(float s, AlgVector *pos, AlgQuatern *ori, Spline *spline, QSpline *qspline);
};

#endif
