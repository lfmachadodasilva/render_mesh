// kinematics.h

#ifndef kinematics_h
#define kinematics_h

#include "ds/array.h"
#include "defines.h"

class PATH_API CamKinematics
{
  struct Segment {
		float s;
		float t;
		float saccum;
		float taccum;
		float v;
		float v0, v1;
		float sa, sb;
		float aa, ab;
		Segment () {}
		Segment (float ps, float ts)
		: s(ps), t(ts)
		{
		}
	};
	float m_alpha;
	DsArray<Segment> m_segs;
public:
	CamKinematics (float alpha)
  : m_alpha(alpha)
	{
	}
	~CamKinematics ()
	{
	}
	void AddSegment (float s, float t);
	int GetNSegments ();
	void SetDistance (int i, float s);
	void SetTime (int i, float t);
	void ComputeParameters ();
	void Debug (const char* label=0);
	float GetTotalTime ();
  float GetKnotTime (int i);
	void GetDisplacement (float t, int* idx, float* s, float* saccum);
};

#endif
