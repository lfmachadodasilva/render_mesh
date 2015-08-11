// -------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/bmp.cpp $
// $Revision: 533 $
// $Date: 2011-02-11 16:18:11 -0200 (sex, 11 fev 2011) $
//
// $Author: lduarte $
// -------------------------------------------------------------------------------

/*
 %M Read and write BitMaP format.
 %d We assume 8 or 24 bits per pixel only.
 24-bit image means true color, and
 8-bit image means gray scale true-color.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

/* %F Write 2-byte number: LSB first format */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static unsigned int bmpWrite2Bytes (FILE *fp, unsigned int v)
{
 unsigned char c[2];
 c[0] = v;
 c[1] = (v>>8);
 fwrite(&c,1,2,fp);
 return v;
}

/* %F Write 4-byte number: LSB first format */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static unsigned int bmpWrite4Bytes (FILE *fp, unsigned int v)
{
 unsigned char c[4];
 c[0] = v;
 c[1] = (v>>8);
 c[2] = (v>>16);
 c[3] = (v>>24);
 fwrite(&c,1,4,fp);
 return v;
}

/* %F Reverse RGB order: RGB <-> BGR */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static void reverseRGB (int n, unsigned char *pixels)
{
 int i;
 unsigned char *rgb;
 for (i=0; i<n; i++)
 {
  unsigned char t;
  rgb = pixels+(i*3);
  t = rgb[0]; rgb[0] = rgb[2]; rgb[2] = t; 
 } 
}

/* %F Write gray scale palette. */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static void bmpWritePalette (FILE *fp)
{
 int i;
 unsigned char color=0;
 unsigned char zero=0;
 for (i=0; i<256; i++)
 {
  fwrite(&color,1,1,fp);
  fwrite(&color,1,1,fp);
  fwrite(&color,1,1,fp);
  fwrite(&zero,1,1,fp);
  color++;
 }
}

/* 
 %F Write BMP format.
 %n Image row must be aligned to 32-bits.
 %o 1 on success, 0 on error.
*/
// --------------------------------------------------------------------
// --------------------------------------------------------------------
int bmpWrite(char *filename, unsigned int width, int unsigned height,
             unsigned int nbits, unsigned char *pixels)
{
 int offset = nbits == 24 ? 54 : (256*4) /* palette */ + 54;
 int headersize = 40;
 int rowsize = (width*nbits)%32 == 0 ? 
               (width*nbits)/32*4 : ((width*nbits)/32+1)*4;
 int imgsize = rowsize*height;
 int filesize = offset + imgsize;
 int zero = 0;
 int nplanes = 1;
 int compression = 0;
 int resolution = 2925;
 FILE* fp = fopen(filename,"wb");
 if (fp == NULL)
  return 0;
 fwrite("BM",1,2,fp);
 bmpWrite4Bytes(fp,filesize);
 bmpWrite4Bytes(fp,zero);
 bmpWrite4Bytes(fp,offset);
 bmpWrite4Bytes(fp,headersize);
 bmpWrite4Bytes(fp,width);
 bmpWrite4Bytes(fp,height);
 bmpWrite2Bytes(fp,nplanes);
 bmpWrite2Bytes(fp,nbits);
 bmpWrite4Bytes(fp,compression);
 bmpWrite4Bytes(fp,imgsize);
 bmpWrite4Bytes(fp,resolution);
 bmpWrite4Bytes(fp,resolution);
 bmpWrite4Bytes(fp,zero);
 bmpWrite4Bytes(fp,zero);
 if (nbits==24)
  reverseRGB(imgsize/3,pixels);
 else
  bmpWritePalette(fp);
 fwrite(pixels,1,imgsize,fp);
 if (nbits==24)
  reverseRGB(imgsize/3,pixels);
 fclose(fp);
 return 1;  
}

/* %F Report reading error. */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static void* bmpError (char *s)
{
 fprintf(stderr,"bmp: %s\n",s);
 return NULL;
}

/* %F Read 2-byte number: LSB first format */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static unsigned int bmpRead2Bytes (FILE *fp)
{
 unsigned char c[2];
 unsigned int v = 0;
 fread(&c,1,2,fp);
 v = c[0]+
     ((unsigned int)c[1]<<8);
 return v;
}

/* %F Read 4-byte number: LSB first format */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static unsigned int bmpRead4Bytes (FILE *fp)
{
 unsigned char c[4];
 unsigned int v = 0;
 fread(&c,1,4,fp);
 v = c[0]+
     ((unsigned int)c[1]<<8)+
     ((unsigned int)c[2]<<16)+
     ((unsigned int)c[3]<<24);
 return v;
}

/* %F Read palette: actually, skip it, considering it is gray scaled. */
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
static unsigned char* bmpReadPalette (FILE *fp, int palettesize)
{
 static unsigned char palette[256];
 char red, green, blue, zero;
 int i;
 for (i=0; i<palettesize/4; i++)
 {
  fread(&red,1,1,fp); 
  fread(&green,1,1,fp); 
  fread(&blue,1,1,fp); 
  fread(&zero,1,1,fp);
  if (red != green || red != blue)
   return (unsigned char*)bmpError("invalid palette values");
  palette[i] = red;
 }
 return palette;
}

/*
 %F Read BMP format.
 %n As assured by the BMP format, image row will be aligned to 32-bits.
 %o Reads width, height, and nbits, and returns an allocated 32-bits-row 
 aligned image. It returns NULL on error.
*/
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
unsigned char* bmpRead(char *filename, unsigned int* width, unsigned int* height,
                       unsigned int* nbits, unsigned int* rowsize)
{
 unsigned char *pixels;
 unsigned char *palette;
 char filetype[2];
 unsigned int filesize;
 unsigned int imgsize;
 unsigned int zero;
 unsigned int offset;
 unsigned int headersize;
 unsigned int nplanes;
 unsigned int compression;
 unsigned int resolution;
 FILE* fp = fopen(filename,"rb");
 if (fp == NULL)
  return NULL;
 fread(filetype,1,2,fp);
 if (filetype[0] != 'B' || filetype[1] != 'M')
  return (unsigned char*)bmpError("Not a BMP file");
 filesize = bmpRead4Bytes(fp);
 zero = bmpRead4Bytes(fp);
 offset = bmpRead4Bytes(fp);
 headersize = bmpRead4Bytes(fp);
 *width = bmpRead4Bytes(fp);
 *height = bmpRead4Bytes(fp);
 nplanes = bmpRead2Bytes(fp);
 *nbits = bmpRead2Bytes(fp);
 if (*nbits != 24 && *nbits != 8)
  return (unsigned char*)bmpError("Must have 8 or 24 bits per pixel");
 compression = bmpRead4Bytes(fp);

 imgsize = bmpRead4Bytes(fp);
 imgsize = ((*width) * (*nbits) + 7) / 8 * abs((int)(*height));
 
 pixels = (unsigned char*)malloc(imgsize);
 if (pixels == NULL)
  return (unsigned char*)bmpError("Could not allocate image.");
 resolution = bmpRead4Bytes(fp);
 resolution = bmpRead4Bytes(fp);
 zero = bmpRead4Bytes(fp);
 zero = bmpRead4Bytes(fp);
 palette = bmpReadPalette(fp,offset-54);
 fread(pixels,1,imgsize,fp);
 if (*nbits == 24)
  reverseRGB(imgsize/3,pixels);
 else
 {
  unsigned int i;
  for (i=0; i<imgsize; i++)
   pixels[i] = palette[pixels[i]];
 }
 fclose(fp);
 *rowsize = ((*width)*(*nbits))%32 == 0 ? 
            ((*width)*(*nbits))/32*4 : (((*width)*(*nbits))/32+1)*4;
 return pixels;
}
