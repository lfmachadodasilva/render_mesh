// -------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/bmp.h $
// $Revision: 8 $
// $Date: 2009-07-10 17:24:28 -0300 (sex, 10 jul 2009) $
//
// $Author: fred $
// -------------------------------------------------------------------------------

/*
 %M Read and write BitMaP format.
 %d We assume 8 or 24 bits per pixel only.
 24-bit image means true color, and
 8-bit image means gray scale true-color.
*/

#ifndef _BMP_H
#define _BMP_H

int bmpWrite(char *filename, unsigned int width, int unsigned height,
             unsigned int nbits, unsigned char *pixels);

unsigned char* bmpRead(char *filename, unsigned int* width, unsigned int* height,
                       unsigned int* nbits, unsigned int* rowsize);

#endif
