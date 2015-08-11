#ifndef WATER_OGL_RENDERER
#define WATER_OGL_RENDERER

#include "defines.h"
#include "watersim.h"
#include "waterindex.h"

#define WATER_GRID_32  5
#define WATER_GRID_64  6
#define WATER_GRID_128 7
#define WATER_GRID_256 8

class CWaterOGLRenderer
{
public:
	CWaterOGLRenderer( CWaterSim* waterSim );
	~CWaterOGLRenderer();
	void Init();

	void Load();
	void UnLoad();
	void Render();
    void Render(int lod, int isUpBorderLow, int isDownBorderLow, int isLeftBorderLow, int isRightBorderLow);
	void Render_lowest();
	void DrawNormals();

    int TextureRepeat(int number);
	int TextureRepeat();

private:
	int m_gridSize;         // watermap size in array units
	int m_gridSizePlusOne;  // watermap size in array units plus One
	WaterIndexes* m_indexes;
	CWaterSim*    m_waterSim;
	float*        m_vertex;        // Vertex array pointer
	float*        m_normal;        // Normal array pointer
	float*        m_texCoord;      // Texture Coordinate array pointer
    int           m_textureRepeat;     // Number of Times that the texture repeat across surface in both ocean plane directions

	int isCompiledVAExtensionPresent;
    
	// private Methods
	void initTexCoord();
	void allocMemory();
	void freeMemory();
};

#endif

