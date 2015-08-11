// ------------------------------------------------------------------------------------------------- 
// Anflex Project -- Tecgraf/PUC-Rio  CENPES/Petrobras 
// www.tecgraf.puc-rio.br 
// 
// Created by lfmachado in April/2012.
// 
// $URL: $ 
// $Revision: $ 
// $Date: $ 
// 
// $LastChangedBy: $ 
// -------------------------------------------------------------------------------------------------

#ifndef ANFLEX_INTERFACE_RENDER_H
#define ANFLEX_INTERFACE_RENDER_H

#include <vector>
#include <string>
using std::vector;
using std::string;

// Lib vis
#include "alg\matrix.h"

#include "vrbv\node.h"
#include "vdlib\frustumculler.h"

// Opengl
#include "GL\glew.h"

// Local
#include "canvas\box.h"

class cShader;
class cRenderAtt;
class cAppGauge;
class cTexture;

struct sVertex
{
  AlgVector v;
  AlgVector normal;
  float s, t;
};

struct sFace3v
{
  int v1, v2, v3;
};

class cRender
{
public:

  enum eAttType { FE_MESH_QUAD, FE_MESH_SPHERE, FE_MESH_POINT };

  enum eGeometryType { POINT = 1, LINE, TRIANGLE, };

  static bool m_new_render;

protected:
  /**
  * @brief Geometry type - eGeometryType
  */
  eGeometryType m_geometry_type;

  int m_num_geometries, m_num_vertex;

  GLuint *m_index;

  GLfloat *m_vertex,        // location = 0
          *m_texture_coord, // location = 1
          *m_normal,        // location = 2 
          *m_color;         // location = 3

  vector<GLuint> m_vec_vao_id; // Vertex Array Object

  GLuint m_vao_id, // Vertex Array Object
         m_ibo_id, // Index Buffer Object
         m_vbo_id; // Vertex Array Buffer

  /**
	* @brief Texture
	*/
  bool m_render_texture;
  GLuint m_texture_id;

  bool m_render_wireframe;

  sBox m_bbox;
          
  AlgMatrix m_transformation_matrix;

  vdlib::FrustumCuller *m_frustum_culler;
  vrbv::Node           *m_scene_root;

  cTexture *m_texture;

  // METHODS
protected:

  /*
  * @brief Constructor
  */
  cRender(void);

  /*
  * @brief Free array mesh
  */
  void m_free_mesh(void);

  /*
  * @brief Free buffers 
  */
  void m_free_buffer(void);

  /*
  * @brief Render using shader
  *
  * @param[in] shader
  * @param[in] render attribute
  */
  virtual void render_shader(const cShader *shader, const cRenderAtt *render_att) = 0;

  /*
  * @brief Render using old opengl
  *
  * @param[in] render attribute
  */
  virtual void render_old(const cRenderAtt *render_att) = 0;

public:

  // structs to help
  vector<sVertex> vecVertex;
  vector<sFace3v> vecTria;

  /*
  * @brief Destructor
  */
  virtual ~cRender(void);

  /*
  * @brief Create vertex array buffer and shader
  */
  bool create_vao_shader(const cShader *shader);
  bool create_vao_shader2(const cShader *shader);

  /*
  * @brief Main render
  *
  * @param[in] shader
  * @param[in] render attribute
  */
  virtual void render(const cShader *shader, const cRenderAtt *render_att) = 0;

  /*
  * @brief Get number of geometries (triangle or lines)
  *
  * @return number of geometries
  */
  int get_num_geometries(void) { return m_num_geometries; }

  /*
  * @brief Get number of vertex
  *
  * @return number of vertex
  */
  int get_num_vertex(void) { return m_num_vertex; }

  /*
  * @brief Get array of vertex coordinates
  *
  * @return array of vertex
  */
  GLfloat* get_vertex(void) { return m_vertex; }

  vrbv::Node* get_scene_root(void) { return m_scene_root; }

  vdlib::FrustumCuller* get_frustum_culler(void) { return m_frustum_culler; }

  // Transformations
  void reset_transformation(void) { m_transformation_matrix.Identity(); }
  AlgMatrix get_transformation(void) { return m_transformation_matrix; }
  const float* get_transformation(void) const { return m_transformation_matrix.GetMatrix(); }
  void add_translate(float &tx, float &ty, float &tz)
  { 
    m_transformation_matrix.Translate(tx, ty, tz); 
  }
  void add_rotate(float &rx, float &ry, float &rz)
  { 
    m_transformation_matrix.Rotate(rx, 1, 0, 0); 
    m_transformation_matrix.Rotate(ry, 0, 1, 0); 
    m_transformation_matrix.Rotate(rz, 0, 0, 1); 
  }
  void add_scale(float &sx, float &sy, float &sz)
  { 
    m_transformation_matrix.Scale(sx, sy, sz); 
  }
  // end of add transformations

  sBox get_bbox(void) { return m_bbox; }
  sBox get_transform_bbox(void);

  void set_render_wireframe(bool render_wireframe) { m_render_wireframe = render_wireframe; }

  virtual void create_array(cAppGauge *gauge) = 0;
  virtual void calc_normals(cAppGauge *gauge) = 0;
  virtual void create_scene(void) = 0;
};

#endif // ANFLEX_INTERFACE_RENDER_SHADER_H