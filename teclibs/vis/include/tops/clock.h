/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 -W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/
#ifndef _TOP_CLOCK_H
#define _TOP_CLOCK_H

#include "defines.h"

class TopModel;

class TOPS_API TopClock
{
public:
  static unsigned int Advance();
  static unsigned int GetInitTime();
  static unsigned int GetCurrTime();
  static void AddModel(TopModel* m);
  static void RemModel(TopModel* m);
};

#endif
