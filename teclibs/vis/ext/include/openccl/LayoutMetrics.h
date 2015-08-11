/******************************************************************************\

  Copyright 2005 The University of North Carolina at Chapel Hill.
  All Rights Reserved.

  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies. Any use in a commercial organization requires a separate license.

  IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL BE LIABLE
  TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
  DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS SOFTWARE AND
  ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA HAVE BEEN
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.


  Permission to use, copy, modify and distribute this software and its
  documentation for educational, research and non-profit purposes, without
  fee, and without a written agreement is hereby granted, provided that the
  above copyright notice and the following three paragraphs appear in all
  copies.

  THE UNIVERSITY OF NORTH CAROLINA SPECIFICALLY DISCLAIM ANY WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
  FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN
  "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA HAS NO OBLIGATION TO
  PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


   ---------------------------------
  |Please send all BUG REPORTS to:  |
  |                                 |
  |   sungeui@cs.unc.edu            |
  |                                 |
   ---------------------------------


  The authors may be contacted via:

  US Mail:         Sung-Eui Yoon or Dinesh Manocha
                       Department of Computer Science
                       Sitterson Hall, CB #3175
                       University of North Carolina
                       Chapel Hill, NC 27599-3175

\*****************************************************************************/






// Programmer: Sung-Eui Yoon (Dec-26, 2004)
#ifndef _Layout_Metrics_
#define _Layout_Metrics_


/*
Usage:

	CMetrics COMetric;

	COMetric.InitOrdering ();
	
	COMetric.AddOrdering ();	// 1st ordering	
	COMetric.AddOrdering ();	// 2nd ordering	

	int Result = COMetric.GetBestOrdering ();	// return 1 or 2 in this case


	// reuse this class call InitOrdering and continue same job.	
	COMetric.InitOrdering ();

	COMetric.AddOrdering ();	// 1st ordering	
	.....

*/


#include <map>
using namespace std;

namespace OpenCCL 
{

// ---------------------------------------------------------------------
struct ltstr_map
{
	bool operator () (const unsigned int a, const unsigned int b) const
	{
		return a < b; 
	}
};

// CHyperPlane is a sorted as edge length. Each edge length has its counts of occurrence.
typedef map <const unsigned int, int, ltstr_map> CHyperPlane;
// ------------------------------------------------------------




class CMetrics
{
	bool m_bMetricType;		// true --> cache-oblivious
					// false -> cache-aware

	CHyperPlane m_hpBestOrdering;	// Best or initial ordering
	int m_NumAddedOrdering;
	int m_BestOrdering;

	float PerformCOMetric (CHyperPlane & HyperPlane);	// cache-oblvious metric
	void InitOrdering (int NumEdgeLengths, int * EdgeLengths);

public:
	CMetrics (void);
	void InitOrdering (void);	// clean records of AddOrdering	
	int AddOrdering (int NumEdgeLengths, int * EdgeLengths);
	int GetBestOrdering (void);	// return the best ordering among added orderings.



	
};



}	// end of namespace
#endif


