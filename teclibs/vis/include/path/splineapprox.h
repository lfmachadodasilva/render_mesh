// splineapprox.h
// Approximate a spline by a corresponding polyline
// Aug 2006

#ifndef splineapprox_h
#define splineapprox_h

#include "ds/array.h"
#include "alg/spline.h"
#include "defines.h"

class PATH_API CamSplineApprox
{
	struct Pair {
		float s;
		float t;
	};
	struct Seg {
		DsArray<Pair> v;
		float len;
		float laccum;
		int last;
		Seg () : last(1) { }
    void operator = (Seg &b)
    {
      this->len = b.len;
      this->laccum = b.laccum;
      this->last = b.last;
      int bsize = b.v.Size();
      this->v.Resize(bsize);
      for (int i=0; i<bsize; i++)
        this->v[i] = b.v[i];
    }
	};
	int m_ndiscr;
	AlgSpline* m_spl;
	DsArray<Seg> m_seg;
	int m_slast;
public:
  CamSplineApprox (AlgSpline* spl, int n=100);
	~CamSplineApprox ();
	void Recompute ();
	int GetNSegments ();
  float GetTotalLength ();
	float GetLength (int iseg);
	float GetParameter (float s);
};

#endif
