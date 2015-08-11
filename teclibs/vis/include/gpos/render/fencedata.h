#ifndef FENCE_DATA_H
#define FENCE_DATA_H

#include <GL/glew.h>
#include <alg/vector.h>
#include <ds/array.h>

struct UGLCylinder;
class VglViewSurface;

class FenceData
{
public:
  /**
   * Constructor.
   *
   * @param r red component of the fence color.
   * @param g green component of the fence color.
   * @param b blue component of the fence color.
   * @param radius fence's radius, in pixels.
   */
  FenceData (float r=-1.0f, float g=-1.0f, float b=-1.0f, float radius=3.0f);
  virtual ~FenceData ();
  /**
   * Returns the fence data classname (useful for safe casts).
   */
  const char* ClassName () const { return "FenceData"; };
  
  void IncRef () {++m_refcount;}
  void DecRef () {--m_refcount;}
  int GetRefCount () const {return m_refcount;}

  /**
   * Equal operator.
   */
  FenceData& operator= (const FenceData& f);

  /*********************** Posts operations. *********************************/
  /**
   * Return fence's posts count.
   * @return Posts count.
   */
  int GetPostCount () const
  {
    return m_posts.Size();
  }

  /**
   * Return a post coordinates.
   * @param post_i post index, from 0 to post_count-1
   * @return fence post coordinates
   */
  AlgVector GetPostCoords (int post_i) const
  {
    return m_posts.Get(post_i);
  }

  /**
   * Reset fence, deleting all added posts.
   */
  void Clear ()
  {
    assert(m_edit_enabled);
    m_posts.Clear();
    m_post_rad.Clear();
  }

  /**
   * Add post with coordinates (x,y,z) to the end of the fence.
   *
   * @param x post's x coordinate
   * @param y post's y coordinate
   * @param z post's z coordinate
   */
  void AddPost (float x, float y, float z);

  /**
   * Set ith post's coordinates (x,y,z).
   *
   * @param post_i index from 0..n-1
   * @param x post's x coordinate
   * @param y post's y coordinate
   * @param z post's z coordinate
   * @return when post updated, false when index not valid.
   */
  bool SetPost (int post_i, float x, float y, float z);

  /**
   * Delete post with index post_i.
   *
   * @param post_i index from 0..n-1
   * @return true when post deleted, false when index not valid.
   */
  bool DeletePost (int post_i);

  /**
   * Draw fence data.
   * For now draw fence's posts.
  */
  void Draw () const;

  /**
   * Update radii in world coordinates for posts. Should be called by cliente
   * before each Draw call.
   * @param width_factor optional width factor
   */
  void UpdatePostsRadii (float width_factor = 1.f);

  void SetPickActive (bool flag)
  {
    m_pick_active = flag;
  }

  bool IsPickActive () const
  {
    return m_pick_active;
  }

  void SetPostColor (float r, float g, float b)
  {
    m_post_color.Set(r, g, b);
  }

  void GetPostColor (float* r, float* g, float* b) const
  {
    *r = m_post_color.x;
    *g = m_post_color.y;
    *b = m_post_color.z;
  }
  
  void GetPostColor (AlgVector* color) const
  {
    color->Set(m_post_color);
  }

  void SetSliceColor (float r, float g, float b)
  {
    m_slice_color.Set(r, g, b);
  }

  void GetSliceColor (float* r, float* g, float* b) const
  {
    *r = m_slice_color.x;
    *g = m_slice_color.y;
    *b = m_slice_color.z;
  }

  void GetSliceColor (AlgVector* color) const
  {
    color->Set(m_slice_color);
  }

  void SetPostRadius (float r)
  { 
    m_post_rad_window = r;
  }

  float GetPostRadius () const
  { 
    return m_post_rad_window; 
  }

  void SetZLimits (float zmin, float zmax)
  {
    m_zmin = zmin;
    m_zmax = zmax;
  }

  void GetZLimits (float* zmin, float* zmax) const
  {
    *zmin = m_zmin;
    *zmax = m_zmax;
  }

  /**
   * Turn in/off edition mode (useful for Draw method).
   * @param flag should be true to turn on edition mode.
   * NOTE: when true, view mode is automatically turned off,
   * since they are mutually exclusive.
   */
  void SetEditEnabled (bool flag)
  {
    m_edit_enabled = flag;
    if (flag)
      SetViewEnabled(false);
  }
  /**
   * Return whether fence is in edition mode.
   * @return whether fence is in edition mode.
   */
  bool IsEditEnabled () const
  {
    return m_edit_enabled;
  }

  /**
   * Turn in/off view mode (useful for Draw method).
   * @param flag should be true to turn on view mode.
   * NOTE: when true, edition mode is automatically turned off,
   * since they are mutually exclusive.
   */
  void SetViewEnabled (bool flag)
  {
    m_view_enabled = flag;
    if (flag)
      SetEditEnabled(false);
  }
  /**
   * Return whether fence is in view mode.
   * @return whether fence is in view mode.
   */
  bool IsViewEnabled () const
  {
    return m_view_enabled;
  }
  /**
   * Configure posts opacity.
   */
  void SetPostsOpacity (float alpha)
  {
    m_posts_opacity = alpha;
  }
  /**
   * Return whether fence should be drawn.
   */
  bool IsDrawEnabled () const
  {
    return m_edit_enabled || m_view_enabled;
  }
private:
  /**
   * Check whether post_i has coordinates x,y using a certain tolerance.
   */
  bool IsPost (int post_i, float x, float y) const;
  /**
   * Check whether post_i has coordinates x,y,z using a certain tolerance.
   */
  bool IsPost (int post_i, float x, float y, float z) const;

  /**
   * Draw fence's posts.
   */
  void DrawPosts () const;

  /**
   * Draw fence's slices (quads) - link pairs of consecutive posts.
   */
  void DrawSlices () const;

private:
  int m_refcount;             /**< Reference count.                   */
  AlgVector m_post_color;     /**< Post RGB color (0..1 range).       */
  AlgVector m_slice_color;    /**< Fence slice RGB color (0..1 range).*/
  float m_post_rad_window;    /**< Post radius in window space.       */
  DsArray<float> m_post_rad;  /**< Posts radii in world space.         */
  bool m_pick_active;         /**< Active pick flag.                  */
  bool m_edit_enabled;        /**< Flag to control draw and updates.  */
  bool m_view_enabled;        /**< Flag to control draw and updates.  */
  float m_posts_opacity;      /**< Posts alpha.                       */
  float m_zmin;               /**< Minimum Z-coordinate.              */
  float m_zmax;               /**< Maximum Z-coordinate.              */
  UGLCylinder* m_post_cyl;    /**< Post cylinder shape.               */
  DsArray<AlgVector> m_posts; /**< Posts coordinates in the fence.    */
};

#endif  // FENCE_DATA_H
