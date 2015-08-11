// Point extractor
// rodesp@tecgraf.puc-rio.br
// Mar 2011

#ifndef TPV_GEOMETRY_POINTEXTRACTOR_H
#define TPV_GEOMETRY_POINTEXTRACTOR_H

class UGLArray;
class TopModel;
class TopElement;
class TpvProperty;

/**
 * Interface.
 * Extracts points from TopS entities into vertex arrays.
 */
class TpvPointExtractor
{
public:
  virtual ~TpvPointExtractor ()
  {
  }

  /**
   * Extracts point coordinates from an element.
   * 'model' is the model that owns the element.
   * Coordinates must be added to the 'positions' array using AddValue().
   */
  virtual void ExtractPositions (const TopElement& elem, 
                                 TopModel* model, 
                                 UGLArray* positions)
  {
  }

  /**
   * Extracts point field from the field associated to an element.
   * The number of field values must correspond to the number of point positions
   * extracted.
   * 'model' is the model that owns the element.
   * Field values must be added to the 'texcoords' array using AddValue().
   */
  virtual void ExtractField (const TopElement& elem, 
                             TopModel* model, 
                             TpvProperty* property, 
                             UGLArray* texcoords)
  {
  }
};

#endif