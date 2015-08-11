#ifndef TOP_MESH_QUALITY_H
#define TOP_MESH_QUALITY_H

#include <tops/tops.h>

/**
  Mesh quality.
*/
class TOPS_API TopMeshQuality
{
protected:
  TopModel* m_model;

public:
  TopMeshQuality(TopModel* m);

  virtual ~TopMeshQuality();

  /**
      Computes the quality of a single element.
  */
  virtual double GetElemQuality(const TopElement& el) = 0;

  /**
    Gets the limits of the quality values imposed by this metric.
  */
  virtual void GetMetricLimits(double* minval, double* maxval) = 0;

  /**
    Gets the limits of the quality values computed from the model.
  */
  virtual void GetMeshLimits(double* minval, double* maxval);

  /**
    Computes the histogram of the mesh quality distribution.
    @param n Number of intervals.
    @param minval Minimum value.
    @param maxval Maximum value.
    @param histogram Output array, with size n, for the histogram data. 
  */
  void ComputeHistogram(int n, double minval, double maxval, int* histogram);
};

#endif

