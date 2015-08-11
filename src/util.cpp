// -------------------------------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/util.cpp $
// $Revision: 933 $
// $Date: 2011-11-16 18:40:42 -0200 (qua, 16 nov 2011) $
//
// $Author: thyago $
// -------------------------------------------------------------------------------------------------

#ifdef _WIN32
#include <windows.h>
#endif

#include "float.h"

#include "vgl\camera.h"

#include "util.h"

#include <list>
#include <set>
#include <string>
#include <vector>

#ifdef _WIN32
 #include <windows.h> 
 #include <direct.h>      
 #include <htmlhelp.h>
 #include <process.h>
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

using std::list;
using std::set;
using std::string;
using std::vector;
//using std::map;

#define HLSMAX 240.0f
#define RGBMAX 255.0f

#define   MTOL  1.0e-10
#define   TOL   1.0e-08

// Orthonormal base for extrusion calc.
//static void CalcVecBase(cCoord<real>& e1, cCoord<real>& e2, cCoord<real>& e3, real beta = 0.0f, bool useBeta = false);

////--------------------------------------------------------------------------------------------------
////--------------------------------------------------------------------------------------------------
//// Permite a escolha de arquivos a serem abertos.
//int fileDlgExt( char* title, char* type, char* ext, char* file, char* filename)
//{
// Ihandle *file_dlg  = NULL;
// int status = -1;
// int filternumber;
//
// file_dlg = IupFileDlg();
//
// IupSetAttribute( file_dlg, IUP_FILE,       file   );
// IupSetAttribute( file_dlg, IUP_TITLE,      title  );
// IupSetAttribute( file_dlg, IUP_EXTFILTER,  ext    );
// IupSetAttribute( file_dlg, IUP_DIALOGTYPE, type   );
//
// IupPopup( file_dlg, IUP_CURRENT, IUP_CURRENT );
//
// status = IupGetInt( file_dlg, IUP_STATUS );
// filternumber = IupGetInt( file_dlg, IUP_FILTERUSED );
//  
// if( status >= 0 )
//  strcpy( filename, IupGetAttribute( file_dlg, IUP_VALUE ) );
//
// IupDestroy( file_dlg );
//
// if( status >= 0 )
//  return filternumber;
// else
//  return 0;
//}
//
////--------------------------------------------------------------------------------------------------
////--------------------------------------------------------------------------------------------------
//bool FileDialog(string type, string title, string filter, string& name)
//{
//  Ihandle* h = IupFileDlg();
//
//  IupSetAttribute(h, IUP_DIALOGTYPE, (char*)type.c_str());
//  IupSetAttribute(h, IUP_TITLE, (char*)title.c_str());
//  IupSetAttribute(h, IUP_FILTER, (char*)filter.c_str());
//  IupSetAttribute(h, IUP_NOCHANGEDIR, IUP_YES);
//  IupPopup(h, IUP_CENTER, IUP_CENTER);
//
//  if(IupGetInt(h, IUP_STATUS) != -1)
//  {
//    name = IupGetAttribute(h, IUP_VALUE);
//    return true;
//  }
//  return false;
//}

#define SMALL_NUM  0.00000001 // anything that avoids division overflow
// dot product (3D) which allows vector operations in arguments
#define dot(u,v)   ((u).x * (v).x + (u).y * (v).y + (u).z * (v).z)
// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int intersect_ray_triangle( const AlgVector &ray_ori, const AlgVector &ray_dest, 
                            const AlgVector v0, const AlgVector &v1, const AlgVector &v2, 
                            AlgVector *I)
{
    AlgVector u, v, n; // triangle vectors
    AlgVector dir, w0, w; // ray vectors
    float r, a, b; // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = v1 - v0;
    v = v2 - v0;
    n = u.Cross(v);//u * v;             // cross product
    if (n == AlgVector(0,0,0))            // triangle is degenerate
      return -1;                 // do not deal with this case

    dir = ray_dest - ray_ori;             // ray direction vector
    w0 = ray_ori - v0;

    a = -dot(n, w0);
    b = dot(n, dir);
    if (fabs(b) < SMALL_NUM)       // ray is parallel to triangle plane
    {     
      if (a == 0)                // ray lies in triangle plane
        return 2;
      else return 0;             // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                   // ray goes away from triangle
        return 0;                  // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    *I = ray_ori + r * dir;           // intersect point of ray and plane

    // is I inside T?
    float    uu, uv, vv, wu, wv, D;
    uu = dot(u,u);
    uv = dot(u,v);
    vv = dot(v,v);
    w = *I - v0;
    wu = dot(w,u);
    wv = dot(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    float s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)        // I is outside T
      return 0;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
      return 0;

    return 1;                      // I is in T
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void createNewRGB(float &r, float &g, float &b, int mode) 
{
  if(mode == 1)
  {
    r = 1.0f - r;
    g = 1.0f - g;
  }
  else if(mode == 2)
  {
    r = 1.0f - r;
    g = 1.0f - g;
    b = 1.0f - b;
  }
  else if(mode == 3)
  {
    r = g;
    g = 1.0f - r;
    b = 1.0f - b;
  }
  else if(mode == 4)
  {
    float h, l, s;
    r *= 255.0f;
    g *= 255.0f;
    b *= 255.0f;

    rgb_to_hls(r, g, b, h, l, s);

    if(s < 150.0f)
    {
      if(l < 150.0f)
        l = 240.0f;
      else
        l = 0.0;
    }
    else
    {
      h += 120.0f;

      if(h > 240.0f)
        h -= 240.0f;

      l = 240.0f - l;
    }

    s = 240.0f;

    hls_to_rgb(h, l, s, r, g, b);

    r /= 255.0f;
    g /= 255.0f;
    b /= 255.0f;
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void newRandomRGB(float &r, float &g, float &b)
{
  r = ((float)rand() / ((float)(RAND_MAX)+(float)(1)));
  g = ((float)rand() / ((float)(RAND_MAX)+(float)(1)));
  b = ((float)rand() / ((float)(RAND_MAX)+(float)(1)));
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
string get_file_name(string fullpath)
{
  string project;

#ifdef _WIN32
  string::size_type pos = fullpath.rfind('\\');
#else
  string::size_type pos = fullpath.rfind('/');
#endif

  string::size_type len = fullpath.size() - pos;
  if(pos != string::npos)
    project.assign(fullpath, pos + 1, len);
  else
    project.assign(fullpath, 0, len);

  return project;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void createNewRGBCurrentColor(float &r, float &g, float &b,int mode)
{
 float color[4], clear_color[4];
 glGetFloatv(GL_CURRENT_COLOR, color);
 glGetFloatv(GL_COLOR_CLEAR_VALUE, clear_color);

 r = (float)(color[0] + clear_color[0]) / 2.0f;
 g = (float)(color[1] + clear_color[1]) / 2.0f;
 b = (float)(color[2] + clear_color[2]) / 2.0f;
 
 if(mode == 1)
 {
  r = 1.0f - r;
  g = 1.0f - g;
 }
 else if(mode == 2)
 {
  r = 1.0f - r;
  g = 1.0f - g;
  b = 1.0f - b;
 }
 else if(mode == 3)
 {
  r = g;
  g = 1.0f - r;
  b = 1.0f - b;
 }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void rgb_to_hls(float r, float g, float b, float &h, float &l, float &s)
{
 float cMax = max(r, max(g, b));
 float cMin = min(r, min(g,b));
 float Rdelta, Gdelta, Bdelta;

 l = ((cMax + cMin)*HLSMAX + RGBMAX) / (RGBMAX * 2.0f); 

 if(cMax == cMin)
 {
  s = 0.0;
  h = HLSMAX*2/3;
 }
 else
 {
  /* saturation */ 
  if(l <= 0.5*HLSMAX)
   s = ( ((cMax-cMin)*HLSMAX) + ((cMax+cMin)/2.0f) ) / (cMax+cMin);
  else
   s = ( ((cMax-cMin)*HLSMAX) + ((2.0f*RGBMAX-cMax-cMin)/2.0f) ) / (2.0f*RGBMAX-cMax-cMin);

  /* hue */ 
  Rdelta = ( ((cMax-r)*(HLSMAX/6.0f)) + ((cMax-cMin)/2.0f) ) / (cMax-cMin);
  Gdelta = ( ((cMax-g)*(HLSMAX/6.0f)) + ((cMax-cMin)/2.0f) ) / (cMax-cMin);
  Bdelta = ( ((cMax-b)*(HLSMAX/6.0f)) + ((cMax-cMin)/2.0f) ) / (cMax-cMin);

  if (r == cMax)
   h = Bdelta - Gdelta;
  else if (g == cMax)
   h = (HLSMAX/3) + Rdelta - Bdelta;
  else /* B == cMax */ 
   h = ((2*HLSMAX)/3) + Gdelta - Rdelta;

  if (h < 0)
   h += HLSMAX;
  if (h > HLSMAX)
   h -= HLSMAX;
 }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
float hue_to_rgb(float n1, float n2, float hue)
{
 /* range check: note values passed add/subtract thirds of range */ 
 if (hue < 0)
  hue += HLSMAX;
 
 if (hue > HLSMAX)
  hue -= HLSMAX;

 /* return r,g, or b value from this tridrant */ 
 if (hue < (HLSMAX/6))
  return ( n1 + (((n2-n1)*hue+(HLSMAX/12))/(HLSMAX/6)) );
 if (hue < (HLSMAX/2))
  return ( n2 );
 if (hue < ((HLSMAX*2)/3))
  return ( n1 + (((n2-n1)*(((HLSMAX*2)/3)-hue)+(HLSMAX/12))/(HLSMAX/6)));
 else
  return ( n1 );
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void hls_to_rgb(float h, float l, float s, float &r, float &g, float &b)
{
 float Magic1, Magic2;

 if (s == 0) /* achromatic case */ 
 {
  r = g = b = (l*RGBMAX)/HLSMAX;
 }
 else  /* chromatic case */ 
 {
  /* set up magic numbers */ 
  if (l <= (HLSMAX*0.5))
   Magic2 = (l*(HLSMAX + s) + (HLSMAX*0.5f))/HLSMAX;
  else
   Magic2 = l + s - ((l*s) + (HLSMAX*0.5f))/HLSMAX;
  
  Magic1 = 2*l-Magic2;
  
  /* get RGB, change units from HLSMAX to RGBMAX */ 
  r = (hue_to_rgb(Magic1,Magic2,h+(HLSMAX/3))*RGBMAX + (HLSMAX/2))/HLSMAX;
  g = (hue_to_rgb(Magic1,Magic2,h)*RGBMAX + (HLSMAX/2)) / HLSMAX;
  b = (hue_to_rgb(Magic1,Magic2,h-(HLSMAX/3))*RGBMAX + (HLSMAX/2))/HLSMAX;
 }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void generate_select_color(float &r, float &g, float &b)
{
 float h, l, s;
 r*=255.0f;
 g*=255.0f;
 b*=255.0f;

 rgb_to_hls(r, g, b, h, l, s);
 l *= 1.8f;
 if(l > 240.0)
  l = 240.0f;
 hls_to_rgb(h, l, s, r, g, b);

 r/=255.0f;
 g/=255.0f;
 b/=255.0f;
}