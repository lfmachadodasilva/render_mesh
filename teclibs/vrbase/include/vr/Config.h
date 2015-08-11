/*
 * vrbase
 * Copyright 2007-2009 CENPES/Petrobras Tecgraf/PUC-Rio
 */

#ifndef _VR_CONFIG_H_
#define _VR_CONFIG_H_

// Equivalent to sizeof(void*)
#define VR_POINTER_SIZE 8

// Possible values for VR_BYTE_ORDER:
#define VR_BIG_ENDIAN 		1
#define VR_LITTLE_ENDIAN 	2

// Detected byte order for this platform:
#define VR_BYTE_ORDER	VR_LITTLE_ENDIAN

// Sanity check all settings:
#if VR_POINTER_SIZE != 4 && VR_POINTER_SIZE != 8 && \
	VR_BYTE_ORDER != VR_BIG_ENDIAN && VR_BYTE_ORDER != VR_LITTLE_ENDIAN
	#error vrbase was not properly configured.
#endif

#endif
