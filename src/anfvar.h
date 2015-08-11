// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2011.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_ANFVAR_H
#define ANFLEX_INTERFACE_ANFVAR_H

// C/C++ libraries
#include <vector>
using std::vector;
// Enf of C/C++ libraries

#include "canvas\canvas-main.h"
#include "render\shader.h"

#include "model.h"
#include "util.h"
#include "fps.h"

#include "vrbv\node.h"

struct sAccelerationRender;
class cRenderPick;

#ifdef _ANFLEX_

sAccelerationRender *g_accel_render = NULL;

cModel *g_model = NULL;

cRenderAtt *g_render_att = NULL;

cCanvasMain *g_canvas_main = NULL;

cCanvasMain *g_canvas_obj = NULL;

cFPS *g_fps = NULL;

cShader *g_shader = NULL;

cShader *g_shader2 = NULL;

vector<cRenderPick *> g_vec_selected;

cRenderPick *g_last_focus = NULL;

#else

extern sAccelerationRender *g_accel_render;

extern cModel *g_model;

extern cRenderAtt *g_render_att;

extern cCanvasMain *g_canvas_main;

extern cCanvasMain *g_canvas_obj;

extern cFPS *g_fps;

extern cShader *g_shader;

extern cShader *g_shader2;

extern vector<cRenderPick *> g_vec_selected;

extern cRenderPick *g_last_focus;

#endif

#endif // ANFLEX_INTERFACE_ANFVAR_H