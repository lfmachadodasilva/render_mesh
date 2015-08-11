// ------------------------------------------------------------------------
// Anflex Project -- Tecgraf/PUC-Rio
// www.tecgraf.puc-rio.br
//
// $HeadURL: https://subversion.tecgraf.puc-rio.br/svn/anflex-interface/trunk/src/util.h $
// $Revision: 556 $
// $Date: 2011-02-23 19:09:46 -0300 (qua, 23 fev 2011) $
//
// $Author: thyago $
// ------------------------------------------------------------------------


#ifndef ANFLEX_INTERFACE_UTIL_H
#define ANFLEX_INTERFACE_UTIL_H

#include <string>
#include <list>
using std::string;
using std::list;

#include <GL/glew.h>
#include <GL/glut.h>

// Library vis
#include "alg\matrix.h"
#include "alg\vector.h"

class VglCamera;

struct sLightAtt
{
  GLfloat position_light[4];
  GLfloat ambient_light[4];
  GLfloat diffuse_light[4];
  GLfloat specular_light[4];
  GLfloat As[4];
};

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
// Cria um dialogo para abrir/salvar arquivo
//int fileDlgExt( char* title, char* type, char* ext, char* file, char* filename);

char* TrimString(char *s);
void RemoveTraillingChars(string &s);

//bool FileDialog(string type, string title, string filter, string& name);

void createNewRGB(float &r, float &g, float &b, int mode = 1);
void createNewRGBCurrentColor(float &r, float &g, float &b, int mode = 1);

void rgb_to_hls(float r, float g, float b, float &h, float &l, float &s);
void hls_to_rgb(float h, float l, float s, float &r, float &g, float &b);
void generate_select_color(float &r, float &g, float &b);

void newRandomRGB(float &r, float &g, float &b);

string get_file_name(string fullpath);

int intersect_ray_triangle( const AlgVector &ray_ori, const AlgVector &ray_dest, 
                            const AlgVector v0, const AlgVector &v1, const AlgVector &v2, 
                            AlgVector *I);


#endif

