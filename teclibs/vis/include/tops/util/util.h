/**
  TopS - Topological data structure for mesh representation.
  
  TopS is a software developed by Tecgraf/PUC-Rio & UIUC.
  It is requested that the TopS users provide the appropriate
  credits and references to the work.
  
  References:
  1 - W. Celes, G.H. Paulino, R. Espinha, "A compact adjacency-based
  topological data structure for finite element mesh representation",
  IJNME, 2005 (in press)
  2 - W. Celes, G.H. Paulino, R. Espinha, "Efficient Handling of Implicit
  Entities in Reduced Mesh Representations", JCISE, Special Issue on
  Mesh-Based Geometric Data Processing, 2005 (in press)
  
  Aug 2005
*/

#ifndef _TOP_UTIL_H
#define _TOP_UTIL_H

#include <assert.h>
#include <tops/tops.h>
#include "meshquality.h"

class TOPS_API TopMakeCrackListener {
public:
  virtual ~TopMakeCrackListener() {}
  virtual void InsertElem(TopModel* m, TopElement el) = 0;
  virtual void CrackFacet(TopModel* m, TopFacetUse fu1, TopFacetUse fu2) = 0;
};

/**
    Some utility functions.
*/
class TOPS_API TopUtil
{
private:
  static bool SmoothWeighted(
    TopModel* m, TopMeshQuality* quality, int maxsteps, double factor, 
    double qmin, double qmax, int* constrained);

  static bool SmoothAvg(
    TopModel* m, TopMeshQuality* quality, int maxsteps, double factor, 
    double qmin, double qmax, int* constrained);

public:

  /**
      Randomly sort objects.
    First, objects are added to the sorter by using the Add() method. 
    Then the method Sort() is called.
  */
  template<class T>
  class RandomSorter
  {
  private:  
    struct SortBin
    {
      T v;
      int rnd;
      SortBin(T v, int rnd) : v(v), rnd(rnd) {}
    };
    TopRawArray<SortBin> m_v;
    static int Cmp(const void* a, const void* b)
    {
      if (((SortBin*) a)->rnd < ((SortBin*) b)->rnd)
        return -1;
      else if (((SortBin*) a)->rnd > ((SortBin*) b)->rnd)
        return 1;
      else 
        return 0;
    }
  public:
    RandomSorter() {}
    ~RandomSorter() {}
    void Add(T v) {m_v.Append(SortBin(v, rand()));}
    void Sort() {qsort(m_v.GetArray(), m_v.Size(), sizeof(SortBin), Cmp);}
    int GetSize() { return m_v.Size(); }
    T Get(int i) { return m_v.Get(i).v; }
  };

  /**
    Sets ids of nodes and elements in the model. The ids are sequentially
    set, following the traversal order of NodeItr and ElemItr, and starting 
    from the given initial ids.
  */
  static void SetIds(TopModel* model, 
                     int initial_node_id, 
                     int initial_elem_id);

  /**
      Jitters internal nodes of the model.
    Assumes that mesh has not been modified yet.
    Currently, only for triangular and tetrahedral elements.
  */
  static void JitterInternalNodes(TopModel* m, double factor);

  /**
      Checks the orientation of all the faces of the model.
    Assumes that faces are planar.
  */
  static bool CheckFaceOrientations(TopModel* m);

  /**
    Checks whether mesh geometry is degenerated (e.g. two
    nodes of a bulk element are at the same position).
  */
  static bool CheckNonDegenerateGeometry(TopModel* m);

  /**
      Computes the bounding box of the model.
  */
  static void ComputeBoundingBox(TopModel* m, 
    double* xmin, double* xmax, double* ymin, double* ymax, double* zmin, double* zmax);

  /**
      Smooths triangular or tetrahedral meshes using Laplacian filter
    and the given quality metric, with weight factor equal to 1 for every 
    edge incident to each of the smoothed vertices.
      The algorithm will converge if every element in the mesh has quality
    grater required quality factor.
    @param quality Mesh quality metric.
    @param maxsteps Maximum number of smooth steps.
    @param factor Nodal movement multiplication factor.
    @param qmin Minimum required quality factor.
    @param qmax Maximum required quality factor.
    @param constrained Nodal constraint array. If constrained[i] != 0,
    node will not be moved.
    @param const_nodes Array of the constrained nodes.
    @return Whether the algorithm has converged or not.
  */
  static bool Smooth(TopModel* m, 
    TopMeshQuality* quality, int maxsteps, double factor, 
    double qmin, double qmax, int* constrained);

#ifdef TOP_USE_NON_ORIENTED_IMPLICIT_ENTITIES 
  /**
    Refines the facet arond the given vertex for a tolerance value.
    Parameters:
      v: A vertex in the model.
      f: One of the facets incident to the vertex v.
      tol: Tolerance factor. The facet is repeatedly split until it reaches
      a size that is less than the given tolerance.
  */
  static TopFacet RefineVertexFacet4K8(TopModel* m, TopVertex v, TopFacet f, double tol);

  /**
    Refines all the facet arond the given vertex for a tolerance value.
    (see RefineVertexFacet4K8).
    Parameters:
      v: A vertex in the model.
      tol: Tolerance factor. The facets is repeatedly split until it reaches
      a size that is less than the given tolerance.
  */
  static TopVertex RefineVertex4K8(TopModel* m, TopVertex v, double tol);

  /**
    Creates a crack along the interior of a triangle of a 4K mesh, for
    a given vertex and direction of propagation.

    Starting from a vertex, it traverses all the vertex-uses (vu), looking
    for the one in the triangle which is on the given direction of propagation. 
    The crack direction is rounded to the closest multiple of 45 degrees. Hence,
    if the local id of the vertex-use is 2, it is in the square-angle corner of the triangle.
    In this case, the crack can be inserted along either one of the two incident facets 
    or the opposite facet is first swapped and then the crack is inserted along the
    resulting facet. If local id is 0 or 1, the crack is always inserted along one of its incident
    facets.

    Parameters:
      v: The vertex around which the crack will be created.
      dirx, diry: Direction of propagation.
      can_split: Defines whether edge swapping (and recursively, some splits) are 
        allowed.
      insert_coh: Whether a cohesive element will be inserted on the crack.
  */
  static void MakeCrack4K8(TopModel* m, TopVertex v, double dirx, double diry, 
    bool can_split, bool insert_coh, TopMakeCrackListener* listener = NULL);
#endif
};

#endif

