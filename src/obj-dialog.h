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

#ifndef ANFLEX_INTERFACE_OBJ_DIALOG_H
#define ANFLEX_INTERFACE_OBJ_DIALOG_H

#include "string"
using std::string;

#include "canvas\box.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>

#define CANVAS_OBJ "canvas_obj"

class cObjDialog
{
private:

  sBox m_bbox;

  // handle
  Ihandle *m_dg;

  Ihandle* create_dialog(void);
  void set_callbacks(void);
  void init_dialog(void);

  void create_object(string filename);
  bool create_scene(void);

protected:

public:

  /**
	* @brief Constructor
	*/
	cObjDialog(void);

	/**
	* @brief Destructor
	*/
	~cObjDialog(void);

	/**
	* @brief Show dialog
	*/
	void show_dialog(void);
};

#endif // ANFLEX_INTERFACE_OBJ_DIALOG_H