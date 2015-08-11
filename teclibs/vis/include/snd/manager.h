#ifndef SNDMANAGER_H
#define SNDMANAGER_H

#include "defines.h"
//#include "backsound.h"
//#include "pointsound.h"
//#include "listener.h"

class SndPointSound;
class SndBackSound;

class SND_API SndManager
{
public:
  static bool Init ();
  static bool Shutdown ();

	// Configura o volume de todos os sons
	static void SetDoppler(float velocity, float factor);
		
	// Configura o volume de todos os sons
	static void SetGlobalVolume(float volume);

	// Configura o volume de todos os PointSounds
	static void SetPointsVolume(float volume);

	// Configura o volume de todos os BackSounds
	static void SetBacksVolume(float volume);

	// Insere um som na lista de back sounds
	static void InsertSound(SndBackSound* sound);
	// Insere um som na lista de point sounds
	static void InsertSound(SndPointSound* sound);

	// Remove um som na lista de back sounds
	static void RemoveSound(SndBackSound* sound);
	// Remove um som na lista de point sounds
	static void RemoveSound(SndPointSound* sound);

	// Retorna o BufferID se som já foi carregado
	static int FindSoundBuffer(char* sound);
	
	// Configura a Posição do Listener
	static void SetListenerPos(float* position);
	static void SetListenerPos(float xposition, float yposition, float zposition);

	// Configura a Velocidade do Listener
	static void SetListenerVel(float* velocity);
	static void SetListenerVel(float xvelocity, float yvelocity, float zvelocity);

	// Configura a Orientação do Listener
	static void SetListenerOri(float* orientation);
	static void SetListenerOri(float xorientation, float yorientation, float zorientation, float xup, float yup, float zup);
	
	// Atualiza os sons
	static void UpdateVtime(float vtime);
};
#endif

