/**
 * General intersection tests.
 * Implementation for template class defined in intersect.h.
 * author: Cesar Palomo <cpalomo@tecgraf.puc-rio.br>
 * author: Jeronimo <jeronimo@tecgraf.puc-rio.br>
 * date:   1-Dec-2009
 */
#define INTERSECTTEMPLATE template <class POLYMODELCLASS>
#define INTERSECTCLASS    Intersect<POLYMODELCLASS>
#define CUT_TOL 1e-2
#define SERIALIZATION_VERSION 1.01f
#define DUMMY_POLY_INDEX -1
#ifndef MAX_RADIAL_GRID_ANGLE
# define MAX_RADIAL_GRID_ANGLE 10.0f
#endif

//* Useful defines
#ifndef DEG2RAD
#define DEG2RAD(d) ((d)*0.017453292464387f)
#endif
#ifndef CYL2CART_X
#define CYL2CART_X(r,t) ((r)*(cosf(DEG2RAD(t))))
#endif
#ifndef CYL2CART_Y
#define CYL2CART_Y(r,t) ((r)*(sinf(DEG2RAD(t))))
#endif
#ifndef CYL2CARTRW_X
#define CYL2CARTRW_X(rw,r,t) CYL2CART_X((rw)+(r),t)
#endif
#ifndef CYL2CARTRW_Y
#define CYL2CARTRW_Y(rw,r,t) CYL2CART_Y((rw)+(r),t)
#endif

INTERSECTTEMPLATE 
INTERSECTCLASS::Intersect (const POLYMODELCLASS& poly_model)
: m_poly_model(poly_model)
#if DEBUG_TESTED_ELEMS
, m_tested_elems(NULL)
#endif
{
  m_last_result.faces = NULL;
  m_last_result.faces_count = 0;
  m_last_result.intervals = NULL;
  m_last_result.intervals_count = 0;
  m_hierarchy = new Hierarchy();
}

INTERSECTTEMPLATE 
INTERSECTCLASS::~Intersect ()
{
  delete m_hierarchy;
}

INTERSECTTEMPLATE 
int INTERSECTCLASS::GetBlockVerticesCB (float** coords, 
                                        int block_i, 
                                        void* data)
{
  POLYMODELCLASS* poly_model = (POLYMODELCLASS*)data;

  const Block& block = poly_model->GetBlock(block_i);
  int array_size = 0;
  // compute array size
  for (int e = 0; e < block.GetPolyCount(); e++) {
    int poly_i = block.GetPoly(e);
    array_size += 3*poly_model->GetVertexCount(poly_i);
  }
  // create array
  *coords = (float*)realloc(*coords, array_size*sizeof(float));
  float* c = *coords;
  for (int e = 0; e < block.GetPolyCount(); e++) {
    int poly_i = block.GetPoly(e);
    int poly_v_count;
    poly_model->GetVertexCoords(&poly_v_count, c, poly_i);
    c += 3*poly_v_count;
  }
  int vertex_count = array_size/3;
  return vertex_count;
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::Setup ()
{
  // build bounding volumes structure
#define HIERARCHY_STORE_VERTICES 0
#if HIERARCHY_STORE_VERTICES
  vrbv::SceneData scenedata;
#else
  vrbv::SceneData scenedata(false);
  GeomInfoCallback cb;
  cb.SetVertexCoordsCB(INTERSECTCLASS::GetBlockVerticesCB, &m_poly_model);
  scenedata.setGetCoordsCB(&cb);
#endif
  // create scenedata geometry
  int num_added_blocks = 0;
  float avg_z = 0.0f;
  scenedata.beginScene();
  // for each block...
  for (int b = 0; b < m_poly_model.GetNumBlocks(); b++) {
    const Block& block = m_poly_model.GetBlock(b);
    if (block.GetPolyCount() != 0) {
#if HIERARCHY_STORE_VERTICES
      // retrieve coords for block b
      DsArray<float> block_coords;
      for (int p = 0; p < block.GetPolyCount(); p++) {
        int poly_i = block.GetPoly(p);
        // resize block array to fit new poly's vertices
        int n_vertex = m_poly_model.GetVertexCount(poly_i);
        int old_size = block_coords.Size();
        block_coords.Resize(old_size + 3*n_vertex);
        float* pos = block_coords.GetAddress(old_size);
        // for each poly's vertex...
        for (int v_i = 0; v_i < n_vertex; v_i++, pos += 3)
          m_poly_model.GetVertexCoords(pos, poly_i, v_i);
      }
      vrbv::Geometry* geom = new vrbv::Geometry();
      geom->setId(b);
      scenedata.beginGeometry(geom);
      scenedata.addVertices(block_coords.GetArray(), block_coords.Size());
#else
      vrbv::Geometry* geom = new vrbv::Geometry();
      geom->setId(b);
      scenedata.beginGeometry(geom);

      // calculate vertices count for block
      int vertex_count = 0;
      for (int p = 0; p < block.GetPolyCount(); p++) {
        int poly_i = block.GetPoly(p);
        vertex_count += m_poly_model.GetVertexCount(poly_i);
      }
      scenedata.setCurGeomVerticesCount(vertex_count);
#endif
      scenedata.endGeometry();
      avg_z += geom->getBoundingBox().center.z;
      num_added_blocks++;
    }
  }
  scenedata.endScene();

  if (num_added_blocks > 0) {
    m_hierarchy->SetNumAddedBlocks(num_added_blocks);
    m_hierarchy->SetAverageZ(avg_z / num_added_blocks);
    m_hierarchy->BuildTree(scenedata);
  }
  else {
    // must clean up hierarchy Node, since it will never be referenced nor deleted
    delete scenedata.getSceneNode()->getHierarchyNode();
  }
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::SetScale (AlgVector& scale, AlgVector& center)
{
  m_hierarchy->SetScale(scale);
  m_hierarchy->SetScaleCenter(center);
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::ComputeCut (DsArray<CutFace>& result, 
                                 const vrbv::Plane& plane)
{
  // TODO
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::Serialize (IOStream* s)
{
  return m_hierarchy->Serialize(s);
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::Deserialize (IOStream* s)
{
  return m_hierarchy->Deserialize(s);
}

/******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************
 ******************************************************************************************************************************/
// TODO convert legacy code above

#if SUPPORT_RADIAL_MODEL
INTERSECTTEMPLATE 
int INTERSECTCLASS::getRadialIntersections(TopElement el, const TopFacetUse& fu, float* planeLimits, float* planeEquation, float** point)
{
  // split:
  //                    0 _ 1 _ x
  //                   /|  /|
  //                  2 _ 3 |
  //                 /| | | |
  //                y | 4 _ 5
  //                  |/  |/
  //                  6 _ 7
  //                    |
  //                    z

  TopModel *model = GetModel()->GetElemModel(el);
  float rw = GetRadialRW();
  int face = fu.GetLocalId();

  int nIntersections = 0;

  if (face != 4 && face != 5) {
    int split = 0;

    float x1,y1,z1;
    float x2,y2,z2;
    float dx = 0.0f;
    float dy = 0.0f;
    float dz = 0.0f;
    float b1x,b1y,b1z;
    float b2x,b2y,b2z;
    bool invert = false;

    switch(face) {
    case(0):
      {
        model->GetPosition(model->GetVertexNode(fu, 0), &x1, &y1, &z1);
        model->GetPosition(model->GetVertexNode(fu, 1), &x2, &y2, &z2);

        b1x = x1;
        b1y = y1;
        b1z = z1;
        model->GetPosition(model->GetVertexNode(fu, 3), &b2x, &b2y, &b2z);


        if ( (y2 - y1) > MAX_RADIAL_GRID_ANGLE)
          split =  (int)ceil((y2 - y1)/MAX_RADIAL_GRID_ANGLE);

        if (split > 0) {
          dy = (y2-y1)/split;
          //dz = (z2-z1)/split; // nao seria sempre 0 ?
          //model->GetPosition(model->GetVertexNode(fu, 1), &x2, &y2, &z2);
          dx = (x2-x1)/split;
        }

        break;
      }
    case(1):
      {
        model->GetPosition(model->GetVertexNode(fu, 0), &x1, &y1, &z1);
        model->GetPosition(model->GetVertexNode(fu, 3), &x2, &y2, &z2);


        b1x = x1;
        b1y = y1;
        b1z = z1;
        model->GetPosition(model->GetVertexNode(fu, 1), &b2x, &b2y, &b2z);


        if ( (y2 - y1) > MAX_RADIAL_GRID_ANGLE)
          split =  (int)ceil((y2 - y1)/MAX_RADIAL_GRID_ANGLE);

        if (split > 1) {
          dy = (y2-y1)/split;
          //dz = (z2-z1)/split; // nao seria sempre 0 ?
          //model->GetPosition(model->GetVertexNode(fu, 3), &x2, &y2, &z2);
          dx = (x2-x1)/split;
        }
        invert = true;
        break;
      }
    case(2):
      {
        model->GetPosition(model->GetVertexNode(fu, 0), &x1, &y1, &z1);
        model->GetPosition(model->GetVertexNode(fu, 1), &x2, &y2, &z2);

        b1x = x1;
        b1y = y1;
        b1z = z1;

        model->GetPosition(model->GetVertexNode(fu, 3), &b2x, &b2y, &b2z);


        if ( (y2 - y1) > MAX_RADIAL_GRID_ANGLE)
          split = (int)ceil((y2 - y1)/MAX_RADIAL_GRID_ANGLE);

        if (split > 0) {
          dy = (y2-y1)/split;
          dx = (x2-x1)/split;
          //model->GetPosition(model->GetVertexNode(fu, 1), &x2, &y2, &z2);
          //dz = (z2-z1)/split;

        }
        break;
      }
    case(3):
      {
        model->GetPosition(model->GetVertexNode(fu, 0), &x1, &y1, &z1);
        model->GetPosition(model->GetVertexNode(fu, 3), &x2, &y2, &z2);

        b1x = x1;
        b1y = y1;
        b1z = z1;
        model->GetPosition(model->GetVertexNode(fu, 1), &b2x, &b2y, &b2z);


        if ( (y2 - y1) > MAX_RADIAL_GRID_ANGLE)
          split = (int)ceil((y2 - y1)/MAX_RADIAL_GRID_ANGLE);

        if (split > 0) {
          dy = (y2-y1)/split;
          dx = (x2-x1)/split;
          //model->GetPosition(model->GetVertexNode(fu, 3), &x2, &y2, &z2);
          //dz = (z2-z1)/split;
        }
        invert = true;
        break;
      }
    default:
#ifdef VERBOSE
      printf("Face Invalida: %d\n%s: %d",face,__FILE__,__LINE__);
#endif
      return 0;
      break;
    }


    if (split > 1 ) {
      (*point) = (float*)malloc(split*6*3*sizeof(float));
      if ((*point) == NULL) {
#ifdef VERBOSE
        printf("Cannot alloc memory at %s:%d\n",__FILE__,__LINE__);
#endif
        return 0;
      }

      dz = 0.0f;
      for (int j = 0; j < split; ++j) {
        if (invert) {
          float faceVertex[12];
          float cx = CYL2CARTRW_X(rw,b1x,b1y);
          float cy = CYL2CARTRW_Y(rw,b1x,b1y);
          faceVertex[0] = cx;
          faceVertex[1] = cy;
          faceVertex[2] = b1z;
          //glVertex3f(cx,cy,b1z);

          cx = CYL2CARTRW_X(rw,b2x,b2y);
          cy = CYL2CARTRW_Y(rw,b2x,b2y);

          faceVertex[3] = cx;
          faceVertex[4] = cy;
          faceVertex[5] = b2z;
          //glVertex3f(cx,cy,b2z);

          b1x = b1x + dx;
          b1y = b1y + dy;

          b2x = b2x + dx;
          b2y = b2y + dy;

          cx = CYL2CARTRW_X(rw,b2x,b2y);
          cy = CYL2CARTRW_Y(rw,b2x,b2y);

          faceVertex[6] = cx;
          faceVertex[7] = cy;
          faceVertex[8] = b2z;
          //glVertex3f(cx,cy,b2z);

          cx = CYL2CARTRW_X(rw,b1x,b1y);
          cy = CYL2CARTRW_Y(rw,b1x,b1y);

          faceVertex[9] = cx;
          faceVertex[10] = cy;
          faceVertex[11] = b1z;
          //glVertex3f(cx,cy,b1z);

          if (hasIntersection( faceVertex, planeLimits, &((*point)[3*nIntersections])))
            nIntersections++;
          if (hasIntersection( faceVertex, &(planeLimits[3]), &((*point)[3*nIntersections])))
            nIntersections++;
          for (int i = 0; i < 4; ++i) {
            float edgeVertex[6];
            edgeVertex[0] = faceVertex[3*i+0];
            edgeVertex[1] = faceVertex[3*i+1];
            edgeVertex[2] = faceVertex[3*i+2];
            edgeVertex[3] = faceVertex[3*((i+1)%4)+0];
            edgeVertex[4] = faceVertex[3*((i+1)%4)+1];
            edgeVertex[5] = faceVertex[3*((i+1)%4)+2];
            if (HasIntersectionWithEdge((float*)edgeVertex, 
                                        ((float*)edgeVertex)+3, 
                                        planeLimits, 
                                        planeEquation, 
                                        &((*point)[3*nIntersections])))
            {
              nIntersections++;
            }
          }
        }
        else {
          float faceVertex[12];
          float cx = CYL2CARTRW_X(rw,b2x,b2y);
          float cy = CYL2CARTRW_Y(rw,b2x,b2y);
          //glVertex3f(cx,cy,b2z);

          faceVertex[0] = cx;
          faceVertex[1] = cy;
          faceVertex[2] = b2z;

          cx = CYL2CARTRW_X(rw,b1x,b1y);
          cy = CYL2CARTRW_Y(rw,b1x,b1y);
          //glVertex3f(cx,cy,b1z);

          faceVertex[3] = cx;
          faceVertex[4] = cy;
          faceVertex[5] = b1z;

          b1x = b1x + dx;
          b1y = b1y + dy;

          b2x = b2x + dx;
          b2y = b2y + dy;

          cx = CYL2CARTRW_X(rw,b1x,b1y);
          cy = CYL2CARTRW_Y(rw,b1x,b1y);
          //glVertex3f(cx,cy,b1z);

          faceVertex[6] = cx;
          faceVertex[7] = cy;
          faceVertex[8] = b1z;

          cx = CYL2CARTRW_X(rw,b2x,b2y);
          cy = CYL2CARTRW_Y(rw,b2x,b2y);

          faceVertex[9] = cx;
          faceVertex[10] = cy;
          faceVertex[11] = b2z;
          //glVertex3f(cx,cy,b2z);

          if (hasIntersection( faceVertex, planeLimits, &((*point)[3*nIntersections])))
            nIntersections++;
          if (hasIntersection( faceVertex, &(planeLimits[3]), &((*point)[3*nIntersections])))
            nIntersections++;
          for (int i = 0; i < 4; ++i) {
            float edgeVertex[6];
            edgeVertex[0] = faceVertex[3*i+0];
            edgeVertex[1] = faceVertex[3*i+1];
            edgeVertex[2] = faceVertex[3*i+2];
            edgeVertex[3] = faceVertex[3*((i+1)%4)+0];
            edgeVertex[4] = faceVertex[3*((i+1)%4)+1];
            edgeVertex[5] = faceVertex[3*((i+1)%4)+2];
            if (HasIntersectionWithEdge((float*)edgeVertex, 
                                        ((float*)edgeVertex)+3, 
                                        planeLimits, 
                                        planeEquation, 
                                        &((*point)[3*nIntersections])))
            {
              nIntersections++;
            }
          }
        }

      };
    }
    else {
      (*point) = (float*)malloc(6*3*sizeof(float));
      if ((*point) == NULL) {
#ifdef VERBOSE
        printf("Cannot alloc memory at %s:%d\n",__FILE__,__LINE__);
#endif
        return 0;
      }
      float faceVertex[12];
      for (int i = 0; i < 4; i++) {
        float x,y,z;
        model->GetPosition(model->GetVertexNode(fu, i), &x, &y, &z);

        // converte para coordenadas cartesianas
        float cx = CYL2CARTRW_X(rw,x,y);
        float cy = CYL2CARTRW_Y(rw,x,y);
        faceVertex[3*i+0] = cx;
        faceVertex[3*i+1] = cy;
        faceVertex[3*i+2] = z;
      }
      if (hasIntersection( faceVertex, planeLimits, &((*point)[3*nIntersections])))
        nIntersections++;
      if (hasIntersection( faceVertex, &(planeLimits[3]), &((*point)[3*nIntersections])))
        nIntersections++;
      for (int i = 0; i < 4; ++i) {
        float edgeVertex[6];
        edgeVertex[0] = faceVertex[3*i+0];
        edgeVertex[1] = faceVertex[3*i+1];
        edgeVertex[2] = faceVertex[3*i+2];
        edgeVertex[3] = faceVertex[3*((i+1)%4)+0];
        edgeVertex[4] = faceVertex[3*((i+1)%4)+1];
        edgeVertex[5] = faceVertex[3*((i+1)%4)+2];
        if (HasIntersectionWithEdge((float*)edgeVertex, 
                                    ((float*)edgeVertex)+3, 
                                    planeLimits, 
                                    planeEquation, 
                                    &((*point)[3*nIntersections])))
        {
          nIntersections++;
        }
      }
    }
  }
  else {
    (*point) = (float*)malloc(6*3*sizeof(float));
    if ((*point) == NULL) {
#ifdef VERBOSE
      printf("Cannot alloc memory at %s:%d\n",__FILE__,__LINE__);
#endif
      return 0;
    }
    float faceVertex[12];

    for (int i = 0; i < 4; i++) {
      float x,y,z;
      model->GetPosition(model->GetVertexNode(fu, i), &x, &y, &z);

      // converte para coordenadas cartesianas
      float cx = CYL2CARTRW_X(rw,x,y);
      float cy = CYL2CARTRW_Y(rw,x,y);
      faceVertex[3*i+0] = cx;
      faceVertex[3*i+1] = cy;
      faceVertex[3*i+2] = z;
    }
    if (hasIntersection( faceVertex, planeLimits, &((*point)[3*nIntersections])))
      nIntersections++;
    if (hasIntersection( faceVertex, &(planeLimits[3]), &((*point)[3*nIntersections])))
      nIntersections++;
    for (int i = 0; i < 4; ++i) {
      float edgeVertex[6];
      edgeVertex[0] = faceVertex[3*i+0];
      edgeVertex[1] = faceVertex[3*i+1];
      edgeVertex[2] = faceVertex[3*i+2];
      edgeVertex[3] = faceVertex[3*((i+1)%4)+0];
      edgeVertex[4] = faceVertex[3*((i+1)%4)+1];
      edgeVertex[5] = faceVertex[3*((i+1)%4)+2];
      if (HasIntersectionWithEdge((float*)edgeVertex, 
                                  ((float*)edgeVertex)+3, 
                                  planeLimits, 
                                  planeEquation, 
                                  &((*point)[3*nIntersections])))
      {
        nIntersections++;
      }
    }
  }
  return nIntersections;
}
#endif

INTERSECTTEMPLATE 
bool INTERSECTCLASS::HasIntersection (const float* face, 
                                      int face_v_count,
                                      float *planeLimits,
                                      const float direction[3], 
                                      float* point, 
                                      bool is_infinite_plane)
{
  // TODO remove limitation to a face with exactly 4 vertices
  assert(face_v_count == 4);
  return HasIntersectionWithFace(face, 
                                 face+3,
                                 face+6,
                                 face+9,
                                 planeLimits,
                                 direction,
                                 point,
                                 is_infinite_plane);
}

/**
* Esta funcao testa a intersecao de uma faceta com um plano limitado.
* Para isso, um raio que sai dos limites do plano é lancado na direcao -direction
* e sua intersecao com o poligono que representa a faceta é testada.
* A faceta não é planar. Admitindo que seja quase planar, projeta-se o
* ultimo vertice no plano para efeito de calculo.
* Caso a faceta nao seja quase planar aparecerao buracos no corte.
*/
INTERSECTTEMPLATE 
bool INTERSECTCLASS::HasIntersectionWithFace (const float v0[3], 
                                              const float v1[3], 
                                              const float v2[3], 
                                              const float v3[3], 
                                              float* planeLimits,
                                              const float direction[3],
                                              float* point, 
                                              bool is_infinite_plane)
{
  float x0 = v0[0];
  float y0 = v0[1];
  float z0 = v0[2];
  float x1 = v1[0];
  float y1 = v1[1];
  float z1 = v1[2];
  float x2 = v2[0];
  float y2 = v2[1];
  float z2 = v2[2];
  float x3 = v3[0];
  float y3 = v3[1];
  float z3 = v3[2];

  float vec1[] = { x1-x0, y1-y0, z1-z0 };
  float vec2[] = { x3-x0, y3-y0, z3-z0 };
  float faceEq[] = {0, 0, 0, 0};
  Cross(vec1, vec2, faceEq);
  if (Normalize(faceEq) == 0.f) {
#ifdef VERBOSE
    printf("Face degenerada:\n");
    printf("V0: x = %f, y = %f, z = %f\n", x0, y0, z0 );
    printf("V1: x = %f, y = %f, z = %f\n", x1, y1, z1 );
    printf("V2: x = %f, y = %f, z = %f\n", x2, y2, z2 );
    printf("V3: x = %f, y = %f, z = %f\n", x3, y3, z3 );
#endif
    return false; //Nao devia entrar aqui. Se entra, entao temos celulas degeneradas
  }

  faceEq[3] = -(faceEq[0]*x0 + faceEq[1]*y0 + faceEq[2]*z0);

  float rayDirection[] = { -direction[0], -direction[1], -direction[2] };

  if (LinePlaneIntersect(planeLimits, rayDirection, faceEq, point)) {
    if (!is_infinite_plane) {
      //Projecao de x2 no plano da faceta. Assume-se que a faceta seja quase plana.
      float p2[] = {x2, y2, z2};
      ProjectPointToPlane(p2, faceEq, p2);
      x2 = p2[0]; y2 = p2[1]; z2 = p2[2];
      float points[] = { x0,y0,z0,
                         x1,y1,z1,
                         x2,y2,z2,
                         x3,y3,z3 };

      if (IsInsidePolygon(point, 4, points))
        return true;
    }
  }
  return false;
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::HasIntersectionWithEdge(const float v0[3], 
                                             const float v1[3], 
                                             float *planeLimits, 
                                             float* planeEquation, 
                                             const float direction[3],
                                             float* point, 
                                             bool is_infinite_plane)
{
  float x0 = v0[0];
  float y0 = v0[1];
  float z0 = v0[2];
  float x1 = v1[0];
  float y1 = v1[1];
  float z1 = v1[2];

  float d0 = planeEquation[0]*x0 + planeEquation[1]*y0 + planeEquation[2]*z0 + planeEquation[3];

  float d1 = planeEquation[0]*x1 + planeEquation[1]*y1 + planeEquation[2]*z1 + planeEquation[3];

  //testa se os pontos da aresta estao no mesmo lado do plano.
  if (d0*d1 > 0 || fabs(d0 - d1) < CUT_TOL)
    return false;
  else if (!is_infinite_plane) {
    if (planeLimits[3] > planeLimits[0]) {
      //testa se os pontos da aresta estão alem do limite do plano
      if (x0 < planeLimits[0] && x1 < planeLimits[0])
        return false;
      if (x0 > planeLimits[3] && x1 > planeLimits[3])
        return false;
    }
    else {
      //testa se os pontos da aresta estão alem do limite do plano
      if (x0 > planeLimits[0] && x1 > planeLimits[0])
        return false;
      if (x0 < planeLimits[3] && x1 < planeLimits[3])
        return false;
    }

    if (planeLimits[4] > planeLimits[1]) {
      //testa se os pontos da aresta estão alem do limite do plano
      if (y0 < planeLimits[1] && y1 < planeLimits[1])
        return false;
      if (y0 > planeLimits[4] && y1 > planeLimits[4])
        return false;
    }
    else {
      //testa se os pontos da aresta estão alem do limite do plano
      if (y0 > planeLimits[1] && y1 > planeLimits[1])
        return false;
      if (y0 < planeLimits[4] && y1 < planeLimits[4])
        return false;
    }
  }
  float d0abs = fabs(d0);
  float d1abs = fabs(d1);
  float ratio0 = d0abs/(d0abs+d1abs);
  float ratio1 = 1 - ratio0; // d1abs/(d0abs+d1abs)
  //Calcula ponto de intersecao da aresta com o plano
  if (x0 < x1)
    point[0] = x0 + ratio0*(x1-x0);
  else
    point[0] = x1 + ratio1*(x0-x1);
  if (y0 < y1)
    point[1] = y0 + ratio0*(y1-y0);
  else
    point[1] = y1 + ratio1*(y0-y1);

  point[2] = planeLimits[2];

  if (is_infinite_plane) {
    if (z0 < z1)
      point[2] = z0 + ratio0*(z1-z0);
    else
      point[2] = z1 + ratio1*(z0-z1);
    return true;
  }
  else {
    // project point to plane, and test whether it inside plane limits
    AlgVector point_hit(point[0], point[1], 0);
    if (z0 < z1)
      point_hit.z = z0 + ratio0*(z1-z0);
    else
      point_hit.z = z1 + ratio1*(z0-z1);
    //testa se os pontos da aresta estão alem do limite do plano
    bool test_3d = true;
    // x coordinate
    if (planeLimits[0] < planeLimits[3]) {
      if (point_hit.x < planeLimits[0] || point_hit.x > planeLimits[3])
        test_3d = false;
    }
    else if (planeLimits[0] > planeLimits[3]) {
      if (point_hit.x > planeLimits[0] || point_hit.x < planeLimits[3])
        test_3d = false;
    }
    // y coordinate
    if (planeLimits[1] < planeLimits[4]) {
      if (point_hit.y < planeLimits[1] || point_hit.y > planeLimits[4])
        test_3d = false;
    }
    else if (planeLimits[1] > planeLimits[4]) {
      if (point_hit.y > planeLimits[1] || point_hit.y < planeLimits[4])
        test_3d = false;
    }
    // z coordinate
    if (planeLimits[2] < planeLimits[5]) {
      if (point_hit.z < planeLimits[2] || point_hit.z > planeLimits[5])
        test_3d = false;
    }
    else if (planeLimits[2] > planeLimits[5]) {
      if (point_hit.z > planeLimits[2] || point_hit.z < planeLimits[5])
        test_3d = false;
    }
    
    // if intersection point projected to 2D belongs to polygon, HIT
    if (test_3d) {
      point[2] = point_hit.z;
      return true;
    }
  }

  return false;
}

INTERSECTTEMPLATE 
int INTERSECTCLASS::PolyAgainstPlane (int poly_index, 
                                      float* planeLimits, 
                                      float* planeEquation, 
                                      const float direction[3], 
                                      float* totalIntersectionPoints, 
                                      bool is_infinite_plane)
{
  int nTotalIntersections = 0;
  float* intersectionPoints = totalIntersectionPoints;

  // check plane against edges
  for (int e = 0; e < m_poly_model.GetEdgeCount(poly_index); e++) {
    float edge[6];  // 2 vertices
    m_poly_model.GetEdgeCoords(edge, poly_index, e);
    if (HasIntersectionWithEdge(edge, 
                                edge+3,
                                planeLimits, 
                                planeEquation, 
                                direction, 
                                &(intersectionPoints[3*nTotalIntersections]), 
                                is_infinite_plane))
    {
      nTotalIntersections++;
    }
  }

  // check plane limits against faces (when checking a finite plane)
  if (!is_infinite_plane) {
    float* face = NULL;
    for (int f = 0; f < m_poly_model.GetFaceCount(poly_index); f++) {
      int face_v_count = m_poly_model.GetFaceVertexCount (poly_index, f);
      face = (float*)realloc(face, 3 * face_v_count * sizeof(float));
      m_poly_model.GetFaceCoords(face, poly_index, f);
      if (HasIntersection(face,
                          face_v_count,
                          planeLimits, 
                          direction, 
                          &(intersectionPoints[3*nTotalIntersections]), 
                          is_infinite_plane))
      {
        nTotalIntersections++;
      }
      // TODO should not it be else if rather than if?
      if (HasIntersection(face, 
                          face_v_count,
                          &(planeLimits[3]), 
                          direction, 
                          &(intersectionPoints[3*nTotalIntersections]), 
                          is_infinite_plane))
      {
        nTotalIntersections++;
      }
    }
    free(face);
  }
  return nTotalIntersections;
}

INTERSECTTEMPLATE 
int INTERSECTCLASS::PolyAgainstPlane (int face_count,
                                      const float* faces,
                                      const int* faces_v_count,
                                      int edge_count,
                                      const float* edges,
                                      float* planeLimits, 
                                      float* planeEquation, 
                                      const float direction[3], 
                                      float* totalIntersectionPoints, 
                                      bool is_infinite_plane)
{
  int nTotalIntersections = 0;
  float* intersectionPoints = totalIntersectionPoints;

  // check plane against edges
  for (int e = 0; e < edge_count; e++) {
    // skip previous edges (2 3D vertices)
    const float* edge = edges + 2*3*e;
    if (HasIntersectionWithEdge(edge, 
                                edge+3,
                                planeLimits, 
                                planeEquation, 
                                direction, 
                                &(intersectionPoints[3*nTotalIntersections]), 
                                is_infinite_plane))
    {
      nTotalIntersections++;
    }
  }

  // check plane limits against faces
  const float* face = faces;
  for (int f = 0; f < face_count; f++) {
    int vert_count = faces_v_count[f];
    if (HasIntersection(face,
                        vert_count,
                        planeLimits, 
                        direction, 
                        &(intersectionPoints[3*nTotalIntersections]), 
                        is_infinite_plane))
    {
      nTotalIntersections++;
    }
    // TODO should not it be else if rather than if?
    if (HasIntersection(face, 
                        vert_count,
                        &(planeLimits[3]), 
                        direction, 
                        &(intersectionPoints[3*nTotalIntersections]), 
                        is_infinite_plane))
    {
      nTotalIntersections++;
    }

    // advance to next face
    face += vert_count;
  }

  return nTotalIntersections;
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::HasIntersection (int poly_index,
                                      float *planeLimits, 
                                      float* planeEquation, 
                                      const float direction[3], 
                                      bool is_infinite_plane)
{
  float* totalIntersectionPoints = NULL;
  int nTotalIntersections = 0;

#if SUPPORT_RADIAL_MODEL
  if (IsModelRadial())
    nTotalIntersections = getRadialElementIntersection(el,planeLimits,planeEquation,&totalIntersectionPoints);
  else {
#endif
    totalIntersectionPoints = (float*)malloc(12*3*sizeof(float));
    if (totalIntersectionPoints == NULL) {
#ifdef VERBOSE
      printf("Cannot alloc memory at %s:%d\n",__FILE__,__LINE__);
#endif
      return false;
    }
    nTotalIntersections = PolyAgainstPlane(poly_index, 
                                           planeLimits, 
                                           planeEquation, 
                                           direction, 
                                           totalIntersectionPoints, 
                                           is_infinite_plane);
#if SUPPORT_RADIAL_MODEL
  }
#endif
  if (nTotalIntersections < 3) {
    if (totalIntersectionPoints)
      free(totalIntersectionPoints);
    return false;
  }

  nTotalIntersections = Triangularize(nTotalIntersections, totalIntersectionPoints, planeEquation);

  if (nTotalIntersections < 3) {
    if (totalIntersectionPoints)
      free(totalIntersectionPoints);
    return false;
  }

  // generate CutFace with new points
  // create array with vertices
  DsArray<CutVertex> points;
  points.Resize(nTotalIntersections);
  float* ptrInt = totalIntersectionPoints;
  for (int i = 0; i < nTotalIntersections; i++)
  {
    CutVertex vert;
    vert.coords.Set(ptrInt);
    points[i] = vert;
    // TODO: from_edge / edge_id
    // TODO interpolate params
    ptrInt += 3;
  }
  CutFace face;
  face.poly_index = poly_index;
  face.vert_count = nTotalIntersections;
  face.vertices = points.TakeOverArray();
  // TODO move state to another object rather than Intersect
  m_faces_ds_array.Append(face);

  if (totalIntersectionPoints)
    free(totalIntersectionPoints);

  return true;

}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::HasIntersection (int face_count,
                                      const float* faces,
                                      const int* faces_v_count,
                                      int edge_count,
                                      const float* edges,
                                      float *planeLimits, 
                                      float* planeEquation, 
                                      const float direction[3], 
                                      bool is_infinite_plane)
{
  float* totalIntersectionPoints = NULL;
  int nTotalIntersections = 0;

#if SUPPORT_RADIAL_MODEL
  if (IsModelRadial())
    nTotalIntersections = getRadialElementIntersection(el,planeLimits,planeEquation,&totalIntersectionPoints);
  else {
#endif
    totalIntersectionPoints = (float*)malloc(12*3*sizeof(float));
    if (totalIntersectionPoints == NULL) {
#ifdef VERBOSE
      printf("Cannot alloc memory at %s:%d\n",__FILE__,__LINE__);
#endif
      return false;
    }
    nTotalIntersections = PolyAgainstPlane(face_count,
                                           faces,
                                           faces_v_count,
                                           edge_count,
                                           edges,
                                           planeLimits, 
                                           planeEquation, 
                                           direction, 
                                           totalIntersectionPoints, 
                                           is_infinite_plane);
#if SUPPORT_RADIAL_MODEL
  }
#endif
  if (nTotalIntersections < 3) {
    if (totalIntersectionPoints)
      free(totalIntersectionPoints);
    return false;
  }

  nTotalIntersections = Triangularize(nTotalIntersections, totalIntersectionPoints, planeEquation);

  if (nTotalIntersections < 3) {
    if (totalIntersectionPoints)
      free(totalIntersectionPoints);
    return false;
  }

  // generate CutFace with new points
  // create array with vertices
  DsArray<CutVertex> points;
  points.Resize(nTotalIntersections);
  float* ptrInt = totalIntersectionPoints;
  for (int i = 0; i < nTotalIntersections; i++)
  {
    CutVertex vert;
    vert.coords.Set(ptrInt);
    points[i] = vert;
    // TODO: from_edge / edge_id
    // TODO interpolate params
    ptrInt += 3;
  }
  CutFace face;
  face.poly_index = DUMMY_POLY_INDEX;
  face.vert_count = nTotalIntersections;
  face.vertices = points.TakeOverArray();
  // TODO move state to another object rather than Intersect
  m_faces_ds_array.Append(face);

  if (totalIntersectionPoints)
    free(totalIntersectionPoints);

  return true;

}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::CheckIntersection (int edge_count,
                                        const float* edges,
                                        int face_count,
                                        const float* faces,
                                        const int* faces_v_count,
                                        float* planeLimits,
                                        float* planeEquation,
                                        const float direction[3],
                                        bool is_infinite_plane)
{
  float dir[3];
  dir[0] = direction ? direction[0] : 0.0f;
  dir[1] = direction ? direction[1] : 0.0f;
  dir[2] = direction ? direction[2] : 1.0f;

  // clear previous results
  FreeResult();

  HasIntersection(face_count,
                  faces,
                  faces_v_count,
                  edge_count,
                  edges,
                  planeLimits, 
                  planeEquation, 
                  dir,
                  is_infinite_plane);
  // update result
  // TODO move state to another object rather than Intersect
  m_last_result.faces_count = m_faces_ds_array.Size();
  m_last_result.faces = m_faces_ds_array.TakeOverArray();
  return m_last_result.faces_count != 0;
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::CheckIntersection (int poly_index,
                                        float *planeLimits,
                                        float* planeEquation,
                                        const float direction[3],
                                        bool is_infinite_plane)
{
  float dir[3];
  dir[0] = direction ? direction[0] : 0.0f;
  dir[1] = direction ? direction[1] : 0.0f;
  dir[2] = direction ? direction[2] : 1.0f;

  // clear previous results
  FreeResult();

  HasIntersection(poly_index,
                  planeLimits, 
                  planeEquation, 
                  dir,
                  is_infinite_plane);
  // update result
  // TODO move state to another object rather than Intersect
  m_last_result.faces_count = m_faces_ds_array.Size();
  m_last_result.faces = m_faces_ds_array.TakeOverArray();
  return m_last_result.faces_count != 0;
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::CheckIntersection(float *planeLimits, 
                                       float* planeEquation,
                                       const float direction[3],
                                       bool is_infinite_plane)
{
  float dir[3];
  dir[0] = direction ? direction[0] : 0.0f;
  dir[1] = direction ? direction[1] : 0.0f;
  dir[2] = direction ? direction[2] : 1.0f;

  // clear previous results
  FreeResult();

#if !TEST_CUT_PERFORMANCE
  // iterate over hierarchy and decide which leaves 
  // must be checked against cut plane
  if (m_hierarchy->GetTreeRoot()) {
    ComputeIntersection(m_hierarchy->GetTreeRoot(),
                        planeLimits,
                        planeEquation,
                        dir,
                        is_infinite_plane);
  }
#else
  if (UtlDebug::GetFlag("CUT_USE_HIERARCHY")) {
    // iterate over hierarchy and decide which leaves 
    // must be checked against cut plane
    if (m_hierarchy->GetTreeRoot()) {
      ComputeIntersection(m_hierarchy->GetTreeRoot(),
                          planeLimits,
                          planeEquation,
                          dir,
                          is_infinite_plane);
    }
  }
  else {
    // iterate over all polys
    for (int poly_index = 0; poly_index < m_poly_model.GetPolyCount(); poly_index++) {
      HasIntersection(poly_index, 
                      planeLimits, 
                      planeEquation,
                      dir,
                      is_infinite_plane);
#if COLLECT_CUT_STATISTICS
      m_last_result.elem_tested_count++;
#endif
    }
  }

# if COLLECT_CUT_STATISTICS
  m_last_result.elem_not_tested_count = 
    m_poly_model.GetPolyCount() - m_last_result.elem_tested_count;
# endif
#endif

  // update result
  m_last_result.faces_count = m_faces_ds_array.Size();
  m_last_result.faces     = m_faces_ds_array.TakeOverArray();
  return m_last_result.faces_count != 0;
}

INTERSECTTEMPLATE
void INTERSECTCLASS::ComputeIntersection (vrbv::Node* node,
                                          float *plane_limits, 
                                          float* plane_eq,
                                          const float direction[3],
                                          bool is_infinite_plane) 
{
#if COLLECT_CUT_STATISTICS
  m_last_result.hierarchy_nodes_tested_count++;
#endif
  if (HasIntersection(node,
                      plane_limits,
                      plane_eq,
                      direction,
                      is_infinite_plane))
  {
    // plane intersects node's bounding box
    if (node->isLeaf()) {
      ComputeLeafIntersection(node, 
                              plane_limits, 
                              plane_eq,
                              direction,
                              is_infinite_plane); 
    } else {
      if (node->getLeftChild()) {
        ComputeIntersection(node->getLeftChild(),
                            plane_limits, 
                            plane_eq,
                            direction,
                            is_infinite_plane);
      }
      if (node->getRightChild()) {
        ComputeIntersection(node->getRightChild(),
                            plane_limits, 
                            plane_eq,
                            direction,
                            is_infinite_plane);
      }
    }
  }
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::ComputeLeafIntersection (vrbv::Node* node,
                                              float *plane_limits, 
                                              float* plane_eq,
                                              const float direction[3],
                                              bool is_infinite_plane)
{
  // iterate over blocks in this node
  GeometryVector& geom_vec = node->getGeometries();
  for (unsigned int geom_i = 0; geom_i < geom_vec.size(); geom_i++) {

    int block_index = geom_vec[geom_i]->getId();
    const Block& block = m_poly_model.GetBlock(block_index);

    // polys in this block should be checked against cut plane
    for (int i = 0; i < block.GetPolyCount(); i++) {
      int poly_index = block.GetPoly(i);
      if (HasIntersection(poly_index, 
                          plane_limits, 
                          plane_eq,
                          direction,
                          is_infinite_plane))
      {
        // empty
      }
#if DEBUG_TESTED_ELEMS
      if (m_tested_elems != NULL)
        m_tested_elems->Set(m_poly_model.GetPolyID(poly_index), true);
#endif
#if COLLECT_CUT_STATISTICS
      m_last_result.elem_tested_count++;
#endif
    }
  }
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::HasIntersection (vrbv::Node* node,
                                      float* plane_limits, 
                                      float* plane_eq,
                                      const float direction[3],
                                      bool is_infinite_plane)
{
// 	*     7+------+6
// 	*     /|     /|
// 	*    / |    / |
// 	*   / 3+---/--+2
// 	* 4+------+5 /    y  z
// 	*  | /    | /     | /
// 	*  |/     |/      |/
// 	* 0+------+1      *---x
  static const int edges_indices[12][2] = {
    {0, 1},
    {1, 5},
    {5, 4},
    {4, 0},
    {0, 3},
    {4, 7},
    {1, 2},
    {5, 6},
    {3, 2},
    {2, 6},
    {6, 7},
    {7, 3}
  };
  static const int faces_indices[6][4] = {
    {0, 1, 5, 4},
    {3, 2, 6, 7},
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {1, 2, 6, 5},
    {0, 3, 7, 4}
  };
  float vertices[24];
  node->getBoundingBox().computeVerticesArray(vertices);
  float intersection_points[3];
  if (is_infinite_plane) {
    // just test if any points lie on different plane subspaces
    float x0 = *(vertices + 0);
    float y0 = *(vertices + 1);
    float z0 = *(vertices + 2);
    float d0 = plane_eq[0]*x0 + plane_eq[1]*y0 + plane_eq[2]*z0 + plane_eq[3];
    for (int v=1; v<8; ++v) {
      float x1 = *(vertices + 3*v + 0);
      float y1 = *(vertices + 3*v + 1);
      float z1 = *(vertices + 3*v + 2);
      float d1 = plane_eq[0]*x1 + plane_eq[1]*y1 + plane_eq[2]*z1 + plane_eq[3];
      // test if points lie on different plane subspaces
      if (d0*d1 <= 0 && fabs(d0 - d1) >= CUT_TOL)
        return true;
    }
  } else {
    // test intersection with edges
    for (int i = 0; i < 12; ++i) {
      float* v0 = vertices + 3*edges_indices[i][0];
      float* v1 = vertices + 3*edges_indices[i][1];
      if (HasIntersectionWithEdge(v0, 
                                  v1, 
                                  plane_limits, 
                                  plane_eq,
                                  direction,
                                  intersection_points, 
                                  is_infinite_plane))
      {
        return true;
      }
    }
  }
  // Plane-face intersection test
  if (!is_infinite_plane) {
    for (int i = 0; i < 6; ++i) {
      float* v0 = &vertices[3*faces_indices[i][0]];
      float* v1 = &vertices[3*faces_indices[i][1]];
      float* v2 = &vertices[3*faces_indices[i][2]];
      float* v3 = &vertices[3*faces_indices[i][3]];
      if (HasIntersectionWithFace(v0, 
                                  v1,
                                  v2,
                                  v3,
                                  plane_limits,
                                  direction,
                                  intersection_points,
                                  is_infinite_plane))
      {
        return true;
      }
      if (HasIntersectionWithFace(v0, 
                                  v1,
                                  v2,
                                  v3,
                                  plane_limits+3,
                                  direction,
                                  intersection_points, 
                                  is_infinite_plane))
      {
        return true;
      }
    }
  }
  return false;
}

INTERSECTTEMPLATE float INTERSECTCLASS::GetSerializationVersion ()
{
  return SERIALIZATION_VERSION + Hierarchy::GetSerializationVersion();
}

// Implements ray/box intersection test with Slabs method:
// defined in textbook Real time rendering 2nd edition 
// by Akenine-Moller and Haines, p. 572-574.
INTERSECTTEMPLATE bool INTERSECTCLASS::Check (const geoms::Ray& r,
                                              const vrbv::Box& bb)
{
  // if ray has limits (segment), test if extremities are contained in box
  if (r.IsLimited()) {
    // work in the box's coordinate system
    geoms::Segment s(r);
    AlgVector p[2] = {s.p1 - AlgVector(bb.center.ptr), 
                      s.p2 - AlgVector(bb.center.ptr)};
    // axis: assumed to be normalized
    AlgVector axis[3];
    for (int a_i = 0; a_i < 3; a_i++)
      axis[a_i].Set(bb.axis[a_i].ptr);

    // project extremities in each axis and check whether they are inside Box
    bool inside = true;
    for (int p_i = 0; p_i < 2 && inside; p_i++) {
      for (int a_i = 0; a_i < 3 && inside; a_i++) {
        float axis_projection = p[p_i].Dot(axis[a_i]);
        float current_extents = bb.extents[a_i];
        inside = fabsf(axis_projection) <= current_extents;
      }
    }
    if (inside)     // both extremities inside box
      return true;
  }

  // calculate intersection
  float t_min = -FLT_MAX;
  float t_max = FLT_MAX;
  AlgVector p = AlgVector(bb.center.ptr) - r.o;

  // iterate over 3 axis and check intersection with slabs
  float t1, t2;
  for (int i = 0; i < 3; i++) {
    AlgVector a_i(bb.axis[i].ptr);
    float e = a_i.Dot(p);
    float f = a_i.Dot(r.d);
    float h_i = bb.extents[i];
    float inv_f = 1.f / f;
    if (fabsf(f) > GEOMS_EPSILON_ZERO) {
      t1 = (e + h_i) * inv_f;
      t2 = (e - h_i) * inv_f;
      // ensure t1 has the smallest value
      if (t1 > t2) {
        float tmp = t2;
        t2 = t1;
        t1 = tmp;
      }
      // update t_min (max(t_axis_x_min, t_axis_y_min, t_axis_z_min))
      if (t1 > t_min)
        t_min = t1;
      // update t_max (min(t_axis_x_max, t_axis_y_max, t_axis_z_max))
      if (t2 < t_max)
        t_max = t2;
      // rejection cases: ray misses planes for this axis
      if (t_min > t_max)
        return false;
      if (t_max < -GEOMS_EPSILON_ZERO)  // box behind ray origin
        return false;
    }
    else if (-e - h_i > GEOMS_EPSILON_ZERO || -e + h_i < GEOMS_EPSILON_ZERO) 
      return false;               // ray parallel, outside slab
  }
  float t_value = t_min > GEOMS_EPSILON_ZERO ? t_min : t_max;
  // check t_value against ray's limits
  return t_value <= r.l;
}

// Test whether segment's extremities are in the
// same half-space (half-spaces determined by normal direction).
INTERSECTTEMPLATE 
bool INTERSECTCLASS::AreExtremitiesInSameHalfSpace (const geoms::Ray& r,
                                                    const geoms::Plane& plane)
{
  geoms::Segment s(r);
  float dist_p1 = plane.Distance(s.p1);
  float dist_p2 = plane.Distance(s.p2);
  return ((dist_p1 > GEOMS_TOL_PLANE_DIST && dist_p2 > GEOMS_TOL_PLANE_DIST) || 
          (dist_p1 < -GEOMS_TOL_PLANE_DIST && dist_p2 < -GEOMS_TOL_PLANE_DIST));
}

// From Real-time rendering p. 582: when 
// solving plane equation for t, if |n_p*d| < epsilon, ray 
// is considered parallel.
INTERSECTTEMPLATE 
bool INTERSECTCLASS::IsParallel (const geoms::Ray& r,
                                 const geoms::Plane& plane,
                                 float *n_dot_d)
{
  *n_dot_d = plane.normal.Dot(r.d);
  return fabsf(*n_dot_d) < GEOMS_EPSILON_ZERO;
}

// Test whether t lays inside ray's limits.
INTERSECTTEMPLATE 
bool INTERSECTCLASS::IsInsideRayLimits (const geoms::Ray& r,
                                        const geoms::Plane& plane,
                                        float n_dot_d,
                                        float* t)
{
  *t = -(plane.d + plane.normal.Dot(r.o))/n_dot_d;
  return *t > -GEOMS_EPSILON_ZERO && *t < r.l + GEOMS_EPSILON_ZERO;
}

// Implements ray/plane intersection test:
// defined in textbook Real time rendering 2nd edition 
// by Akenine-Moller and Haines, p. 582.
INTERSECTTEMPLATE bool INTERSECTCLASS::Check (const geoms::Ray& r,
                                              const geoms::Plane& plane)
{
  float t_dummy;
  return Compute(r, plane, &t_dummy);
}

// Computes ray/plane intersection:
// defined in textbook Real time rendering 2nd edition 
// by Akenine-Moller and Haines, p. 582.
INTERSECTTEMPLATE bool INTERSECTCLASS::Compute (const geoms::Ray& r,
                                                const geoms::Plane& plane,
                                                float* t_result,
                                                bool* ray_enters_plane)
{
  // Rejection test 1: test whether segment's extremities are in the
  // same half-space (half-spaces determined by normal direction).
  if (AreExtremitiesInSameHalfSpace(r, plane))
    return false;

  // Rejection test 2 from Real-time rendering p. 582: when 
  // solving plane equation for t, if |n_p*d| < epsilon, ray 
  // is considered parallel and intersection never occurs.
  float n_dot_d;
  if (IsParallel(r, plane, &n_dot_d))
    return false;

  // Rejection test 3: t must lay inside ray's limits.
  if (IsInsideRayLimits(r, plane, n_dot_d, t_result)) {
    if (ray_enters_plane != NULL)
      *ray_enters_plane = n_dot_d < 0.0f;
    return true;
  }

  return false;
}

INTERSECTTEMPLATE bool INTERSECTCLASS::Check (const geoms::Point2D& t,
                                              const geoms::Polygon2D& polygon)
{
  bool inside = false;
  int n = polygon.GetVertexCount();
  const Point2D* e0 = polygon.GetVertex(n-1);
  const Point2D* e1;
  bool y0 = e0->y >= t.y;                // e0 above t?
  for (int i = 0; i < n; i++) {
    e1 = polygon.GetVertex(i);
    bool y1 = e1->y >= t.y;              // e1 above t?
    // are e0 and e1 one above and the other below t?
    if (y0 != y1) {
      bool is_x_pos = (e1->y - t.y)*(e0->x - e1->x) > (e1->x - t.x)*(e0->y - e1->y);
      if (y1 == is_x_pos)
        inside = !inside;
    }
    y0 = y1;
    e0 = e1;
  }
  return inside;
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::Check (const geoms::Ray& r,
                            const DsArray<geoms::Plane>& plane_face,
                            const DsArray<DsArray<float>*>& coords_face)
{
  // test ray against each face
  for (int face_i = 0; face_i < plane_face.Size(); face_i++) {
    const geoms::Plane& plane = plane_face[face_i];
    if (plane.IsDegenerate())
      continue;

    // test face's supporting plane against ray
    float t;
    bool ray_intersects_plane;
    if (Compute(r, plane, &t, &ray_intersects_plane)) {
      DsArray<float>* coords =  coords_face[face_i];
      // project vertices to fitting plane
      Project3DPointsToPlane(coords, coords->Size()/3, plane);

      // Rejection test from Real-time rendering p. 583-584:
      // calculate intersection point p and project p and polygon(face)
      // in one of the xy-,xz-,yz- planes where the area of projected
      // polygon is maximized.
      AlgVector point_hit = r.o + t*r.d;
      Polygon2D polygon_2D;
      Point2D point_2D;
      ProjectTo2D(point_2D, 
        polygon_2D, 
        point_hit, 
        plane.normal, 
        *coords);
      // if intersection point projected to 2D belongs to polygon, HIT
      if (Check(point_2D, polygon_2D))
        return true;
    }
  }
  return false;
}

INTERSECTTEMPLATE 
bool INTERSECTCLASS::Compute (const geoms::Ray& r,
                              const DsArray<geoms::Plane>& plane_face,
                              const DsArray<DsArray<float>*>& coords_face,
                              float* t1,
                              float* t2)
{
  *t1 = GEOMS_T_INSIDE_POLY;
  *t2 = GEOMS_T_INSIDE_POLY;

  // possibly ray intersects all planes
  DsArray<float> inters;
  DsArray<bool> r_enters_p;
  // test ray against each face
  for (int face_i = 0; face_i < plane_face.Size(); face_i++) {
    const geoms::Plane& plane = plane_face[face_i];
    if (plane.IsDegenerate())
      continue;

    // test face's supporting plane against ray
    float t;
    bool ray_enters_plane;
    if (Compute(r, plane, &t, &ray_enters_plane)) {
      DsArray<float>* coords =  coords_face[face_i];
      // project vertices to fitting plane
      Project3DPointsToPlane(coords, coords->Size()/3, plane);

      // Rejection test from Real-time rendering p. 583-584:
      // calculate intersection point p and project p and polygon(face)
      // in one of the xy-,xz-,yz- planes where the area of projected
      // polygon is maximized.
      AlgVector point_hit = r.o + t*r.d;
      Polygon2D polygon_2D;
      Point2D point2D;
      ProjectTo2D(point2D, 
        polygon_2D, 
        point_hit, 
        plane.normal, 
        *coords);
      // if intersection point projected to 2D belongs to polygon, HIT
      if (Check(point2D, polygon_2D)) {
        inters.Append(t);
        r_enters_p.Append(ray_enters_plane);
      }
    }
  }

  // MISS ?
  if (inters.Size() == 0)
    return false;
  else if (inters.Size() == 1) {
    // decide whether t1 or t2 gets GEOMS_T_INSIDE_POLY value
    geoms::Segment s(r);
    if (r_enters_p[0]) {
      // segment end must lay inside all half-spaces
      if (!IsInsideAllHalfSpaces(s.p2, plane_face))
        return false;
      else
        *t1 = inters[0];
    }
    else {
      // segment start must lay inside all half-spaces
      if (!IsInsideAllHalfSpaces(s.p1, plane_face))
        return false;
      else
        *t2 = inters[0];
    }
  }
  else {
    // find min and max t
    float tmin = inters[0];
    float tmax = inters[0];
    int i_tmin = 0;
    int i_tmax = 0;
    for (int i = 1; i < inters.Size(); i++) {
      if (inters[i] < tmin) {
        tmin = inters[i];
        i_tmin = i;
      }
      else if (inters[i] > tmax) {
        tmax = inters[i];
        i_tmax = i;
      }
    }
    // when tmin differs from tmax, store results
    if (fabsf(tmin - tmax) > GEOMS_TOL_PLANE_DIST) {
      *t1 = tmin;
      *t2 = tmax;
    }
    else {
      // when tmin too close to tmax and one enters and the other leaves poly, ignore intersection
      if (r_enters_p[i_tmin] != r_enters_p[i_tmax])
        return false;
      else // otherwise, pick only one of them
      {
        // decide whether t1 or t2 gets GEOMS_T_INSIDE_POLY value
        geoms::Segment s(r);
        if (r_enters_p[i_tmin]) {
          // segment end must lay inside all half-spaces
          if (!IsInsideAllHalfSpaces(s.p2, plane_face))
            return false;
          else
            *t1 = tmin;
        }
        else {
          // segment start must lay inside all half-spaces
          if (!IsInsideAllHalfSpaces(s.p1, plane_face))
            return false;
          else
            *t2 = tmax;
        }
      }
    }
  }
  return true;
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::CreatePlanes (int poly_index,
                                   DsArray<geoms::Plane>& plane_face,
                                   DsArray<DsArray<float>*>& coords_face)
{
  int faces_count = m_poly_model.GetFaceCount(poly_index);

  plane_face.Resize(faces_count);
  coords_face.Resize(faces_count);

  for (int face_i = 0; face_i < faces_count; face_i++) {
    // read face's number of vertices and resize vertices array
    DsArray<float>* coords =  coords_face[face_i] = new DsArray<float>;
    int vert_count = m_poly_model.GetFaceVertexCount(poly_index, face_i);
    coords->Resize(3*vert_count, true);
    float* v = coords->GetArray();

    // read face's vertices coordinates and build plane
    m_poly_model.GetFaceCoords(v, poly_index, face_i);

    // create fitting plane for face_i
    CreateFittingPlane(plane_face[face_i], vert_count, v);

    // postpone vertices fitting to plane projection
  }
}

INTERSECTTEMPLATE bool INTERSECTCLASS::Check (const geoms::Ray& r,
                                              int poly_index)
{
  // build planes
  DsArray<geoms::Plane> plane_face;
  DsArray<DsArray<float>*> coords_face;
  CreatePlanes(poly_index, plane_face, coords_face);

  // test ray against polyhedra
  bool hit = Check(r, plane_face, coords_face);

  // clean up
  for (int fi = 0; fi < plane_face.Size(); fi++)
    delete coords_face[fi];

  return hit;
}

INTERSECTTEMPLATE bool INTERSECTCLASS::Compute (const geoms::Ray& r,
                                                int poly_index,
                                                float* t1,
                                                float* t2)
{
  // build planes
  DsArray<geoms::Plane> plane_face;
  DsArray<DsArray<float>*> coords_face;
  CreatePlanes(poly_index, plane_face, coords_face);

  // test ray against each face
  bool hit = Compute(r, plane_face, coords_face, t1, t2);

  // clean up
  for (int fi = 0; fi < plane_face.Size(); fi++)
    delete coords_face[fi];

  return hit;
}

INTERSECTTEMPLATE bool INTERSECTCLASS::Check (const geoms::Segment& s)
{
  if (m_hierarchy == NULL || m_hierarchy->GetTreeRoot() == NULL)
    return false;

  // ray-object intersections are done
  geoms::Ray r(s.p1, s.p2-s.p1, true);

  // iterate over hierarchy and check intersection with bounding volumes
  DsQueue<vrbv::Node*> nodes_queue;
  nodes_queue.EnqueueConst(m_hierarchy->GetTreeRoot());
  vrbv::Node* node;

  while (nodes_queue.Dequeue(&node)) {
    // test intersection against node's BB
    if (Check(r, node->getBoundingBox())) {
      if (!node->isLeaf()) {
        assert(node->getLeftChild() != NULL);
        assert(node->getRightChild() != NULL);
        // not leaf: enqueue node's children
        if (node->getLeftChild() != NULL)
          nodes_queue.EnqueueConst(node->getLeftChild());
        if (node->getRightChild() != NULL)
          nodes_queue.EnqueueConst(node->getRightChild());
      }
      else {
        // leaf: iterate over blocks in this node and test
        GeometryVector& geom_vec = node->getGeometries();
        for (unsigned int geom_i = 0; geom_i < geom_vec.size(); geom_i++) {

          int block_index = geom_vec[geom_i]->getId();
          const Block& block = m_poly_model.GetBlock(block_index);

          // Poly's in this block have to be checked against segment
          for (int i = 0; i < block.GetPolyCount(); i++) {
            int poly_index = block.GetPoly(i);
#if 0 && DEBUG_TESTED_ELEMS // store every poly in this block
            if (m_tested_elems != NULL)
              m_tested_elems->Set(m_poly_model.GetPolyID(poly_index), true);
#endif
#if COLLECT_CUT_STATISTICS
            m_last_result.elem_tested_count++;
#endif
            // check intersection with poly
            if (Check(r, poly_index)) {
#if DEBUG_TESTED_ELEMS // store intersected poly
              if (m_tested_elems != NULL)
                m_tested_elems->Set(m_poly_model.GetPolyID(poly_index), true);
#endif
              return true;  // at least one poly intercepted by segment
            }
          }
        }
      }
    }
  }
  return false;
}

INTERSECTTEMPLATE int
INTERSECTCLASS::SegmentIntervalCompare (CutSegmentInterval* s_i_1,
                                        CutSegmentInterval* s_i_2)
{
  float diff_t_min = s_i_1->t_min - s_i_2->t_min;

  // t_min_1 ~ t_min_2?
  if (fabsf(diff_t_min) < GEOMS_EPSILON_ZERO)  // use t_max to decide
    return s_i_1->t_max - s_i_2->t_max <= 0.f ? -1 : 1;

  return diff_t_min <= 0.f ? -1 : 1;
}

INTERSECTTEMPLATE bool INTERSECTCLASS::Compute (const geoms::Segment& s, 
                                                bool clean_prev_results)
{
  if (clean_prev_results)
    FreeResult();

  if (m_hierarchy == NULL || m_hierarchy->GetTreeRoot() == NULL)
    return false;

  // intervals created by cut with segment
  DsArray<CutSegmentInterval*> intervals;

  // ray-object intersections are actually done
  geoms::Ray r(s.p1, s.p2-s.p1, true);

  // iterate over hierarchy and check intersection with bounding volumes
  DsQueue<vrbv::Node*> nodes_queue;
  nodes_queue.EnqueueConst(m_hierarchy->GetTreeRoot());
  vrbv::Node* node;

  while (nodes_queue.Dequeue(&node)) {
    // test intersection against node's BB
    if (Check(r, node->getBoundingBox())) {
      if (!node->isLeaf()) {
        assert(node->getLeftChild() != NULL);
        assert(node->getRightChild() != NULL);
        // not leaf: enqueue node's children
        if (node->getLeftChild() != NULL)
          nodes_queue.EnqueueConst(node->getLeftChild());
        if (node->getRightChild() != NULL)
          nodes_queue.EnqueueConst(node->getRightChild());
      }
      else {
        // leaf: iterate over blocks in this node and compute intersections
        float t1, t2;
        GeometryVector& geom_vec = node->getGeometries();
        for (unsigned int geom_i = 0; geom_i < geom_vec.size(); geom_i++) {

          int block_index = geom_vec[geom_i]->getId();
          const Block& block = m_poly_model.GetBlock(block_index);
          
          // Poly's in this block have to be checked against segment
          for (int i = 0; i < block.GetPolyCount(); i++) {
            int poly_index = block.GetPoly(i);
#if 0 && DEBUG_TESTED_ELEMS // store every poly in this block
            if (m_tested_elems != NULL)
              m_tested_elems->Set(m_poly_model.GetPolyID(poly_index), true);
#endif
#if COLLECT_CUT_STATISTICS
            m_last_result.elem_tested_count++;
#endif
            // check intersection with poly
            if (Compute(r, poly_index, &t1, &t2)) {
              // store intersected poly
              CutSegmentInterval* interv = new CutSegmentInterval;
              interv->poly_id = m_poly_model.GetPolyID(poly_index);
              interv->t_min = (t1 == GEOMS_T_INSIDE_POLY) ? t1 : t1 * r.inv_l; //0..1
              interv->t_max = (t2 == GEOMS_T_INSIDE_POLY) ? t2 : t2 * r.inv_l; //0..1
              intervals.Append(interv);
#if DEBUG_TESTED_ELEMS // store intersected poly
              if (m_tested_elems != NULL)
                m_tested_elems->Set(m_poly_model.GetPolyID(poly_index), true);
#endif
            }
          }
        }
      }
    }
  }

  // sort result into ascending intervals' t_min
  CutSegmentInterval** seg_interv = intervals.GetArray();
  int n = intervals.Size();
  utlSimpleQuickSort(seg_interv,
                     n,
                     INTERSECTCLASS::SegmentIntervalCompare);
  // analyze tmax[i] and tmin[i+1] to correct floating point imprecisions
  for (int i = 0; i < n-1; i++) {
    CutSegmentInterval* interv_1 = intervals[i];
    CutSegmentInterval* interv_2 = intervals[i+1];
    if (fabsf(interv_1->t_max -interv_2->t_min) < GEOMS_TOL_MIN_MAX_DIST)
      interv_1->t_max = interv_2->t_min;
  }

  // In some cases, due to the fit plane phase of the intersection test against
  // cell, a segment may only enter a cell, never leaving it. We ignore those
  // cases, excluding them from the final result.
  // Those cases are identified as the intersections that have t_max inside
  // polygon (excluding the last intersection).
  
  // decide which intervals to keep
  int num_inters_to_test = n-1;
  for (int i = 0; num_inters_to_test > 0; num_inters_to_test--) {
    if (intervals[i]->t_max == GEOMS_T_INSIDE_POLY)
      intervals.Remove(i);
    else
      i++;
  }

  // update result
  m_last_result.intervals_count = intervals.Size();
  m_last_result.intervals = intervals.TakeOverArray();
  return m_last_result.intervals_count != 0;
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::ProjectTo2D (Point2D& point_2D, 
                                  Polygon2D& polygon_2D, 
                                  const AlgVector& point_3D,
                                  const AlgVector& plane_normal, 
                                  const DsArray<float>& coords)
{
  // decide which component to neglect to maximize polygon's projected area
  static const int X = 0;
  static const int Y = 1;
  static const int Z = 2;
  int coord_to_neglect = -1;
  float nx_abs = fabsf(plane_normal.x);
  float ny_abs = fabsf(plane_normal.y);
  float nz_abs = fabsf(plane_normal.z);
  if (nx_abs > ny_abs) {
    if (nx_abs > nz_abs)
      coord_to_neglect = X;  // x component
    else
      coord_to_neglect = Z;  // z component
  }
  else {
    if (ny_abs > nz_abs)
      coord_to_neglect = Y;  // y component
    else
      coord_to_neglect = Z;  // z component
  }
  static const int coords_to_keep[3][2] = {{Y, Z}, {X, Z}, {X, Y}};
  int c0 = coords_to_keep[coord_to_neglect][0];
  int c1 = coords_to_keep[coord_to_neglect][1];

  // neglect component in point p (equivalent to projection)
  const float* p_inters = point_3D;
  point_2D.x = p_inters[c0];
  point_2D.y = p_inters[c1];

  // build Polygon2D neglecting component (equivalent to projection)
  const float* v_p = coords.GetArrayConst();
  int v_count = coords.Size() / 3;
  for (int v_i = 0; v_i < v_count; v_i++, v_p += 3) {
    polygon_2D.AddVertex(v_p[c0], v_p[c1]);
  }
}

INTERSECTTEMPLATE 
void INTERSECTCLASS::Project3DPointsToPlane (DsArray<float>* coords,
                                             int points_count,
                                             const geoms::Plane& plane)
{
  float* c = coords->GetArray();
  for (int i = 0; i < points_count; i++, c += 3) {
    float dist = plane.Distance(AlgVector(c[0], c[1], c[2]));
    c[0] = c[0] - plane.normal.x * dist;
    c[1] = c[1] - plane.normal.y * dist;
    c[2] = c[2] - plane.normal.z * dist;
  }
}

float Dot (const float* v1, const float* v2)
{
  return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}
