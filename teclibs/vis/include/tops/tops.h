/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 - W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef _TOPS_H
#define _TOPS_H

#include "defines.h"

#include "model.h"
#include "multimodel.h"
#include "elem/concretet3.h"
#include "elem/concretet6.h"
#include "elem/concreteq4.h"
#include "elem/concreteq8.h"
#include "elem/concretetet4.h"
#include "elem/concretetet10.h"
#include "elem/concretehex8.h"
#include "elem/concretehex8_reserv.h"
#include "elem/concretehex8_sreserv.h"
#include "elem/concretehex20.h"
#include "elem/concretewedge15.h"
#include "elem/concretewedge6.h"
#include "elem/concreteinf2e2.h"
#include "elem/concreteinf2e3.h"
#include "elem/concreteinf2v2.h"
#include "elem/concreteinf3q4.h"
#include "elem/concreteinf3q8.h"
#include "elem/concreteq9.h"

#include "elem/concretecoh2e2.h"
#include "elem/concretecoh2e3.h"
#include "elem/concretecoh3q4.h"
#include "elem/concretecoh3q8.h"
#include "elem/concretecoh3t3.h"
#include "elem/concretecoh3t6.h"

#include "elem/concretepoly2d.h"
#include "elem/concreteline2.h"
#endif
