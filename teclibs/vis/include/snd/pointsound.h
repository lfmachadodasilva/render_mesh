#ifndef SNDPOINTSOUND_H
#define SNDPOINTSOUND_H

#include "defines.h"
#include "sound.h"

class SND_API SndPointSound : public SndSound
{
	friend class SndManager;
private:
	float pointsvolume;
	float rolloff;

	float position[3];
	float velocity[3];
	float direction[3];

	float maxdistance;
	float mindistance;

protected:
	// Atualiza o Volume dos Points
	void SetPointsVolume(float volume);

	// Atualiza o Volume do Som
	virtual void UpdateVolume();

	//Atualiza o Source
	virtual void UpdateSource();

public:
	// Contrutor padr�o
	SndPointSound();

	// Destrutor padr�o
	~SndPointSound();

	// Configura a nova posicao
	void SetPosition(float * position);
	void SetPosition(float xposition, float yposition, float zposition);
	
	// Configura a nova velocidade
	void SetVelocity(float * velocity);
	void SetVelocity(float xvelocity, float yvelocity, float zvelocity);

	// Configura a nova direcao
	void SetDirection(float * direction);
	void SetDirection(float xdirection, float ydirection, float zdirection);

	// Configura o Volume do som(0%-100%)
	void SetVolume(float volume);

	// Configura a distance m�xima de propaga��o sonora
	void SetMaxDistance(float maxdistance);
  float GetMaxDistance() { return maxdistance; }

	// Configura a distance minima de propaga��o sonora
	void SetMinDistance(float mindistance);
  float GetMinDistance() { return mindistance; }

	// Configura o RollOff
	void SetRollOff(float rolloff);
};

#endif

