/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * metis.h
 *
 * This file includes all necessary header files
 *
 * Started 8/27/94
 * George
 *
 */


#include <stdio.h>
#ifdef __STDC__
#include <stdlib.h>
#else
#include <malloc.h>
#include <stdlib.h>
#endif
#ifndef WIN32
#include <strings.h>
#endif
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>

#ifdef DMALLOC
#include <dmalloc.h>
#endif

#include <defs.h>
#include <struct.h>
#include <macros.h>
#include <rename.h>
#include <proto.h>

