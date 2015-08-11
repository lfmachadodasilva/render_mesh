/*
 * $Id: interactapi.h,v 1.1 2004/01/22 18:32:05 joaoluiz Exp $
 * (C) COPYRIGHT 2004, Tecgraf/PUC-Rio.
 * All Rights Reserved
 * Duplication of this program or any part thereof without the express
 * written consent of the author is prohibited
 */

/**
 * @file interactapi.h
 * @author Joao Luiz Elias Campos.
 * @date January 22, 2004
 */

#ifndef __interactapi_h
#define __interactapi_h

#define INTERACT_VERSION   "2.3.0"
#define INTERACT_COPYRIGHT "Copyright (C) 1996-2004 Tecgraf/PUC-Rio"

#if !defined(INTERACT_API)
# if defined(WIN32) && defined(USE_DLL)
#  if defined(INTERACT_MAKE_DLL)
#   define INTERACT_API __declspec(dllexport)
#  else
#   define INTERACT_API __declspec(dllimport)
#  endif
# else
#  define INTERACT_API
# endif
#endif

#endif


