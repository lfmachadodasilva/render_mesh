/*
 * Copyright 2003 Sandia Corporation.
 * Under the terms of Contract DE-AC04-94AL85000, there is a non-exclusive
 * license for use of this work by or on behalf of the
 * U.S. Government. Redistribution and use in source and binary forms, with
 * or without modification, are permitted provided that this Notice and any
 * statement of authorship are reproduced on all copies.
 */

#ifndef _PSI_GAMMA_H
#define _PSI_GAMMA_H

#include <topsview/defines.h>

#define PSI_GAMMA_SIZE 512
#define PSI_GAMMA_PATH "../../../src/topsview/renderer/cg"
#define PSI_GAMMA_FILENAME PSI_GAMMA_PATH"/PsiGammaTable512.txt"

#define PSI_GAMMA_LOOKUP(gamma_back, gamma_front)			\
    PsiGammaTable[((int)((gamma_front)*PSI_GAMMA_SIZE))*PSI_GAMMA_SIZE + \
		  (int)((gamma_back)*PSI_GAMMA_SIZE)]

#define PSI_LOOKUP(taud_back, taud_front)				\
    PSI_GAMMA_LOOKUP((taud_back)/((taud_back+1)),(taud_front/((taud_front)+1)))

// Must be called once, at the beginning of the program.
TPV_API void PsiGammaInitTable(const char* filename=PSI_GAMMA_FILENAME, int size=PSI_GAMMA_SIZE);

TPV_API const float* PsiGammaGetTable();

#endif

