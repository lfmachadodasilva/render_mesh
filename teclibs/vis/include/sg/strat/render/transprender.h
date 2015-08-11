// Transparent scene renderer
// fabraham@tecgraf.puc-rio.br
// Jul 2003

#ifndef SG_TRANSP_RENDER
#define SG_TRANSP_RENDER

#include "flexrender.h"

#define SG_MAX_PEELS 1024

class SG_API SGTranspRender : public SGFlexRender
{
  unsigned int m_program;
  unsigned int m_zbuffer2;
  unsigned int m_peels[SG_MAX_PEELS];
  unsigned int m_opaque_peel;
  unsigned int m_queries[SG_MAX_PEELS];
  unsigned int m_results[SG_MAX_PEELS];
  bool m_correct_transparency;
  bool m_supports_depth_peeling;
  int m_num_frames;
  int m_num_peels;
  int m_max_peels;
  int m_query_frequency;
  int m_curr_peel;
  int m_width, m_height;
  int m_curr;
  int m_bindepth;
  static bool s_supports_depth_peeling;

  static void InitExtensions ();

  void InitPeel (unsigned int peel);
  void BeginPeelsDrawing();
  void PeelPreRender(int id);
  void PeelPostRender(int id);
  void EndPeelsDrawing();
  void Resize (int w, int h);
public:
  SGTranspRender ();
  virtual ~SGTranspRender ();

  void Init ();
  bool SetCorrectTransparency (bool flag);
  void SetMaxPeels (int max_num_peels);
  void SetQueryFrequency (int query_frequency);

  // overwritten strategy methods
  virtual int Load (SGBin* b);
  virtual int Load (SGColScene* s);
  virtual int Unload (SGBin* b);
  virtual int Unload (SGColScene* s);
};

#endif
