#ifndef WATERSIM
#define WATERSIM

#ifdef _WIN32
#include <windows.h>
#endif

#include <rfftw.h>
#include "defines.h"
#include "triple.h"

// watermap size in array units
const int WATERWIDTH        = 64;

// constants and macros for determining amplitude for each wave number
// all units are in meters, seconds
#ifndef M_PI
# define M_PI			3.14159
#endif

#define WATER_GRID_32  5
#define WATER_GRID_64  6
#define WATER_GRID_128 7
#define WATER_GRID_256 8

class OCEAN_API CWaterSim
{
public:
  CWaterSim( int gridPower, float waterSize, float windAngleDegrees, float amplitudeFactor );
  ~CWaterSim();

  void Init();
  void Update(float elapsedSecs);

  void EnableChoppy();
  void DisableChoppy();
  int  IsChoppyEnable();

  void EnableNormalFFT();
  void DisableNormalFFT();
  int  IsNormalFFTEnable();

  float ChoppyCoef( float choppyCoef );
  float ChoppyCoef();

  float WindDir(float angle);
  float WindDir();

  int WindDependence( int windDependence );
  int WindDependence();

  float Amplitude( float amplitudeFactor );
  float Amplitude();

  float SimulationVelocity(float velocity);
  float SimulationVelocity();

  float WaterSize(float waterSize);
  float WaterSize();

  int WaterGrid(int gridPower);
  int WaterGrid();

  float GetMaxAmplitude();    // should be GetMaxBoundBoxSizeY?
  float GetMaxBoundBoxSizeX();
  float GetMaxBoundBoxSizeZ();

  // returns a pointer to a memory of size ( 2 power WaterGrid() plus 1 ) X ( 2 power WaterGrid() plus 1 )
  float* GetVertexPointer();
  float* GetNormalPointer();

  // returns a pointer to a memory of size ( 2 power WaterGrid() ) X ( 2 power WaterGrid() )
  unsigned char* NormalBumpMap();

  // elapsed time - used as a variable in the IFFT
  double time;

private:
  // private user acessible variables
  int m_gridPower;        // 2 power m_gridPower is the watermap size in array units
  int m_gridSize;         // watermap size in array units
  int m_gridSizePlusOne;  // watermap size in array units plus One
  int m_gridSizeMinusOne; // watermap size in array units minus One
  int m_windDependence;   // dependence of waves related to the wind
  int m_choppy;           // use or not use choppy waves
  int m_normalFFT;
  float m_waterSize;      // watermap size in world units
  float m_windAngle;		// angle ranging 0 - 359
  float m_choppyCoef;     // 
  float m_amplitudeFactor;// scale in amplitude
  float m_simVelocity;    // simulation velocity

  float m_boundBoxSizeX;
  float m_boundBoxSizeY;
  float m_boundBoxSizeZ;

  unsigned char* m_bumpNormalMap;

  // really private variables
  rfftwnd_plan fplan;     // rfftw plan

  fftw_complex* h0;		// Initial fourier array
  fftw_complex* ht;       // Temporary fourier array
  fftw_real* h;           // Temporary Height Array
  float* w;               // Wave Frequencies Array
  fftw_real* dx;			// Temporary Displacement in X Dimension
  fftw_real* dz;			// Temporary Displacement in Y Dimension

  float* m_vertex;        // Vertex array pointer
  float* m_normal;        // Normal array pointer

  float m_windx;          
  float m_windy;

  // private Methods
  void CalculateNormals();
  void CalculateNormalsFFT();
  void initH0();
  void initW();
  void initXZ();
  void allocMemory();
  void freeMemory();
};

#endif
