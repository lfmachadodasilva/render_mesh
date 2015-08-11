/******************************************************************************
*******************************************************************************
**
**  Terrain Library
**  Tecgraf PUC-Rio
**  Autor: Luiz Gustavo Bustamante Magalhaes
**  Date: 07 October 2004
**
**  Brief Description: Implementation of the P. Lindstrom and V. Pascucci paper 
**                     Terrain Simplification Simplified (May 2002)
**
*******************************************************************************
******************************************************************************/

#ifndef TERRAIN
#define TERAAIN

#ifndef TERRAIN_DLL
# ifndef TEC_DLL
#  define TERRAINAPI
# else
#  define TERRAINAPI __declspec(dllimport)
# endif
#else
# define TERRAINAPI __declspec(dllexport)
#endif

class TerrainImpl;
class Rnd;
class UtlTexture;

/** Terrain Class Definition. */
class TERRAINAPI Terrain
{
  friend class TerrainNormals;
public:
  typedef void (*PROGRESS_CALLBACK)(void*, float);

  Terrain();
  ~Terrain();

  /** Initialize.
  * 
  * @return Returns 1 if sucess and 0 if not.
  */
  int Initialize();

  /** LoadFromImage.
  * Loads a terrain from a image File and do all necessary preprocessing.
  * 
  * @param heightMapFileName [in] Image heightmap filename, best if dimensions are power of 2 plus 1.
  * @param textureFileName [in] Texture filename, best if dimensions are power of 2.
  * @param reindex [in] Reindex or not the terrain data layout.
  * @param origin_x [in] Terrain Origin X-Position in World Coordinates (default is 0).
  * @param origin_y [in] Terrain Origin Y-Position in World Coordinates (default is 0).
  * @param origin_z [in] Terrain Origin Z-Position in World Coordinates (default is 0).
  * @param scale_x [in] Terrain Origin X-Position in World Coordinates (default is 1).
  * @param scale_y [in] Terrain Origin Y-Position in World Coordinates (default is 1).
  * @param scale_z [in] Terrain Origin Z-Position in World Coordinates (default is 1).
  * @return Returns 1 if sucessful and 0 if not.
  */
  int LoadFromImage(char* heightMapFileName, char* textureFileName=0, bool reindex = 0,
				    const float origin_x = 0, const float origin_y = 0, const float origin_z = 0,
					const float scale_x = 1 , const float scale_y = 1 , const float scale_z = 1);

  int Load(float* heightMap, int h_width, int h_height,
	       unsigned char* texturePtr, int t_width, int t_height,
		   bool reindex = 0,
		   const float origin_x = 0, const float origin_y = 0, const float origin_z = 0,
		   const float scale_x = 1 , const float scale_y = 1 , const float scale_z = 1);

  /** Load.
  * Loads an already preprocessed terrain file.
  * 
  * @param heightMapFileName [in] Image heightmap filename, best if dimensions are power of 2 plus 1.
  * @param outOfCore [in] outOfCore must be zero to disable or 1 to enable.
  * @param textureFileName [in] Texture filename, best if dimensions are power of 2.
  * @return Returns 1 if sucess and 0 if not.
  */
  int Load(char* vtfFilename, bool outOfCore=0, char* textureFileName=0);

  /** Save.
  * Saves an already preprocessed terrain file.
  * 
  * @param filename [in] Destiny filename (usually extension should be .vtf).
  * @return Returns 1 if sucessful and 0 if not.
  */
  int Save(const char* filename);

  /** Render.
  * Renders the Terrain.
  */
  void Render();

  /** GetUpdatePosition.
  *
  * Checks if update viewer position is enabled or not.
  * It can be used to externaly view how the view frustum works from another position.
  * 
  * @return Returns 1 if update position is enabled and 0 if not.
  */
  int GetUpdatePosition() { return m_updatePosition; }

  /** SetUpdatePosition.
  *
  * @param update update must be 1 to Enable and 0 to disable.
  * @return Return old state.
  */
  int SetUpdatePosition(int update);

  /** GetBBox.
  *
  * @param x_min [out] Bounding Box X-Minimum coordinate.
  * @param y_min [out] Bounding Box Y-Minimum coordinate.
  * @param z_min [out] Bounding Box Z-Minimum coordinate.
  * @param x_max [out] Bounding Box X-Maximum coordinate.
  * @param y_max [out] Bounding Box Y-Maximum coordinate.
  * @param z_max [out] Bounding Box Z-Maximum coordinate.
  */
  void GetBBox(float *x_min, float *y_min, float *z_min,
	           float *x_max, float *y_max, float *z_max);

  /** GetHeight.
  * Returns the height at position (xWorld, zWorld).
  *
  * @param xWorld [in] X-Position in World Coordinates.
  * @param zWorld [in] Z-Position in World Coordinates.
  * @param height [out] pointer to store the resulting height.
  * @return Returns false if not sucessfull or if not inside terrain boundaries.
  */
  bool GetHeight(float xWorld, float zWorld, float* height);

  /** GetErrorTolerance.
  * Error tolerance is given in pixels. 
  * 
  * @return Returns the current error tolerance.
  */
  float GetErrorTolerance() { return m_errorTolerance; }

  /** SetErrorTolerance.
  * Error tolerance is given in pixels. 
  * So if you want an error of at most 2.5 pixels you should set to this value (2.5).
  *
  * @param tolerance [in] Tolerance given in pixels(should not be 0.0 or negative).
  * @return Return old error tolerance.
  */
  float SetErrorTolerance(float tolerance);

  /** GetEnableTexture.
  * Checks if rendering with texture is enabled or not.
  *
  * @return Return 1 if texture is enable and 0 otherwise.
  */
  int GetEnableTexture() { return m_textureEnabled; }

  /** SetEnableTexture.
  * Enables a rendering the terrain with texture if a texture was loaded.
  *
  * @param texture [in] texture must be 1 to Enable and 0 to disable.
  * @return Return old state.
  */
  int SetEnableTexture(int texture);

  /** SetProgressCallback.
  * With this function the user can set an progress callback.
  * Function must have this assignature "void callback_function(void* data, float progress);"
  *
  * @param cb [in] function that is going to be called.
  * @param data [in] void pointer to any data that is going to be passed to the callback function.
  */
  void SetProgressCallback(PROGRESS_CALLBACK cb, void* data);
  int GetNumVertices ();

  UtlTexture* GetTexture() { return m_texture; }

protected:
  float        m_errorTolerance;
  int          m_updatePosition;
  int          m_textureEnabled;
  TerrainImpl* m_terrain;
  Rnd*         m_renderer;
  UtlTexture*  m_texture;
};

#endif
